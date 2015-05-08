//
//  FinalProjectApp.cpp
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//


/*
 
 FIXING TO-DO 5/5
 
 - REMOVE ALL THE LOAD TEXTURES
 - SET THE ACCELERATION
 - PLAY SOUND WHEN SHOOTING THE BULLET
 - CHANGE THE SOUND FOR THE TITLE SCREEN!
 - ALSO MAKE A SCREEN FOR WIN
 - NUMBER OF BULLETS LEFT
 
 */


#include "FinalProjectApp.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include <stdlib.h>
#include<vector>
#include <SDL_mixer.h>
#include "Bullet.h"
#include "Entity.h"
#include "SheetSprite.h"
#include "Gun.h"
class Entity;
using namespace std;
enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL };
int state;
int MAX_GUYS = 54;
int MAX_BULLETS = 100;
int NUM_OF_GUYS_ALIVE=54;
int BIG_GUYS = 5;

//#define FIXED_TIMESTEP 0.015f;

FinalProjectApp::FinalProjectApp() {
    
    Setup();

    done = false;
    lastFrameTicks = 0.0f;
    
    
    font = LoadTexture("pixel_font.png");
    pacmanTex = LoadTexture("pacman.png");
   
     title = LoadTexture("Space-invaders.png");
      gameoverimage = LoadTexture("gameover.jpg");
     space1 = LoadTexture("space1.png");
    star = LoadTexture("star.png");
     bg_image = LoadTexture("space-background1.png");
   

    
    state = 0;

    score = 0;
    
    gun = new Gun(0.0,0.0, 0.0, 0.5, 0.5);
     gun->gunTexture = LoadTexture("gun.png");
    
    gun->x = 0.0;
    gun->y = -0.7;
    
    
    bullet1 = LoadTexture("bullet.png");
    youwin = LoadTexture("youwin.png");
    
    gun->velocity_x = 0.0f;
    gun->acceleration_x = 0.0f;
    gun->friction_x = 6.0f;
    
    float positionX = -0.8;
    float positionY = 0.9;
    float index = 0;
    
    monster1.x_pos = -.8;
    monster1.y_pos = 1.2;
    
    monster2.x_pos = .8;
    monster2.y_pos = 2.2;
    
    monster3.x_pos = .1;
    monster3.y_pos = 2.2;
    
    UFO.x_pos = 0.0;
    UFO.y_pos = 1.5;
    UFO.rotation = 0.0;
   
    bonus_star.x_pos = 0.9;
    bonus_star.y_pos = 2.5;
    bonus_star.rotation = 0.0;
    
    monster1.image = space1;
    monster2.image = LoadTexture("monster2.png");
    monster3.image = LoadTexture("monster3.png");
    UFO.image = LoadTexture("UFO.png");
    bonus_star.image = star;
    
    bigGuys.push_back(monster1);
    bigGuys.push_back(monster2);
    bigGuys.push_back(UFO);
     bigGuys.push_back(monster3);
    bigGuys.push_back(bonus_star);
  
   // for (int i = 0; i<bigGuys.size(); i++){
     //   bigGuys[i].direction_x = cos(bigGuys[i].height/bigGuys[i].width);
    //}
  
    
   // someSound = Mix_LoadWAV("file.mp3");
  //  someSound = loadSound("some_wave_file.wav");
     ///Mix_PlayMusic(someSound, -1);
    
    gameover = Mix_LoadMUS( "gameover.mp3");
    music = Mix_LoadMUS( "music.mp3");
    shoot= Mix_LoadWAV("tama1.wav");
    opening = Mix_LoadMUS("01-TitleScreen.mp3");
    coin = Mix_LoadWAV("drop.wav");
    win_music = Mix_LoadMUS("yoin.mp3");
    
    Mix_PlayMusic(opening, -1);
    
    for (int i =0; i < MAX_GUYS; i++ ){
        
        if(index == 6 ) index = 0;
        if (positionX > 0.8) positionX =-0.8;
        // if ( i == 9 ) positionY -= 0.2;
        if ( i % 9 == 0 ) positionY -= 0.2;
        Entity* e1 = new Entity(positionX, positionY, 0.05, 0.05, index, 16,16, true);
        e1->direction_x = 0.3;
        theGuys.push_back(*e1);
        positionX+=0.2;
        
        index++;
        
    }
    
    //produce random numbers
    
    srand(10);
    float random = rand()/100;
    
    
    for (int i =0; i < BIG_GUYS; i++ ){
      
        Entity* b1 = new Entity(random, positionY, 0.05, 0.05, index, 16,16, true);
        theGuys.push_back(*b1);
      //  index++;
        
    }
    

    
    
    for ( int i = 0; i < MAX_BULLETS; i++){
        bullets.push_back(Bullet(gun->x, gun->y, 0.0, 0.05,0.05));
        
    }
    

}



