#include <cstdlib>  

float generateRandom(float min, float max)
{
    float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return min + t * (max - min);
}
