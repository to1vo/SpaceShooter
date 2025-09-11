// Toivo Lindholm 2025

#include <iostream>
#include "enemy.h"
#include "game.h"

int Enemy::enemy_count = 0;

Enemy::Enemy(float x, float y, float w, float h, int speed, int damage, int health, std::string sprite, Game* game_manager) : GameObject(x, y, w, h, sprite, game_manager, Enemy::enemy_count){
    Enemy::enemy_count++;

    this->speed = speed;
    this->damage = damage;
    this->health = health;

    std::cout << "ENEMY CREATED" << std::endl;
    
    std::cout << "ENEMIES" << std::endl;
    for(int i=0; i<game_manager->enemies.size(); i++){
        std::cout << game_manager->enemies[i]->id << std::endl;
    }
}

Enemy::~Enemy(){
    std::cout << "ENEMY DESTROYED" << std::endl; 
    SDL_DestroyTexture(texture);    
    texture = nullptr;
}

//update timer
void Enemy::update(float time){
    if(destroy_timer > destroy_time){
        destroy();
        return;
    }
    angle += 0.8;
    move();
    destroy_timer += time;
}

//move down
void Enemy::move(){
    y += speed;
}

void Enemy::take_damage(int amount){
    std::cout << "ENEMY TAKING DAMAGE " << amount << std::endl;
    health -= amount;
    if(health <= 0){
        destroy();
    }
}

//removes itself from the container vector
void Enemy::destroy(){
    game_manager->remove_gameobject(id, game_manager->enemies);
}