#pragma once
#include "SFML/Graphics.hpp"
#include "math.h"

class Math {
    public:
        static const float PI;
        static const float DEG_TO_RAD;

        static sf::Vector2i iRotateAroundOrigin(int x, int y, float deg) {
            int _x = x*cos(deg) - y*sin(deg);
            int _y = y*cos(deg) + x*sin(deg);
            return {_x, _y};
        }

        static sf::Vector2f fRotateAroundOrigin(float x, float y, float deg) {
            float _x = x*cos(deg) - y*sin(deg);
            float _y = y*cos(deg) + x*sin(deg);
            return {_x, _y};
        }

        static float intersection(float a, float b, float c, float d) {
            return (d - b) / (a - c);
        }

        static float slope(float Ax, float Ay, float Bx, float By) {
            return (By - Ay) / (Bx - Ax);
        }

        static float origin(float Ax, float Ay, float slope) {
            return Ay - Ax * slope;
        }

        static float distance(int x, int y, int x2, int y2) {
            return sqrt((float)(x - x2)*(x - x2) + (y - y2)*(y - y2));
        }

        static sf::Vector2f slopeAndOrigin(float Ax, float Ay, float Bx, float By) {
            float slope = Math::slope(Ax, Ay, Bx, By);
            return {slope, origin(Ax, Ay, slope)};
        }
};