FinalProjectApp::~FinalProjectApp() {
    Cleanup();
    SDL_Quit();
   // Mix_FreeChunk(someSound);
   Mix_FreeMusic(music);
      Mix_FreeMusic(gameover);
}

void FinalProjectApp::Setup() {
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    displayWindow = SDL_CreateWindow("Final Project", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED  , 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    
    
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    
    
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 );
  
    
}

void FinalProjectApp::Update(float elapsed) {
    
    switch(state) {
        case STATE_TITLE_SCREEN:
            UpdateTitleScreen(elapsed);
            break;
        case STATE_GAME_LEVEL:
            UpdateGameLevel(elapsed);
            break;
        case STATE_GAME_OVER:
            UpdateGameOver(elapsed);
            break;
        case STATE_WIN:
            UpdateWin(elapsed);
            break;
        case RULE_LEVEL:
            UpdateRuleLevel(elapsed);
            break;
    }
    
}

void FinalProjectApp::Render() {
    
    
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    switch(state) {
        case STATE_TITLE_SCREEN:
            RenderTitleScreen();
            break;
        case STATE_GAME_LEVEL:
            RenderGameLevel();
            break;
        case STATE_GAME_OVER:
            RenderGameOver();
            break;
        case STATE_WIN:
            RenderWin();
            break;
        case RULE_LEVEL:
            RenderRuleLevel();
            break;
    }
    
    SDL_GL_SwapWindow(displayWindow);
    
    
    
    
    
}




void FinalProjectApp::RenderGameLevel(){
//   displayScore();
    
  
    DrawSprite(bg_image, 0, 0, 0.00, 1.30, 1.0);
    
   
    gun->DrawSprite(gun->gunTexture, gun->x, gun->y, 0.0, 0.05, 0.05);
    
  for (int i =0; i < theGuys.size(); i++ ){
        if ( theGuys[i].visible == true ) {
            
            theGuys[i].DrawSpriteSheetSprite(pacmanTex);
          
        }
    }
    displayScore();
    
    for (int i =0; i < bullets.size(); i++ ){
        
        DrawSprite(bullet1, bullets[i].x, bullets[i].y, 0.0, 0.07, 0.07);
        
    }
    
    for (int i =0; i < bigGuys.size(); i++ ){
    if ( bigGuys[i].visible == true ) {
    DrawSprite(bigGuys[i].image, bigGuys[i].x_pos, bigGuys[i].y_pos, 0, .1, .1);
        if (bounce_X(bigGuys[i])){
            bigGuys[i].direction_y = -(bigGuys[i].direction_y);
            
        }
     }
    
//    DrawSprite(bullet1,0 ,0, 0, 0.07, 0.07);
   
    }
    
}
void FinalProjectApp::RenderTitleScreen(){
    
  
   // playSound(someSound, false);
    
    //REMOVE THESE!!!!↑
    
    DrawSprite(title, 0.0,0.0, 0, 1.0, 1.0);
   //DrawSprite(space1, elapsed*100, elapsed, 0, .3, .3);

    
   // DrawText(font, "Final Project", 0.07f, 0.05f, 0.0f, 0.0f, 1.0f, 1.0f, -.7, .4);
    DrawText(font, "Final Project", 0.07f, 0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -.8, 0.8);
    DrawText(font, "Enter", 0.15f, 0.07f, 0.0f, 1.0f, 1.0f, 1.0f, -0.4, -0.8);
    
    
    
}
void FinalProjectApp::RenderGameOver(){
    
  
    DrawSprite(gameoverimage, 0, 0, 0, .6, 0.6);

    DrawText(font, "GAME OVER", 0.15f, 0.05f, 0.0f, 1.0f, 0.0f, 1.0f, -.8, 0.8);
    DrawText(font, "TRY AGAIN", 0.15f, 0.07f, 0.0f, 0.0f, 1.0f, 1.0f, -0.9, -0.8);
    
    
    
    
}

