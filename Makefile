all: gfx
	mkdir -p bin
	/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc -mthumb-interwork -specs=gba.specs src/main.c src/bios.s src/gfx/*.s -o bin/main.o -O2 -Wno-int-conversion -g
	/opt/devkitpro/devkitARM/bin/arm-none-eabi-objcopy -v -O binary bin/main.o main.gba
	/opt/devkitpro/tools/bin/gbafix main.gba -tLumos -cTIHE -mTI -r1.0

gfx: force
	mkdir -p src/gfx
	grit gfx/ball.png -o src/gfx/ball
	grit gfx/enemy.png -o src/gfx/enemy
	grit gfx/enemy_2.png -o src/gfx/enemy_2
	grit gfx/room.png -o src/gfx/room
	grit gfx/bullet.png -o src/gfx/bullet
	grit gfx/room_door.png -o src/gfx/room_door
	grit gfx/larry_frente_1.png -o src/gfx/larry_frente_1
	grit gfx/larry_frente_2.png -o src/gfx/larry_frente_2
	grit gfx/larry_lado_1.png -o src/gfx/larry_lado_1
	grit gfx/larry_lado_2.png -o src/gfx/larry_lado_2
	grit gfx/larry_tras_1.png -o src/gfx/larry_tras_1
	grit gfx/larry_tras_2.png -o src/gfx/larry_tras_2
	grit gfx/ronaldo_frente_1.png -o src/gfx/ronaldo_frente_1
	grit gfx/ronaldo_frente_2.png -o src/gfx/ronaldo_frente_2
	grit gfx/ronaldo_lado_1.png -o src/gfx/ronaldo_lado_1
	grit gfx/ronaldo_lado_2.png -o src/gfx/ronaldo_lado_2
	grit gfx/ronaldo_tras_1.png -o src/gfx/ronaldo_tras_1
	grit gfx/ronaldo_tras_2.png -o src/gfx/ronaldo_tras_2
	grit gfx/lorraine_frente_1.png -o src/gfx/lorraine_frente_1
	grit gfx/lorraine_frente_2.png -o src/gfx/lorraine_frente_2
	grit gfx/lorraine_lado_1.png -o src/gfx/lorraine_lado_1
	grit gfx/lorraine_lado_2.png -o src/gfx/lorraine_lado_2
	grit gfx/lorraine_tras_1.png -o src/gfx/lorraine_tras_1
	grit gfx/lorraine_tras_2.png -o src/gfx/lorraine_tras_2
	grit gfx/lumos.png -o src/gfx/lumos
	grit gfx/lumos_1.png -o src/gfx/lumos_1
	grit gfx/lumos_1_45.png -o src/gfx/lumos_1_45
	grit gfx/lumos_2_45.png -o src/gfx/lumos_2_45
	grit gfx/lumos_vert.png -o src/gfx/lumos_vert
	grit gfx/lumos_1_vert.png -o src/gfx/lumos_1_vert
	grit gfx/patrono_1.png -o src/gfx/patrono_1
	grit gfx/patrono_1_vert.png -o src/gfx/patrono_1_vert
	grit gfx/patrono_2_vert.png -o src/gfx/patrono_2_vert
	grit gfx/cachorro_1_hor.png -o src/gfx/cachorro_1_hor
	grit gfx/cachorro_1_vert.png -o src/gfx/cachorro_1_vert
	grit gfx/lontra_1_hor.png -o src/gfx/lontra_1_hor
	grit gfx/lontra_1_vert.png -o src/gfx/lontra_1_vert
	grit gfx/hud.png -o src/gfx/hud
	grit gfx/vela_acesa_1.png -o src/gfx/vela_acesa_1
	grit gfx/vela_acesa_2.png -o src/gfx/vela_acesa_2
	grit gfx/vela_apagada_1.png -o src/gfx/vela_apagada_1
	grit gfx/vela_apagada_2.png -o src/gfx/vela_apagada_2

clean:
	rm -rf bin main.gba main.sav

force:
