// Toivo Lindholm 2025

#include <iostream>
#include "player.h"
#include "game.h"
#include "projectile.h"
#include "collision.h"

Player::Player(){}
Player::Player(float x, float y, float w, float h, float speed, float maxHealth, std::string sprite, std::array<int, 5> keys, Game* game_manager) : GameObject(x, y, w, h, sprite, game_manager){
    this->speed = speed;
    this->keys = keys;
    this->maxHealth = maxHealth;
    this->health = maxHealth;
}

void Player::update(float time) {
    increase_timer(time);
    check_collisions();
    check_movement_keys();
    check_action_keys();
}

//updates the shooting cooldown timer
void Player::increase_timer(float& time){
    if(shoot_cooldown_timer < shoot_cooldown){
        shoot_cooldown_timer += time;
    }
}

bool Player::can_shoot(){
    return shoot_cooldown_timer >= shoot_cooldown;
}

void Player::check_collisions(){
    int enemy_id;

    for(int i=(int)game_manager->enemies.size()-1; i>-1; i--){
        enemy_id = Collision::is_colliding(*this, *game_manager->enemies[i]);

        if(enemy_id != -1){
            take_damage(game_manager->enemies[i]->damage);
            game_manager->remove_gameobject(enemy_id, game_manager->enemies);
        }
    }
}

//SHOULD ALL KEYS BE CHECKED IN HERE?
void Player::check_movement_keys(){
    //up
    if(Game::key_is_pressed(keys[0])){
        move_up();
    }

    //left
    if(Game::key_is_pressed(keys[1])){
        moving_horizontally = true;
        move_left();
    } else {
        moving_horizontally = false;
    }

    //down
    if(Game::key_is_pressed(keys[2])){
        move_down();
    }

    //right
    if(Game::key_is_pressed(keys[3])){
        moving_horizontally = true;
        move_right();
    } else {
        moving_horizontally = false;
    }
}

void Player::check_action_keys(){
    if(Game::key_is_pressed(keys[4])){
        shoot();
    }
}

void Player::move_up(){
    y -= speed;
}

void Player::move_left(){
    x -= speed;
}

void Player::move_down(){
    y += speed;
}

void Player::move_right(){
    x += speed;
}


void Player::take_damage(int amount){
    std::cout << "PLAYER TAKING DAMAGE " << amount << std::endl;

    health -= amount;

    if(health <= 0){
        game_manager->set_game_over();
    }
}

//instantiates a projectile to its container
//x and y positions come from player's position
void Player::shoot(){
    if(can_shoot()){
        std::cout << "SHOOTING" << std::endl;

        int projectile_width = 3;
        int projectile_height = 8;
        int projectile_speed = 7;
        int projectile_dmg = 50;
        std::string projectile_sprite = "laser";

        game_manager->add_gameobject(new Projectile(x, y, projectile_width, projectile_height, projectile_speed, projectile_dmg, projectile_sprite, game_manager), game_manager->projectiles);

        shoot_cooldown_timer = 0;
    }
}