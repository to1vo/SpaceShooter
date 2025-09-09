// Toivo Lindholm 2025

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H
#include <string> 
#include <SDL3_ttf/SDL_ttf.h>

class TextObject {
    public:
        TextObject(TTF_TextEngine* text_engine, float x, float y, std::string value, TTF_Font* font);
        TextObject();
        ~TextObject();
        void draw_textobject();
        void update_value(std::string new_value);

    protected:
        float x, y;
    
    private:
        TTF_TextEngine* text_engine = nullptr;
        TTF_Text* text = nullptr;
        std::string value;
        TTF_Font* font = nullptr;
};

#endif