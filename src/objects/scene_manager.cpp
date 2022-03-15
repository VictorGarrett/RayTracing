#include "objects/scene_manager.h"
#include "objects/object_builder.h"
#include "yaml-cpp/yaml.h" 
#include <string>   

SceneManager::SceneManager(){

}

SceneManager::~SceneManager(){
    for(auto i = loadedScenes.begin(); i != loadedScenes.end(); i++){
        delete i->second;
    }
}

Scene* SceneManager::getScene(const char* path){

    ObjectBuilder objBuilder;
    Scene* newScene = new Scene();

    YAML::Node sceneNode = YAML::LoadFile(path);

    for(auto i = sceneNode.begin(); i != sceneNode.end(); i++){
        
        if(i->second["primitive"]["type"].as<std::string>() == "sphere"){
            objBuilder.setPrimitiveSphere({
                                            i->second["primitive"]["position"][0].as<float>(),
                                            i->second["primitive"]["position"][1].as<float>(),
                                            i->second["primitive"]["position"][2].as<float>()
                                          },
                                            i->second["primitive"]["radius"].as<float>());
        }
        else if(i->second["primitive"]["type"].as<std::string>() == "plane"){
            objBuilder.setPrimitivePlane({
                                            i->second["primitive"]["position"][0].as<float>(),
                                            i->second["primitive"]["position"][1].as<float>(),
                                            i->second["primitive"]["position"][2].as<float>()
                                          },
                                          {
                                            i->second["primitive"]["normal"][0].as<float>(),
                                            i->second["primitive"]["normal"][1].as<float>(),
                                            i->second["primitive"]["normal"][2].as<float>()
                                          });
        }


        objBuilder.setMaterial({
                                i->second["material"]["color"][0].as<float>(), 
                                i->second["material"]["color"][1].as<float>(),
                                i->second["material"]["color"][2].as<float>()
                               },
                               { 
                                i->second["material"]["emissive"][0].as<float>(),
                                i->second["material"]["emissive"][1].as<float>(),
                                i->second["material"]["emissive"][2].as<float>()
                               }
                              );

        objBuilder.setLightSource(i->second["light"].as<bool>());

        Object* obj = objBuilder.getObject();
        newScene->addObject(obj);

        if(i->second["light"].as<bool>())
          newScene->addLight(obj);
    }
    loadedScenes.insert({path, newScene});

    return newScene;
}
