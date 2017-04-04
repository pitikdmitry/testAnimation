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
//    void move(int directionParam);
//    void jump();
//    void idle();
    void setPhysicsBody();

//    void update();

private:
    bool is_onGround;
    PhysicsBody* physicsBody;
    ~Player();
//    bool moving;

//    int direction;
//    Sprite* sprite;

    void initPlayer();
};

#endif /* PLAYER_H_ */