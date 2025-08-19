// Toivo Lindholm 2025

#include <iostream>
#include "projectile.h"
#include "game.h"
#include "collision.h"

Projectile::Projectile(){}
Projectile::Projectile(float x, float y, float w, float h, float speed, float damage, std::string sprite, Game* game_manager) : GameObject(x, y, w, h, sprite, game_manager, game_manager->get_new_projectile_id()){
    this->speed = speed;
    this->damage = damage;
    std::cout << "PROJECTILE CREATED" << std::endl;
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

    //check collision with enemies
    for(int i=game_manager->enemies.size()-1; i>-1; i--){
        int enemy_id = Collision::is_colliding_top(*this, *game_manager->enemies[i]);
        if(enemy_id != -1){
            game_manager->remove_enemy(enemy_id);
            game_manager->update_score(10);      
            destroy();  
        }    
    }
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