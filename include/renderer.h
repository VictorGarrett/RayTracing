#include <vector>

#include "primitives.h"
#include "camera.h"
#include "light.h"

class Renderer{

    private:
        Renderer(){}
        ~Renderer(){}

        static const color getSample(int x, int y, const std::vector<Primitive*>& objects, const std::vector<LightSource*>& lights, const Camera& camera);

    public:

        static void renderToImage(unsigned char* imageData, int imageChannels,
                           const std::vector<Primitive*>& objects, const std::vector<LightSource*>& lights, const Camera& camera);

};