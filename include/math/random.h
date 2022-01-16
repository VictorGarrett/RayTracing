#include <stdint.h>


class Random{

    private:
        uint64_t state;
    
    public:
        Random(uint64_t seed);
        ~Random();

        uint64_t next();

        inline double dUnif(){
            return next()/(double)UINT64_MAX;
        }

};
