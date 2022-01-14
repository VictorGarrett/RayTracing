#include "objects/object.h"


class ObjectBuilder{

    private:
        Material* objMaterial;
        Primitive* objShape;

    public:
        ObjectBuilder();
        ~ObjectBuilder();

        void setPrimitiveSphere(point position, float radius);
        void setPrimitivePlane(point position, vec3f normal);
        void setMaterial(color matColor, float specular, float diffuse, float shininess);

        Object* getObject();
};