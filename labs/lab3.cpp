#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

enum State { INIT, FIRST, NOMATCH };
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
    int lastRow;
    int lastColumn;
	int lastRow2;
	int lastColumn2;
    State state;
};


class View {
public:
    void show(Model * model);
};


class Controller {
public:
    Controller() {
        model = new Model(8,8);
        view = new View;
    }
	
	~Controller(){
		delete model;
		delete view;
	}

    void loop();
private:
    Model * model;
    View * view;
};


Model::Model(int w, int h) {
    width = w;
    height = h;
    lastRow = -1;
    lastColumn = -1;
    state = INIT;
	

    grid = new char*[h];
    visible = new char*[h];
    for (int i = 0; i < height; i++) {
        grid[i] = new char[w];
        visible[i] = new char[w];

    }
	
	char letter = 'A';
    for (int i = 0; i < height; i++) {
		
        for (int j = 0; j < width; j++) {
			
            grid[i][j] = letter;
            visible[i][j] = '*';
			
			if((j) % 2 == 1)
			{
				if(letter == 'Z')
				{
					letter = 'A';
				}
				else
				{
					letter++;
				}
			}
        }
    }
	srand(time(0));
	
	// Shuffle here
	int otheri, otherj;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			otheri = rand() % height;
			otherj = rand() % width;
			// Swap here
			letter = grid[i][j];
			grid[i][j] = grid[otheri][otherj];
			grid[otheri][otherj] = letter;
		}
	}
}

Model::~Model() {
    for (int i = 0; i < height; i++) {
        delete grid[i];
        delete visible[i];
    }
    delete grid;
    delete visible;
}

bool Model::valid(int row, int column) {
    return (((row >= 0) && (row < height)) && ((column >= 0) && (column < width)));
}
bool Model::matched(int row, int column) {
    return true;
}
void Model::flip(int row, int col) {
	
	if (!valid(row, col)) { return; }
	if((row == lastRow) && (col == lastColumn)){ return;}
	switch(state)
	{
		case NOMATCH:
			visible[lastRow][lastColumn] = '*';
			visible[lastRow2][lastColumn2] = '*';
		case INIT:
			visible[row][col] = grid[row][col];
			lastRow = row;
			lastColumn = col;
			state = FIRST;
			break;
		case FIRST:
			visible[row][col] = grid[row][col];
			lastRow2 = row;
			lastColumn2 = col;
			if (grid[lastRow][lastColumn] != grid[lastRow2][lastColumn2])
			{
				state = NOMATCH;
			}
			else
			{
				state = INIT;
			}
			break;
		
	}

}

bool Model::gameOver() {
	
	for (int i = 0; i < height; i++) {
		
        for (int j = 0; j < width; j++) {
			if(visible[i][j] != grid[i][j])
			{
				return false;
			}
            
        }
    }
	
    return true;
}
int Model::getWidth() {
    return width;
}
int Model::getHeight() {
    return height;
}
char Model::get(int row, int col) {
    return visible[row][col];
}

void View::show(Model * model) {
    for (int j = 0; j < model->getWidth(); j++) {
        cout << "\t" << j;
    }
    cout << endl;
    for (int i = 0; i < model->getHeight(); i++) {
        cout << i;
        for (int j = 0; j < model->getWidth(); j++) {
            cout << "\t" << model->get(i, j);
        }
        cout << endl;
    }
}


void Controller::loop() {
    int row, col;
    while (!model->gameOver()) {
        view->show(model);
        cout << "Enter row:    ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        model->flip(row, col);
    }
	cout << "You win!\n";
}
int main() {
    Controller c;
    c.loop();
}