#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

class Explosion {
private:
    int x, y, radius, duration;
    unsigned int dt;

public:
    Explosion(int _x, int _y, int _radius, int _duration);
    void updateDuration();
    int getDuration();
    int getX();
    int getY();
    int getRadius();
    void setTime(unsigned int _dt);
};

#endif // EXPLOSION_H_INCLUDED
