//
//  SheetSprite.h
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__SheetSprite__
#define __NYUCodebase__SheetSprite__



#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>
#include "SheetSprite.h"

using namespace std;


class SheetSprite {
public:
    
    SheetSprite();
    SheetSprite(unsigned int textureID, float u, float v, float width, float height);
    void Draw(float scale);
    void DrawSpriteSheetSprite(GLuint textureID,int  spriteCountX, int spriteCountY, int index);
    float scale;
    unsigned int textureID;
    float x;
    float y;
    float u;
    float v;
    float width;
    float height;
    
};



#endif /* defined(__NYUCodebase__SheetSprite__) */
