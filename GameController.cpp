#include "GameController.h"
#define PI  3.141592653589793238462643383279502884L

void initGame(Puck &puck, Paddle &left, Paddle &right, SDL_Surface* screen) {
	puck.setX(screen->w / 2);
	puck.setY(screen->h / 2);
	puck.setSize(10);
	puck.setSpeed(1);

	int alpha = (rand() / (float)RAND_MAX) * 2 * PI; //random goc alpha doan [0, 2pi]
    //neu alpha nam trong doan [4pi/9, 5pi/9] hoac [13pi/9, 14pi/9] random lai
	while ((4 * PI / 9 < alpha && alpha < 5 * PI / 9) || (13 * PI / 9 < alpha && alpha < 14 * PI / 9))
		alpha = (rand() / (float)RAND_MAX) * 2 * PI;

	puck.setDx(cos(alpha) * puck.getSpeed());
	puck.setDy(sin(alpha) * puck.getSpeed());

	left.setX(20);
	left.setY(screen->h / 2 - 50);
	left.setW(10);
	left.setH(50);
	left.setSpeed(0);

	right.setX(screen->w - 20 - 10);
	right.setY(screen->h / 2 - 50);
	right.setW(10);
	right.setH(50);
	right.setSpeed(0);
}

 //kiem tra puck va cham voi paddle, tra ve 1 neu co va cham, tra ve 0 neu khong va cham
int checkCollision(Puck puck, Paddle paddle) {
	int left_puck, left_paddle;
	int right_puck, right_paddle;
	int top_puck, top_paddle;
	int bottom_puck, bottom_paddle;

	left_puck = puck.getX();
	right_puck = puck.getX() + puck.getSize();
	top_puck = puck.getY();
	bottom_puck = puck.getY() + puck.getSize();

	left_paddle = paddle.getX();
	right_paddle = paddle.getX() + paddle.getW();
	top_paddle = paddle.getY();
	bottom_paddle = paddle.getY() + paddle.getH();


	if (left_puck > right_paddle) {
		return 0;
	}

	if (right_puck < left_paddle) {
		return 0;
	}

	if (top_puck > bottom_paddle) {
		return 0;
	}

	if (bottom_puck < top_paddle) {
		return 0;
	}

	return 1;
}

//Nhan vao puck,paddle,surface
//Tra ve 1 neu nguoi 1 win, 2 neu nguoi 2 win
//chua co ai win thi tra ve 0
int movePuck(Puck &puck, Paddle paddle[], SDL_Surface *screen, Mix_Chunk* chunk) {

	//puck doi huong do va cham voi thanh san dau
	if (puck.getY() < 0 || puck.getY() + puck.getSize() > screen->h)
		puck.setDy(puck.getDy() * -1);

	//puck va cham thanh san bên phai, player 1 win
	if (puck.getX() + puck.getSize() > screen->w) {
		initGame(puck, paddle[0], paddle[1], screen);
		return 1;
	}

	//puck va cham thanh san bên trai, player 2 win
	if (puck.getX() < 0) {
		initGame(puck, paddle[0], paddle[1], screen);
		return 2;
	}

	for (int i = 0; i < 2; i++) {
		int c = checkCollision(puck, paddle[i]); //kiem tra puck va cham voi paddle, tra ve 1 neu co va cham //

		if (c == 1) {
			if (!Mix_Playing(-1))
				Mix_PlayChannel(-1, chunk, 0);
			puck.setSpeed(puck.getSpeed() * 1.1); //

			float alpha = atan(puck.getDy() / puck.getDx());
			float t = ((puck.getY() + puck.getSize() / 2) - (paddle[i].getY() + paddle[i].getH() / 2)) * PI / (paddle[i].getH() * 10);

			if (i == 0) {
				puck.setDx(-(cos(PI - alpha + t) * puck.getSpeed()));
				puck.setDy(-(sin(PI - alpha + t) * puck.getSpeed()));
			}
			else {
				puck.setDx(cos(PI - alpha + t) * puck.getSpeed());
				puck.setDy(sin(PI - alpha + t) * puck.getSpeed());
			}
		}
	}
	puck.setX(puck.getDx() + puck.getX());
	puck.setY(puck.getDy() + puck.getY());

	return 0;
}

//nhan su kien tu ban phim de di chuyen paddle
void handleEvent(SDL_Event& e, Paddle paddle[]) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			paddle[1].setSpeed(-1);
			break;
		case SDLK_DOWN:
			paddle[1].setSpeed(1);
			break;
		case SDLK_e:
			paddle[0].setSpeed(-1);
			break;
		case SDLK_d:
			paddle[0].setSpeed(1);
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			paddle[1].setSpeed(0);
			break;
		case SDLK_DOWN:
			paddle[1].setSpeed(0);
			break;
		case SDLK_e:
			paddle[0].setSpeed(0);
			break;
		case SDLK_d:
			paddle[0].setSpeed(0);
			break;
		}
	}
}

//cai dat cho paddle been trai di chuyen theo huong di chuyen cua puck
//nhan vao data cua 2 paddle, puck, surface
void movePaddleAi(Paddle paddle[], Puck puck, SDL_Surface *screen) {
	float y = puck.getY();
	float x = puck.getX();
	float dy = puck.getDy();
	float center = paddle[0].getY() + 25;

	if (puck.getDx() < 0) {
		while (x >= paddle[0].getX() + paddle[0].getW()) {
			if (y + puck.getSize() > screen->h || y < 0)
				dy *= -1;
			x += puck.getDx();
			y += dy;
		}

		if (center < y + puck.getSize() / 2)
			paddle[0].setY(paddle[0].getY() + 1);
		else if (center > y + puck.getSize() / 2)
			paddle[0].setY(paddle[0].getY() - 1);
	}

	paddle[1].setY(paddle[1].getY() + paddle[1].getSpeed());

	if (paddle[1].getY() <= 0)
		paddle[1].setY(0);

	if (paddle[1].getY() >= screen->h - paddle[1].getH())
		paddle[1].setY(screen->h - paddle[1].getH());
}

//di chuyen 2 paddle
//Nhan vao data cua 2 paddle va thong tin surface de kiem tra vi tri co thoa dieu kien
void movePaddle(Paddle paddle[], SDL_Surface *screen) {
	for (int i = 0; i < 2; i++) {
		paddle[i].setY(paddle[i].getY() + paddle[i].getSpeed());

		if (paddle[i].getY() <= 0)
			paddle[i].setY(0);

		if (paddle[i].getY() >= screen->h - paddle[i].getH())
			paddle[i].setY(screen->h - paddle[i].getH());
	}
}

//Nhan vao data cua puck, va surface de ve len -> tra ve hinh ve cua puck
void draw_puck(Puck puck, SDL_Surface *screen) {

	SDL_Rect src;

	src.x = puck.getX();
	src.y = puck.getY();
	src.w = puck.getSize();
	src.h = puck.getSize();

	int r = SDL_FillRect(screen, &src, 0xffffffff);

	if (r != 0) {

		cout << "fill rectangle faliled in func drawball()";
	}
}

//Nhan vao data cua 2 paddle, va surface de ve len -> tra ve hinh ve cua paddle
void draw_paddle(Paddle paddle[], SDL_Surface *screen) {

	SDL_Rect src;
	int i;

	for (i = 0; i < 2; i++) {

		src.x = paddle[i].getX();
		src.y = paddle[i].getY();
		src.w = paddle[i].getW();
		src.h = paddle[i].getH();

		int r = SDL_FillRect(screen, &src, 0xffffffff);

		if (r != 0) {

			printf("fill rectangle faliled in func draw_paddle()");
		}
	}
}
