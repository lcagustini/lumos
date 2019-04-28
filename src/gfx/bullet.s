
@{{BLOCK(bullet)

@=======================================================================
@
@	bullet, 16x16@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2019-04-27, 23:32:25
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global bulletTiles		@ 128 unsigned chars
	.hidden bulletTiles
bulletTiles:
	.word 0x00000000,0x00000000,0x10000000,0x11100000,0x11110000,0x11111000,0x11111000,0x11111000
	.word 0x00000000,0x00000000,0x00000001,0x00000011,0x00001111,0x00011111,0x00011111,0x00111111
	.word 0x11111100,0x11111100,0x11111100,0x11111000,0x11100000,0x10000000,0x00000000,0x00000000
	.word 0x00111111,0x00111111,0x00111111,0x00011111,0x00011111,0x00001111,0x00000010,0x00000000

	.section .rodata
	.align	2
	.global bulletPal		@ 32 unsigned chars
	.hidden bulletPal
bulletPal:
	.hword 0x7C1F,0x03BF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(bullet)
