// Toivo Lindholm 2025

#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 350
#define FPS 62.0
#define DELTA_TIME (1.0/FPS)
#define DELAY_MS 16
#define STATE_MENU 0
#define STATE_PLAY 1
#define STATE_GAMEOVER 2

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
#include "textobject.h"
#include "animated_textobject.h"

class Game {
    public:
        static std::vector<SDL_Keycode> keys_pressed;
        static SDL_Renderer* renderer;
    
        std::vector<Enemy*> enemies;
        std::vector<Projectile*> projectiles;
    
        Game();
        void init();
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
                    delete container[i];
                    container.erase(container.begin()+i);
                    break;
                }
            }
        }
        
        static SDL_Texture* load_texture(const std::string& filename, SDL_Renderer* renderer);
        static bool key_is_pressed(const SDL_Keycode& keycode);
        static int get_key_position(const SDL_Keycode& keycode);
        
    private:
        int score = 0;
        int game_state = STATE_MENU;
        SDL_Window* window;
        Player player;
        EnemySpawner enemy_spawner;
        SDL_Texture* menu_bg_texture;
        TTF_Font* font_big;
        TTF_Font* font_medium;
        TTF_TextEngine* text_engine;
        TextObject score_text;
        TextObject gameover_text;
        AnimatedTextObject menu_text;
        TextObject restart_text;
        
        void start();
        void init_sdl();
        void read_input();
        void handle_key_down(const SDL_Keycode& keycode);
        void handle_key_up(const SDL_Keycode& keycode);
        void clear_renderer();
        void update_renderer();
        void draw();
        void draw_texture(SDL_Texture* texture, int x, int y, int w, int h, float angle = 0);
        void update();
        void game_loop();
        void update_score_text();
        void reset();
        
        template <typename T>
        void clear_container(std::vector<T*>& container){
            for(int i=(int)container.size()-1; i>-1; i--){
               remove_gameobject(container[i]->id, container);
            }
        }
};

#endif