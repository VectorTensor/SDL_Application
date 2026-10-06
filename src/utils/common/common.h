
#ifndef SPRITEANIMATION_COMMON_H
#define SPRITEANIMATION_COMMON_H

inline int REFERENCE_X = 960;
inline int REFERENCE_Y = 640;

struct Transform {
    float x;
    float y;
    float w;
    float h;
};

struct Transform2 {
    float x = 0.0f;
    float y = 0.0f;
};

#endif // SPRITEANIMATION_COMMON_H
