#include "list.h"

#ifndef _MODEL_H
#define _MODEL_H

enum Direction { UP, DOWN, LEFT, RIGHT, DEAD };

typedef struct {
    int x;
    int y;
} Coordinate;


class Model {
public:

    Model(int w, int h);
    ~Model();
    void go(Direction d);
    void crawl();
    bool gameOver();
    List<Coordinate> snake;
    Coordinate food;
    Direction direction;
    int width;
    int height;
};

#endif