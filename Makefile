build:
	g++ -std=c++14 \
	./src/*.cpp \
	-Wfatal-errors \
	-o game \
	-I"./lib/glm" \
	-L"./lib/glm" \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-llua \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

debug:
	g++ -std=c++14 \
	./src/*.cpp \
	-Wall \
	-Wextra \
	-Wpedantic \
	-o game \
	-I"./lib/glm" \
	-L"./lib/glm" \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-llua \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clean:
	rm ./game;

run:
	./game;
