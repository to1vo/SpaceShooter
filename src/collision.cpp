// Toivo Lindholm 2025

#include <iostream>
#include "collision.h"

//checks the collision between two objects
//returns the id of the object_2
//IS GAME_MANAGER AS AN ARGUMENT NEEDED???
int Collision::is_colliding_top(GameObject& obj_1, GameObject& obj_2){
    //x axis
    if((obj_1.x >= obj_2.x && obj_1.x <= obj_2.x+obj_2.width) || (obj_1.x+obj_1.width >= obj_2.x && obj_1.x+obj_1.width <= obj_2.x+obj_2.width)){
        //y axis
        if((obj_1.y < obj_2.y+obj_2.height) && (obj_1.y+obj_1.height > obj_2.y)){
            return obj_2.id;
        }
    }
    return -1; 
}

int Collision::is_colliding_down(GameObject& obj_1, GameObject& obj_2){
    //x axis
    if((obj_1.x >= obj_2.x && obj_1.x <= obj_2.x+obj_2.width) || (obj_1.x+obj_1.width >= obj_2.x && obj_1.x+obj_1.width <= obj_2.x+obj_2.width)){
        //y axis
        if((obj_1.y < obj_2.y) && (obj_1.y+obj_1.height > obj_2.y)){
            return obj_2.id;
        }
    }
    return -1;
}

int Collision::is_colliding_left(GameObject& obj_1, GameObject& obj_2){
    //y axis
    if((obj_1.y <= obj_2.y && obj_1.y+obj_1.height > obj_2.y) || (obj_1.y > obj_2.y && obj_1.y < obj_2.y+obj_2.height)){
        //x axis
        if(obj_1.x <= obj_2.x+obj_2.width){
            return obj_2.id;
        }
    }
    return -1;
}

int Collision::is_colliding_right(GameObject& obj_1, GameObject& obj_2){
    //y axis
    if((obj_1.y <= obj_2.y && obj_1.y+obj_1.height > obj_2.y) || (obj_1.y > obj_2.y && obj_1.y < obj_2.y+obj_2.height)){
        //x axis
        if(obj_1.x+obj_1.width >= obj_2.x){
            return obj_2.id;
        }
    }
    return -1;
}