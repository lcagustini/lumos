#include "gba.h"
#include "gfx/ball.h"
#include "gfx/room.h"
#include "gfx/room_door.h"
#include "gfx/enemy.h"
#include "gfx/bullet.h"

#include <stdbool.h>

#define INTTOFP(a) (a<<8)
#define FPTOINT(a) (a>>8)

#define ABS(a) ((a)<0 ? (-a) : (a))

#define PLAYER_SPEED (0b1011 << 5)
#define MONSTER_SPEED INTTOFP(1)

struct {
    u16 x;
    u16 y;
} player = {0};

struct {
    u16 x;
    u16 y;
    u8 health;
} monsters[50] = {0};
u8 monstersLen = 0;

typedef enum {
    SCROLL_UP,
    SCROLL_LEFT,
    SCROLL_DOWN,
    SCROLL_RIGHT,
} ScrollDir;

void DMA3Copy(volatile const void *dest, volatile const void *src, u16 size) {
    REG_DMA3SAD = src;
    REG_DMA3DAD = dest;
    REG_DMA3CNT_L = size;
    REG_DMA3CNT_H = BIT10 | BIT15;
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

    while(1) {
        if (~REG_KEYPAD & KEYPAD_UP) {
            player.y -= PLAYER_SPEED;
        }
        if (~REG_KEYPAD & KEYPAD_LEFT) {
            player.x -= PLAYER_SPEED;
        }
        if (~REG_KEYPAD & KEYPAD_DOWN) {
            player.y += PLAYER_SPEED;
        }
        if (~REG_KEYPAD & KEYPAD_RIGHT) {
            player.x += PLAYER_SPEED;
        }

        updateMonsters();

        while(!(REG_DISPSTAT & BIT00)); //Wait VBlank migue

        if (FPTOINT(player.x) == 0) {
            scroll(SCROLL_LEFT);
        }
        else if (FPTOINT(player.x) == 240-16) {
            scroll(SCROLL_RIGHT);
        }
        else if (FPTOINT(player.y) == 0) {
            scroll(SCROLL_UP);
        }
        else if (FPTOINT(player.y) == 160-16) {
            scroll(SCROLL_DOWN);
        }

        //TODO: Truncate player x and y
        OAM_ATTRIBS[0] = (OAM_ATTRIBS[0] & 0b1111111100000000) | FPTOINT(player.y);
        OAM_ATTRIBS[1] = (OAM_ATTRIBS[1] & 0b1111111000000000) | FPTOINT(player.x);

        for (int i = 0; i < monstersLen; i++) {
            OAM_ATTRIBS[4 + i*4] = (OAM_ATTRIBS[4 + i*4] & 0b1111111100000000) | FPTOINT(monsters[i].y);
            OAM_ATTRIBS[5 + i*4] = (OAM_ATTRIBS[5 + i*4] & 0b1111111000000000) | FPTOINT(monsters[i].x);
        }

        while(REG_DISPSTAT & BIT00); //Wait VBlank end migue
    }

    return 0;
}
