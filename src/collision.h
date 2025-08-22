// Toivo Lindholm 2025

#ifndef COLLISION_H
#define COLLISION_H
#include "gameobject.h"

class Collision {
    public:
        static int is_colliding(GameObject& obj_1, GameObject& obj_2);
    
    private:
        static bool is_colliding_top(GameObject& obj_1, GameObject& obj_2);
        static bool is_colliding_down(GameObject& obj_1, GameObject& obj_2);
        static bool is_colliding_left(GameObject& obj_1, GameObject& obj_2);
        static bool is_colliding_right(GameObject& obj_1, GameObject& obj_2);
        static bool is_in_range_y(GameObject& obj_1, GameObject& obj_2);
        static bool is_in_range_x(GameObject& obj_1, GameObject& obj_2);
};

#endif