
@{{BLOCK(ball)

@=======================================================================
@
@	ball, 16x16@4, 
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
	.global ballTiles		@ 128 unsigned chars
	.hidden ballTiles
ballTiles:
	.word 0x11110000,0x11111000,0x11111100,0x11111110,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00001111,0x00011111,0x00111111,0x01111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111110,0x11111100,0x11111000,0x11110000
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x01111111,0x00111111,0x00011111,0x00001111

	.section .rodata
	.align	2
	.global ballPal		@ 32 unsigned chars
	.hidden ballPal
ballPal:
	.hword 0x7C1F,0x001F,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(ball)
