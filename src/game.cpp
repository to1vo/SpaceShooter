// Toivo Lindholm 2025

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <SDL3/SDL_init.h>
#include <SDL3_image/SDL_image.h>
#include "game.h"

// *********************************
//GAME_MANAGER STATIC VARIABLES AND FUNCTIONS
std::vector<SDL_Keycode> Game::keys_pressed = {};
SDL_Renderer* Game::renderer = nullptr;

//loads a texture from given asset filename with no extension needed (expects png)
//returns the texture or if failed -> NULL
SDL_Texture* Game::load_texture(const std::string& filename, SDL_Renderer* renderer) {
    SDL_Texture* texture;
    // char path[MAX_PATH];
    // GetModuleFileNameA(NULL, path, MAX_PATH);
    // std::filesystem::path exePath(path);
    // std::filesystem::path folder = exePath.root_directory();
    // std::string filepath = folder.string()+"/resources/images/"+filename+".png";
    std::string filepath = "../resources/images/"+filename+".png";

    std::cout << "LOADING A TEXTURE " << filepath << std::endl;

    texture = IMG_LoadTexture(renderer, filepath.data());

    if(texture == NULL){
        std::cout << "Failed to load texture" << std::endl;
        return NULL;
    }

    return texture;
}

//checks if a given key is pressed
bool Game::key_is_pressed(const SDL_Keycode& keycode){
    for(int i=0; i<Game::keys_pressed.size(); i++){
        if(Game::keys_pressed[i] == keycode){
            return true;
        }
    }
    return false;
}

//gives the index of key in the vector of pressed keys
//does not exist (not pressed) -> -1
int Game::get_key_position(const SDL_Keycode& keycode){
    for(int i=0; i<Game::keys_pressed.size(); i++){
        if(Game::keys_pressed[i] == keycode){
            return i;
        }
    }
    return -1;
}
// *********************************



Game::Game(){}

void Game::start(){
    std::cout << "Game started" << std::endl;
    init_sdl();
    init();
    game_loop();
}

//initializes SDL
void Game::init_sdl(){
    window = SDL_CreateWindow("Space Game", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Game::renderer = SDL_CreateRenderer(window, NULL);
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Couldn't initialize video";
        exit(1);
    }
    
    if(!TTF_Init()){
        std::cout << "Failed to initialize SDL_TTF";
        exit(1);
    }

    text_engine = TTF_CreateRendererTextEngine(renderer);
    
    if(window == nullptr){
        std::cout << "Failed to create window";
        exit(1);
    }
    
    if(Game::renderer == nullptr){
        std::cout << "Failed to create renderer";
        exit(1);
    }
}

//initializes the game
void Game::init(){  
    //open the font(s)
    score_font = TTF_OpenFont("../resources/fonts/VT323-Regular.ttf", 30);
    gameover_font = TTF_OpenFont("../resources/fonts/VT323-Regular.ttf", 60);
    if(!score_font || !gameover_font){
        std::cout << "Failed to open font"; 
        exit(1);
    }
    
    //set the gameover text
    gameover_text = TTF_CreateText(text_engine, gameover_font, "GAMEOVER", 0);
    
    //initializing the player
    //first 4 keys for movement last one for action
    std::array<int, 5> player_keys = {SDLK_W, SDLK_A, SDLK_S, SDLK_D, SDLK_SPACE};
    int player_x = SCREEN_WIDTH/2;
    int player_y = SCREEN_HEIGHT-100;
    int player_width = 32;
    int player_height = 32;
    int player_speed = 3;
    int player_maxhealth = 100;
    std::string player_sprite = "rectangle";

    player = Player(player_x, player_y, player_width, player_height, player_speed, 
    player_maxhealth, "rectangle", player_keys, this);
    
    int enemy_spawner_y = -40;
    enemy_spawner = EnemySpawner(enemy_spawner_y, this);

    update_score_text();
}

//the main game loop
void Game::game_loop(){
    while(true){
        clear_renderer();
        read_input();
        update();
        draw();
        update_renderer();        
        SDL_Delay(DELAY_MS);  
    }
}

//reads user input
void Game::read_input(){
    SDL_Event event;
    
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_EVENT_QUIT:
                exit(0);
                break;
            case SDL_EVENT_KEY_DOWN:
                if(event.key.repeat == 0){
                    handle_key_down(event.key.key);
                }
                break;
            case SDL_EVENT_KEY_UP:
                if(event.key.repeat == 0){
                    handle_key_up(event.key.key);
                }
                break;
            default:
                break;
        }
    }
}

