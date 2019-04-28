all: gfx
	mkdir -p bin
	/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc -mthumb-interwork -specs=gba.specs src/main.c src/gfx/room.s src/gfx/ball.s src/gfx/enemy.s src/gfx/bullet.s src/gfx/room_door.s -o bin/main.o -O0 -Wno-int-conversion
	/opt/devkitpro/devkitARM/bin/arm-none-eabi-objcopy -v -O binary bin/main.o main.gba
	/opt/devkitpro/tools/bin/gbafix main.gba -tLumos -cTIHE -mTI -r1.0

gfx: force
	mkdir -p src/gfx
	grit gfx/ball.png -o src/gfx/ball
	grit gfx/enemy.png -o src/gfx/enemy
	grit gfx/room.png -o src/gfx/room
	grit gfx/bullet.png -o src/gfx/bullet
	grit gfx/room_door.png -o src/gfx/room_door

clean:
	rm -rf bin main.gba main.sav

force:
