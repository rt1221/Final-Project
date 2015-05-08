//
//  Bullet.h
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__Bullet__
#define __NYUCodebase__Bullet__

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

using namespace std;


class Bullet {
public:
    
    Bullet(float x, float y, float angle, float w, float h , bool shoot=  false);
    
    void Shoot();
    
    void draw();
    
    float x;
    float y;
    float angle;
    float w;
    float h;
    bool shoot;
    vector<Bullet*> bullets;
    GLuint bullet;
    
    
    //float bullet_y = gun_y;
   // int unused_bullets = MAX_BULLETS;
    

    
    
};


#endif /* defined(__NYUCodebase__Bullet__) */
