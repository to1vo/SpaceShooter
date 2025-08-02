#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL3/SDL.h>
#include <string>

class Game;

class GameObject {
    public:
        float x, y, width, height;
        int id;
        SDL_Texture* texture;
        std::string sprite;

        GameObject();
        GameObject(float x, float y, float w, float h, std::string sprite, Game* game_manager, int id = 0);
        virtual void update(float& time) = 0;
        Game* game_manager;
};

#endif