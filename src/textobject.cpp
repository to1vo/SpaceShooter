// Toivo Lindholm 2025

#include <iostream>
#include "textobject.h"

TextObject::TextObject(){}
TextObject::TextObject(TTF_TextEngine* text_engine, float x, float y, std::string value, TTF_Font* font){
    this->x = x;
    this->y = y;
    this->value = value;
    this->font = font;
    this->text_engine = text_engine;
    this->text = TTF_CreateText(text_engine, font, value.c_str(), 0);
}

void TextObject::draw_textobject(){
    TTF_DrawRendererText(text, x, y);
}

//update the text value
void TextObject::update_value(const std::string& new_value){
    TTF_DestroyText(text);
    text = TTF_CreateText(text_engine, font, new_value.c_str(), 0);
}