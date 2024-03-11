#pragma once

#include "SFML/Graphics.hpp"

class Animator {
    public:
        int frame = 0;
        int frames;
        float speed;
        bool pingpong;
        bool animated;
        int width;
        int height;
        float progress = 0.0;
        bool reverse = false;

        Animator(int _width, int _height, int amount_of_frames, float _speed = 1.0, bool _pingpong = false);
};