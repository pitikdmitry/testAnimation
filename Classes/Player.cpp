//
// Created by nyam on 03.04.17.
//
#include <iostream>
#include "Player.h"
#include "definitions.h"

Player::~Player()
{
    CC_SAFE_RELEASE(idleAnimate);
    CC_SAFE_RELEASE(moveAnimate);
}

Player* Player::create( )
{
    Player * player = new Player();
    if(player && player->initWithFile("Idle (1).png"))
//    if(player)
    {

//        cocos2d::Node::
//        Player::setPhysicsBody();
        player->autorelease();

        return player;
    }

    CC_SAFE_DELETE(player);
    return NULL;
}

void Player::setPhysicsBody()
{
    physicsBody = PhysicsBody::createBox(Size(86.0f,100.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setCollisionBitmask( PLAYER_BITMASK );
    physicsBody->setContactTestBitmask( true );
//    physicsBody = PhysicsBody::createCircle(100);
//    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable( true );
    addComponent(physicsBody);
    initPlayer();
}

//Player::Player()
//{
//    auto physicsBody = PhysicsBody::createBox(Size(50.0f,50.0f));
//    physicsBody->setDynamic(true);
//    sprite = Sprite::create("Idle (1).png");
//    sprite->setPosition(50, 50);
//    initPlayer();
////apply physicsBody to the sprite
//    sprite->addComponent(physicsBody);
//}

void Player::initPlayer()
{
    moving = false;
    jumping = true;
    idling = false;
    is_onGround = false;
    char str[100] = {0};

    Vector<SpriteFrame*> idleAnimFrames(10);
    for(int i = 1; i <= 10; i++) //Iterate for the number of images you have
    {
        sprintf(str, "Idle (%i).png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,80,100)); //The size of the images in an action should be the same
        frame->setAnchorPoint(Vec2(0.5, 0));
        idleAnimFrames.pushBack(frame);
    }

    auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.20f);
    idleAnimate = Animate::create(idleAnimation);
    idleAnimate->retain(); //Retain to use it later
//    this->runAction(RepeatForever::create(idleAnimate)); //This will be the starting animation

    Vector<SpriteFrame*> moveAnimFrames(8);
    for(int i = 1; i <= 8; i++)
    {
        sprintf(str, "Run (%i).png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,80,100));
        frame->setAnchorPoint(Vec2(0.5, 0));
        moveAnimFrames.pushBack(frame);
    }

    auto moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.09f);
    moveAnimate = Animate::create(moveAnimation);
    moveAnimate->retain();

    Vector<SpriteFrame*> jumpAnimFrames(10);
    for(int i = 1; i <= 10; i++)
    {
        sprintf(str, "Jump (%i).png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,80,100));
        frame->setAnchorPoint(Vec2(0.5, 0));
        jumpAnimFrames.pushBack(frame);
    }

    auto jumpAnimation = Animation::createWithSpriteFrames(jumpAnimFrames, 0.3f);
    jumpAnimate = Animate::create(jumpAnimation);
    jumpAnimate->retain();
    this->runAction(RepeatForever::create(jumpAnimate));
}

void Player::move(int directionParam)
{
    if(true == is_onGround ) {
        std::cout<<"move";
//        jumping = false;
        idling = false;
        moving = true;
        this->stopAllActions();
        this->runAction(RepeatForever::create(moveAnimate));
        direction = directionParam;
    }
    else
    {
        idling = false;
        moving = true;
        direction = directionParam;
    }
}

void Player::idle()
{
    if(true == is_onGround) {
        std::cout<<"idle";
        moving = false;
        jumping = false;
        idling = true;
        this->stopAllActions();
        this->runAction(RepeatForever::create(idleAnimate));
    }
}

void Player::jump()
{
    if( true == is_onGround )
    {
        std::cout<<"jump";
        idling = false;
//        moving = false;
        jumping = true;
        this->stopAllActions();
        this->runAction(RepeatForever::create(jumpAnimate));
    }
//    this->setPositionY(this->getPositionY() + 50);
}

void Player::update()
{
    if(idling) {
        if (true == is_onGround) {
            idle();
        }
    }
    if(moving) //check if moving
    {
        int speed = 0;
        if( true == is_onGround)
        {
            speed = SPEED_OF_THE_PLAYER;
        }
        else
        {
            speed = SPEED_OF_THE_PLAYER_IN_THE_AIR;
        }
        if(direction == 0) //check if going left
        {
            this->setScaleX(-1); //flip
            this->setPositionX(this->getPositionX() - speed);
        }
        else
        {
            this->setScaleX(1); //flip
            this->setPositionX(this->getPositionX() + speed);
        }
    }
    if(jumping)
    {
        if(true == is_onGround) {
            Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
            body_velocity.y = 150;
            this->getPhysicsBody()->setVelocity( body_velocity );
            is_onGround = false;
        }
    }
//    moving = false;
//    jumping = false;
//    idling = false;

}




