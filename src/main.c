#include "gba.h"
#include "gfx/ball.h"
#include "gfx/room.h"
#include "gfx/room_door.h"
#include "gfx/enemy.h"

#include <stdbool.h>

struct {
    u8 x;
    u8 y;
} player = {0};

typedef enum {
    SCROLL_UP,
    SCROLL_LEFT,
    SCROLL_DOWN,
    SCROLL_RIGHT,
} ScrollDir;

void scroll(ScrollDir dir) {
    { //Room_door
        REG_DMA3SAD = room_doorTiles;
        REG_DMA3DAD = BG_TILE_VRAM_BASE1;
        REG_DMA3CNT_L = room_doorTilesLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_DMA3SAD = room_doorMap;
        REG_DMA3DAD = BG_MAP_VRAM_BASE16;
        REG_DMA3CNT_L = room_doorMapLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_DMA3SAD = room_doorPal;
        REG_DMA3DAD = BG_PALETTE_POINTER + 32;
        REG_DMA3CNT_L = room_doorPalLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

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
                player.y += 2;
                scroll -= 2;
                break;
            case SCROLL_LEFT:
                player.x += 2;
                scroll -= 2;
                break;
            case SCROLL_DOWN:
                player.y -= 2;
                scroll += 2;
                break;
            case SCROLL_RIGHT:
                player.x -= 2;
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
        OAM_ATTRIBS[0] = (OAM_ATTRIBS[0] & 0b1111111100000000) | player.y;
        OAM_ATTRIBS[1] = (OAM_ATTRIBS[1] & 0b1111111000000000) | player.x;

        while(REG_DISPSTAT & BIT00); //Wait VBlank end migue
    }

    switch (dir) {
        case SCROLL_UP:
            player.y -= 32;
            break;
        case SCROLL_LEFT:
            player.x -= 32;
            break;
        case SCROLL_DOWN:
            player.y += 32;
            break;
        case SCROLL_RIGHT:
            player.x += 32;
            break;
    }

    { //Room_door
        REG_DMA3SAD = BG_TILE_VRAM_BASE1;
        REG_DMA3DAD = BG_TILE_VRAM_BASE0;
        REG_DMA3CNT_L = room_doorTilesLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_DMA3SAD = BG_MAP_VRAM_BASE16;
        REG_DMA3DAD = BG_MAP_VRAM_BASE10;
        REG_DMA3CNT_L = room_doorMapLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_DMA3SAD = BG_PALETTE_POINTER + 32;
        REG_DMA3DAD = BG_PALETTE_POINTER;
        REG_DMA3CNT_L = room_doorPalLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_BG0HOFS = 0;
        REG_BG0VOFS = 0;

        REG_BG1HOFS = 0;
        REG_BG1VOFS = 0;
    }
}

int main() {
    REG_DISPCNT = BIT06 | BIT08 | BIT09 | BIT10 | BIT12; //Mode 0 + BG0-2 + OBJ + 1D OBJ Mapping

    player.x = 10;
    player.y = 10;

    { //Ball
        REG_DMA3SAD = ballTiles;
        REG_DMA3DAD = OBJ_TILE_VRAM + 32*1; //tilebase
        REG_DMA3CNT_L = ballTilesLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_DMA3SAD = ballPal;
        REG_DMA3DAD = OBJ_PALETTE_POINTER; //palette number
        REG_DMA3CNT_L = ballPalLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        OAM_ATTRIBS[1] = BIT14;
        OAM_ATTRIBS[2] = BIT00;
    }
    { //Enemy
        REG_DMA3SAD = enemyTiles;
        REG_DMA3DAD = OBJ_TILE_VRAM + 32*5; //tilebase
        REG_DMA3CNT_L = enemyTilesLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_DMA3SAD = enemyPal;
        REG_DMA3DAD = OBJ_PALETTE_POINTER + 32; //palette number
        REG_DMA3CNT_L = enemyPalLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        OAM_ATTRIBS[5] = BIT14;
        OAM_ATTRIBS[6] = BIT00 | BIT02 | BIT12;
    }
    { //Room
        REG_DMA3SAD = roomTiles;
        REG_DMA3DAD = BG_TILE_VRAM_BASE0;
        REG_DMA3CNT_L = roomTilesLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_DMA3SAD = roomMap;
        REG_DMA3DAD = BG_MAP_VRAM_BASE10;
        REG_DMA3CNT_L = roomMapLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_DMA3SAD = roomPal;
        REG_DMA3DAD = BG_PALETTE_POINTER;
        REG_DMA3CNT_L = roomPalLen/4; //Words to copy
        REG_DMA3CNT_H = BIT10 | BIT15;

        REG_BG0CNT = BIT09 | BIT11 | BIT14 | BIT15;
    }

    while(1) {
        if (~REG_KEYPAD & KEYPAD_UP) {
            player.y--;
        }
        if (~REG_KEYPAD & KEYPAD_LEFT) {
            player.x--;
        }
        if (~REG_KEYPAD & KEYPAD_DOWN) {
            player.y++;
        }
        if (~REG_KEYPAD & KEYPAD_RIGHT) {
            player.x++;
        }

        while(!(REG_DISPSTAT & BIT00)); //Wait VBlank migue

        if (player.x == 0) {
            scroll(SCROLL_LEFT);
        }
        else if (player.x == 240-16) {
            scroll(SCROLL_RIGHT);
        }
        else if (player.y == 0) {
            scroll(SCROLL_UP);
        }
        else if (player.y == 160-16) {
            scroll(SCROLL_DOWN);
        }

        //TODO: Truncate player x and y
        OAM_ATTRIBS[0] = (OAM_ATTRIBS[0] & 0b1111111100000000) | player.y;
        OAM_ATTRIBS[1] = (OAM_ATTRIBS[1] & 0b1111111000000000) | player.x;

        while(REG_DISPSTAT & BIT00); //Wait VBlank end migue
    }

    return 0;
}
