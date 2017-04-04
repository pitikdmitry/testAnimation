#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//    scene->getPhysicsWorld( )->setGravity( Vect(0, -9.8f) );

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
        auto physicsBody = PhysicsBody::createBox(Size(50.0f,50.0f));

        physicsBody->setDynamic(false);
        auto sprite = Sprite::create("Crate.png");
        sprite->setPosition(i * 50, 50);
        addChild(sprite);
//apply physicsBody to the sprite
        sprite->addComponent(physicsBody);

    }
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    auto edgeNode = Node::create();
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    this->addChild( edgeNode );


    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    player = Player::create();
    player->setPosition(Vec2(origin.x + visibleSize.width / 2
            , origin.y + visibleSize.height / 2));
    player->setPhysicsBody();
    this->addChild(player, 5);

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
                break;
        }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    player->idle();
}
