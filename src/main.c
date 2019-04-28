#include "gba.h"
#include "bios.h"
#include "gfx/room.h"
#include "gfx/room_door.h"
#include "gfx/enemy.h"
#include "gfx/lumos.h"
#include "gfx/hud.h"

#include "gfx/larry_frente.h"
#include "gfx/larry_lado.h"
#include "gfx/larry_tras.h"

#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define INTTOFP(a) (a<<8)
#define FPTOINT(a) (a>>8)

#define ABS(a) ((a)<0 ? (-a) : (a))

#define PLAYER_SPEED (0b1011 << 5)
#define MONSTER_SPEED (0b111 << 4)
#define BULLET_SPEED INTTOFP(3)

#define DIAGONAL_BULLET_SPEED (u16)((FPTOINT(BULLET_SPEED)*1.41/2.0)*256)

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

    u16 bullet_timer;
    u16 mana_timer;

    s8 mana;
    s8 health;
    PlayerDir dir;
} player;

typedef struct {
    u16 x;
    u16 y;
    s8 health;
    // TODO: monster type
} Monster;
Monster monsters[50];
u8 monstersLen;

typedef enum {
    INVALID_ROOM = 0,

    DEFAULT_ROOM,
    DOOR_ROOM
} RoomType;

typedef struct {
    u8 x;
    u8 y;
    // TODO: monster type
} SpawnLoc;

typedef struct {
    RoomType type;
    SpawnLoc monsterSpawns[10];
    u8 monsterSpawnsLen;
    // TODO: itens
    // TODO: light sources
} Room;
Room rooms[10][10];

#define STARTING_ROOM_X 5
#define STARTING_ROOM_Y 5

u8 currentRoomX = STARTING_ROOM_X;
u8 currentRoomY = STARTING_ROOM_Y;

struct {
    u16 x;
    u16 y;
    BulletDir dir;
} playerBullets[10];
u8 playerBulletsLen;

void DMA3Copy(volatile const void *dest, volatile const void *src, u16 size) {
    REG_DMA3SAD = src;
    REG_DMA3DAD = dest;
    REG_DMA3CNT_L = size;
    REG_DMA3CNT_H = BIT10 | BIT15;
}

