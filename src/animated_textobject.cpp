// Toivo Lindholm 2025

#include "animated_textobject.h"

AnimatedTextObject::AnimatedTextObject(){}
AnimatedTextObject::AnimatedTextObject(TTF_TextEngine* text_engine, float x, float y, std::string value, TTF_Font* font, float speed, float max_y_up, float max_y_down) : TextObject(text_engine, x, y, value, font){
    this->speed = speed;
    this->max_y_up = max_y_up;
    this->max_y_down = max_y_down;
    this->original_y = y;
}

//Moves the textobject vertically inside given range
//Speed decides the starting direction
void AnimatedTextObject::animate(float delta_time){
    if(y <= original_y-max_y_up || y >= original_y+max_y_down){
        speed = -speed;
    }
    y += speed;
}