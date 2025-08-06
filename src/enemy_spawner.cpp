// Toivo Lindholm 2025

#include "enemy_spawner.h"
#include "enemy.h"

EnemySpawner::EnemySpawner(int y){
    this->y = y;
}

void EnemySpawner::update_spawner(float& time){
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
    game_manager->add_enemy(new Enemy(50, y, 35, 35, 4, 50, 100, "rectangle-red", game_manager));       
}