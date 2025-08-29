// Toivo Lindholm 2025

#include <iostream>
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

void EnemySpawner::update(float time){
    if(spawn_cooldown_timer >= spawn_cooldown_time){
        spawn_enemy();
        //reset the timer 
        spawn_cooldown_timer = 0;
    } else {
        spawn_cooldown_timer += time;
    }
}

//instantiates and adds new enemy to enemy-vector of gamemanager
//y-position for enemy is the y-position of the spawner
void EnemySpawner::spawn_enemy(){
    //random number inside given area
    int enemy_x = 50 + rand() % (SCREEN_WIDTH-100+1);
    int enemy_width = 35;
    int enemy_height = 35;
    int enemy_speed = 2;
    int enemy_dmg = 50;
    int enemy_health = 100;
    std::string enemy_sprite = "rectangle-red";

    game_manager->add_enemy(new Enemy(enemy_x, y, enemy_width, enemy_height, enemy_speed, enemy_dmg, enemy_health, enemy_sprite, game_manager));       
}