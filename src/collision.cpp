// Toivo Lindholm 2025

#include <iostream>
#include "../include/collision.h"

//checks the collision between two objects
//returns the id of the object_2
int Collision::is_colliding(GameObject& obj_1, GameObject& obj_2){
    if(is_in_range_x(obj_1, obj_2) && is_in_range_y(obj_1, obj_2)){
        return obj_2.id;
    }
    return -1;
}

bool Collision::is_colliding_top(GameObject& obj_1, GameObject& obj_2){
    //x axis
    if(is_in_range_x(obj_1, obj_2)){
        //y axis
        if((obj_1.y < obj_2.y+obj_2.height) && (obj_1.y+obj_1.height > obj_2.y)){
            return true;
        }
    }
    return false;
}

bool Collision::is_colliding_down(GameObject& obj_1, GameObject& obj_2){
    //x axis
    if(is_in_range_x(obj_1, obj_2)){
        //y axis
        if((obj_1.y < obj_2.y) && (obj_1.y+obj_1.height > obj_2.y)){
            return true;
        }
    }
    return false;
}

bool Collision::is_colliding_left(GameObject& obj_1, GameObject& obj_2){
    //y axis
    if(is_in_range_y(obj_1, obj_2)){
        //x axis
        if(obj_1.x <= obj_2.x+obj_2.width){
            return true;
        }
    }
    return false;
}

bool Collision::is_colliding_right(GameObject& obj_1, GameObject& obj_2){
    //y axis
    if(is_in_range_y(obj_1, obj_2)){
        //x axis
        if(obj_1.x+obj_1.width >= obj_2.x){
            return true;
        }
    }
    return false;
}

bool Collision::is_in_range_y(GameObject& obj_1, GameObject& obj_2){
    if((obj_1.y <= obj_2.y && obj_1.y+obj_1.height > obj_2.y) || (obj_1.y > obj_2.y && obj_1.y < obj_2.y+obj_2.height)){
        return true;
    }
    return false;
}

bool Collision::is_in_range_x(GameObject& obj_1, GameObject& obj_2){
    if((obj_1.x >= obj_2.x && obj_1.x <= obj_2.x+obj_2.width) || (obj_1.x+obj_1.width >= obj_2.x && obj_1.x+obj_1.width <= obj_2.x+obj_2.width)){
        return true;
    }
    return false;
}
