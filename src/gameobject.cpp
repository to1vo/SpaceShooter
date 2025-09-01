// Toivo Lindholm 2025

#include <iostream>
#include "../include/gameobject.h"
#include "../include/game.h"

GameObject::GameObject(){}
GameObject::GameObject(float x, float y, float w, float h, std::string sprite, Game* game_manager, int id){
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->sprite = sprite;
    this->texture = Game::load_texture(sprite, Game::renderer);
    this->game_manager = game_manager;
    this->id = id;
}