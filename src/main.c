#include "gba.h"
#include "bios.h"
#include "gfx/room.h"
#include "gfx/room_door.h"
#include "gfx/enemy.h"
#include "gfx/enemy_2.h"
#include "gfx/lumos.h"
#include "gfx/lumos_vert.h"
#include "gfx/lumos_1_45.h"
#include "gfx/patrono_1.h"
#include "gfx/hud.h"

#include "gfx/vela_apagada_1.h"
#include "gfx/vela_acesa_1.h"
#include "gfx/vela_apagada_2.h"
#include "gfx/vela_acesa_2.h"

#include "gfx/larry_frente_1.h"
#include "gfx/larry_frente_2.h"
#include "gfx/larry_lado_1.h"
#include "gfx/larry_lado_2.h"
#include "gfx/larry_tras_1.h"
#include "gfx/larry_tras_2.h"

#include "gfx/ronaldo_frente_1.h"
#include "gfx/ronaldo_frente_2.h"
#include "gfx/ronaldo_lado_1.h"
#include "gfx/ronaldo_lado_2.h"
#include "gfx/ronaldo_tras_1.h"
#include "gfx/ronaldo_tras_2.h"

#include "gfx/lorraine_frente_1.h"
#include "gfx/lorraine_frente_2.h"
#include "gfx/lorraine_lado_1.h"
#include "gfx/lorraine_lado_2.h"
#include "gfx/lorraine_tras_1.h"
#include "gfx/lorraine_tras_2.h"

#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define INTTOFP(a) (a<<8)
#define FPTOINT(a) (a>>8)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a)<0 ? (-a) : (a))

#define PLAYER_SPEED (0b1011 << 5)
#define MONSTER_SPEED (0b111 << 4)
#define BULLET_SPEED INTTOFP(3)

#define DIAGONAL_BULLET_SPEED (u16)((FPTOINT(BULLET_SPEED)*1.41/2.0)*256)

/* OAMATTRIBS: (cada 4 -> uma sprite)
 *  0    -> player
 *  4+   -> enemy
 *  240+ -> candles
 *  320+ -> player bullet
 */

u32 frame;

enum {
    LARRY,
    RONALDO,
    LORRAINE,
} character = LARRY;

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

    s16 mana;
    s16 health;
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
    u8 x;
    u8 y;
    bool on;
} Light;

