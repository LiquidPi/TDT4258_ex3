#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#include "drawapi.h"
#include "control_interface.h"

#define PADDLE_START 0
#define PADDLE_HEIGHT 100
#define PADDLE_END (WINDOW_H-PADDLE_HEIGHT)

#define PADDLE_0_BORDER 25
#define PADDLE_1_BORDER WINDOW_W-10-30

#define BALL_SIZE 20

#define PADDLE_STEP 2
#define BALL_SPEED 2.0f

//Parameters for rendering score
#define MAX_SCORE 5
#define SCORE_INCREMENT_W 10

//Game state
float ballx = (float)(WINDOW_W/2);
float bally = (float)(WINDOW_H/2);
int scores[] = {0, 0};

float ballDirection[] = {
	1.0f, 0.0f
};

char gameOver = 0;
int count = 0; //Used for blinking
int paddles[] = {WINDOW_H/2-50, WINDOW_H/2-50};

/*  Takes the (approx.) square root of a number
 *  Input:  float num: number to be squared.
 *  Output: float: the square root of num.
 */
float sqrt(float num)
{
    float guess, e, upperbound;
    guess = 1;
    e = 0.001;
    do 
    {
        upperbound = num / guess;
        guess = (upperbound + guess) / 2;
    } while (!(guess * guess >= num - e && 
               guess * guess <= num + e));
    return guess;
}

/*  Collection of functions to draw different objects on screen
 */
void drawPaddle(int x, int y) {
	drawRectangle(x, y, 15, 100);
}

void drawLeftPaddle() {
	drawPaddle(10, paddles[0]);
}

void drawRightPaddle() {
	drawPaddle(WINDOW_W-10-30, paddles[1]);
}

void drawBall() {
	drawRectangle((int)ballx, (int)bally, 20, 20);
}

void drawScore() {
	int offsetX = (MAX_SCORE*SCORE_INCREMENT_W);

	if(scores[0] < MAX_SCORE-1 || count < 50) {
		drawRectangle(WINDOW_W/2-offsetX, 0, scores[0]*SCORE_INCREMENT_W, 20);
	}
	if(scores[1] < MAX_SCORE-1 || count < 50) {
		drawRectangle(WINDOW_W/2+offsetX-scores[1]*SCORE_INCREMENT_W, 0, scores[1]*SCORE_INCREMENT_W, 20);
	}
}

/*  Moves a paddle up or down.
 *  Input:  int index: index of which paddle to move
 			int amount: how much to move paddle
 *  Output: none
 */
void movePaddle(int index, int amount) {
	if(index > 1)
		return;
	paddles[index] += amount;
	if(paddles[index] < PADDLE_START) {
		paddles[index] = PADDLE_START;
	} else if(paddles[index] > PADDLE_END) {
		paddles[index] = PADDLE_END;
	}
}

/*  Increase score of a player, and check if the game have ended.
 *  Also deals with the direction the ball travels at the start of a new round.
 *  Input:  int winner: index of player whose score to increase.
 *  Output: none
 */
void someoneWon(int winner) {
	scores[winner]++;
	if(scores[winner] == MAX_SCORE) {
		gameOver = 1;
	}
	ballx = (float)(WINDOW_W/2);
	bally = (float)(WINDOW_H/2);

	//Randomize ball direction
	int direction = rand()%2;
	ballDirection[0] = direction==0?-1.0f:1.0f;
	ballDirection[1] = (float)(rand()%100)/100.0f-0.5f;
}

/*  Handle collision between ball and paddle.
 *  Input:  float paddlePos: the position of the paddle
 *  Output: none
 */
void paddleCollide(float paddlePos) {
	ballDirection[0] = -ballDirection[0];
	float dist = paddlePos-(bally-((float)BALL_SIZE/2.0f));
	ballDirection[1] = dist/-100.0f;
}

/*  Update the state of the game.
 *  Handles paddle movement, ball movement, and collisions.
 *  Input:  none
 *  Output: none
 */
void updateGameState() {
	struct gamepad g = GetCurrentInput();
	if(g.up_0) {
		movePaddle(0, PADDLE_STEP);
	}
	if(g.down_0) {
		movePaddle(0, -PADDLE_STEP);
	}
	if(g.up_1) {
		movePaddle(1, PADDLE_STEP);
	}
	if(g.down_1) {
		movePaddle(1, -PADDLE_STEP);
	}
	//movePaddle(1, -1);

	//Update ball position
	ballx += ballDirection[0]*BALL_SPEED;
	bally += ballDirection[1]*BALL_SPEED;

	//X collisions
	if(ballx <= PADDLE_0_BORDER) {
		//Detect bounce
		if(bally >= paddles[0]-BALL_SIZE && bally <= paddles[0]+PADDLE_HEIGHT) {
			paddleCollide(paddles[0]);
		} else {
			someoneWon(1);
		}
	} else if(ballx >= PADDLE_1_BORDER - BALL_SIZE) {
		//Detect bounce
		if(bally >= paddles[1]-BALL_SIZE && bally <= paddles[1]+PADDLE_HEIGHT) {
			paddleCollide(paddles[1]);
		} else {
			someoneWon(0);
		}
	}

	//Y collisions
	if(bally < 0) {
		ballDirection[1] = -ballDirection[1];
	}
	if(bally+BALL_SIZE > WINDOW_H) {
		ballDirection[1] = -ballDirection[1];
	}
}

/*  Reset game after game over, returning it to its inital state.
 *  Input:  none
 *  Output: none
 */
void resetGame() {
	gameOver = 0;
	scores[0] = 0;
	scores[1] = 0;

	paddles[0] = WINDOW_H/2-50;
	paddles[1] = WINDOW_H/2-50;

	ballx	= (float)(WINDOW_W/2);
	bally	= (float)(WINDOW_H/2);
}

/*  Main loop
 */
int main(int argc, char** argv) {
	srand(time(NULL));
	INIT_DRAWING();

	ClearAll();
	RefreshAll();

	while(1)
	{
		ClearAll();
		if(!gameOver) {
			updateGameState();

			drawLeftPaddle();
			drawRightPaddle();
			drawBall();
		} else {
			if(scores[0] > scores[1]) {
				drawLeftPaddle();
			} else {
				drawRightPaddle();
			}
			struct gamepad g = GetCurrentInput();
			if(g.start) {
				resetGame();
			}
		}
		drawScore();

		DIRTY(0, 0, WINDOW_W, WINDOW_H);

		if(count > 100) {
			count = 0;
		}
		count++;
	}
    return 0;
}

