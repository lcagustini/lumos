all: gfx
	mkdir -p bin
	/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc -O2 -mthumb-interwork -specs=gba.specs src/main.c -o bin/main.o
	/opt/devkitpro/devkitARM/bin/arm-none-eabi-objcopy -v -O binary bin/main.o main.gba
	/opt/devkitpro/tools/bin/gbafix main.gba -tLumos -cTIHE -mTI -r1.0

gfx: force
	mkdir -p src/gfx
	grit gfx/ball.png -o src/gfx/ball

clean:
	rm -rf bin main.gba main.sav

force:
