
@{{BLOCK(lumos_1)

@=======================================================================
@
@	lumos_1, 16x16@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2019-04-28, 02:15:21
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global lumos_1Tiles		@ 128 unsigned chars
	.hidden lumos_1Tiles
lumos_1Tiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00700300,0x20003000,0x33200030
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00133322,0x01734336
	.word 0x34322000,0x43332213,0x34322000,0x33200030,0x20003000,0x00700300,0x00000000,0x00000000
	.word 0x13344433,0x13445443,0x17344433,0x01334332,0x00133322,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global lumos_1Pal		@ 32 unsigned chars
	.hidden lumos_1Pal
lumos_1Pal:
	.hword 0x7C1F,0x6B30,0x7FD3,0x7FF6,0x7FF9,0x7FFC,0x7FD5,0x7FD7
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(lumos_1)
