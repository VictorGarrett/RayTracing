#include "objects/object.h"


class ObjectBuilder{

    private:
        Material* objMaterial;
        Primitive* objShape;
        bool isLightSource;

    public:
        ObjectBuilder();
        ~ObjectBuilder();

        void setPrimitiveSphere(point position, float radius);
        void setPrimitivePlane(point position, vec3f normal);
        void setMaterial(color matColor, color emiColor);
        void setLightSource(bool isLightSource);

        Object* getObject();
};