typedef struct {
    RoomType type;
    SpawnLoc monsterSpawns[10];
    u8 monsterSpawnsLen;
    Light lightSources[4];
    u8 lightSourcesLen;
    // TODO: itens
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
    bool patrono;
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
            if(playerBullets[i].patrono) {
                if(playerBullets[i].x + INTTOFP(2) < monsters[j].x + INTTOFP(2 + 12) &&
                        playerBullets[i].x + INTTOFP(2 + 30) > INTTOFP(2) + monsters[j].x &&
                        playerBullets[i].y + INTTOFP(2) < monsters[j].y + INTTOFP(2 + 12) &&
                        playerBullets[i].y + INTTOFP(2 + 30) > INTTOFP(2) + monsters[j].y)
                {
                    monsters[j].health--;
                }
            } else {
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

        BG_MAP_VRAM_BASE24[34] = 2 | BIT13;
        BG_MAP_VRAM_BASE24[35] = 3 | BIT13;
        BG_MAP_VRAM_BASE24[36] = 3 | BIT13;
        BG_MAP_VRAM_BASE24[37] = 3 | BIT13;
        BG_MAP_VRAM_BASE24[38] = 2 | BIT10 | BIT13;
        if (step == 1) {
            BG_MAP_VRAM_BASE24[34] = 12 | BIT13;
        }
        if (step > 1) {
            BG_MAP_VRAM_BASE24[34] = 8 | BIT13;
        }
        if (step == 3) {
            BG_MAP_VRAM_BASE24[35] = 15 | BIT13;
        }
        if (step > 3) {
            BG_MAP_VRAM_BASE24[35] = 9 | BIT13;
        }
        if (step == 5) {
            BG_MAP_VRAM_BASE24[36] = 11 | BIT13;
        }
        if (step > 5) {
            BG_MAP_VRAM_BASE24[36] = 13 | BIT13;
        }
        if (step == 7) {
            BG_MAP_VRAM_BASE24[37] = 6 | BIT13;
        }
        if (step > 7) {
            BG_MAP_VRAM_BASE24[37] = 16 | BIT13;
        }
        if (step == 9) {
            BG_MAP_VRAM_BASE24[38] = 7 | BIT13;
        }
        if (step > 9) {
            BG_MAP_VRAM_BASE24[38] = 1 | BIT13;
        }
    }
    {
        s32 step = player.health/10;

        BG_MAP_VRAM_BASE24[2] = 4 | BIT13;
        BG_MAP_VRAM_BASE24[3] = 4 | BIT13;
        BG_MAP_VRAM_BASE24[4] = 4 | BIT13;
        BG_MAP_VRAM_BASE24[5] = 4 | BIT13;
        BG_MAP_VRAM_BASE24[6] = 4 | BIT13;
        if (step == 1) {
            BG_MAP_VRAM_BASE24[2] = 10 | BIT13;
        }
        if (step > 1) {
            BG_MAP_VRAM_BASE24[2] = 14 | BIT13;
        }
        if (step == 3) {
            BG_MAP_VRAM_BASE24[3] = 10 | BIT13;
        }
        if (step > 3) {
            BG_MAP_VRAM_BASE24[3] = 14 | BIT13;
        }
        if (step == 5) {
            BG_MAP_VRAM_BASE24[4] = 10 | BIT13;
        }
        if (step > 5) {
            BG_MAP_VRAM_BASE24[4] = 14 | BIT13;
        }
        if (step == 7) {
            BG_MAP_VRAM_BASE24[5] = 10 | BIT13;
        }
        if (step > 7) {
            BG_MAP_VRAM_BASE24[5] = 14 | BIT13;
        }
        if (step == 9) {
            BG_MAP_VRAM_BASE24[6] = 10 | BIT13;
        }
        if (step > 9) {
            BG_MAP_VRAM_BASE24[6] = 14 | BIT13;
        }
    }
}

