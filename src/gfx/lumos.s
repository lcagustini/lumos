
@{{BLOCK(lumos)

@=======================================================================
@
@	lumos, 16x16@4, 
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
	.global lumosTiles		@ 128 unsigned chars
	.hidden lumosTiles
lumosTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x10020030,0x21100200
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00333111,0x03343323
	.word 0x42211003,0x33222110,0x42211003,0x21100200,0x10020030,0x00000000,0x00000000,0x00000000
	.word 0x33444333,0x34454434,0x33444333,0x03343323,0x00333111,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global lumosPal		@ 32 unsigned chars
	.hidden lumosPal
lumosPal:
	.hword 0x7C1F,0x6B30,0x7FD3,0x7FF6,0x7FF9,0x7FFC,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(lumos)
