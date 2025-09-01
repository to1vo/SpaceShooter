//Toivo Lindholm 2025

#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

class Game;


class EnemySpawner {
    public: 
        void update(float time);

        EnemySpawner();
        EnemySpawner(int y, Game* game_manager);
    private:    
        int y;
        int spawn_cooldown_time = 2;
        float spawn_cooldown_timer = spawn_cooldown_time;
        Game* game_manager;

        void spawn_enemy();
};

#endif