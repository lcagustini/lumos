
@{{BLOCK(larry_lado)

@=======================================================================
@
@	larry_lado, 16x16@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2019-04-28, 02:35:22
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global larry_ladoTiles		@ 128 unsigned chars
	.hidden larry_ladoTiles
larry_ladoTiles:
	.word 0xAAA00000,0x666A0000,0x6666A000,0xA666A000,0xAAA6A000,0xA8A6A000,0x88A6A000,0x8A6A0000
	.word 0x00000AAA,0x0000A666,0x000A666A,0x000A66A8,0x000AAA88,0x00028888,0x00028988,0x00002988
	.word 0x2AA00000,0x11100000,0x44100000,0x82100000,0x22100000,0x241B0000,0x114B0000,0x00CB0000
	.word 0x00000288,0x00000022,0x00000351,0x00000744,0x00000344,0x00000144,0x00000141,0x000BCCB0

	.section .rodata
	.align	2
	.global larry_ladoPal		@ 32 unsigned chars
	.hidden larry_ladoPal
larry_ladoPal:
	.hword 0x7C1F,0x0842,0x3ABA,0x0016,0x14A5,0x7FFF,0x10C8,0x1639
	.hword 0x46FC,0x2168,0x0866,0x1089,0x14AB,0x0000,0x0000,0x0000

@}}BLOCK(larry_lado)
