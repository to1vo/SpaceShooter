// Toivo Lindholm 2025

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H
#include <string> 
#include <SDL3_ttf/SDL_ttf.h>

class TextObject {
    public:
        TextObject(TTF_TextEngine* text_engine, float x, float y, std::string value, TTF_Font* font);
        TextObject();
        void draw_textobject();
        void update_value(const std::string& new_value);

    protected:
        float x, y;
    
    private:
        TTF_TextEngine* text_engine;
        TTF_Text* text;
        std::string value;
        TTF_Font* font;
};

#endif