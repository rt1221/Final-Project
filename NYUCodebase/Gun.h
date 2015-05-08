//
//  Gun.h
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__Gun__
#define __NYUCodebase__Gun__


#include <stdio.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>

#include "Entity.h"
#include "SheetSprite.h"
#define FIXED_TIMESTEP 0.16666f

using namespace std;


class Gun {
public:
    
    Gun(float x, float y, float angle, float w, float h);
    
 //   void Shoot();
    
    void draw();
    void DrawSprite(GLint texture, float x, float y, float rotation, float w, float h);
    
    float x;
    float y;
    float angle;
    float w;
    float h;
    
    float acceleration_x;
    float friction_x;
    float velocity_x;
    
    GLuint gunTexture;
    
    float lerp(float v0, float v1, float t);
    
    
    void FixedUpdate();

    
    
    
};


#endif /* defined(__NYUCodebase__Gun__) */
