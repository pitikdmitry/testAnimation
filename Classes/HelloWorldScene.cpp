#include "HelloWorldScene.h"
#include <iostream>
#include <functional>
#define OBSTACLE_COLLISION_BITMASK

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld( )->setGravity( Vect(0, -200.8f) );

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}




// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
//    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

//

    for(int i = 0; i < 15; ++i)
    {
        auto physicsBody = PhysicsBody::createBox(Size(50.0f,50.0f), PhysicsMaterial(0.1f, .1f, 0.0f));
        physicsBody->setCollisionBitmask( GROUND_BITMASK );
        physicsBody->setContactTestBitmask( true );
        physicsBody->setDynamic(false);
        auto sprite = Sprite::create("Crate.png");
        sprite->setPosition(i * 50, 50);
        addChild(sprite);
//apply physicsBody to the sprite
        sprite->addComponent(physicsBody);

    }
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    auto edgeNode = Node::create();
//    edgeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    this->addChild( edgeNode );

    player = Player::create();
    player->setPosition(Vec2(origin.x + visibleSize.width / 2
            , origin.y + visibleSize.height / 2));
    player->setPhysicsBody();
    this->addChild(player, 5);



    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    std::function<void(PhysicsContact& contact, const PhysicsContactPostSolve& solve)> onContactPostSolve;
    auto contactListener = EventListenerPhysicsContact::create( );
//    std::bind(MyClass::my_callback_with_param, this, 1)
    contactListener->onContactBegin = CC_CALLBACK_1( HelloWorld::onContactBegin, this);
//    contactListener->onContactPostSolve = CC_CALLBACK_2(HelloWorld::onContactPostSolve,onContactBegin, this);
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( contactListener, this );


    this->scheduleUpdate();

    return true;
}



void HelloWorld::update(float dt)
{
    player->update();
}

//bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
//{
//    if(touch->getLocation().x < player->getPositionX())
//    {
//        player->move(0); // param '0' for left
//    }
//    if(touch->getLocation().x > player->getPositionX())
//    {
//        player->move(1); // param '0' for right
//    }
//
//    return true;
//}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
        switch (keyCode) {
            case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
                player->move(0);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_D:
                player->move(1);
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_W:
                player->jump();
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_S:
                break;
            default:
                player->idle();
                break;
        }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            if(true == player->is_onGround)
            {
                player->moving = false;
                player->jumping = false;
                player->idling = true;
            }
            else
            {
                player->moving = false;
                player->jumping = true;
                player->idling = false;
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            if(true == player->is_onGround)
            {
                player->moving = false;
                player->jumping = false;
                player->idling = true;
            }
            else
            {
                player->moving = false;
                player->jumping = true;
                player->idling = false;
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            if(true == player->moving )
            {
                player->jumping = false;
                player->idling = false;
            }
            else
            {
                player->jumping = false;
                player->idling = true;
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            break;
        default:
            break;
    }

    std::cout<<"released";
//    player->idle();


//    player->idling = true;
}

bool HelloWorld::onContactBegin( cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();

    if ( ( PLAYER_BITMASK == a->getCollisionBitmask( ) && GROUND_BITMASK == b->getCollisionBitmask() ) || ( PLAYER_BITMASK == b->getCollisionBitmask( ) && GROUND_BITMASK == a->getCollisionBitmask() ) )
    {
        player->is_onGround = true;
        player->jumping = false;
        if(false == player->moving)
        {
            player->idling = true;
        }
        else
        {
            player->moving = true;
        }
//        player->idle();
        std::cout<<"first";
    }
//    Sprite *player1 = contact.getShapeA( )->getSprite();

    return true;
}

//bool HelloWorld::onContactPostSolve( cocos2d::PhysicsContact &contact, const PhysicsContactPostSolve& solve)
//{
//
//}
