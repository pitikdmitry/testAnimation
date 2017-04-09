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
    CC_SAFE_RELEASE(jumpAnimate);
}
//void setPhysicsBody(PhysicsBody* physicsBody)
void Player::move()
{
    current_anim = moving_anim;
    this->stopAllActions();
//    this->removeComponent(getPhysicsBody( ));
//    this->setPhysicsBody(moveBody);
//    this->addComponent( moveBody );
    this->runAction(RepeatForever::create( moveAnimate ));
}

void Player::run_fire()
{
    current_anim = run_fire_anim;
    this->stopAllActions();
    this->runAction(RepeatForever::create( run_fireAnimate ));
}

void Player::idle()
{
    current_anim = idling_anim;
    this->stopAllActions( );
//    this->removeComponent(getPhysicsBody( ));
//    this->setPhysicsBody(nullptr);
//    this->setPhysicsBody(idleBody);
//    this->addComponent( idleBody );
    this->runAction(RepeatForever::create( idleAnimate ));
}

void Player::jump()
{
    current_anim = jumping_anim;
    this->stopAllActions();
    this->runAction(RepeatForever::create( jumpAnimate ));
}

void Player::jump_fire()
{
    current_anim = jump_fire_anim;
    this->stopAllActions();
    this->runAction(RepeatForever::create( jump_fireAnimate ));
}

void Player::die()
{
    current_anim = death_anim;
    idling = false;
    moving = false;
    jumping = false;
    shooting = false;
    this->stopAllActions();
    this->runAction(RepeatForever::create( deathAnimate ));
}

void Player::shoot()
{
    current_anim = shoot_stay_anim;
    this->stopAllActions();
    this->runAction(RepeatForever::create( shootingAnimate ));
}

void Player::stay_with_gun()
{
    current_anim = stay_with_gun_anim;
    this->stopAllActions();
    this->runAction(RepeatForever::create( stay_with_gunAnimate ));
}

void Player::fly()
{
    std::cout << "flyyyyyyy";
    jetpack_anim = flying;
    this->stopAllActions();
    this->runAction(RepeatForever::create( flyingAnimate ));
}

void Player::update( )
{
    if( false == jetpack ) {

        if (true == death) {
            if (current_anim != death_anim) {
                die();
            }
            return;
        }

        if (false == jumping && false == moving) {
            if( current_anim != shoot_stay_anim && true == is_onGround && true == shooting ){
                shoot();
            }
            else if(  current_anim != stay_with_gun_anim && true == is_onGround && false == shooting && timer < 250 )
            {
                stay_with_gun();
            }
            else if( current_anim != idling_anim && true == is_onGround && false == shooting && timer >= 250 ) {
                    idle();
            }
        }

        if (moving) {
            if (true == is_onGround) {
                speed = SPEED_OF_THE_PLAYER;
            } else {
                speed = SPEED_OF_THE_PLAYER_IN_THE_AIR;
            }
            if (direction == 0) {
                this->setScaleX(-1);
                this->setPositionX(this->getPositionX() - speed);
            } else {
                this->setScaleX(1);
                this->setPositionX(this->getPositionX() + speed);
            }

            if (true == is_onGround && false == jumping && false == shooting && current_anim != run_fire_anim && timer < 250 ) {
                run_fire();
            }
            else if (true == is_onGround && false == jumping && false == shooting && current_anim != moving_anim && timer >= 250) {
                move();
            }
            else if (true == is_onGround && false == jumping && true == shooting && current_anim != run_fire_anim ) {
                run_fire();
            }
        }

        if (jumping) {
            if( current_anim != jump_fire_anim && true == shooting){
                jump_fire();
            }
            if( current_anim != jump_fire_anim && false == shooting && timer < 250 ){
                jump_fire();
            }
            if (true == is_onGround) {
                if ( current_anim != jumping_anim && false == shooting && timer >= 250 ) {
                    jump();
                }
                else if ( current_anim != jump_fire_anim && false == shooting && timer < 250 ) {
                    jump_fire();
                }
                Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
                body_velocity.y = 150;
                this->getPhysicsBody()->setVelocity(body_velocity);
                is_onGround = false;
            }
        }
        if ( is_onGround == false && false == shooting && current_anim != jump_fire_anim && timer < 250 ){
            jump_fire();
        }
    }
    else{
        if( true == is_onGround && jetpack_anim != staying ){
            jetpack_anim = staying;
            idle();
        }
        else if( false == is_onGround && jetpack_anim != flying ){
            fly();
        }
        if( moving ) {

            if (direction == 0) {
                this->setScaleX(-1);
                this->setPositionX( this->getPositionX() - 1.3 * SPEED_OF_THE_PLAYER );
            } else {
                this->setScaleX(1);
                this->setPositionX( this->getPositionX() + 1.3 * SPEED_OF_THE_PLAYER );
            }
        }
        if( jumping ) {
            Vec2 body_velocity = this->getPhysicsBody()->getVelocity();
            body_velocity.y = 150;
            is_onGround = false;
            this->getPhysicsBody()->setVelocity(body_velocity);
        }
    }
    ++timer;
//    std::cout<<timer<<std::endl;
}




