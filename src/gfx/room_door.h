
//{{BLOCK(room_door)

//======================================================================
//
//	room_door, 512x512@4, 
//	Transparent color : FF,00,FF
//	+ palette 16 entries, not compressed
//	+ 15 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 480 + 8192 = 8704
//
//	Time-stamp: 2019-04-27, 23:32:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROOM_DOOR_H
#define GRIT_ROOM_DOOR_H

#define room_doorTilesLen 480
extern const unsigned int room_doorTiles[120];

#define room_doorMapLen 8192
extern const unsigned short room_doorMap[4096];

#define room_doorPalLen 32
extern const unsigned short room_doorPal[16];

#endif // GRIT_ROOM_DOOR_H

//}}BLOCK(room_door)
