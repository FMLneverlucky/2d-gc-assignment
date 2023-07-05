#pragma once
class EnemyAggro :
    public Enemy2D
{
public:

protected:
    enum type
    {
        NEAR = 0,
        FAR = 1,
        NUM_TYPE
    };

};