void FinalProjectApp::UpdateTitleScreen(float elapsed){
    
   //  DrawSprite(space1, 0 , 0, 0, .3, .3);
   
    
    
  //  while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                        done = true;
            
        }
        //if press enter then shows the rule level
        else if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN ) {
                state = 4;
                //Mix_PlayMusic(music, -1);
            }
        }
   // }
}


void FinalProjectApp:: UpdateRuleLevel(float elapsed){
    
    if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
        done = true;
        
    }
    //if press enter then state = 1
    else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE ) {
            state = 1;
           Mix_PlayMusic(music, -1);
        }
    }

    
}


void FinalProjectApp::UpdateWin(float elapsed){
  //  while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        
    else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.scancode == SDL_SCANCODE_RETURN ) {
            state = 0;
           // Mix_PlayMusic(music, -1);
        }
    }
   // }

    
    
    
}
void FinalProjectApp::UpdateGameLevel(float elapsed){
    
//displayScore();
   // DrawSprite(bullet1, bullet[i].x, bullet[i].y, 0.0, 0.5, 0.5);
  
   // Mix_PlayMusic(music, -1);

   // DrawSprite(space1, 0.0 , 0.0, 0, .5, .5);
   
    
     if( MAX_BULLETS <= 0 ){
        state = 2;
        Mix_PlayMusic(gameover, -1);

    }
    
    else if( MAX_BULLETS > 0 && NUM_OF_GUYS_ALIVE == 0){
        state = 3;
       // done = true;
       // play winning sound
        Mix_PlayMusic(win_music, -1);
        
    }
    
    for (int i =0; i < bullets.size(); i++ ){
        bullets[i].y += elapsed;
    }
    
    
    
    
    for(int j =0; j< bullets.size(); j++ ){
        for (int i =0; i < theGuys.size(); i++ ){
            
            if(theGuys[i].checkCollision(bullets[j])){
                if ( theGuys[i].visible == true ) {
                theGuys[i].Kill();
                    NUM_OF_GUYS_ALIVE--;
                score+=100;
                //for the score up sound
                 //   Mix_PlayMusic(coin, 0);
                    Mix_PlayChannel(0, coin, 0);

                }
            }
        }
        
    }
    
   
  
    //I want the characters to move around....
    /*if ( x_pos >= 1.0 ) {
     direction_x = -direction_x;
     }
     if ( x_pos <= -1.0 ) {direction_x = -direction_x;}
     
     x_pos += direction_x * speed * elapsed;*/

     //   theGuys[i].Move(elapsed);
        //if ( theGuys[i].visible == true ) {
           /* if(i >= 0 && i < 9 ) theGuys[i].Move(elapsed*1.1);
            if(i >= 9 && i < 18 ) theGuys[i].Move(elapsed*0.8);
            if(i >= 18 && i < 27 ) theGuys[i].Move(elapsed*1.7);
            if(i >= 27 && i < 36 ) theGuys[i].Move(elapsed*0.5);
            if(i >= 36 && i < 45 ) theGuys[i].Move(elapsed*1.3);
      //      theGuys[i].DrawSpriteSheetSprite(pacmanTex);*/
      //  }

    
    for (int i =0; i < bigGuys.size(); i++ ){
       if(i%2 == 0 ){
    bigGuys[i].x_pos+= elapsed/10;
   bigGuys[i].y_pos-= elapsed/10;
        }
        if(i%2 == 1 ){
            bigGuys[i].x_pos-= elapsed/10;
            bigGuys[i].y_pos-= elapsed/10;
        }
        
        // bigGuys[i].x_pos += elapsed*distance_to_travel_in_one_second*bigGuys[i].direction_x;
    }
    
   /* for (int i =0; i< theGuys.size(); i++){
        if(i >= 0 && i < 9 ){
            
        theGuys[i].x_pos += elapsed*0.5;
        
        if ( theGuys[i].x_pos >= 1.0 ) { theGuys[i].direction_x = theGuys[i].direction_x; }
        if ( theGuys[i].x_pos <= -1.0 ) {theGuys[i].direction_x = -theGuys[i].direction_x;}
        
        theGuys[i].x_pos += theGuys[i].direction_x * theGuys[i].speed * elapsed;
            
        }
        //if(i >= 0 && i < 9 ) theGuys[i].Move(elapsed);
    }
    */
    
    for(int j =0; j< bullets.size(); j++ ){
         for (int i =0; i < bigGuys.size(); i++ ){
            if(bigGuys[i].checkCollision(bullets[j])){
                
            
                if ( bigGuys[i].visible == true ) {
                    bigGuys[i].Kill();
                    score+= 50;
                    
                    for ( int i = 0; i <= 5; i++){
                        bullets.push_back(Bullet(gun->x, gun->y, 0.0, 0.05,0.05));
                        
                    }
                    MAX_BULLETS+=5;

                    //if the big monster is shot, 5+ BULLETS!!!
                }
            }
            }
        }
    

    

    

    
}
void FinalProjectApp::UpdateGameOver(float elapsed){
    
  //  while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
 //   }
}


