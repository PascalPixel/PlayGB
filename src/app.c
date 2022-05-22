//
//  app.c
//  PlayGB
//
//  Created by Matteo D'Ignazio on 14/05/22.
//

#include "app.h"
#include "game_scene.h"
#include "library_scene.h"
#include "preferences.h"

PGB_Application *PGB_App;

void PGB_init() {
    
    PGB_App = pgb_malloc(sizeof(PGB_Application));
    
    PGB_App->scene = NULL;
    PGB_App->pendingScene = NULL;
    
    playdate->file->mkdir("games");
    playdate->file->mkdir("saves");
    
    prefereces_init();
    
    PGB_App->bodyFont = playdate->graphics->loadFont("fonts/Roobert-11-Medium", NULL);
    PGB_App->titleFont = playdate->graphics->loadFont("fonts/Roobert-20-Medium", NULL);
    PGB_App->subheadFont = playdate->graphics->loadFont("fonts/Asheville-Sans-14-Bold", NULL);
    PGB_App->labelFont = playdate->graphics->loadFont("fonts/Nontendo-Bold", NULL);
    
    PGB_LibraryScene *libraryScene = PGB_LibraryScene_new();
    PGB_present(libraryScene->scene);
}

void PGB_update() {
    
    if(PGB_App->scene != NULL){
        void *managedObject = PGB_App->scene->managedObject;
        PGB_App->scene->update(managedObject);
    }
    
    if(PGB_App->pendingScene != NULL){
        // present pending scene
        
        if(PGB_App->scene != NULL){
            prefereces_save_to_disk();
            
            void *managedObject = PGB_App->scene->managedObject;
            PGB_App->scene->free(managedObject);
        }
        
        PGB_App->scene = PGB_App->pendingScene;
        PGB_App->pendingScene = NULL;
        
        playdate->system->removeAllMenuItems();
        PGB_App->scene->menu(PGB_App->scene->managedObject);
        
        playdate->display->setRefreshRate(PGB_App->scene->preferredFrameRate);
    }
}

void PGB_present(PGB_Scene *scene) {
    
    PGB_App->pendingScene = scene;
}

void PGB_quit() {
    
    prefereces_save_to_disk();
    
    if(PGB_App->scene != NULL){
        void *managedObject = PGB_App->scene->managedObject;
        PGB_App->scene->free(managedObject);
    }
    
    pgb_free(PGB_App);
}
