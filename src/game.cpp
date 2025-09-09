// Toivo Lindholm 2025

#include <windows.h>
#include <filesystem>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
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

void Game::init(){
    std::cout << "Initializing the game..." << std::endl;

    init_sdl();

    std::cout << "Loading fonts..." << std::endl;

    //open the font(s)
    font_medium = TTF_OpenFont("../resources/fonts/VT323-Regular.ttf", 30);
    font_big = TTF_OpenFont("../resources/fonts/VT323-Regular.ttf", 60);
    if(!font_medium || !font_big){
        std::cout << "Failed to open font"; 
        exit(1);
    }
    
    //set up the menu
    menu_bg_texture = load_texture("menu-background", renderer);
    
    //create all textobjects for the game
    menu_text = AnimatedTextObject(text_engine, SCREEN_WIDTH/4, SCREEN_HEIGHT-100, "Press Enter To Start", font_medium, 0.5, 15, 15);
    gameover_text = TextObject(text_engine, SCREEN_WIDTH/3.3, SCREEN_HEIGHT/3, "GAMEOVER", font_big);
    restart_text = TextObject(text_engine, SCREEN_WIDTH/4, SCREEN_HEIGHT-160, "Press Enter To Restart", font_medium);
    score_text = TextObject(text_engine, SCREEN_WIDTH-130, 20, "Score: 0", font_medium);

    start();

    game_loop();
}

//initializes SDL
void Game::init_sdl(){
    // window = SDL_CreateWindow("Space Shooter", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    window = SDL_CreateWindow("Space Shooter", 0, 0, SDL_WINDOW_FULLSCREEN);
    Game::renderer = SDL_CreateRenderer(window, NULL);

    
    if(window == nullptr){
        std::cout << "Failed to create window";
        exit(1);
    }
    
    //just a placeholder for now
    if(!SDL_SetWindowIcon(window, IMG_Load("../resources/images/rectangle-red.png"))){
        std::cout << "Failed to set the window icon" << std::endl;
    }

    if(Game::renderer == nullptr){
        std::cout << "Failed to create renderer";
        exit(1);
    }

    if(!SDL_SetRenderLogicalPresentation(Game::renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE)){
        std::cout << "Failed to set LogicalPresentation mode" << std::endl;
        exit(1);
    }
        
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Couldn't initialize video";
        exit(1);
    }
    
    if(!TTF_Init()){
        std::cout << "Failed to initialize SDL_TTF";
        exit(1);
    }
    
    text_engine = TTF_CreateRendererTextEngine(renderer);    
}

void Game::start(){
    //create the player
    //first 4 keys for movement last one for action
    std::array<int, 5> player_keys = {SDLK_W, SDLK_A, SDLK_S, SDLK_D, SDLK_SPACE};
    int player_x = SCREEN_WIDTH/2;
    int player_y = SCREEN_HEIGHT-100;
    int player_width = 32;
    int player_height = 32;
    int player_speed = 3;
    int player_maxhealth = 100;
    std::string player_sprite = "player";
    
    player = Player(player_x, player_y, player_width, player_height, player_speed, 
    player_maxhealth, player_sprite, player_keys, this);
    
    int enemy_spawner_y = -40;
    enemy_spawner = EnemySpawner(enemy_spawner_y, this);
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
    if(game_state == STATE_MENU){
        menu_text.animate(DELTA_TIME);
        if(key_is_pressed(SDLK_RETURN)){
            game_state = STATE_PLAY;
        }
        return;
    }

    if(game_state == STATE_GAMEOVER){
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
    for(int i=(int)projectiles.size()-1; i>-1; i--){
        projectiles[i]->update(DELTA_TIME);
    }
    
    //enemies
    for(int i=(int)enemies.size()-1; i>-1; i--){
        enemies[i]->update(DELTA_TIME);
    }
}

void Game::draw(){
    if(game_state == STATE_MENU){
        draw_texture(menu_bg_texture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        menu_text.draw_textobject();
        return;
    }

    if(game_state == STATE_GAMEOVER){
        gameover_text.draw_textobject();
        restart_text.draw_textobject();
        return;
    }

    //player
    draw_texture(player.texture, player.x, player.y, player.width, player.height);

    //enemies
    for(int i=(int)enemies.size()-1; i>-1; i--){
        Enemy* enemy = enemies[i];
        draw_texture(enemy->texture, enemy->x, enemy->y, enemy->width, enemy->height, enemy->angle);
    }

    //projectiles
    for(int i=(int)projectiles.size()-1; i>-1; i--){
        Projectile* projectile = projectiles[i];
        draw_texture(projectile->texture, projectile->x, projectile->y, projectile->width, projectile->height);
    }

    //UI
    score_text.draw_textobject();
}

//draws the given texture
void Game::draw_texture(SDL_Texture* texture, int x, int y, int w, int h, float angle){
    SDL_FRect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    SDL_RenderTextureRotated(Game::renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
    // SDL_RenderTexture(Game::renderer, texture, NULL, &dest);
}

//increases the score by given amount
void Game::update_score(int amount){
    score += amount;
    update_score_text();
}

//updates the score_text with current score
void Game::update_score_text(){
    std::string str = "Score: "+std::to_string(score);
    score_text.update_value(str);
}

void Game::set_game_over(){
    //set the gameover state
    game_state = STATE_GAMEOVER;
}

//clears/resets everything
//back to initial-state
void Game::reset(){
    std::cout << "RESETTING THE GAME" << std::endl;
    clear_container(enemies);
    clear_container(projectiles);
    keys_pressed.clear();
    score = 0;
    update_score_text();
    game_state = STATE_PLAY;
    start();
}