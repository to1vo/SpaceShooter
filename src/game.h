// Toivo Lindholm 2025

#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 350
#define FPS 62
#define DELTA_TIME (1/FPS)
#define DELAY_MS 16

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
        int get_new_enemy_id();
        int get_new_projectile_id();
        void add_enemy(Enemy* obj);
        void add_projectile(Projectile* obj);
        void remove_enemy(int id);
        void remove_projectile(int id);
        void update_score(int amount);

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
        TTF_TextEngine* text_engine;
        TTF_Text* score_text;

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
};

#endif