//handles a key being pressed
//adds key to the vector keys_pressed
void Game::handle_key_down(const SDL_Keycode& keycode){
    //if it does not already exist
    if(!key_is_pressed(keycode)){
        Game::keys_pressed.push_back(keycode);
        // std::cout << event.key << std::endl;
    }
}

//handles a key being released
//remove key from the vector keys pressed
void Game::handle_key_up(const SDL_Keycode& keycode){
    int index = get_key_position(keycode);
    //if it exists
    if(index != -1){
        Game::keys_pressed.erase(Game::keys_pressed.begin()+index);
        // std::cout << event.key << std::endl;
    }
}

void Game::clear_renderer() {
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
}

void Game::update_renderer(){
    SDL_RenderPresent(Game::renderer);
}

//update the states of gameobjects
void Game::update(){
    if(game_over){
        if(key_is_pressed(SDLK_RETURN)){
            reset();
        }
        return;
    }
    //player
    player.update(DELTA_TIME);
    
    //spawner(s)
    enemy_spawner.update(DELTA_TIME);
    
    //projectiles
    for(int i=0; i<projectiles.size(); i++){
        projectiles[i]->update(DELTA_TIME);
    }
    
    //enemies
    for(int i=0; i<enemies.size(); i++){
        enemies[i]->update(DELTA_TIME);
    }
}

void Game::draw(){
    if(game_over){
        TTF_DrawRendererText(gameover_text, SCREEN_WIDTH/3.3, SCREEN_HEIGHT/3);
        return;
    }
    //player
    draw_sprite(&player);
    
    //projectiles
    for(int i=0; i<projectiles.size(); i++){
        draw_sprite(projectiles[i]);
    }
    
    //enemies
    for(int i=0; i<enemies.size(); i++){
        draw_sprite(enemies[i]);
    }

    //UI
    TTF_DrawRendererText(score_text, SCREEN_WIDTH-125, 20);
}

//draws a single gameobject
void Game::draw_sprite(GameObject* obj){
    SDL_FRect dest; 
    dest.x = obj->x;
    dest.y = obj->y;
    dest.w = obj->width;
    dest.h = obj->height;
    
    SDL_RenderTexture(Game::renderer, obj->texture, NULL, &dest);
}

//increases the score by given amount
void Game::update_score(int amount){
    score += amount;
    update_score_text();
}

//updates the score_text with current score
void Game::update_score_text(){
    std::string score_text_str = "Score: "+std::to_string(score);
    score_text = TTF_CreateText(text_engine, score_font, score_text_str.c_str(), 0);
}

void Game::set_game_over(){
    game_over = true;
}

//clears/resets everything
//back to initial-state
void Game::reset(){
    //DELETE THE FONT/TEXT POINTERS
    std::cout << "RESETING" << std::endl;
    // score = 0;
    // clear_enemies();
    // clear_projectiles();
    // keys_pressed.clear();
    // game_over = false;
    // init();
}

void Game::clear_enemies(){
    for(int i=(int)enemies.size(); i>-1; i--){
        remove_enemy(enemies[i]->id);
    }
}

void Game::clear_projectiles(){
    for(int i=(int)projectiles.size(); i>-1; i--){
        remove_projectile(projectiles[i]->id);
    }
}

//returns new id for enemy
int Game::get_new_enemy_id(){
    return enemies.size();
}

//returns new id for projectile
int Game::get_new_projectile_id(){
    return projectiles.size();
}

//adds an object to the enemy-vector
void Game::add_enemy(Enemy* obj){
    enemies.push_back(obj);
}

//adds an object to the projectile-vector
void Game::add_projectile(Projectile* obj){
    projectiles.push_back(obj);
}

void Game::remove_enemy(int id){
    for(int i=(int)enemies.size()-1; i > -1; i--){
        if(enemies[i]->id == id){
            delete enemies[i];
            enemies.erase(enemies.begin()+i);
            std::cout << "ENEMY DESTROYED" << std::endl;
            break;
        }
    }
}

void Game::remove_projectile(int id){
    for(int i=(int)projectiles.size()-1; i > -1; i--){
        if(projectiles[i]->id == id){
            delete projectiles[i];
            projectiles.erase(projectiles.begin()+i);
            std::cout << "PROJECTILE DESTROYED" << std::endl;
            break;
        }
    }
}
