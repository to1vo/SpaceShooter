// Toivo Lindholm 2025

#include <ctime>
#include <cstdlib>
#include "enemy_spawner.h"
#include "enemy.h"
#include "game.h"

EnemySpawner::EnemySpawner(){};
EnemySpawner::EnemySpawner(int y, Game* game_manager){
    srand(time(0));
    this->y = y;
    this->game_manager = game_manager;
}

void EnemySpawner::update(float& time){
    if(spawn_cooldown_timer > spawn_cooldown_time){
        spawn_enemy();
        //reset the timer 
        spawn_cooldown_timer = 0;
    }
    spawn_cooldown_timer += time;
}

//adds new enemy to enemy-vector of gamemanager
void EnemySpawner::spawn_enemy(){
    int x_position = 50 + rand() % (SCREEN_WIDTH-100+1);
    game_manager->add_enemy(new Enemy(x_position, y, 35, 35, 2, 50, 100, "rectangle-red", game_manager));       
}