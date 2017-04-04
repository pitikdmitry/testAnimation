//
// Created by nyam on 03.04.17.
//

#include "Player.h"

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
//    moving = false;
    char str[100] = {0};

//    Vector<SpriteFrame*> idleAnimFrames(10);
//    for(int i = 1; i <= 10; i++) //Iterate for the number of images you have
//    {
//        sprintf(str, "Idle (%i).png",i);
//        auto frame = SpriteFrame::create(str,Rect(0,0,80,100)); //The size of the images in an action should be the same
//        idleAnimFrames.pushBack(frame);
//    }
//
//    auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.20f);
//    idleAnimate = Animate::create(idleAnimation);
//    idleAnimate->retain(); //Retain to use it later
//    this->runAction(RepeatForever::create(idleAnimate)); //This will be the starting animation

    Vector<SpriteFrame*> moveAnimFrames(8);
    for(int i = 1; i <= 8; i++)
    {
        sprintf(str, "Run (%i).png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,80,100));
        moveAnimFrames.pushBack(frame);
    }

    auto moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.09f);
    moveAnimate = Animate::create(moveAnimation);
    moveAnimate->retain();
    this->runAction(RepeatForever::create(moveAnimate));
//    Vector<SpriteFrame*> jumpAnimFrames(8);
//    for(int i = 1; i <= 8; i++)
//    {
//        sprintf(str, "Jump (%i).png",i);
//        auto frame = SpriteFrame::create(str,Rect(0,0,80,100));
//
//        jumpAnimFrames.pushBack(frame);
//    }
//
//    auto jumpAnimation = Animation::createWithSpriteFrames(jumpAnimFrames, 0.09f);
//    jumpAnimate = Animate::create(jumpAnimation);
//    jumpAnimate->retain();
}
//
//void Player::move(int directionParam)
//{
//    this->stopAllActions();
//    this->runAction(RepeatForever::create(moveAnimate));
//
//    direction = directionParam;
//    moving = true;
//}
//
//void Player::idle()
//{
//    moving = false;
//    this->stopAllActions();
//    this->runAction(RepeatForever::create(idleAnimate));
//}
//
//void Player::update()
//{
//    if(moving) //check if moving
//    {
//        if(direction == 0) //check if going left
//        {
//            this->setScaleX(-1); //flip
//            this->setPositionX(this->getPositionX() - 5);
//        }
//        else
//        {
//            this->setScaleX(1); //flip
//            this->setPositionX(this->getPositionX() + 5);
//        }
//    }
//}