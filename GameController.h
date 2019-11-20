#ifndef GameController_h
#define GameController_h

#include "Puck.h"
#include "Paddle.h"
#include <SDL.h>
#include <math.h>
#include <iostream>
#include <SDL_mixer.h>

using namespace std;

void initGame(Puck &puck, Paddle &left, Paddle& right, SDL_Surface* screen);

int checkCollision(Puck puck, Paddle paddle);
int movePuck(Puck &puck, Paddle paddle[], SDL_Surface* screen, Mix_Chunk* chunk);

void handleEvent(SDL_Event& e, Paddle paddle[]);
void movePaddleAi(Paddle paddle[], Puck puck, SDL_Surface *screen);
void movePaddle(Paddle paddle[], SDL_Surface *screen);


void draw_puck(Puck puck, SDL_Surface *screen);
void draw_paddle(Paddle paddle[], SDL_Surface *screen);


#endif