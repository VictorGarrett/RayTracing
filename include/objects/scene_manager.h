#pragma once

#include "objects/scene.h"
#include <unordered_map>

class SceneManager{

    private:
        std::unordered_map<const char*, Scene*> loadedScenes;
    
    public: 
        SceneManager();
        ~SceneManager();

        Scene* getScene(const char* path);


};