#include "HelloWorldScene.h"
#include <iostream>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    auto physicsBody2 = PhysicsBody::createBox(Size(50.0f,50.0f), PhysicsMaterial(0.1f, .1f, 0.0f));
    physicsBody2->setCollisionBitmask( GROUND_BITMASK );
    physicsBody2->setContactTestBitmask( true );
    physicsBody2->setDynamic(false);
    auto sprt = Sprite::create("Crate.png");
    sprt->setPosition(150, 150);
    addChild(sprt);
    sprt->addComponent(physicsBody2);



    for(int i = 0; i < 20; ++i)
    {
        auto physicsBody = PhysicsBody::createBox(Size(50.0f,50.0f), PhysicsMaterial(0.1f, .1f, 0.0f));
        physicsBody->setCollisionBitmask( GROUND_BITMASK );
        physicsBody->setContactTestBitmask( true );
        physicsBody->setDynamic(false);
        auto sprite = Sprite::create("Crate.png");
        sprite->setPosition(i * 50, 50);
        addChild(sprite);
        sprite->addComponent(physicsBody);

    }
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    auto edgeNode = Node::create();
//    edgeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    this->addChild( edgeNode );

    player = Blonde_player::create();
    player->setPosition(Vec2(origin.x + visibleSize.width / 2
            , origin.y + visibleSize.height / 2));
    player->initPlayer();
    this->addChild(player, 5);

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    std::function<void(PhysicsContact& contact, const PhysicsContactPostSolve& solve)> onContactPostSolve;
    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1( HelloWorld::onContactBegin, this);
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( contactListener, this );

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);



    this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt)
{
    player->update();
    if( true == player->shooting && player->timer % 10 == 0 ){
        Bullet* bul = Bullet::create( player );
        bullets.push_back( bul );
        addChild( bul );
    }
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
        switch (keyCode) {
            case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
                player->moving = true;
                player->direction = 0;
                player->key_A = true;
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_D:
                player->moving = true;
                player->direction = 1;
                player->key_D = true;
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_W:
                player->jumping = true;
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case cocos2d::EventKeyboard::KeyCode::KEY_S:

                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_U:
                player->death = true;
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_O:
                player->jetpack = true;
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_P:
                player->jetpack = false;
                break;
            default:
                //
                break;
        }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {

        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            player->key_A = false;
            if( false == player->key_D ){
                player->moving = false;
            }
            else{
                player->direction = 1;
            }
            if( false == player->jumping && false == player->moving ){
                player->idling = true;
            }
            break;

        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            player->key_D = false;
            if( false == player->key_A ){
                player->moving = false;
            }
            else{
                player->direction = 0;
            }
            if( false == player->jumping && false == player->moving ){
                player->idling = true;
            }
            break;

        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            player->jumping = false;
            break;

        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            break;

        default:
            break;
    }
}

bool HelloWorld::onContactBegin( cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA( )->getBody( );
    PhysicsBody *b = contact.getShapeB( )->getBody( );

    if ( ( PLAYER_BITMASK == a->getCollisionBitmask( ) && GROUND_BITMASK == b->getCollisionBitmask() ) || ( PLAYER_BITMASK == b->getCollisionBitmask( ) && GROUND_BITMASK == a->getCollisionBitmask() ) )
    {
        player->is_onGround = true;
    }
    return true;
}


void HelloWorld::onMouseUp(Event *event)
{
    player->shooting = false;
    player->timer = 0;
}

void HelloWorld::onMouseDown(Event *event)
{
    std::cout<<"mouse down";
    player->shooting = true;
}























