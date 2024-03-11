#pragma once

enum ENTITY_CONTROLLER {
    PLAYER,
    PLAYER_CAR,
    AI_CAR,
    EMPTY_CAR
};

class Player {
    public:
    enum PLAYER_CAR_IVARS {
        COLOR,
        ABER_CORE_LEVEL,
        ENGINE_LEVEL,
        ENGINE_SOUND_TICKS,
        IS_BEING_DRIVEN
    };

    enum PLAYER_CAR_FVARS {
        ABER_RECHARGE
    };
};

class Enemy {
    public:
    enum ENEMY_CAR_IVARS {
        IS_TARGETING,
        TARGET_X,
        TARGET_Y,
        TURNING_INTO_ANGLE,
        TURNING_DIRECTION, //left is -1, right is 1
        ENGINE_SOUND_TICKS
    };
};