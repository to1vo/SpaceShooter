// Toivo Lindholm 2025

#include <iostream>
#include "enemy.h"
#include "game.h"

Enemy::Enemy(float x, float y, float w, float h, int speed, int damage, int health, std::string sprite, Game* game_manager) : GameObject(x, y, w, h, sprite, game_manager, game_manager->get_new_enemy_id()){
    this->speed = speed;
    this->damage = damage;
    this->health = health;
    std::cout << "ENEMY CREATED" << std::endl;
}

//update timer
void Enemy::update(float& time){
    if(destroy_timer < destroy_time){
        if(time == 1){
            destroy_timer += 1;
        }
    } else {
        destroy();
        return;
    }
    move();
}

//move down
void Enemy::move(){
    y += speed;
}

//removes itself from the container vector
void Enemy::destroy(){
    game_manager->remove_enemy(id);
}