#include <vector>

#include "object.h"
#include "camera.h"
#include "light.h"

class Renderer{

    private:
        Renderer(){}
        ~Renderer(){}

        static void normalizeExposure(std::vector<color>& imageBuffer);
        static color getSample(int x, int y, const std::vector<Object*>& objects, const std::vector<LightSource*>& lights, const Camera& camera);

    public:

        static void renderToImage(unsigned char* imageData, int imageChannels,
                           const std::vector<Object*>& objects, const std::vector<LightSource*>& lights, const Camera& camera);

};