#include "objects/object.h"

#include <vector>

class Scene{

    public:
        std::vector<Object*> objects;
        std::vector<Object*> lights;

    public:
        Scene();
        ~Scene();

        void addObject(Object* obj);
        void removeObject(Object* obj);

        void addLight(Object* obj);
        void removeLight(Object* obj);

        inline std::vector<Object*>& getLights(){
            return lights;
        }

        Object* operator[](int i);
        inline std::vector<Object*>::iterator begin(){ return objects.begin();}
        inline std::vector<Object*>::iterator end(){return objects.end();}
        inline int size(){return objects.size();}


};