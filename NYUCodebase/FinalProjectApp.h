//
//  FinalProjectApp.h
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__FinalProjectApp__
#define __NYUCodebase__FinalProjectApp__


#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>
#include "Entity.h"
#include "SheetSprite.h"
#include "Bullet.h"
#include "Gun.h"
#include "MixerSound.h"

#define FIXED_TIMESTEP 0.16666f
#define GRAVITY 0.089;

using namespace std;
class Entity;
class Bullet;

class FinalProjectApp{
public:
    bool done;
    
    SDL_Event event;
    
    FinalProjectApp();
    ~FinalProjectApp();
    void Render();
    void Setup();
    void ProcessEvents();
    void displayScore();
    void Cleanup();
    bool UpdateAndRender();
    void Update(float elapsed);
    void FixedUpdate();
    void RenderGameLevel();
    void RenderRuleLevel();
    void RenderTitleScreen();
    void RenderGameOver();
    void UpdateTitleScreen(float elapsed);
    void UpdateGameLevel(float elapsed);
    void UpdateGameOver(float elapsed);
    void DrawSpriteSheetSprite(GLuint textureID,int  spriteCountX, int spriteCountY);
    int loadSound(const char *soundFile);
    void appAudioCallback(void *userdata, Uint8 *stream, int len);
    void DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x_pos, float y_pos);
    void playSound(int soundIndex, bool loop);
    void DrawSprite(GLint texture, float x, float y, float rotation, float w, float h);
    void displayWin();
    void RenderWin();
    void UpdateWin(float elapsed);
    GLuint LoadTexture(const char *image_path);
    bool bounce_X(Entity entity);
    void  UpdateRuleLevel(float elapsed);
private:
    enum gameState { STATE_TITLE_SCREEN, STATE_GAME_LEVEL, STATE_GAME_OVER, STATE_WIN, RULE_LEVEL};
    bool loop=true;
    SDL_Window* displayWindow;
    GLuint bg;
    int state;
    GLuint font;
    GLuint sprite_player;
    float lastFrameTicks;
    float timeLeft = 0.0f;
    Bullet* bullet;
    Gun* gun;
    GLuint pacmanTex;
    
    vector<MixerSound> mixSounds;
    
    vector<Entity> theGuys;
    vector<Bullet> bullets;
    vector<Entity> entities;
    vector<Entity> bigGuys;
    
    GLuint q_box_texture;
    GLuint bullet1;
    GLuint youwin;
    GLuint star;
    GLuint bg_image;
    
    Mix_Chunk *someSound;
    Mix_Music *music;
    Mix_Music *gameover;
    Mix_Music *opening;
    Mix_Chunk *coin;
    Mix_Chunk *shoot;
    Mix_Music *win_music;
    
    GLuint title;
    GLuint gameoverimage;
    GLuint space1;
    int score;
    int count = 0;
    
    
    Entity monster1;
    Entity monster2;
    Entity monster3;
    Entity bonus_star;
    Entity UFO;
    
      float distance_to_travel_in_one_second = 0.5;
    
    
    
};


#endif /* defined(__NYUCodebase__FinalProjectApp__) */
