
@{{BLOCK(larry_frente)

@=======================================================================
@
@	larry_frente, 16x16@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2019-04-28, 02:43:40
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global larry_frenteTiles		@ 128 unsigned chars
	.hidden larry_frenteTiles
larry_frenteTiles:
	.word 0xAAA00000,0x444A0000,0x44A4A000,0x4A9AA000,0xA994A000,0x99942000,0x98992000,0x98920000
	.word 0x00000AAA,0x0000A444,0x000A4444,0x000A4444,0x000A44AA,0x0002AA99,0x00029989,0x00002989
	.word 0x99211000,0x221DD100,0x35DDD100,0x6DD19200,0x3DD12200,0xDDD12000,0xDDD10000,0xCBBBC000
	.word 0x00011299,0x001DD122,0x001DDD56,0x00291DD3,0x00221DD6,0x00021DD7,0x00001DD1,0x000CBBBC

	.section .rodata
	.align	2
	.global larry_frentePal		@ 32 unsigned chars
	.hidden larry_frentePal
larry_frentePal:
	.hword 0x7C1F,0x0842,0x3ABA,0x0016,0x10C8,0x7FFF,0x1639,0x1084
	.hword 0x2168,0x46FC,0x0866,0x14AB,0x1089,0x14A5,0x0000,0x0000

@}}BLOCK(larry_frente)
