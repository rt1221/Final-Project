//
//  MixerSound.h
//  NYUCodebase
//
//  Created by Risa Teshigawara on 4/29/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__MixerSound__
#define __NYUCodebase__MixerSound__

#include <stdio.h>
#include <SDL_mixer.h>

class MixerSound{
public:
    Uint32 offset;
    Uint32 length;
    Uint8 *buffer;
    float volume;
    SDL_AudioFormat format;
    bool loaded;
    bool playing;
    bool loop;
    
    
};





#endif /* defined(__NYUCodebase__MixerSound__) */
