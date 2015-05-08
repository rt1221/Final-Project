//
//  Bullet.cpp
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "Bullet.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>
#include "Entity.h"

    
Bullet::Bullet(float x, float y, float angle, float w, float h , bool shoot):
    x(x),y(y),angle(angle),w(w),h(h){
   
    
    };
    
void Bullet::Shoot(){
        
        for (int i =0; i < bullets.size(); i++ ){
            if( bullets[i]->shoot == true ) { bullets[i]->draw(); }
        }
        
        
    }
    
    
void Bullet::draw(){
        
        glLoadIdentity();
        glTranslatef(x, y, 0.0);
        glRotatef(angle, 0.0, 0.0, 1.0);
        
        
        //  GLfloat quad[] = {-x, y, -x, -y, x, -y, x, y};
        GLfloat quad[] = {-w, h, -w, -h, w, -h, w, h};
        glVertexPointer(2, GL_FLOAT, 0, quad);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_QUADS, 0, 4);
        
        //  GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
        //glTexCoordPointer(2, GL_QUADS, 0, quadUVs);
        
        
    }
    
