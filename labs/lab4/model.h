#include <vector>

#ifndef _MODEL_H
#define _MODEL_H

enum State { INIT, FIRST, NO_MATCH };


class Model {

public:

    Model(int w, int h);
    ~Model();

    int getWidth();
    int getHeight();
    char get(int row, int column);
    void flip(int row, int column);
    bool gameOver();
	
private:

    bool valid(int row, int column);
    bool matched(int row, int column);
    char ** grid;
    char ** visible;
    int width;
    int height;
	int lastrow;
	int lastcolumn;
	int lastraw;
	int lastcal;
    State state;
};


#endif