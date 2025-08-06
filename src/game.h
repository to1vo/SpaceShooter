// Toivo Lindholm 2025

#ifndef GAME_H
#define GAME_H
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 350
#include <vector>
#include <array>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "player.h"
#include "gameobject.h"

class Game {
    public:
        static std::vector<int> keys_pressed;
        static SDL_Renderer* renderer;
        
        Game();
        void start();
        int get_new_enemy_id();
        int get_new_projectile_id();
        void add_enemy(GameObject* obj);
        void add_projectile(GameObject* obj);
        void remove_enemy(int id);
        void remove_projectile(int id);
        void update_score(int amount);

        static SDL_Texture* load_texture(const std::string& filename, SDL_Renderer* renderer);
        static bool key_is_pressed(int key);
        static int get_key_position(int key);
        static int is_colliding_top(Game& game_manager, GameObject& obj_1, GameObject& obj_2);

    private:
        int score;
        SDL_Window* window;
        float time, frames;
        std::vector<GameObject*> enemies;
        std::vector<GameObject*> projectiles;
        Player player;
        TTF_Font* score_font;
        TTF_TextEngine* text_engine;
        TTF_Text* score_text;

        void init_sdl();
        void init();
        void read_input();
        void handle_key_down(SDL_KeyboardEvent& event);
        void handle_key_up(SDL_KeyboardEvent& event);
        void calculate_time(float& last_time);
        void setup_renderer();
        void display();
        void draw();
        void draw_sprite(GameObject* obj);
        void update();
        void game_loop();
        void update_score_text();
};

#endif