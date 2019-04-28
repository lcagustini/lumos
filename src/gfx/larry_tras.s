
@{{BLOCK(larry_tras)

@=======================================================================
@
@	larry_tras, 16x16@4, 
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
	.global larry_trasTiles		@ 128 unsigned chars
	.hidden larry_trasTiles
larry_trasTiles:
	.word 0x55500000,0x35350000,0x33535000,0x33535000,0x35335000,0x33335000,0x33335000,0x33350000
	.word 0x00000555,0x00005333,0x00053333,0x00053333,0x00053333,0x00053333,0x00055333,0x00005333
	.word 0x33522000,0x55299200,0x22999200,0x99927100,0x99921100,0x99921000,0x99920000,0x68886000
	.word 0x00022533,0x00299255,0x00299922,0x00172999,0x00112999,0x00012994,0x00002992,0x00068886

	.section .rodata
	.align	2
	.global larry_trasPal		@ 32 unsigned chars
	.hidden larry_trasPal
larry_trasPal:
	.hword 0x7C1F,0x3ABA,0x0842,0x10C8,0x1084,0x0866,0x1089,0x46FC
	.hword 0x14AB,0x14A5,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(larry_tras)
