//
//  scene.h
//  PlayGB
//
//  Created by Matteo D'Ignazio on 14/05/22.
//

#ifndef scene_h
#define scene_h

#include <stdio.h>
#include "utility.h"

typedef struct PGB_Scene {
    void *managedObject;
    
    unsigned int preferredFrameRate;
    
    void(*update)(void *object);
    void(*menu)(void *object);
    void(*free)(void *object);
} PGB_Scene;

PGB_Scene* PGB_Scene_new(void);

void PGB_Scene_update(void *scene);
void PGB_Scene_free(void *scene);

#endif /* scene_h */
