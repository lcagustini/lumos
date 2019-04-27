
//{{BLOCK(room)

//======================================================================
//
//	room, 256x256@8, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	+ 5 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 320 + 2048 = 2880
//
//	Time-stamp: 2019-04-27, 19:48:56
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROOM_H
#define GRIT_ROOM_H

#define roomTilesLen 320
extern const unsigned int roomTiles[80];

#define roomMapLen 2048
extern const unsigned short roomMap[1024];

#define roomPalLen 512
extern const unsigned short roomPal[256];

#endif // GRIT_ROOM_H

//}}BLOCK(room)
