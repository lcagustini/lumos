
@{{BLOCK(bullet)

@=======================================================================
@
@	bullet, 8x8@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 1 tiles not compressed
@	Total size: 32 + 32 = 64
@
@	Time-stamp: 2019-04-28, 02:09:47
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global bulletTiles		@ 32 unsigned chars
	.hidden bulletTiles
bulletTiles:
	.word 0x00000000,0x00011100,0x00111110,0x01111110,0x01111110,0x00111110,0x00111000,0x00000000

	.section .rodata
	.align	2
	.global bulletPal		@ 32 unsigned chars
	.hidden bulletPal
bulletPal:
	.hword 0x7C1F,0x03BF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(bullet)
