// Toivo Lindholm 2025

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <SDL3/SDL_init.h>
#include <SDL3_image/SDL_image.h>
#include "game.h"

//STATICS
std::vector<int> Game::keys_pressed = {};
SDL_Renderer* Game::renderer = nullptr;

//loads a texture from given asset
SDL_Texture* Game::load_texture(const std::string& filename, SDL_Renderer* renderer) {
    SDL_Texture* texture;
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::filesystem::path exePath(path);
    std::filesystem::path folder = exePath.parent_path();
    std::string filepath = folder.string()+"/assets/"+filename+".png";

    std::cout << "LOADING A TEXTURE " << filepath << std::endl;

    texture = IMG_LoadTexture(renderer, filepath.data());

    if(texture == NULL){
        std::cout << "Failed to load texture";
        return NULL;
    }

    return texture;
}

//check if key is already in the vector
bool Game::key_is_pressed(int key){
    for(int i=0; i<Game::keys_pressed.size(); i++){
        if(Game::keys_pressed[i] == key){
            return true;
        }
    }
    return false;
}

//get the index of key in the vector
//does not exist -> -1
int Game::get_key_position(int key){
    for(int i=0; i<Game::keys_pressed.size(); i++){
        if(Game::keys_pressed[i] == key){
            return i;
        }
    }
    return -1;
}


Game::Game(){
    std::cout << "Game started" << std::endl;
}

void Game::start(){
    init_sdl();
    init();
    game_loop();
}

void Game::set_game_over(){
    game_over = true;
    // score = 0;
    // enemies.clear();
    // projectiles.clear();
}

//initialize SDL stuff
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

//initializes the game (all objects etc.)
void Game::init(){  
    //Open the font
    score_font = TTF_OpenFont("fonts/VT323-Regular.ttf", 30);
    if(!score_font){
        std::cout << "Failed to open font"; 
        exit(1);
    } 
    
    update_score_text();
    
    delta_time = 1 / 62.0;
    std::array<int, 5> player_keys = {119, 97, 115, 100, 32};
    player = Player(SCREEN_WIDTH/2, SCREEN_HEIGHT-100, 32, 32, 3, 100, "rectangle", player_keys, this);
    enemy_spawner = EnemySpawner(-40, this);
}

//reads all input
void Game::read_input(){
    SDL_Event event;
    
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_EVENT_QUIT:
            exit(0);
            break;
            case SDL_EVENT_KEY_DOWN:
            handle_key_down(event.key);
            break;
            case SDL_EVENT_KEY_UP:
            handle_key_up(event.key);
            break;
            default:
            break;
        }
    }
}

//handles key pressed
void Game::handle_key_down(SDL_KeyboardEvent& event){
    //add key to the vector of keys_pressed
    //if it does not already exist
    if(event.repeat == 0){
        if(!key_is_pressed(event.key)){
            Game::keys_pressed.push_back(event.key);
            // std::cout << event.key << std::endl;
        }
    }
}

//handles key released
void Game::handle_key_up(SDL_KeyboardEvent& event){
    //remove key from the vector of keys pressed
    //if it exists in there
    if(event.repeat == 0){
        int index = get_key_position(event.key);
        if(index != -1){
            Game::keys_pressed.erase(Game::keys_pressed.begin()+index);
            // std::cout << event.key << std::endl;
        }
    }
}

//setup the renderer for drawing
void Game::setup_renderer() {
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
}

//display
void Game::display(){
    SDL_RenderPresent(Game::renderer);
}

//main draw function
void Game::draw(){
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

//functionality for individual render
void Game::draw_sprite(GameObject* obj){
    SDL_FRect dest; 
    dest.x = obj->x;
    dest.y = obj->y;
    dest.w = obj->width;
    dest.h = obj->height;
    
    SDL_RenderTexture(Game::renderer, obj->texture, NULL, &dest);
}

//update the states of objects
void Game::update(){
    //player
    player.update(delta_time);
    
    //spawners
    enemy_spawner.update(delta_time);
    
    //projectiles
    for(int i=0; i<projectiles.size(); i++){
        projectiles[i]->update(delta_time);
    }
    
    //enemies
    for(int i=0; i<enemies.size(); i++){
        enemies[i]->update(delta_time);
    }
}

void Game::game_loop(){
    while(true){
        if(!game_over){
            setup_renderer();
            read_input();
            update();
            draw();
            display();        
            SDL_Delay(16);  

            continue;
        } 

        read_input();
        SDL_Delay(16);
    }
}

//returns new id for gameobject
int Game::get_new_enemy_id(){
    // std::cout << "NEW ID RECEIVED: " << enemies.size() << std::endl;
    return enemies.size();
}
int Game::get_new_projectile_id(){
    return projectiles.size();
}

//adds an object to the list of gameobjects
void Game::add_enemy(Enemy* obj){
    enemies.push_back(obj);
}
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

//increases the score by given amount
void Game::update_score(int amount){
    score += amount;
    update_score_text();
}

//updates the score_text object
void Game::update_score_text(){
    std::string score_text_str = "Score: "+std::to_string(score);
    score_text = TTF_CreateText(text_engine, score_font, score_text_str.c_str(), 0);
}
