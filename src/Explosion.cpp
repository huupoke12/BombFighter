#include "Explosion.h"

Explosion::Explosion(int _x, int _y, int _radius, int _duration) {
    x = _x;
    y = _y;
    radius = _radius;
    duration = _duration;
}

void Explosion::updateDuration() {
    duration -= dt;
}

int Explosion::getDuration() {
    return duration;
}

int Explosion::getX() {
    return x;
}
int Explosion::getY() {
    return y;
}
int Explosion::getRadius() {
    return radius;
}

void Explosion::setTime(unsigned int _dt) {
    dt = _dt;
}
