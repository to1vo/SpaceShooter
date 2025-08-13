// Toivo Lindholm 2025

#include "enemy_spawner.h"
#include "enemy.h"
#include "game.h"

EnemySpawner::EnemySpawner(){};
EnemySpawner::EnemySpawner(int y, Game* game_manager){
    this->y = y;
    this->game_manager = game_manager;
}

void EnemySpawner::update(float& time){
    if(spawn_cooldown_timer < spawn_cooldown_time){
        if(time == 1){
            spawn_cooldown_timer += 1;
        }
    } else {
        spawn_enemy();
        //reset the timer 
        spawn_cooldown_timer = 0;
    }    
}

//adds new enemy to enemy-vector of gamemanager
void EnemySpawner::spawn_enemy(){
    game_manager->add_enemy(new Enemy(50, y, 35, 35, 2, 50, 100, "rectangle-red", game_manager));       
}