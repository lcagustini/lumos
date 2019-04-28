
@{{BLOCK(room_door)

@=======================================================================
@
@	room_door, 512x512@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 15 tiles (t|f reduced) not compressed
@	+ regular map (in SBBs), not compressed, 64x64 
@	Total size: 32 + 480 + 8192 = 8704
@
@	Time-stamp: 2019-04-27, 22:03:10
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global room_doorTiles		@ 480 unsigned chars
	.hidden room_doorTiles
room_doorTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x99922999,0x95999959,0x99955999,0x39533593,0x29533592,0x99955999,0x95999959,0x99933999
	.word 0x22999923,0x66955963,0x99955999,0x55555555,0x55555555,0x99955999,0x66955966,0x33999933
	.word 0x22999923,0x46955963,0x74955999,0x57455555,0x58745555,0x58745999,0x58574966,0x58574933
	.word 0x24444443,0x47777774,0x75585587,0x85585585,0x85585585,0x85585585,0x85585585,0x85585585
	.word 0x22999923,0x66955964,0x99955947,0x55555475,0x55554775,0x99954755,0x66947755,0x33947855
	.word 0x99922999,0x95999959,0x99955999,0x39555593,0x29555592,0x99955999,0x95999959,0x99933999
	.word 0x22955923,0x66955963,0x99955999,0x95555559,0x95555559,0x99955999,0x66955966,0x33955933

	.word 0x22222223,0x66666663,0x66666663,0x33333333,0x22232222,0x66636666,0x66636666,0x33333333
	.word 0x58574223,0x58574663,0x58574663,0x58574333,0x58574222,0x58574666,0x58574666,0x58574333
	.word 0x85585585,0x15585585,0x11585585,0x11585585,0x15585585,0x85585585,0x85585585,0x85585585
	.word 0x22247855,0x66647854,0x66647844,0x33347811,0x22247851,0x66647855,0x66647855,0x33347855
	.word 0x58574223,0x66666663,0x66666663,0x33333333,0x22232222,0x66636666,0x66636666,0x33333333
	.word 0x85585585,0x66666663,0x66666663,0x33333333,0x22232222,0x66636666,0x66636666,0x33333333
	.word 0x22247855,0x66666663,0x66666663,0x33333333,0x22232222,0x66636666,0x66636666,0x33333333

	.section .rodata
	.align	2
	.global room_doorMap		@ 8192 unsigned chars
	.hidden room_doorMap
room_doorMap:
	.hword 0x1001,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002
	.hword 0x1002,0x1002,0x1002,0x1002,0x1002,0x1003,0x1004,0x1005
	.hword 0x1002,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002
	.hword 0x1002,0x1002,0x1002,0x1002,0x1002,0x1006,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1009,0x100A,0x100B
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x100C,0x100D,0x100E
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000

	.hword 0x1007,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008,0x1008
	.hword 0x1008,0x1008,0x1008,0x1008,0x1008,0x1007,0x1000,0x1000
	.hword 0x1001,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002
	.hword 0x1002,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002
	.hword 0x1002,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002,0x1002
	.hword 0x1002,0x1002,0x1002,0x1002,0x1002,0x1001,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000
	.hword 0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000

	.section .rodata
	.align	2
	.global room_doorPal		@ 32 unsigned chars
	.hidden room_doorPal
room_doorPal:
	.hword 0x7C1F,0x0C63,0x3A79,0x1D4D,0x318C,0x14EC,0x2590,0x0446
	.hword 0x192F,0x0467,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(room_door)
