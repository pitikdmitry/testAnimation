#ifndef PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"
#include "definitions.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
    Animate * idleAnimate;
    Animate * moveAnimate;
    Animate * run_fireAnimate;
    Animate * jumpAnimate;
    Animate * deathAnimate;
    Animate * flyingAnimate;
    Animate * shootingAnimate;
    Animate * stay_with_gunAnimate;
    Animate * jump_fireAnimate;
    static Player* create( );

    void move();
    void jump();
    void idle();
    void die();
    void fly();
    void shoot();
    void run_fire();
    void stay_with_gun();
    void jump_fire();
    bool moving;
    bool jumping;
    bool idling;

    bool death;
    bool jetpack;
    enum{ idling_anim, moving_anim, jumping_anim, death_anim, shoot_stay_anim, run_fire_anim, stay_with_gun_anim, jump_fire_anim } current_anim;
    enum{ staying, flying } jetpack_anim;
    int direction;
    int speed;
    bool key_A;
    bool key_D;

    void update( );
    bool is_onGround;
    bool shooting;

    ~Player();
    unsigned int timer;

    virtual void initPlayer() = 0;
protected:
    PhysicsBody* moveBody;
    PhysicsBody* idleBody;

};

#endif /* PLAYER_H_ */