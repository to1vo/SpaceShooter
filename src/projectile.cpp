#include <iostream>
#include "projectile.h"
#include "game.h"

Projectile::Projectile(){}
Projectile::Projectile(float x, float y, float w, float h, float speed, float damage, std::string sprite, Game* game_manager) : GameObject(x, y, w, h, sprite, game_manager, game_manager->get_new_projectile_id()){
    // std::cout << "Projectile created!" << std::endl;
    this->speed = speed;
    this->damage = damage;
}

void Projectile::update(float& time){
    if(destroy_timer >= destroy_time){
        destroy();
        return;
    }
    if(time == 1){
        destroy_timer += 1;
    }
    move_up();    
}

void Projectile::move_up(){
    //check collision on top
    //then destroy and do damage to enemy
    y -= speed;    
}

//remove this projectile
void Projectile::destroy(){
    game_manager->remove_projectile(id);
}