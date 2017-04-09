//
// Created by nyam on 09.04.17.
//
#ifndef MYGAME_BLONDE_PLAYER_H
#define MYGAME_BLONDE_PLAYER_H
#include "Player.h"


class Blonde_player : public Player {
public:
    static Player* create( );
    virtual void initPlayer( );
protected:

};


#endif //MYGAME_BLONDE_PLAYER_H
