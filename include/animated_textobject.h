// Toivo Lindholm 2025

#ifndef ANIMATED_TEXTOBJECT_H
#define ANIMATED_TEXTOBJECT_H
#include "textobject.h"

class AnimatedTextObject : public TextObject {
    public:
        AnimatedTextObject(TTF_TextEngine* text_engine, float x, float y, std::string value, TTF_Font* font, float speed, float max_y_up, float max_y_down);
        AnimatedTextObject();
        void animate(float delta_time);

    private:
        float speed, original_y, max_y_up, max_y_down;
};

#endif