//
//  Gun.cpp
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "Gun.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <string>
#include<vector>
#include "Entity.h"


Gun::Gun(float x, float y, float angle, float w, float h ):
x(x),y(y),angle(angle),w(w),h(h){};

float Gun::lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}


void Gun::FixedUpdate(){
    
    velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
    //  velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);
    velocity_x += acceleration_x * FIXED_TIMESTEP;
    //  velocity_y += acceleration_y * FIXED_TIMESTEP;
    
    
    
}



void Gun::draw(){

    
    
    
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, gunTexture);
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
        glTranslatef(x, y, 0.0);
   //     glRotatef(rotation, 0.0, 0.0, 1.0);
        
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
        
        
  //      glDrawArrays(GL_QUADS, 0, 4);
        glDisable(GL_TEXTURE_2D);
        
        

    
    
};

void Gun::DrawSprite(GLint texture, float x, float y, float rotation, float w, float h) {
    
    
    
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


