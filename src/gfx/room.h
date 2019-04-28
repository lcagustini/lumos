
//{{BLOCK(room)

//======================================================================
//
//	room, 512x512@4, 
//	Transparent color : FF,00,FF
//	+ palette 16 entries, not compressed
//	+ 5 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 160 + 8192 = 8384
//
//	Time-stamp: 2019-04-28, 02:09:47
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROOM_H
#define GRIT_ROOM_H

#define roomTilesLen 160
extern const unsigned int roomTiles[40];

#define roomMapLen 8192
extern const unsigned short roomMap[4096];

#define roomPalLen 32
extern const unsigned short roomPal[16];

#endif // GRIT_ROOM_H

//}}BLOCK(room)
