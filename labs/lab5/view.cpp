#include "view.h"

using namespace std;


View::View(string title, int width, int height) {
    fail = false;
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        fail = true;
        return;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fail = true;
        return;
    }

    screen = SDL_GetWindowSurface(window);

    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        fail = true;
        return;
    }
}

View::~View() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


SDL_Surface* View::load(char * path) {

    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        return NULL;
    }

    optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
    

    SDL_FreeSurface( loadedSurface );
    
    return optimizedSurface;
}

void View::show(Model * model) {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
        0x00, 0x00, 0x00));

    SDL_Rect dest;
    dest.w = 16;
    dest.h = 16;
   


    dest.x = model->food.x * 16;
    dest.y = model->food.y * 16;
    SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format,
            0x80, 0x00, 0x00));
    

    for (List<Coordinate>::iterator it=model->snake.begin(); it!=model->snake.end(); it++) {
        dest.x = it->x * 16;
        dest.y = it->y * 16;
        SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format,
        0x00, 0x80, 0x00));
    }
    if (model->gameOver()) {
		dest.x = 0;
		dest.y = 0;
		dest.w = 640;
		dest.h = 640;
		SDL_Surface* surface = load("assets/dead.jpg");
		SDL_BlitSurface( surface, NULL, screen, &dest );
	}
    SDL_UpdateWindowSurface(window);
}