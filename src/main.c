#include <stdbool.h>

#include "gba.h"
#include "gfx/ball.h"
#include "gfx/room.h"
#include "gfx/room_door.h"
#include "gfx/enemy.h"
#include "gfx/lumos.h"

#include "gfx/larry_frente.h"
#include "gfx/larry_lado.h"
#include "gfx/larry_tras.h"

#define INTTOFP(a) (a<<8)
#define FPTOINT(a) (a>>8)

#define ABS(a) ((a)<0 ? (-a) : (a))

#define PLAYER_SPEED (0b1011 << 5)
#define MONSTER_SPEED INTTOFP(1)
#define BULLET_SPEED INTTOFP(1)

/* OAMATTRIBS: (cada 4 -> uma sprite)
 *  0    -> player
 *  4+   -> enemy
 *  320+ -> player bullet
 */

typedef enum {
    DIR_UP,
    DIR_LEFT,
    DIR_DOWN,
    DIR_RIGHT,
} PlayerDir;

typedef enum {
    SCROLL_UP,
    SCROLL_LEFT,
    SCROLL_DOWN,
    SCROLL_RIGHT,
} ScrollDir;

typedef enum {
    BULLET_INVALID = 0b0,
    BULLET_UP = 0b0001,
    BULLET_LEFT = 0b0010,
    BULLET_RIGHT = 0b0100,
    BULLET_DOWN = 0b1000,
} BulletDir;

struct {
    u16 x;
    u16 y;
    PlayerDir dir;
} player = {0};

struct {
    u16 x;
    u16 y;
    u8 health;
} monsters[50] = {0};
u8 monstersLen = 0;

struct {
    u16 x;
    u16 y;
    BulletDir dir;
} playerBullets[10];
u8 playerBulletsLen = 0;

void DMA3Copy(volatile const void *dest, volatile const void *src, u16 size) {
    REG_DMA3SAD = src;
    REG_DMA3DAD = dest;
    REG_DMA3CNT_L = size;
    REG_DMA3CNT_H = BIT10 | BIT15;
}

void updateBullets() {
    for (int i = 0; i < playerBulletsLen; i++) {
        if (playerBullets[i].dir & BULLET_UP) {
            playerBullets[i].y -= BULLET_SPEED;
        }
        if (playerBullets[i].dir & BULLET_LEFT) {
            playerBullets[i].x -= BULLET_SPEED;
        }
        if (playerBullets[i].dir & BULLET_DOWN) {
            playerBullets[i].y += BULLET_SPEED;
        }
        if (playerBullets[i].dir & BULLET_RIGHT) {
            playerBullets[i].x += BULLET_SPEED;
        }

        if (FPTOINT(playerBullets[i].x) <= FPTOINT(BULLET_SPEED)
            || FPTOINT(playerBullets[i].x) >= (240-16-FPTOINT(BULLET_SPEED))
            || FPTOINT(playerBullets[i].y) <= FPTOINT(BULLET_SPEED)
            || FPTOINT(playerBullets[i].y) >= (160-16-FPTOINT(BULLET_SPEED))) {
            playerBullets[i--] = playerBullets[--playerBulletsLen];
            OAM_ATTRIBS[320 + playerBulletsLen*4] = 0;
            OAM_ATTRIBS[321 + playerBulletsLen*4] = 0;
            OAM_ATTRIBS[322 + playerBulletsLen*4] = 0;
        }
    }
}

void updateMonsters() {
    for (int i = 0; i < monstersLen; i++) {
        s32 dx = (s32)player.x - (s32)monsters[i].x;
        s32 dy = (s32)player.y - (s32)monsters[i].y;

        if (ABS(dx) > ABS(dy)) {
            if (dx < 0) {
                monsters[i].x -= MONSTER_SPEED;
            }
            else {
                monsters[i].x += MONSTER_SPEED;
            }
        }
        else {
            if (dy < 0) {
                monsters[i].y -= MONSTER_SPEED;
            }
            else {
                monsters[i].y += MONSTER_SPEED;
            }
        }
    }
}

