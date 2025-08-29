// Toivo Lindholm 2025

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "gameobject.h"

class Projectile : public GameObject {
    public:
        Projectile();
        Projectile(float x, float y, float w, float h, float speed, float damage, std::string sprite, Game* game_manager);
        void update(float time) override;
    
    private:
        int destroy_time = 5;
        float speed, damage; 
        float destroy_timer = 0;

        void move_up();
        void destroy();
};

#endif