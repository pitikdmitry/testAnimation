#ifndef TEAMSTRIKE_BULLET_H
#define TEAMSTRIKE_BULLET_H

#include "definitions.h"
#include "Player.h"
#include "cocos2d.h"
USING_NS_CC;

class Bullet : public cocos2d::Sprite {
public:
    static Bullet* create( const Player* player );
    int getDamage();

private:
    bool life;

    Bullet();
    ~Bullet();

    void initOptions( const Player* player );
//    void addEvents();

private:
    int _damage;
    float _maxSpeed;
    Vec2 _currentSpeed;
};


#endif //TEAMSTRIKE_BULLET_H