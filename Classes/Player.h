#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class Player:public cocos2d::Sprite {
public:
    Animate * idleAnimate;
    Animate * moveAnimate;
    Animate * jumpAnimate;

    static Player* create( );
    void move(int directionParam);
    void jump();
    void idle();
    void setPhysicsBody();
    bool moving;
    bool jumping;
    bool idling;

    void update();

//    void set_is_onGround(bool b){ is_onGround = b; }
    bool is_onGround;
private:

    PhysicsBody* physicsBody;
    ~Player();

    int direction;
//    Sprite* sprite;

    void initPlayer();
};

#endif /* PLAYER_H_ */