void updateBullets() {
    for (int i = 0; i < playerBulletsLen; i++) {
        if ((playerBullets[i].dir & BULLET_UP) && (playerBullets[i].dir & BULLET_LEFT) &&
            !(playerBullets[i].dir & BULLET_RIGHT) && !(playerBullets[i].dir & BULLET_DOWN)) {
            playerBullets[i].x -= DIAGONAL_BULLET_SPEED;
            playerBullets[i].y -= DIAGONAL_BULLET_SPEED;
        }
        if ((playerBullets[i].dir & BULLET_UP) && !(playerBullets[i].dir & BULLET_LEFT) &&
            (playerBullets[i].dir & BULLET_RIGHT) && !(playerBullets[i].dir & BULLET_DOWN)) {
            playerBullets[i].x += DIAGONAL_BULLET_SPEED;
            playerBullets[i].y -= DIAGONAL_BULLET_SPEED;
        }
        if (!(playerBullets[i].dir & BULLET_UP) && (playerBullets[i].dir & BULLET_LEFT) &&
            !(playerBullets[i].dir & BULLET_RIGHT) && (playerBullets[i].dir & BULLET_DOWN)) {
            playerBullets[i].x -= DIAGONAL_BULLET_SPEED;
            playerBullets[i].y += DIAGONAL_BULLET_SPEED;
        }
        if (!(playerBullets[i].dir & BULLET_UP) && !(playerBullets[i].dir & BULLET_LEFT) &&
            (playerBullets[i].dir & BULLET_RIGHT) && (playerBullets[i].dir & BULLET_DOWN)) {
            playerBullets[i].x += DIAGONAL_BULLET_SPEED;
            playerBullets[i].y += DIAGONAL_BULLET_SPEED;
        }
        if ((playerBullets[i].dir & BULLET_UP) && !(playerBullets[i].dir & BULLET_LEFT) &&
            !(playerBullets[i].dir & BULLET_RIGHT) && !(playerBullets[i].dir & BULLET_DOWN)) {
            playerBullets[i].y -= BULLET_SPEED;
        }
        if (!(playerBullets[i].dir & BULLET_UP) && (playerBullets[i].dir & BULLET_LEFT) &&
            !(playerBullets[i].dir & BULLET_RIGHT) && !(playerBullets[i].dir & BULLET_DOWN)) {
            playerBullets[i].x -= BULLET_SPEED;
        }
        if (!(playerBullets[i].dir & BULLET_UP) && !(playerBullets[i].dir & BULLET_LEFT) &&
            (playerBullets[i].dir & BULLET_RIGHT) && !(playerBullets[i].dir & BULLET_DOWN)) {
            playerBullets[i].x += BULLET_SPEED;
        }
        if (!(playerBullets[i].dir & BULLET_UP) && !(playerBullets[i].dir & BULLET_LEFT) &&
            !(playerBullets[i].dir & BULLET_RIGHT) && (playerBullets[i].dir & BULLET_DOWN)) {
            playerBullets[i].y += BULLET_SPEED;
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

        for (int j = 0; j < monstersLen; j++) {
            if(playerBullets[i].x + INTTOFP(2) < monsters[j].x + INTTOFP(2 + 12) &&
                    playerBullets[i].x + INTTOFP(2 + 12) > INTTOFP(2) + monsters[j].x &&
                    playerBullets[i].y + INTTOFP(2) < monsters[j].y + INTTOFP(2 + 12) &&
                    playerBullets[i].y + INTTOFP(2 + 12) > INTTOFP(2) + monsters[j].y)
            {
                monsters[j].health--;
            }
        }
    }
}

bool collidesWithOtherMonsters(u8 index) {
    Monster a = monsters[index];
    for (u8 i = 0; i < monstersLen; i++) {
        if (i == index) continue;
        Monster b = monsters[i];
        if(a.x + INTTOFP(2) < b.x + INTTOFP(12 + 2) &&
                a.x + INTTOFP(12 + 2) > b.x + INTTOFP(2) &&
                a.y + INTTOFP(2) < b.y + INTTOFP(12 + 2) &&
                a.y + INTTOFP(12 + 2) > b.y + INTTOFP(2))
        {
            return true;
        }
    }
    
    return false;
}

bool collidesWithPlayer(u8 index) {
    Monster m = monsters[index];
    if(m.x + INTTOFP(4) < player.x + INTTOFP(8 + 4) &&
            m.x + INTTOFP(8 + 4) > player.x + INTTOFP(4) &&
            m.y + INTTOFP(4) < player.y + INTTOFP(8 + 4) &&
            m.y + INTTOFP(8 + 4) > player.y + INTTOFP(4))
    {
        return true;
    }
    return false;
}

void updateMonsters() {
    for (int i = 0; i < monstersLen; i++) {
        if (monsters[i].health <= 0) {
            monsters[i] = monsters[--monstersLen];

            OAM_ATTRIBS[5 + monstersLen*4] = 0;
            OAM_ATTRIBS[6 + monstersLen*4] = 0;

            u8 cx = currentRoomX;
            u8 cy = currentRoomY;
            rooms[cy][cx].monsterSpawns[i] = rooms[cy][cx].monsterSpawns[--rooms[cy][cx].monsterSpawnsLen];
        }

        s32 dx = (s32)player.x - (s32)monsters[i].x;
        s32 dy = (s32)player.y - (s32)monsters[i].y;

        if (ABS(dx) > ABS(dy)) {
            if (dx < 0) {
                monsters[i].x -= MONSTER_SPEED;
                if (collidesWithOtherMonsters(i)) monsters[i].x += MONSTER_SPEED;
                if (collidesWithPlayer(i)) {
                    monsters[i].x += MONSTER_SPEED;
                    player.health--;
                }
            }
            else {
                monsters[i].x += MONSTER_SPEED;
                if (collidesWithOtherMonsters(i)) monsters[i].x -= MONSTER_SPEED;
                if (collidesWithPlayer(i)) {
                    monsters[i].x -= MONSTER_SPEED;
                    player.health--;
                }
            }
        }
        else {
            if (dy < 0) {
                monsters[i].y -= MONSTER_SPEED;
                if (collidesWithOtherMonsters(i)) monsters[i].y += MONSTER_SPEED;
                if (collidesWithPlayer(i)) {
                    monsters[i].y += MONSTER_SPEED;
                    player.health--;
                }
            }
            else {
                monsters[i].y += MONSTER_SPEED;
                if (collidesWithOtherMonsters(i)) monsters[i].y -= MONSTER_SPEED;
                if (collidesWithPlayer(i)) {
                    monsters[i].y -= MONSTER_SPEED;
                    player.health--;
                }
            }
        }

        // collision with player
    }
}

void drawGUI() {
    {
        s32 step = player.mana/10;

        BG_MAP_VRAM_BASE24[2] = 2 | BIT13;
        BG_MAP_VRAM_BASE24[3] = 3 | BIT13;
        BG_MAP_VRAM_BASE24[4] = 3 | BIT13;
        BG_MAP_VRAM_BASE24[5] = 3 | BIT13;
        BG_MAP_VRAM_BASE24[6] = 2 | BIT10 | BIT13;
        if (step == 1) {
            BG_MAP_VRAM_BASE24[2] = 12 | BIT13;
        }
        if (step > 1) {
            BG_MAP_VRAM_BASE24[2] = 8 | BIT13;
        }
        if (step == 3) {
            BG_MAP_VRAM_BASE24[3] = 15 | BIT13;
        }
        if (step > 3) {
            BG_MAP_VRAM_BASE24[3] = 9 | BIT13;
        }
        if (step == 5) {
            BG_MAP_VRAM_BASE24[4] = 11 | BIT13;
        }
        if (step > 5) {
            BG_MAP_VRAM_BASE24[4] = 13 | BIT13;
        }
        if (step == 7) {
            BG_MAP_VRAM_BASE24[5] = 6 | BIT13;
        }
        if (step > 7) {
            BG_MAP_VRAM_BASE24[5] = 16 | BIT13;
        }
        if (step == 9) {
            BG_MAP_VRAM_BASE24[6] = 7 | BIT13;
        }
        if (step > 9) {
            BG_MAP_VRAM_BASE24[6] = 1 | BIT13;
        }
    }
}

void changeRoom(Room r) {
    // change monsters
    monstersLen = r.monsterSpawnsLen;
    for (u8 i = 0; i < monstersLen; i++) {
        Monster m = {.x = INTTOFP(r.monsterSpawns[i].x), .y = INTTOFP(r.monsterSpawns[i].y), .health = 10}; // TODO: remove hardcoded health
        monsters[i] = m;

        // TODO: switch on monster type
        DMA3Copy(OBJ_TILE_VRAM + 32*5, enemyTiles, enemyTilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 32, enemyPal, enemyPalLen/4);

        OAM_ATTRIBS[5 + i*4] = BIT14;
        OAM_ATTRIBS[6 + i*4] = BIT00 | BIT02 | BIT11 | BIT12;
    }

    // TODO: change itens
    // TODO: change light sources
}

bool scroll(ScrollDir dir) {
    switch (dir) {
        case SCROLL_UP:
            if (rooms[currentRoomY-1][currentRoomX].type != INVALID_ROOM) currentRoomY--;
            else return false;
            break;
        case SCROLL_LEFT:
            if (rooms[currentRoomY][currentRoomX-1].type != INVALID_ROOM) currentRoomX--;
            else return false;
            break;
        case SCROLL_DOWN:
            if (rooms[currentRoomY+1][currentRoomX].type != INVALID_ROOM) currentRoomY++;
            else return false;
            break;
        case SCROLL_RIGHT:
            if (rooms[currentRoomY][currentRoomX+1].type != INVALID_ROOM) currentRoomX++;
            else return false;
            break;
        default:
            assert(false);
    }

    for (u8 i = 0; i < monstersLen; i++) {
        OAM_ATTRIBS[5 + i*4] = 0;
        OAM_ATTRIBS[6 + i*4] = 0;
    }
    monstersLen = 0;

    for (u8 i = 0; i < playerBulletsLen; i++) {
        OAM_ATTRIBS[321 + i*4] = 0;
        OAM_ATTRIBS[322 + i*4] = 0;
    }
    playerBulletsLen = 0;

    u16 tilesLen, mapLen, palLen;

    switch (rooms[currentRoomX][currentRoomY].type) {
        case INVALID_ROOM:
            assert(false);
        case DEFAULT_ROOM:
            {
                tilesLen = roomTilesLen/4;
                mapLen = roomMapLen/4;
                palLen = roomPalLen/4;

                DMA3Copy(BG_TILE_VRAM_BASE1, roomTiles, tilesLen);
                DMA3Copy(BG_MAP_VRAM_BASE17, roomMap, mapLen);
                DMA3Copy(BG_PALETTE_POINTER + 32, roomPal, palLen);

                REG_BG1CNT = BIT00 | BIT01 | BIT02 | BIT08 | BIT12 | BIT14 | BIT15;
            }
            break;
        case DOOR_ROOM:
            {
                tilesLen = room_doorTilesLen/4;
                mapLen = room_doorMapLen/4;
                palLen = room_doorPalLen/4;

                DMA3Copy(BG_TILE_VRAM_BASE1, room_doorTiles, tilesLen);
                DMA3Copy(BG_MAP_VRAM_BASE17, room_doorMap, mapLen);
                DMA3Copy(BG_PALETTE_POINTER + 32, room_doorPal, palLen);

                REG_BG1CNT = BIT00 | BIT01 | BIT02 | BIT08 | BIT12 | BIT14 | BIT15;
            }
            break;
        default:
            assert(false);
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

    {
        DMA3Copy(BG_TILE_VRAM_BASE0, BG_TILE_VRAM_BASE1, tilesLen);
        DMA3Copy(BG_MAP_VRAM_BASE10, BG_MAP_VRAM_BASE17, mapLen);
        DMA3Copy(BG_PALETTE_POINTER, BG_PALETTE_POINTER + 32, palLen);

        REG_BG0HOFS = 0;
        REG_BG0VOFS = 0;

        REG_BG1HOFS = 0;
        REG_BG1VOFS = 0;
    }

    changeRoom(rooms[currentRoomY][currentRoomX]);

    return true;
}

void generateRooms() {
    {
        Room r = { DEFAULT_ROOM, {{80, 50}, {80, 120}}, 2 };
        rooms[STARTING_ROOM_Y][STARTING_ROOM_X] = r;
    }

    {
        Room r = { DEFAULT_ROOM, {{40, 20}, {80, 120}}, 2 };
        rooms[STARTING_ROOM_Y+1][STARTING_ROOM_X] = r;
    }

    {
        Room r = { DEFAULT_ROOM, {{80, 10}, {180, 10}}, 2 };
        rooms[STARTING_ROOM_Y][STARTING_ROOM_X+1] = r;
    }

    {
        Room r = { DEFAULT_ROOM, {{100, 120}, {20, 20}, {70, 130}}, 3 };
        rooms[STARTING_ROOM_Y+1][STARTING_ROOM_X+1] = r;
    }
};

int main() {
reset_game:
    {
        memset(&player, 0, sizeof(player));
        memset(monsters, 0, sizeof(monsters));
        memset(&monstersLen, 0, sizeof(monstersLen));
        memset(playerBullets, 0, sizeof(playerBullets));
        memset(&playerBulletsLen, 0, sizeof(playerBulletsLen));
        memset(rooms, 0, sizeof(rooms));
        currentRoomX = STARTING_ROOM_X;
        currentRoomY = STARTING_ROOM_Y;

        memset((void*)OAM_ATTRIBS, 0, 128 * 4);
    }


    REG_DISPCNT = BIT06 | BIT08 | BIT09 | BIT10 | BIT12; //Mode 0 + BG0-2 + OBJ + 1D OBJ Mapping

    player.x = INTTOFP(10);
    player.y = INTTOFP(10);
    player.mana = 100;
    player.health = 100;

    { //Player
        OAM_ATTRIBS[1] = BIT14;
        OAM_ATTRIBS[2] = BIT00 | BIT10 | BIT11;
    }
    { //Room
        DMA3Copy(BG_TILE_VRAM_BASE0, roomTiles, roomTilesLen/4);
        DMA3Copy(BG_MAP_VRAM_BASE10, roomMap, roomMapLen/4);
        DMA3Copy(BG_PALETTE_POINTER, roomPal, roomPalLen/4);

        REG_BG0CNT = BIT00 | BIT01 | BIT09 | BIT11 | BIT14 | BIT15;
    }
    { //Bullet
        DMA3Copy(OBJ_TILE_VRAM + 32*9, lumosTiles, lumosTilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 64, lumosPal, lumosPalLen/4);
    }
    { //HUD
        DMA3Copy(BG_TILE_VRAM_BASE2, hudTiles, hudTilesLen/4);
        DMA3Copy(BG_PALETTE_POINTER + 64, hudPal, hudPalLen/4);

        REG_BG2CNT = BIT03 | BIT11 | BIT12;
    }

    generateRooms();

    changeRoom(rooms[STARTING_ROOM_X][STARTING_ROOM_Y]);

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
                if (playerBulletsLen < 10 && !player.bullet_timer && player.mana >= 5) {
                    player.bullet_timer = 20;
                    player.mana -= 5;

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

        // player death
        if (player.health <= 0) {
            goto reset_game;
        }

        if (player.bullet_timer) player.bullet_timer--;
        if (player.mana_timer) player.mana_timer--;
        else if (monstersLen && player.mana < 100) {
            player.mana_timer = 20;
            player.mana++;
        }

        // VBLANK BARRIER
        while(!(REG_DISPSTAT & BIT00)); //Wait VBlank migue
        // ACTIVATE

        drawGUI();

        if (FPTOINT(player.x) <= FPTOINT(PLAYER_SPEED)) {
            if (!scroll(SCROLL_LEFT)) player.x += PLAYER_SPEED;
        }
        if (FPTOINT(player.x) >= (240-16-FPTOINT(PLAYER_SPEED))) {
            if (!scroll(SCROLL_RIGHT)) player.x -= PLAYER_SPEED;
        }
        if (FPTOINT(player.y) <= FPTOINT(PLAYER_SPEED)) {
            if (!scroll(SCROLL_UP)) player.y += PLAYER_SPEED;
        }
        if (FPTOINT(player.y) >= (160-16-FPTOINT(PLAYER_SPEED))) {
            if (!scroll(SCROLL_DOWN)) player.y -= PLAYER_SPEED;
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
            OAM_ATTRIBS[322 + i*4] = BIT00 | BIT03 | BIT10 | BIT13;
        }

        while(REG_DISPSTAT & BIT00); //Wait VBlank end migue
    }

    return 0;
}
