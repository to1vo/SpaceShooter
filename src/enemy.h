// Toivo Lindholm 2025

#ifndef ENEMY_H
#define ENEMY_H
#include "gameobject.h"

class Enemy : public GameObject {
    public:
        Enemy(float x, float y, float w, float h, int speed, int damage, int health, std::string sprite, Game* game_manager);    
        void update(float& time) override;

    private:
        int speed, damage, health; 
        int destroy_time = 10;
        float destroy_timer = 0;

        void move();
        void destroy();
};

#endif