#include "objects/object.h"

#include <vector>

class Scene{

    public:
        std::vector<Object*> objects;

    public:
        Scene();
        ~Scene();

        void addObject(Object* obj);
        void removeObject(Object* obj);

        Object* operator[](int i);
        inline std::vector<Object*>::iterator begin(){ return objects.begin();}
        inline std::vector<Object*>::iterator end(){return objects.end();}
        inline int size(){return objects.size();}


};