bool FinalProjectApp::UpdateAndRender() {
    
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
   
    ProcessEvents();
    
    FixedUpdate();
    
    
    Update(elapsed);
    Render();
    return done;
    
    
}


void FinalProjectApp::ProcessEvents() {
    // our SDL event loop
    // check input events
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        } else if (event.type == SDL_KEYDOWN ){
            
            if(event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
              //  if ( gun->x > -1.0 ){
                gun->x -= 0.015;
                 gun->acceleration_x = -.4f;
//                bullets[count].x = gun->x;
                //}
                
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                
                gun->x += 0.015;
                 gun->acceleration_x = .4f;
//                bullets[count].x = gun->x;
                
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
                
                bullets[count].y = gun->y;
                bullets[count].x = gun->x;
               count++;
               MAX_BULLETS--;
                //shooting sound
              //  Mix_PlayMusic(shoot, -1);
                Mix_PlayChannel(1, shoot, 0);
            }
            
            
        } else if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_Q ) {
                state = 2;
                Mix_PlayMusic(gameover, -1);
                //Mix_PlayMusic(gameover, -1);
            }
        }
        
    }

    
}

void FinalProjectApp::Cleanup() {
    // cleanup joysticks, textures, etc.
}


GLuint FinalProjectApp::LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    return textureID;
}


void FinalProjectApp::FixedUpdate(){
    
    gun->FixedUpdate();
    gun->velocity_x -=  FIXED_TIMESTEP * GRAVITY;
     gun->x += gun->velocity_x * FIXED_TIMESTEP;
}



int FinalProjectApp::loadSound(const char *soundFile) {
    Uint8 *buffer;
    SDL_AudioSpec spec;
    Uint32 bufferSize;
    if(SDL_LoadWAV(soundFile, &spec, &buffer, &bufferSize) == NULL) {
        return -1; }
    SDL_AudioCVT cvt;
   // SDL_BuildAudioCVT(&cvt, spec.format, spec.channels, spec.freq, deviceSpec.format, deviceSpec.channels, deviceSpec.freq);
    cvt.len = bufferSize;
    cvt.buf = new Uint8[bufferSize * cvt.len_mult];
    memcpy(cvt.buf, buffer, bufferSize);
    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(buffer);
    MixerSound sound;
    sound.buffer = cvt.buf;
    sound.length = cvt.len_cvt;
    sound.loaded = true;
    sound.offset = 0;
    //sound.format = deviceSpec.format;
    sound.volume = 1.0;
    sound.playing = false;
    mixSounds.push_back(sound);
    return mixSounds.size()-1;
}

void FinalProjectApp::appAudioCallback(void *userdata, Uint8 *stream, int len) {
    FinalProjectApp *app = (FinalProjectApp*) userdata;
    float *mixBuffer = new float[len/4];
    memset(stream, 0, len);
    memset(mixBuffer, 0, len);
    int numSoundsMixed = 0;
    for(
        int i=0; mixSounds.size(); i++) {
        MixerSound *sound = &app->mixSounds[i];
        if(sound->loaded && sound->playing) {
            for(int s=0; s < len/4; s++) {
                float *sourceBuffer = (float*) (sound->buffer+sound->offset);
                mixBuffer[s] += (sourceBuffer[s] * sound->volume);
            }
            numSoundsMixed++;
            sound->offset += len;
            if(sound->offset >= sound->length-len) {
                if(sound->loop) {
                    sound->offset = 0;
                } else {
                    sound->playing = false;
                }
            } }
    }
    if(numSoundsMixed > 0) {
        for(int s=0; s < len/4; s++) {
            ((float*)stream)[s] = mixBuffer[s] / (float)numSoundsMixed;
        }
    }
    free(mixBuffer);
}


void FinalProjectApp::playSound(int soundIndex, bool loop) {
    if(soundIndex >= 0 && soundIndex < mixSounds.size()) {
        mixSounds[soundIndex].playing = true;
        mixSounds[soundIndex].offset = 0;
        mixSounds[soundIndex].loop = loop;
    }
}

void FinalProjectApp::DrawSprite(GLint texture, float x, float y, float rotation, float w, float h) {
    
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    //image size quad[]
    
    //definiting the image size by the coordinate from the parameter
    GLfloat quad[] = {-w, h, -w, -h, w, -h, w, h};
    
    glVertexPointer(2, GL_FLOAT, 0, quad);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    
    // GLfloat quadUVs[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    //enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
    
    
}
void FinalProjectApp::DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x_pos, float y_pos) {
    
    glLoadIdentity();
    glTranslatef(x_pos, y_pos, 0.0);
    
    
    
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float texture_size = 1.0/16.0f;
    vector<float> vertexData;
    vector<float> texCoordData;
    vector<float> colorData;
    for(int i=0; i < text.size(); i++) {
        float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
        float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
        colorData.insert(colorData.end(), {r,g,b,a, r,g,b,a, r,g,b,a, r,g,b,a});
        vertexData.insert(vertexData.end(), {((size+spacing) * i) + (-0.5f * size), 0.5f * size, ((size+spacing) * i) +
            (-0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), 0.5f
            * size});
        
        
        texCoordData.insert(texCoordData.end(), {texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
            texture_size, texture_y + texture_size, texture_x + texture_size, texture_y});
        
        
    }
    
    
    
    
    glColorPointer(4, GL_FLOAT, 0, colorData.data());
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glDrawArrays(GL_QUADS, 0, text.size() * 4);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void FinalProjectApp::displayScore(){
   // void displayScore(int score, GLuint font){
        
    
    string scoreText ="Current Score: ";
    string scoreString = to_string(score);
    scoreText = scoreText+" " + scoreString;
    DrawText(font, scoreText, 0.06f, 0.02f, 1.0f, 1.0f, 0.0f, 1.0f, -.8, 0.87);
    
    string bulletText = "#Bullet: ";
    string numOfBullet = to_string(MAX_BULLETS);
    string text = bulletText + ""  + numOfBullet;
    DrawText(font, text, 0.05f, 0.02f, 0.0f, 1.0f, 1.0f, 1.0f, .3, -0.87);
 
}

void FinalProjectApp::RenderWin(){
    DrawSprite(bg_image, 0, 0, 0.00, 1.30, 1.0);

   
    DrawSprite(star, 0.0f,0.0f , sin(1/2), .9, 0.9);
    DrawSprite(youwin, 0.0f,0.6f , 0.0f, .9, 0.5);
    
    
    string scoreText ="Your Score";
    string scoreString = to_string(score);
    //scoreText = scoreText+" " + scoreString;
    DrawText(font, scoreText, 0.1f, 0.02f, 1.0f, 0.0f, 0.0f, 1.0f, -0.5, 0.0);
    DrawText(font, scoreString, 0.1f, 0.02f, 1.0f, 0.0f, 0.0f, 1.0f, -0.2, -.2);

    
    
    DrawText(font, "PRESS ENTER TO REPLAY", 0.09f, 0.02f, 0.0f, 1.0f, 1.0f, 1.0f, -1.1, -0.6);

    
    }

void FinalProjectApp::RenderRuleLevel(){
    string maxBullets = to_string(MAX_BULLETS);
    string rule1 = "YOU HAVE " + maxBullets + " OF BULLETS INITIALLY. ";
    string rule2 = "IF YOU KILL THE LITTLE MONSTERS, YOU EARN 100 POINTS EACH";
    string rule3 = "IF YOU KILL THE BIGGER MONSTERS, YOU GAIN 5+ BULLETS";
    string rule4 = "WHEN YOU RUN OUT OF BULLETS, YOU AUTOMATICALLY LOSE";
    string rule5 = "PRESS SPACE KEY TO SHOOT THE BULLETS";
    string rule6 = "PRESS SPACE TO START";
    
    DrawText(font, rule1, 0.03f, 0.01f, 1.0f, 1.0f, 1.0f, 1.0f, -1.2, 0.7);
     DrawText(font, rule2, 0.03f, 0.01f, 0.0f, 0.0f, 1.0f, 1.0f, -1.2, 0.5);
    DrawText(font, rule3, 0.03f, 0.01f, 0.0f, 1.0f, 0.0f, 1.0f, -1.2, 0.3);
    DrawText(font, rule4, 0.03f, 0.01f, 1.0f, .0f, 1.0f, 1.0f, -1.2, 0.1);
    DrawText(font, rule5, 0.03f, 0.01f, 1.0f, 1.0f, 0.0f, 1.0f, -1.2, -.1);
    DrawText(font, rule6, 0.04f, 0.01f, 0.0f, 0.0f, 1.0f, 1.0f, -1.2, -.3);
    
}

bool FinalProjectApp::bounce_X(Entity entity){
    /*
     if (ball.y + (ball.theSize_y * 0.5) > 1.00 && ball.x < 1.33 && ball.x > -1.33) {
     return true;
     }
     if (ball.y - (ball.theSize_y * 0.5) < -1.00 && ball.x < 1.33 && ball.x > -1.33) {
     return true;
     }
     
     return false;*/
    
    if (entity.x_pos + (entity.width * 0.5) > 1.33  ) {
        return true;
    }
    
    if (entity.x_pos - (entity.width * 0.5) < -1.33 ) {
        return true;
    }
    
    return false;
    
};


