#include "math/random.h"

Random::Random(uint64_t seed): state(seed){
    
}
Random::~Random(){

}

uint64_t Random::next(){
    state ^= state >> 12;
    state ^= state << 25;
    state ^= state >> 27;

    return state * 2685821657736338717ull;
}