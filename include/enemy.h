// Toivo Lindholm 2025

#ifndef ENEMY_H
#define ENEMY_H
#include "gameobject.h"

class Enemy : public GameObject {
    public:
        Enemy(float x, float y, float w, float h, int speed, int damage, int health, std::string sprite, Game* game_manager);
        ~Enemy(); 
        void update(float time) override;
        void take_damage(int amount);

        int damage;
    private:
        int speed, health; 
        int destroy_time = 10;
        float destroy_timer = 0;

        void move();
        void destroy();
};

#endif