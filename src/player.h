// Toivo Lindholm 2025

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <array>
#include <SDL3/SDL.h>
#include "gameobject.h"

class Player : public GameObject {
    public:
        Player();
        Player(float x, float y, float w, float h, float speed, float maxHealth, std::string sprite, std::array<int, 5> keys, Game* game_manager);    
        void update(float& time) override;
        void take_damage(int amount);

    private:
        float speed, health, maxHealth, shoot_cooldown_timer = 1;
        int shoot_cooldown = 1;
        std::array<int, 5> keys;

        void check_movement_keys();
        void check_action_keys();
        void move_up();
        void move_left();
        void move_down();
        void move_right();
        bool can_shoot();
        void shoot();
        void increase_timer(float& time);
};

#endif