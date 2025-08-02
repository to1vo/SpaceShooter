#include <iostream>
#include "player.h"
#include "game.h"
#include "projectile.h"

Player::Player(){}
Player::Player(float x, float y, float w, float h, float speed, float maxHealth, std::string sprite, std::array<int, 5> keys, Game* game_manager) : GameObject(x, y, w, h, sprite, game_manager){
    this->speed = speed;
    this->keys = keys;
    this->maxHealth = maxHealth;
    this->health = maxHealth;
}

void Player::update(float& time) {
    increase_timer(time);
    check_movement_keys();
    check_action_keys();
}

//updates the shooting cooldown timer
void Player::increase_timer(float& time){
    //60 times in second 
    if(shoot_cooldown_timer < shoot_cooldown && time == 1){
        shoot_cooldown_timer += 1;
    }
}

bool Player::can_shoot(){
    return shoot_cooldown_timer >= shoot_cooldown;
}

void Player::check_movement_keys(){
    //up
    if(Game::key_is_pressed(keys[0])){
        move_up();
    }
    //left
    if(Game::key_is_pressed(keys[1])){
        move_left();
    }
    //down
    if(Game::key_is_pressed(keys[2])){
        move_down();
    }
    //right
    if(Game::key_is_pressed(keys[3])){
        move_right();
    }
}

void Player::move_up(){
    //check for collision on top
    y -= speed;
}

void Player::move_left(){
    //check for collision on left
    x -= speed;
}

void Player::move_down(){
    //check for collision on bottom
    y += speed;
}

void Player::move_right(){
    //check for collision on right
    x += speed;
}

void Player::check_action_keys(){
    if(Game::key_is_pressed(keys[4])){
        shoot();
    }
}

//instantiates a projectile
void Player::shoot(){
    if(can_shoot()){
        game_manager->add_projectile(new Projectile(x, y, 5, 5, 5, 50, "rectangle-green", game_manager));
        shoot_cooldown_timer = 0;
    }
}