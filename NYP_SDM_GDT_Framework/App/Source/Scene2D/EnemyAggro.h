#pragma once
//also need player position
#include "Player2D.h"

class EnemyAggro :public CEnemy2D
{
public:

protected:
    enum TYPE
    {
        CLOSE = 0,
        FAR_AWAY = 1,
        NUM_TYPE
    };

    TYPE currentState;

    // player pointer to get players position
    CPlayer2D* player;

    //since this class is sub class of enemy, can have direct access to enemy
};

