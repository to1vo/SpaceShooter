INCLUDE_PATH = -Iinclude
EXTERNAL_INCLUDE_PATH = -Iexternal/include
EXTERNAL_LIB_PATH = -Lexternal/lib
BUILD_PATH = build/
OBJ_FILES = $(BUILD_PATH)main.o $(BUILD_PATH)game.o $(BUILD_PATH)gameobject.o $(BUILD_PATH)player.o $(BUILD_PATH)projectile.o $(BUILD_PATH)enemy.o $(BUILD_PATH)enemy_spawner.o $(BUILD_PATH)collision.o  

main: $(OBJ_FILES)
	g++ $(OBJ_FILES) $(EXTERNAL_LIB_PATH) -lSDL3 -lSDL3_image -lSDL3_ttf -o bin/spaceshooter

$(BUILD_PATH)%.o: src/%.cpp
	g++ $(INCLUDE_PATH) $(EXTERNAL_INCLUDE_PATH) -c $(<) -o $(BUILD_PATH)$(@F)

# main.o: src/main.cpp
# 	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/main.cpp -o $(BUILD_PATH)$(@F)

clean:
	del build\*.o