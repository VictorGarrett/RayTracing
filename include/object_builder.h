#include "object.h"


class ObjectBuilder{

    private:
        Material* objMaterial;
        Primitive* objShape;

    public:
        ObjectBuilder();
        ~ObjectBuilder();

        void setPrimitiveSphere(point position, float radius);
        void setPrimitivePlane(point position, vec3f normal);
        void setMaterialColor(color matColor);

        Object* getObject();
};