void updateLights() {
#define THRESHOLD0 0
#define THRESHOLD1 (8 * 8)
#define THRESHOLD2 (16 * 16)
#define THRESHOLD3 (36 * 32)
    Room cur = rooms[currentRoomY][currentRoomX];
    for (u16 j = 0; j < 640; j++) {
        BG_MAP_VRAM_BASE10[j] &= ~(BIT12|BIT13|BIT14|BIT15);
    }
    for (int i = 0; i < cur.lightSourcesLen; i++) {
        OAM_ATTRIBS[240 + i*4] = cur.lightSources[i].y | BIT15;
        OAM_ATTRIBS[241 + i*4] = cur.lightSources[i].x | BIT15;
        if (!cur.lightSources[i].on) {
            OAM_ATTRIBS[242 + i*4] = 13 | BIT12 | BIT13;
            continue;
        }
        else {
            OAM_ATTRIBS[242 + i*4] = 21 | BIT14;
        }

        s16 lx = cur.lightSources[i].x + 8;
        s16 ly = cur.lightSources[i].y + 4;

        for (u16 j = 0; j < 640; j++) {
            s16 x = ((j & 0b11111) << 3) + 4;
            if (x >= 240) continue;
            s16 y = ((j >> 5) << 3) + 4;
            s16 dx = x - lx;
            s16 dy = y - ly;
            u32 sqDist = dx * dx + dy * dy;
            //u32 sqDist = ABS(dx) + ABS(dy);

            u16 brightness = BG_MAP_VRAM_BASE10[j] & (BIT12|BIT13|BIT14|BIT15);
            brightness >>= 12;

            if (sqDist > THRESHOLD3) {
            } else if (sqDist > THRESHOLD2 && brightness == 0) {
                BG_MAP_VRAM_BASE10[j] &= ~(BIT12|BIT13|BIT14|BIT15);
                BG_MAP_VRAM_BASE10[j] |= (BIT14);
            } else if (sqDist > THRESHOLD1 &&
                    (brightness == 0 || brightness == 4)) {
                BG_MAP_VRAM_BASE10[j] &= ~(BIT12|BIT13|BIT14|BIT15);
                BG_MAP_VRAM_BASE10[j] |= (BIT12|BIT13);
            } else {
                BG_MAP_VRAM_BASE10[j] &= ~(BIT12|BIT13|BIT14|BIT15);
                BG_MAP_VRAM_BASE10[j] |= (BIT12|BIT14);
            }
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

    updateLights();
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

    for (u8 i = 0; i < 4; i++) {
        OAM_ATTRIBS[240 + i*4] = 0;
        OAM_ATTRIBS[241 + i*4] = 0;
        OAM_ATTRIBS[242 + i*4] = 0;
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
                DMA3Copy(BG_PALETTE_POINTER + 32/2, roomPal, palLen);
                for (int i = 1; i < palLen * 2; i++) {
                    vu16* ptr = (BG_PALETTE_POINTER + 32/2 + i);
                    u8 red = ((*ptr) & 0b0111110000000000) >> 10;
                    u8 green = ((*ptr) & 0b1111100000) >> 5;
                    u8 blue = (*ptr) & 0b11111;
                    u16 reduction = 17;
                    if (red < reduction) red = 0;
                    else red -= reduction;
                    if (green < reduction) green = 0;
                    else green -= reduction;
                    if (blue < reduction) blue = 0;
                    else blue -= reduction;
                    *ptr = (red << 10) | (green << 5) | blue;
                }

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
                DMA3Copy(BG_PALETTE_POINTER + 32/2, room_doorPal, palLen);
                for (int i = 1; i < palLen * 2; i++) {
                    vu16* ptr = (BG_PALETTE_POINTER + 32/2 + i);
                    u8 red = ((*ptr) & 0b0111110000000000) >> 10;
                    u8 green = ((*ptr) & 0b1111100000) >> 5;
                    u8 blue = (*ptr) & 0b11111;
                    u16 reduction = 17;
                    if (red < reduction) red = 0;
                    else red -= reduction;
                    if (green < reduction) green = 0;
                    else green -= reduction;
                    if (blue < reduction) blue = 0;
                    else blue -= reduction;
                    *ptr = (red << 10) | (green << 5) | blue;
                }

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
        DMA3Copy(BG_PALETTE_POINTER, BG_PALETTE_POINTER + 32/2, palLen);

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
        Room r = { DEFAULT_ROOM, {{80, 50}, {80, 120}}, 2, {{70, 70, 1}, {20, 80, 1}, {160, 60, 1}, {80, 90, 1}}, 4 };
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

        frame = 0;

        memset((void*)OAM_ATTRIBS, 0, 128 * 4);
    }


    REG_DISPCNT = BIT06 | BIT08 | BIT09 | BIT10 | BIT12; //Mode 0 + BG0-2 + OBJ + 1D OBJ Mapping

    player.x = INTTOFP(10);
    player.y = INTTOFP(10);
    player.mana = 50;
    player.health = 100;

    { //Player
        switch (character) {
            case LARRY:
                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_frente_1Tiles, larry_frente_1TilesLen/4);
                DMA3Copy(OBJ_PALETTE_POINTER, larry_frente_1Pal, larry_frente_1PalLen/4);
                break;
            case LORRAINE:
                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_frente_1Tiles, lorraine_frente_1TilesLen/4);
                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_frente_1Pal, lorraine_frente_1PalLen/4);
                break;
            case RONALDO:
                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_frente_1Tiles, ronaldo_frente_1TilesLen/4);
                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_frente_1Pal, ronaldo_frente_1PalLen/4);
                break;
        }

        OAM_ATTRIBS[1] = BIT14;
        OAM_ATTRIBS[2] = BIT00 | BIT10 | BIT11;
    }
    { //Room
        DMA3Copy(BG_TILE_VRAM_BASE0, roomTiles, roomTilesLen/4);
        DMA3Copy(BG_MAP_VRAM_BASE10, roomMap, roomMapLen/4);
        DMA3Copy(BG_PALETTE_POINTER + 96/2, roomPal, roomPalLen/4);
        DMA3Copy(BG_PALETTE_POINTER + 128/2, roomPal, roomPalLen/4);
        DMA3Copy(BG_PALETTE_POINTER + 160/2, roomPal, roomPalLen/4);
        for (int j = 96; j <= 160; j+=32) {
            for (int i = 1; i < roomPalLen/2; i++) {
                vu16* ptr = (BG_PALETTE_POINTER + j/2 + i);
                u8 red = ((*ptr) & 0b0111110000000000) >> 10;
                u8 green = ((*ptr) & 0b1111100000) >> 5;
                u8 blue = (*ptr) & 0b11111;
                u16 reduction;
                if (j == 96) reduction = 4;
                if (j == 128) reduction = 9;
                if (j == 160) reduction = 17;
                if (red < reduction) red = 0;
                else red -= reduction;
                if (green < reduction) green = 0;
                else green -= reduction;
                if (blue < reduction) blue = 0;
                else blue -= reduction;
                *ptr = (red << 10) | (green << 5) | blue;
            }
        }
        DMA3Copy(BG_PALETTE_POINTER, BG_PALETTE_POINTER + 160/2, roomPalLen/4);
        DMA3Copy(BG_PALETTE_POINTER + 160/2, roomPal, roomPalLen/4);

        REG_BG0CNT = BIT00 | BIT01 | BIT09 | BIT11 | BIT14 | BIT15;
    }
    { // Bullet H
        DMA3Copy(OBJ_TILE_VRAM + 32*9, lumosTiles, lumosTilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 64, lumosPal, lumosPalLen/4);
    }
    { // Bullet V
        DMA3Copy(OBJ_TILE_VRAM + 32*45, lumos_vertTiles, lumos_vertTilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 64, lumos_vertPal, lumos_vertPalLen/4);
    }
    { // Bullet D
        DMA3Copy(OBJ_TILE_VRAM + 32*49, lumos_1_45Tiles, lumos_1_45TilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 64, lumos_1_45Pal, lumos_1_45PalLen/4);
    }
    { //Candle
        DMA3Copy(OBJ_TILE_VRAM + 32*13, vela_apagada_1Tiles, vela_apagada_1TilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 96, vela_apagada_1Pal, vela_apagada_1PalLen/4);
    }
    { //Candle
        DMA3Copy(OBJ_TILE_VRAM + 32*21, vela_acesa_1Tiles, vela_acesa_1TilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 128, vela_acesa_1Pal, vela_acesa_1PalLen/4);
    }
    { // Patrono
        DMA3Copy(OBJ_TILE_VRAM + 32*29, patrono_1Tiles, patrono_1TilesLen/4);
        DMA3Copy(OBJ_PALETTE_POINTER + 160, patrono_1Pal, patrono_1PalLen/4);
    }
    { // HUD
        DMA3Copy(BG_TILE_VRAM_BASE2, hudTiles, hudTilesLen/4);
        DMA3Copy(BG_PALETTE_POINTER + 64/2, hudPal, hudPalLen/4);

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
            if (~REG_KEYPAD & BUTTON_SELECT) {
                if (character == LARRY) {
                    character = LORRAINE;
                }
                else if (character == LORRAINE) {
                    character = RONALDO;
                }
                else if (character == RONALDO) {
                    character = LARRY;
                }
            }
#define LIGHT_PICKUP_RANGE 20
            if (~REG_KEYPAD & (BUTTON_LEFT|BUTTON_RIGHT)) {
                Room *cur = &rooms[currentRoomY][currentRoomX];
                if (cur->lightSourcesLen) {
                    s16 nearest = 999;
                    u8 nearest_index = 99;
                    for (int i = 0; i < cur->lightSourcesLen; i++) {
                        if (!cur->lightSources[i].on) continue;
                        s16 dx = cur->lightSources[i].x - FPTOINT(player.x);
                        s16 dy = cur->lightSources[i].y - FPTOINT(player.y);
                        s16 manhattan = ABS(dx) + ABS(dy);

                        if (manhattan < nearest) {
                            nearest = manhattan;
                            nearest_index = i;
                        }
                    }
                    if (nearest < LIGHT_PICKUP_RANGE && nearest > 0) {
                        //cur->lightSources[nearest_index] = cur->lightSources[cur->lightSourcesLen-1];
                        //cur->lightSourcesLen -= 1;
                        cur->lightSources[nearest_index].on = false;
                        player.mana = MIN(player.mana + 30, 100);
                        updateLights();
                    }
                }
            }
            if (~REG_KEYPAD & (BUTTON_A|BUTTON_B)) {
                if (playerBulletsLen < 10 && !player.bullet_timer && ((player.mana >= 5 && (~REG_KEYPAD & BUTTON_A)) || (player.mana > 50 && (~REG_KEYPAD & BUTTON_B)))) {
                    player.bullet_timer = 20;
                    if (~REG_KEYPAD & BUTTON_B) player.mana -= 50;
                    else player.mana -= 5;
                    
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
                    playerBullets[playerBulletsLen].patrono = ~REG_KEYPAD & BUTTON_B;

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
        else if (player.mana < 50) {
            player.mana_timer = 20;
            player.mana++;
        }

        // VBLANK BARRIER
        while(!(REG_DISPSTAT & BIT00)) {} //Wait VBlank migue
        // ACTIVATE

        if (!(frame & 0b1111)) {
            if (frame & 0b10000) {
                { //Candle
                    DMA3Copy(OBJ_TILE_VRAM + 32*13, vela_apagada_2Tiles, vela_apagada_2TilesLen/4);
                    DMA3Copy(OBJ_PALETTE_POINTER + 96, vela_apagada_2Pal, vela_apagada_2PalLen/4);
                }
                { //Candle
                    DMA3Copy(OBJ_TILE_VRAM + 32*21, vela_acesa_2Tiles, vela_acesa_2TilesLen/4);
                    DMA3Copy(OBJ_PALETTE_POINTER + 128, vela_acesa_2Pal, vela_acesa_2PalLen/4);
                }
            }
            else {
                { //Candle
                    DMA3Copy(OBJ_TILE_VRAM + 32*13, vela_apagada_1Tiles, vela_apagada_1TilesLen/4);
                    DMA3Copy(OBJ_PALETTE_POINTER + 96, vela_apagada_1Pal, vela_apagada_1PalLen/4);
                }
                { //Candle
                    DMA3Copy(OBJ_TILE_VRAM + 32*21, vela_acesa_1Tiles, vela_acesa_1TilesLen/4);
                    DMA3Copy(OBJ_PALETTE_POINTER + 128, vela_acesa_1Pal, vela_acesa_1PalLen/4);
                }
            }
        }
        if (!((frame + 10) & 0b1111)) {
            if ((frame + 10) & 0b10000) {
                {
                    DMA3Copy(OBJ_TILE_VRAM + 32*5, enemyTiles, enemyTilesLen/4);
                    DMA3Copy(OBJ_PALETTE_POINTER + 32, enemyPal, enemyPalLen/4);
                }
            }
            else {
                {
                    DMA3Copy(OBJ_TILE_VRAM + 32*5, enemy_2Tiles, enemy_2TilesLen/4);
                    DMA3Copy(OBJ_PALETTE_POINTER + 32, enemy_2Pal, enemy_2PalLen/4);
                }
            }
        }

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
                if (!(FPTOINT(player.y) & 0b111)) {
                    if (FPTOINT(player.y) & 0b1000) {
                        switch (character) {
                            case RONALDO:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_tras_1Tiles, ronaldo_tras_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_tras_1Pal, ronaldo_tras_1PalLen/4);
                                break;
                            case LORRAINE:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_tras_1Tiles, lorraine_tras_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_tras_1Pal, lorraine_tras_1PalLen/4);
                                break;
                            case LARRY:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_tras_1Tiles, larry_tras_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, larry_tras_1Pal, larry_tras_1PalLen/4);
                                break;
                        }
                    }
                    else {
                        switch (character) {
                            case RONALDO:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_tras_2Tiles, ronaldo_tras_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_tras_2Pal, ronaldo_tras_2PalLen/4);
                                break;
                            case LORRAINE:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_tras_2Tiles, lorraine_tras_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_tras_2Pal, lorraine_tras_2PalLen/4);
                                break;
                            case LARRY:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_tras_2Tiles, larry_tras_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, larry_tras_2Pal, larry_tras_2PalLen/4);
                                break;
                        }
                    }
                }
                break;
            case DIR_LEFT:
                OAM_ATTRIBS[1] |= BIT12;
                if (!(FPTOINT(player.x) & 0b111)) {
                    if (FPTOINT(player.x) & 0b1000) {
                        switch (character) {
                            case RONALDO:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_lado_1Tiles, ronaldo_lado_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_lado_1Pal, ronaldo_lado_1PalLen/4);
                                break;
                            case LORRAINE:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_lado_1Tiles, lorraine_lado_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_lado_1Pal, lorraine_lado_1PalLen/4);
                                break;
                            case LARRY:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_lado_1Tiles, larry_lado_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, larry_lado_1Pal, larry_lado_1PalLen/4);
                                break;
                        }
                    }
                    else {
                        switch (character) {
                            case RONALDO:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_lado_2Tiles, ronaldo_lado_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_lado_2Pal, ronaldo_lado_2PalLen/4);
                                break;
                            case LORRAINE:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_lado_2Tiles, lorraine_lado_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_lado_2Pal, lorraine_lado_2PalLen/4);
                                break;
                            case LARRY:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_lado_2Tiles, larry_lado_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, larry_lado_2Pal, larry_lado_2PalLen/4);
                                break;
                        }
                    }
                }
                break;
            case DIR_DOWN:
                if (!(FPTOINT(player.y) & 0b111)) {
                    if (FPTOINT(player.y) & 0b1000) {
                        switch (character) {
                            case RONALDO:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_frente_1Tiles, ronaldo_frente_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_frente_1Pal, ronaldo_frente_1PalLen/4);
                                break;
                            case LORRAINE:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_frente_1Tiles, lorraine_frente_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_frente_1Pal, lorraine_frente_1PalLen/4);
                                break;
                            case LARRY:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_frente_1Tiles, larry_frente_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, larry_frente_1Pal, larry_frente_1PalLen/4);
                                break;
                        }
                    }
                    else {
                        switch (character) {
                            case RONALDO:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_frente_2Tiles, ronaldo_frente_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_frente_2Pal, ronaldo_frente_2PalLen/4);
                                break;
                            case LORRAINE:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_frente_2Tiles, lorraine_frente_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_frente_2Pal, lorraine_frente_2PalLen/4);
                                break;
                            case LARRY:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_frente_2Tiles, larry_frente_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, larry_frente_2Pal, larry_frente_2PalLen/4);
                                break;
                        }
                    }
                }
                break;
            case DIR_RIGHT:
                OAM_ATTRIBS[1] &= ~BIT12;
                if (!(FPTOINT(player.x) & 0b111)) {
                    if (FPTOINT(player.x) & 0b1000) {
                        switch (character) {
                            case RONALDO:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_lado_1Tiles, ronaldo_lado_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_lado_1Pal, ronaldo_lado_1PalLen/4);
                                break;
                            case LORRAINE:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_lado_1Tiles, lorraine_lado_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_lado_1Pal, lorraine_lado_1PalLen/4);
                                break;
                            case LARRY:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_lado_1Tiles, larry_lado_1TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, larry_lado_1Pal, larry_lado_1PalLen/4);
                                break;
                        }
                    }
                    else {
                        switch (character) {
                            case RONALDO:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, ronaldo_lado_2Tiles, ronaldo_lado_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, ronaldo_lado_2Pal, ronaldo_lado_2PalLen/4);
                                break;
                            case LORRAINE:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, lorraine_lado_2Tiles, lorraine_lado_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, lorraine_lado_2Pal, lorraine_lado_2PalLen/4);
                                break;
                            case LARRY:
                                DMA3Copy(OBJ_TILE_VRAM + 32*1, larry_lado_2Tiles, larry_lado_2TilesLen/4);
                                DMA3Copy(OBJ_PALETTE_POINTER, larry_lado_2Pal, larry_lado_2PalLen/4);
                                break;
                        }
                    }
                }
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
            if (playerBullets[i].patrono) {
                OAM_ATTRIBS[320 + i*4] = FPTOINT(playerBullets[i].y);
                OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT15;
                OAM_ATTRIBS[322 + i*4] = 29 | BIT10 | BIT12 | BIT14;
            } else {
                OAM_ATTRIBS[320 + i*4] = FPTOINT(playerBullets[i].y);
                if ((playerBullets[i].dir & BULLET_UP) && (playerBullets[i].dir & BULLET_LEFT)) {
                    OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14 | BIT12 | BIT13;
                    OAM_ATTRIBS[322 + i*4] = 49 | BIT10 | BIT13;
                }
                else if ((playerBullets[i].dir & BULLET_UP) && (playerBullets[i].dir & BULLET_RIGHT)) {
                    OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14 | BIT13;
                    OAM_ATTRIBS[322 + i*4] = 49 | BIT10 | BIT13;
                }
                else if ((playerBullets[i].dir & BULLET_DOWN) && (playerBullets[i].dir & BULLET_LEFT)) {
                    OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14 | BIT12;
                    OAM_ATTRIBS[322 + i*4] = 49 | BIT10 | BIT13;
                }
                else if ((playerBullets[i].dir & BULLET_DOWN) && (playerBullets[i].dir & BULLET_RIGHT)) {
                    OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14;
                    OAM_ATTRIBS[322 + i*4] = 49 | BIT10 | BIT13;
                }
                else if (playerBullets[i].dir & BULLET_DOWN) {
                    OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14;
                    OAM_ATTRIBS[322 + i*4] = 45 | BIT10 | BIT13;
                }
                else if (playerBullets[i].dir & BULLET_UP) {
                    OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14 | BIT13;
                    OAM_ATTRIBS[322 + i*4] = 45 | BIT10 | BIT13;
                }
                else if (playerBullets[i].dir & BULLET_LEFT) {
                    OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14 | BIT12;
                    OAM_ATTRIBS[322 + i*4] = BIT00 | BIT03 | BIT10 | BIT13;
                }
                else if (playerBullets[i].dir & BULLET_RIGHT) {
                    OAM_ATTRIBS[321 + i*4] = FPTOINT(playerBullets[i].x) | BIT14;
                    OAM_ATTRIBS[322 + i*4] = BIT00 | BIT03 | BIT10 | BIT13;
                }
            }
        }

        while(REG_DISPSTAT & BIT00); //Wait VBlank end migue
        frame++;
    }

    return 0;
}

