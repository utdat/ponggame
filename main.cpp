
#include <SDL.h>
#include <iostream>
#include "Paddle.h"
#include "Puck.h"
#include "GameController.h"
#include "SDL_mixer.h"


#define window_surface_WIDTH 680	//window height
#define window_surface_HEIGHT 480	//window width

#undef main
SDL_Window* window = NULL;
SDL_Renderer* renderer;

SDL_Surface *menu;
SDL_Surface *screen;
SDL_Surface *image;
SDL_Surface *win;

Mix_Chunk* chunk = NULL;


SDL_Texture *window_surface_texture;
SDL_Event e;


int main() {
	Puck puck;
	Paddle paddle[2];
	bool is_quit = false;				//Bien kiem tra thoat game
	int state = 0;						//Bien kiem tra tinh trang game, 0: game ve trang thai khoi tao, 1: dang choi, 2: trang thai dung, da co nguoi thang
	int checkWin = 0;					//Bien kiem tra nguoi thang. 0: chua co nguoi thang, 1: nguoi 1 win, 2: nguoi 2 win
	int countPlayer = 0;				//Bien dem so nguoi choi, 0: khoi tao, 1: 1 nguoi choi, 2: 2 nguoi choi

	if (SDL_Init(SDL_INIT_VIDEO) < 0)	//Kiem tra thu vien SDL co duoc load chua
	{
		cout << "Failed to initialize the SDL2 library\n";
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("PONG GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);		//Tao window
	if (!window)																											//Kiem tra xem window duoc tao chua
	{
		cout << "Failed to create window\n";
		return -1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout << Mix_GetError();
		return -1;
	}

	//Load Sound Effect
	chunk = Mix_LoadWAV("sound_effects.wav");
	if (chunk == NULL)
	{
		cout << Mix_GetError();
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);		//Tao render
	if (renderer == NULL)														//Kiem tra render duoc tao chua
	{
		cout << "Could not create render " << SDL_GetError();
		return -1;
	}
	SDL_Surface *screen = SDL_CreateRGBSurfaceWithFormat(0, 680, 480, 32, SDL_PIXELFORMAT_RGBA32);	//tao surface screen						
	if (!screen)	//Kiem tra lai
	{
		cout << "Failed to get the surface from the window\n";
		return -1;
	}
	window_surface_texture = SDL_CreateTextureFromSurface(renderer, screen);		//Tao texture tu surface screen vua tao o tren

	initGame(puck, paddle[0], paddle[1], screen);									//Khoi tao data cac vat the trong game
	SDL_Surface *image = SDL_LoadBMP("background.bmp");								//Tao surface de load anh background
	SDL_Surface *menu = SDL_LoadBMP("menu.bmp");									//Tao surface chua anh menu
	SDL_BlitSurface(menu, NULL, screen, NULL);										//thuc hien chen menu vao screen de hien thi len


	while (!is_quit)																//Kiem tra chuong trinh co duoc thoat
	{
		while (SDL_PollEvent(&e) !=0 )												//Bat su kien
		{
			if (e.type == SDL_QUIT)													//Kiem tra co nhan thoat
			{
				is_quit = true;
			}
			handleEvent(e, paddle);													//Bat su kien bam phim de dieu khien paddle
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {						//Bat ban phim va kiem tra
				switch (e.key.keysym.sym) {											
				case SDLK_1:														//Neu nhan 1
					if (state == 0) {												//Kiem tra xem game ve menu chua
						countPlayer = 1;											// set 1 nguoi choi
						state = 1;													//game chuyen sang trang thai dang choi
					}
					break;
				case SDLK_2:														//Nhan 2
					if (state == 0) {												//Kiem tra xem game ve menu chua
						countPlayer = 2;											// set 1 nguoi choi
						state = 1;
					}
					break;
				case SDLK_ESCAPE:													//Nhan ese
					is_quit = true;													//Tra quit ve true -> thoat game
					break;
				case SDLK_n:														//nhan N
					if (state == 2) {												//Kiem tra xem game da ve tinh trang dung (co nguoi win) chua
						SDL_BlitSurface(menu, NULL, screen, NULL);					//Load menu len
						state = 0;													//tra state ve 0, game ve trang thai khoi tao
					}
				}
			}
		}
		if (state == 1) {															//Neu game dang chay
			SDL_RenderClear(renderer);												//Thuc hien xoa khung hinh truoc
			SDL_BlitSurface(image, NULL, screen, NULL);								//load background len

			if (countPlayer == 1) movePaddleAi(paddle, puck, screen);				//kiem tra so nguoi choi de thuc hien dieu kien paddle thich hop
			else if (countPlayer == 2) movePaddle(paddle, screen);

			checkWin = movePuck(puck, paddle, screen, chunk);								//kiem tra xem co nguoi win chua

			draw_puck(puck, screen);												//ve puck, paddle len man hinh
			draw_paddle(paddle, screen);
																					//Kiem tra nguoi win
			if (checkWin == 1) {													
				win = SDL_LoadBMP("win1.bmp");										//load anh nguoi 1 win
				state = 2;															//thiet lap state ve trang thai nghi
				SDL_BlitSurface(win, NULL, screen, NULL);							//tao anh win1 len man hinh
			}
			else if (checkWin == 2) {												
				win = SDL_LoadBMP("win2.bmp");										//load anh nguoi 1 win
				state = 2;															//thiet lap state ve trang thai nghi
				SDL_BlitSurface(win, NULL, screen, NULL);							//tao anh win1 len man hinh
			}
		}

		SDL_UpdateTexture(window_surface_texture,NULL, screen->pixels, screen->w * sizeof(Uint32));		//Cap nhat lai texture
		SDL_RenderCopy(renderer, window_surface_texture, NULL, NULL);									//Thuc hien copy texture vao render
		SDL_RenderPresent(renderer);																	//Cho hien len man hinh
	}

	//Thuc hien giai phong cac surface,texture, render, window sau do thoat
	Mix_CloseAudio();
	SDL_FreeSurface(win);										
	SDL_FreeSurface(menu);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
