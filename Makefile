INCLUDE_PATH = -Iinclude
EXTERNAL_INCLUDE_PATH = -Iexternal/include
EXTERNAL_LIB_PATH = -Lexternal/lib
BUILD_PATH = build/

main: main.o game.o gameobject.o player.o projectile.o enemy.o enemy_spawner.o collision.o
	g++ $(BUILD_PATH)main.o $(BUILD_PATH)game.o $(BUILD_PATH)gameobject.o $(BUILD_PATH)player.o $(BUILD_PATH)projectile.o $(BUILD_PATH)enemy.o $(BUILD_PATH)enemy_spawner.o $(BUILD_PATH)collision.o $(EXTERNAL_LIB_PATH) -lSDL3 -lSDL3_image -lSDL3_ttf -o bin/spaceshooter

main.o: src/main.cpp
	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/main.cpp -o $(BUILD_PATH)$(@F)

game.o: src/game.cpp
	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/game.cpp -o $(BUILD_PATH)$(@F)

gameobject.o: src/gameobject.cpp
	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/gameobject.cpp -o $(BUILD_PATH)$(@F)

player.o: src/player.cpp
	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/player.cpp -o $(BUILD_PATH)$(@F)

projectile.o: src/projectile.cpp
	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/projectile.cpp -o $(BUILD_PATH)$(@F)

enemy.o: src/enemy.cpp
	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/enemy.cpp -o $(BUILD_PATH)$(@F)

enemy_spawner.o: src/enemy_spawner.cpp
	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/enemy_spawner.cpp -o $(BUILD_PATH)$(@F)

collision.o: src/collision.cpp
	g++ $(INCLUDE_PATH) ${EXTERNAL_INCLUDE_PATH} -c src/collision.cpp -o $(BUILD_PATH)$(@F)

clean:
	del build\*.o