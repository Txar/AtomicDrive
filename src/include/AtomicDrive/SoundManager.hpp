#pragma once
#include "SFML/Audio.hpp"
#include <math.h>
#include <iostream>

class SoundManager {
    public:
        class volumeSound {
            public:
                float volume;
                sf::SoundBuffer *buffer;
                int x, y;
                bool isGlobal;
                volumeSound(float volume, sf::SoundBuffer *buffer)
                : volume(volume), buffer(buffer), isGlobal(true) {}

                volumeSound(float volume, sf::SoundBuffer *buffer, int x, int y) 
                : volume(volume), buffer(buffer), x(x), y(y), isGlobal(false) {}
        };

        static sf::SoundBuffer car_crash;
        static sf::SoundBuffer engine_1;

        std::vector<volumeSound> soundQueue;
        sf::Sound sound;

        void initialize() {
            car_crash.loadFromFile("assets/car_crash.wav");
            engine_1.loadFromFile("assets/engine_1.wav");
        }

        void playSounds(int cameraCenterX, int cameraCenterY) {
            for (volumeSound vs : soundQueue) {
                sound.setBuffer(*vs.buffer);
                if (vs.isGlobal) {
                    sound.setVolume(vs.volume*100.0);
                    sound.play();
                }
                else {
                    float volume = vs.volume;
                    float dist = sqrt((vs.x - cameraCenterX)*(vs.x - cameraCenterX) + (vs.y - cameraCenterY)*(vs.y - cameraCenterY));
                    float maxDist = 64 * 16;

                    //std::cout << dist << "\n";
                    if (dist > maxDist) continue;

                    volume = volume * (1.0 - dist/maxDist);
                    if (volume <= 0) continue;
                    
                    sound.setVolume(volume*100.0);
                    sound.play();
                }
            }
            soundQueue.clear();
        }

        void playSound(sf::SoundBuffer &sound, float volume) {
            soundQueue.push_back(volumeSound(volume, &sound));
        }

        void playSound(sf::SoundBuffer &sound, float volume, int x, int y) {
            soundQueue.push_back(volumeSound(volume, &sound, x, y));
        }
};