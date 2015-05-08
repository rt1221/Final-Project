#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Entity.h"
#include "FinalProjectApp.h"

#include "Bullet.h"
#include <SDL_mixer.h>

int main(){
    
    FinalProjectApp f1;
    while(!f1.UpdateAndRender()){}
    
    return 0;
    
}