void scroll(ScrollDir dir) {
    { //Room_door
        DMA3Copy(BG_TILE_VRAM_BASE1, room_doorTiles, room_doorTilesLen/4);
        DMA3Copy(BG_MAP_VRAM_BASE16, room_doorMap, room_doorMapLen/4);
        DMA3Copy(BG_PALETTE_POINTER + 32, room_doorPal, room_doorPalLen/4);

        REG_BG1CNT = BIT02 | BIT12 | BIT14 | BIT15;
    }

    u16 scroll;
    if (dir == SCROLL_UP || dir == SCROLL_LEFT) scroll = 510;
    else scroll = 0;
    while(1) {
        if (dir == SCROLL_UP && scroll <= 512-160) break;
        if (dir == SCROLL_LEFT && scroll <= 512-240) break;
        if (dir == SCROLL_DOWN && scroll >= 160) break;
        if (dir == SCROLL_RIGHT && scroll >= 240) break;

        switch (dir) {
            case SCROLL_UP:
                player.y += INTTOFP(2);
                scroll -= 2;
                break;
            case SCROLL_LEFT:
                player.x += INTTOFP(2);
                scroll -= 2;
                break;
            case SCROLL_DOWN:
                player.y -= INTTOFP(2);
                scroll += 2;
                break;
            case SCROLL_RIGHT:
                player.x -= INTTOFP(2);
                scroll += 2;
                break;
        }

        while(!(REG_DISPSTAT & BIT00)); //Wait VBlank migue
        switch (dir) {
            case SCROLL_UP:
                REG_BG0VOFS = scroll;
                REG_BG1VOFS = scroll + 160;
                break;
            case SCROLL_LEFT:
                REG_BG0HOFS = scroll;
                REG_BG1HOFS = scroll + 240;
                break;
            case SCROLL_DOWN:
                REG_BG0VOFS = scroll;
                REG_BG1VOFS = scroll - 160;
                break;
            case SCROLL_RIGHT:
                REG_BG0HOFS = scroll;
                REG_BG1HOFS = scroll - 240;
                break;
        }

        //TODO: Truncate player x and y
        OAM_ATTRIBS[0] = (OAM_ATTRIBS[0] & 0b1111111100000000) | FPTOINT(player.y);
        OAM_ATTRIBS[1] = (OAM_ATTRIBS[1] & 0b1111111000000000) | FPTOINT(player.x);

        while(REG_DISPSTAT & BIT00); //Wait VBlank end migue
    }

    switch (dir) {
        case SCROLL_UP:
            player.y -= INTTOFP(24);
            break;
        case SCROLL_LEFT:
            player.x -= INTTOFP(24);
            break;
        case SCROLL_DOWN:
            player.y += INTTOFP(24);
            break;
        case SCROLL_RIGHT:
            player.x += INTTOFP(24);
            break;
    }

    { //Room_door
        DMA3Copy(BG_TILE_VRAM_BASE0, BG_TILE_VRAM_BASE1, room_doorTilesLen/4);
        DMA3Copy(BG_MAP_VRAM_BASE10, BG_MAP_VRAM_BASE16, room_doorMapLen/4);
        DMA3Copy(BG_PALETTE_POINTER, BG_PALETTE_POINTER + 32, room_doorPalLen/4);

        REG_BG0HOFS = 0;
        REG_BG0VOFS = 0;

        REG_BG1HOFS = 0;
        REG_BG1VOFS = 0;
    }
}

