// Toivo Lindholm 2025

#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 350
#define FPS 62.0
#define DELTA_TIME (1.0/FPS)
#define DELAY_MS 16

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "player.h"
#include "gameobject.h"
#include "enemy_spawner.h"
#include "enemy.h"
#include "projectile.h"

class Game {
    public:
        static std::vector<SDL_Keycode> keys_pressed;
        static SDL_Renderer* renderer;

        std::vector<Enemy*> enemies;
        std::vector<Projectile*> projectiles;
        
        Game();
        void start();
        void set_game_over();
        void update_score(int amount);
        
        //return new id for the object
        template <typename T>
        int get_new_object_id(std::vector<T*>& container){
            return int(container.size());
        }
        
        //adds an object to the given container
        template <typename T>
        void add_gameobject(T* obj, std::vector<T*>& container){
            container.push_back(obj);
        }
        
        //removes object by id from given container
        template <typename T>
        void remove_gameobject(int id, std::vector<T*>& container){
            for(int i=(int)container.size()-1; i>-1; i--){
                if(container[i]->id == id){
                    SDL_DestroyTexture(container[i]->texture);
                    delete container[i];
                    container.erase(container.begin()+i);
                    std::cout << "GAMEOBJECT DESTROYED" << std::endl;
                    break;
                }
            }
        }
        
        static SDL_Texture* load_texture(const std::string& filename, SDL_Renderer* renderer);
        static bool key_is_pressed(const SDL_Keycode& keycode);
        static int get_key_position(const SDL_Keycode& keycode);

    private:
        int score = 0;
        bool game_over = false;
        SDL_Window* window;
        Player player;
        EnemySpawner enemy_spawner;
        TTF_Font* score_font;
        TTF_Font* gameover_font;
        TTF_TextEngine* text_engine;
        TTF_Text* score_text;
        TTF_Text* gameover_text;

        void init_sdl();
        void init();
        void read_input();
        void handle_key_down(const SDL_Keycode& keycode);
        void handle_key_up(const SDL_Keycode& keycode);
        void clear_renderer();
        void update_renderer();
        void draw();
        void draw_sprite(GameObject* obj);
        void update();
        void game_loop();
        void update_score_text();
        void reset();

        template <typename T>
        void clear_container(std::vector<T*>& container){
            for(int i=(int)container.size(); i>-1; i--){
               remove_gameobject(container[i]->id);
            }
        }
};

#endif