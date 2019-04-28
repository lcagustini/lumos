all: gfx
	mkdir -p bin
	/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc -mthumb-interwork -specs=gba.specs src/main.c src/gfx/*.s -o bin/main.o -O0 -Wno-int-conversion
	/opt/devkitpro/devkitARM/bin/arm-none-eabi-objcopy -v -O binary bin/main.o main.gba
	/opt/devkitpro/tools/bin/gbafix main.gba -tLumos -cTIHE -mTI -r1.0

gfx: force
	mkdir -p src/gfx
	grit gfx/ball.png -o src/gfx/ball
	grit gfx/enemy.png -o src/gfx/enemy
	grit gfx/room.png -o src/gfx/room
	grit gfx/bullet.png -o src/gfx/bullet
	grit gfx/room_door.png -o src/gfx/room_door
	grit gfx/larry_frente.png -o src/gfx/larry_frente
	grit gfx/larry_lado.png -o src/gfx/larry_lado
	grit gfx/larry_tras.png -o src/gfx/larry_tras
	grit gfx/lumos.png -o src/gfx/lumos
	grit gfx/lumos_1.png -o src/gfx/lumos_1

clean:
	rm -rf bin main.gba main.sav

force:
