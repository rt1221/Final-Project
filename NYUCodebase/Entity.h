//
//  Entity.h
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__Entity__
#define __NYUCodebase__Entity__

#include <stdio.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>
#include <SDL_mixer.h>
#include "Bullet.h"
#include "SheetSprite.h"

using namespace std;
class Bullet;
class Entity {
public:
    
    //constructor for entity
   // Entity(float x_pos = 0.0, float y_pos=0.0, float width=0.0, float height=0.0, float index=0,bool visible=true, GLuint textureID = 0);
    
    Entity(float x_pos= 0.0, float y_pos= 0.0, float width= 0.0, float height= 0.0, float index= 0.0, int spriteY= 0, int spriteX= 0, bool visible=true);
    
    
    void DrawSpriteSheetSprite(GLuint textureID);
    
    //void DrawSheet(float scale);
    
    void DrawSprite(GLuint texture, float x, float y, float rotation, float w, float h);
    
    void Kill();
    void Update(float elapsed);
    void Render();
    void FixedUpdate();
    
    void Move(float elapsed);

    bool checkCollision(Bullet bullet);
    //Why is it unknown type...
    
    
    
    GLuint LoadTexture(const char *image_path);
    
  //  GLuint textureID;
    SheetSprite sprite;
    float x_pos;
    float y_pos;
    float width;
    float height;
    float velocity_x;
    float velocity_y;
    float gravity_x;
    float gravity_y;
    float direction_y;
    float spriteIndex;
    int spriteTexture;
    int index;
    int spriteX;
    int spriteY;
    float rotation;
    
    float acceleration_x;
    float acceleration_y;
    float friction_x;
    float friction_y;
    float mass;
    bool isStatic;
    bool enableCollisions;

    bool visible;
    
    float direction_x;
  //  float direction_y;
    float speed;
    float scale;

    GLuint image;
    
};

#endif /* defined(__NYUCodebase__Entity__) */
