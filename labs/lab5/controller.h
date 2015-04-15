#include "model.h"
#include "view.h"

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

class Controller {
public:
    Controller();
    ~Controller();
    void loop();
private:
    Model * model;
    View * view;
};
#endif