int main() {
    REG_DISPCNT = BIT06 | BIT08 | BIT09 | BIT10 | BIT12; //Mode 0 + BG0-2 + OBJ + 1D OBJ Mapping

    player.x = INTTOFP(10);
    player.y = INTTOFP(10);

    monsters[0].x = INTTOFP(50);
    monsters[0].y = INTTOFP(50);
    monsters[0].health = 10;
    monstersLen = 1;

    { //Ball
        DMA3Copy(OBJ_TILE_VRAM + 32*1, ballTiles, ballTilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER, ballPal, ballPalLen/4);

        OAM_ATTRIBS[1] = BIT14;
        OAM_ATTRIBS[2] = BIT00;
    }
    { //Enemy
        DMA3Copy(OBJ_TILE_VRAM + 32*5, enemyTiles, enemyTilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 32, enemyPal, enemyPalLen/4);

        OAM_ATTRIBS[5] = BIT14;
        OAM_ATTRIBS[6] = BIT00 | BIT02 | BIT12;
    }
    { //Room
        DMA3Copy(BG_TILE_VRAM_BASE0, roomTiles, roomTilesLen/4);
        DMA3Copy(BG_MAP_VRAM_BASE10, roomMap, roomMapLen/4);
        DMA3Copy(BG_PALETTE_POINTER, roomPal, roomPalLen/4);

        REG_BG0CNT = BIT09 | BIT11 | BIT14 | BIT15;
    }
    { //Bullet
        DMA3Copy(OBJ_TILE_VRAM + 32*9, lumosTiles, lumosTilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 64, lumosPal, lumosPalLen/4);
    }

    while(1) {
        {
            BulletDir dir = BULLET_INVALID;
            if (~REG_KEYPAD & KEYPAD_UP) {
                player.y -= PLAYER_SPEED;
                player.dir = DIR_UP;
                dir |= BULLET_UP;
            }
            if (~REG_KEYPAD & KEYPAD_LEFT) {
                player.x -= PLAYER_SPEED;
                player.dir = DIR_LEFT;
                dir |= BULLET_LEFT;
            }
            if (~REG_KEYPAD & KEYPAD_DOWN) {
                player.y += PLAYER_SPEED;
                player.dir = DIR_DOWN;
                dir |= BULLET_DOWN;
            }
            if (~REG_KEYPAD & KEYPAD_RIGHT) {
                player.x += PLAYER_SPEED;
                player.dir = DIR_RIGHT;
                dir |= BULLET_RIGHT;
            }
            if (~REG_KEYPAD & BUTTON_A) {
                if (playerBulletsLen < 10) {
                    playerBullets[playerBulletsLen].x = player.x;
                    playerBullets[playerBulletsLen].y = player.y;
                    if (dir) {
                        playerBullets[playerBulletsLen].dir = dir;
                    }
                    else {
                        switch (player.dir) {
                            case DIR_UP:
                                playerBullets[playerBulletsLen].dir = BULLET_UP;
                                break;
                            case DIR_LEFT:
                                playerBullets[playerBulletsLen].dir = BULLET_LEFT;
                                break;
                            case DIR_DOWN:
                                playerBullets[playerBulletsLen].dir = BULLET_DOWN;
                                break;
                            case DIR_RIGHT:
                                playerBullets[playerBulletsLen].dir = BULLET_RIGHT;
                                break;
                        }
                    }

                    playerBulletsLen++;
                }
            }
        }

        updateMonsters();
        updateBullets();

        // VBLANK BARRIER
        while(!(REG_DISPSTAT & BIT00)); //Wait VBlank migue
        // ACTIVATE

        if (FPTOINT(player.x) <= FPTOINT(PLAYER_SPEED)) {
            scroll(SCROLL_LEFT);
        }
        else if (FPTOINT(player.x) >= (240-16-FPTOINT(PLAYER_SPEED))) {
            scroll(SCROLL_RIGHT);
        }
        else if (FPTOINT(player.y) <= FPTOINT(PLAYER_SPEED)) {
            scroll(SCROLL_UP);
        }
        else if (FPTOINT(player.y) >= (160-16-FPTOINT(PLAYER_SPEED))) {
            scroll(SCROLL_DOWN);
        }

        switch (player.dir) {
            case DIR_UP:
                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_trasTiles, larry_trasTilesLen/4);
                DMA3Copy(OBJ_PALETTE_POINTER, larry_trasPal, larry_trasPalLen/4);
                break;
            case DIR_LEFT:
                OAM_ATTRIBS[1] |= BIT12;
                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_ladoTiles, larry_ladoTilesLen/4);
                DMA3Copy(OBJ_PALETTE_POINTER, larry_ladoPal, larry_ladoPalLen/4);
                break;
            case DIR_DOWN:
                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_frenteTiles, larry_frenteTilesLen/4);
                DMA3Copy(OBJ_PALETTE_POINTER, larry_frentePal, larry_frentePalLen/4);
                break;
            case DIR_RIGHT:
                OAM_ATTRIBS[1] &= ~BIT12;
                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_ladoTiles, larry_ladoTilesLen/4);
                DMA3Copy(OBJ_PALETTE_POINTER, larry_ladoPal, larry_ladoPalLen/4);
                break;
        }

        //TODO: Truncate player x and y
        OAM_ATTRIBS[0] = (OAM_ATTRIBS[0] & 0b1111111100000000) | FPTOINT(player.y);
        OAM_ATTRIBS[1] = (OAM_ATTRIBS[1] & 0b1111111000000000) | FPTOINT(player.x);

        for (int i = 0; i < monstersLen; i++) {
            OAM_ATTRIBS[4 + i*4] = (OAM_ATTRIBS[4 + i*4] & 0b1111111100000000) | FPTOINT(monsters[i].y);
            OAM_ATTRIBS[5 + i*4] = (OAM_ATTRIBS[5 + i*4] & 0b1111111000000000) | FPTOINT(monsters[i].x);
        }

        for (int i = 0; i < playerBulletsLen; i++) {
            OAM_ATTRIBS[320 + i*4] = FPTOINT(playerBullets[i].y);
            OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14;
            OAM_ATTRIBS[322 + i*4] = BIT00 | BIT03 | BIT13;
        }

        while(REG_DISPSTAT & BIT00); //Wait VBlank end migue
    }

    return 0;
}
