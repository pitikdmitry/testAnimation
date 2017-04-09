#include <iostream>
#include "Blonde_player.h"
#include "definitions.h"

Player* Blonde_player::create( )
{
    Player * blonde_player = new Blonde_player( );
    if( blonde_player && blonde_player->initWithFile ("1/Idle_001.png" ) )
    {
        blonde_player->autorelease( );
        return blonde_player;
    }

    CC_SAFE_DELETE( blonde_player );
    return NULL;
}

void Blonde_player::initPlayer()
{
    death = false;
    moving = false;
    jumping = false;
    idling = true;
    shooting = false;
    is_onGround = false;
    jetpack = false;
    timer = 0;
    direction = 1;
    speed = 0;
    char str[100] = {0};

    Vector<SpriteFrame*> idleAnimFrames(12);//не забывать менять
    for(int i = 0; i <= 11; i++)
    {
        if( i < 10){
            sprintf(str, "1/Idle_00%i.png",i);
        }
        else{
            sprintf(str, "1/Idle_0%i.png",i);
        }
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        idleAnimFrames.pushBack(frame);
    }
    auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.3f);
    idleAnimate = Animate::create(idleAnimation);
    idleAnimate->retain();
    this->runAction(RepeatForever::create(idleAnimate));

    idleBody = PhysicsBody::createBox(Size(70.0f,153.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    idleBody->setCollisionBitmask( PLAYER_BITMASK );
    idleBody->setContactTestBitmask( true );
    idleBody->setDynamic(true);
    idleBody->setGravityEnable( true );
    idleBody->setRotationEnable( false );
    addComponent( idleBody );

    Vector<SpriteFrame*> moveAnimFrames(8);
    for(int i = 0; i <= 7; i++)
    {
        sprintf(str, "1/Run_00%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        moveAnimFrames.pushBack(frame);
    }
    auto moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.06f);
    moveAnimate = Animate::create(moveAnimation);
    moveAnimate->retain();

    Vector<SpriteFrame*> move_fireAnimFrames(8);
    for(int i = 0; i <= 7; i++)
    {
        sprintf(str, "1/RunWithGun_00%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        move_fireAnimFrames.pushBack(frame);
    }
    auto move_fireAnimation = Animation::createWithSpriteFrames(move_fireAnimFrames, 0.06f);
    run_fireAnimate = Animate::create(move_fireAnimation);
    run_fireAnimate->retain();

    moveBody = PhysicsBody::createBox(Size(153.0f,153.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    moveBody->setCollisionBitmask( PLAYER_BITMASK );
    moveBody->setContactTestBitmask( true );
    moveBody->setDynamic(true);
    moveBody->setGravityEnable( true );
//    addComponent( moveBody );

    Vector<SpriteFrame*> jumpAnimFrames(8);//не забывать менять
    for(int i = 0; i <= 7; i++)
    {
        sprintf(str, "1/Jump_00%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        jumpAnimFrames.pushBack(frame);
    }
    auto jumpAnimation = Animation::createWithSpriteFrames(jumpAnimFrames, 0.15f);
    jumpAnimate = Animate::create(jumpAnimation);
    jumpAnimate->retain();

    Vector<SpriteFrame*> deathAnimFrames(10);//не забывать менять
    for(int i = 0; i <= 9; i++)
    {
        sprintf(str, "1/Die_00%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        deathAnimFrames.pushBack(frame);
    }
    auto deathAnimation = Animation::createWithSpriteFrames(deathAnimFrames, 0.3f, 10);
    deathAnimate = Animate::create(deathAnimation);
    deathAnimate->retain();
//    this->runAction(idleAnimate);

    Vector<SpriteFrame*> flyingAnimFrames(6);//не забывать менять
    for(int i = 0; i <= 5; i++)
    {
        sprintf(str, "1/Jetpack_00%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        flyingAnimFrames.pushBack(frame);
    }
    auto flyingAnimation = Animation::createWithSpriteFrames(flyingAnimFrames, 0.15f, 10);
    flyingAnimate = Animate::create(flyingAnimation);
    flyingAnimate->retain();

    Vector<SpriteFrame*> shootingAnimFrames(4);//не забывать менять
    for(int i = 0; i <= 3; i++)
    {
        sprintf(str, "1/Shot_00%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        shootingAnimFrames.pushBack(frame);
    }
    auto shootingAnimation = Animation::createWithSpriteFrames(shootingAnimFrames, 0.09f, 10);
    shootingAnimate = Animate::create(shootingAnimation);
    shootingAnimate->retain();

    Vector<SpriteFrame*> stay_with_gunAnimFrames(2);//не забывать менять
    for(int i = 0; i <= 1; i++)
    {
        sprintf(str, "1/stayWithGun_00%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        stay_with_gunAnimFrames.pushBack(frame);
    }
    auto stay_with_gunAnimation = Animation::createWithSpriteFrames(stay_with_gunAnimFrames, 1.0f, 10);
    stay_with_gunAnimate = Animate::create(stay_with_gunAnimation);
    stay_with_gunAnimate->retain();

    Vector<SpriteFrame*> jump_fireAnimFrames(3);//не забывать менять
    for(int i = 0; i <= 2; i++)
    {
        sprintf(str, "1/jump_fire_00%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,153,153));
        frame->setAnchorPoint(Vec2(0.5, 0));
        jump_fireAnimFrames.pushBack(frame);
    }
    auto jump_fireAnimation = Animation::createWithSpriteFrames(jump_fireAnimFrames, 0.5f, 10);
    jump_fireAnimate = Animate::create(jump_fireAnimation);
    jump_fireAnimate->retain();
}
