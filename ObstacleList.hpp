#include "ObstacleSprite.hpp"

struct ObstacleList {
    ObstacleSprite obstacle;
    ObstacleList* next;
};