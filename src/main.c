#include "gba.h"
#include "gfx/ball.h"
#include "gfx/room.h"
#include "gfx/enemy.h"

typedef struct {
    u8 x;
    u8 y;
} Player;

int main() {
    REG_DISPCNT = BIT06 | BIT08 | BIT09 | BIT12; //Mode 0 + BG0-1 + OBJ + 1D OBJ Mapping

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

        REG_BG0CNT = BIT07 | BIT09 | BIT11;
    }

    Player player = {0};
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

        //TODO: Truncate player x and y
        OAM_ATTRIBS[0] = (OAM_ATTRIBS[0] & 0b1111111100000000) | player.y;
        OAM_ATTRIBS[1] = (OAM_ATTRIBS[1] & 0b1111111000000000) | player.x;

        while(REG_DISPSTAT & BIT00); //Wait VBlank end migue
    }

    return 0;
}
