#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "engine2d.h"
#include "r_game.h"

char screen_buffer[16*16];

struct timespec work_timer;
double acc_ticks, last_tick;

double rock_acc_tick,rock_acc_tick2,rock_acc_tick3;
int rock_pos_x,rock_pos_y,rock_pos_x2,rock_pos_y2,rock_pos_x3,rock_pos_y3;
int rock_pos_table[16] = {1,3,15,3,8,4,13,5,12,2,7,3,14,3,9,2};
int rock_pos_table2[16] = {8,7,5,6,13,5,1,12,2,10,8,9,2,11,3,8};
int rock_pos_table3[16] = {13,14,8,11,2,9,4,15,6,7,2,6,5,7,10,14};
int rock_cur_table_index = 0;
int rock_cur_table_index2 = 0;
int rock_cur_table_index3 = 0;

int bLoop = 1;

double acc_tick, last_tick;

int run = 0;
int run2 = 0;
int car_posx, car_posy;

static int nFSM = 0;
static int nStep = 0;

void rg_apply_mainTitle();

void rg_PlayGame(double delta_tick)
{
	switch(nStep)
	{
		case 0:
			nStep++;
			system("clear");
			nStep = 1;

			car_posy = 15;
			car_posx = 3;
			run = 0;
			run2=0;
			rock_pos_y = 0;
			rock_pos_y2 =0;
			rock_pos_y3 = 0;
			rock_pos_x = rock_pos_table[ rock_cur_table_index ];
			rock_pos_x2 = rock_pos_table2[ rock_cur_table_index2 ];
			rock_pos_x3 = rock_pos_table3[ rock_cur_table_index3 ];
			break;

		case 1:

			//사용자 입력처리
			if(kbhit() != 0) {
				char ch = getch();
				if(ch == 'q') {
					bLoop = 0;
				}
				else if(ch == 'a') { 
					car_posx -= 1;
				}
				else if(ch == 'd') {
					car_posx +=1;
				}
			}



			//게임로직(판정)
			if(rock_pos_y == car_posy && rock_pos_x == car_posx || rock_pos_y2 ==car_posy && rock_pos_x2 == car_posx || rock_pos_y3 == car_posy && rock_pos_x3 == car_posx) {
				setColor(37,41);
				printf("\n    game over   \r\n");
				setColor(37,40);

				printf("\n게임을 다시 시작하시겠습니까?(y/n) \r\n");

				char ch = getch();

				if(ch == 'y') {
					nStep = 0;
				}
				else {
					bLoop = 0;;
					system("clear");
				}
			}



			//버퍼초기화
			for(int i=0;i<256;i++) {
				screen_buffer[i] = 0;

			}

			//자동차 그리기
			screen_buffer[ car_posy*16 + car_posx] = 2;

			//바위 움직이기
			rock_acc_tick += delta_tick;

			if(rock_acc_tick > 0.4) {
				rock_acc_tick = 0;
				rock_pos_y += 1;
				//화면끝도달..
				if(rock_pos_y >= 16) {
					rock_pos_y = 0;
					rock_cur_table_index++;
					rock_cur_table_index %= 16;
					rock_pos_x = rock_pos_table[rock_cur_table_index];
				}

			}

			//바위그리기
			screen_buffer[ rock_pos_y*16 + rock_pos_x ] = 1;

			if(rock_pos_y*16 + rock_pos_x > 64 && rock_pos_y*16 + rock_pos_x < 80) {
				run = 1;
			}

			if( run == 1) {
				rock_acc_tick2 += delta_tick;
				if(rock_acc_tick2 > 0.2) {
					rock_acc_tick2 = 0;
					rock_pos_y2 += 1;
					//화면끝도달..
					if(rock_pos_y2 >= 16) {
						rock_pos_y2 = 0;
						rock_cur_table_index2++;
						rock_cur_table_index2 %= 16;
						rock_pos_x2 = rock_pos_table2[rock_cur_table_index2];
					}

				}
				screen_buffer[ rock_pos_y2*16 + rock_pos_x2 ] = 1;

			}

			if(rock_pos_y*16 + rock_pos_x > 112 && rock_pos_y*16 + rock_pos_x < 128) {
				run2 = 1;
			}

			if( run2 == 1) {
				rock_acc_tick3 += delta_tick;
				if(rock_acc_tick3 > 0.3) {
					rock_acc_tick3 = 0;
					rock_pos_y3 += 1;
					//화면끝도달..
					if(rock_pos_y3 >= 16) {
						rock_pos_y3 = 0;
						rock_cur_table_index3++;
						rock_cur_table_index3 %= 16;
						rock_pos_x3 = rock_pos_table3[rock_cur_table_index3];
					}

				}
				screen_buffer[ rock_pos_y3*16 + rock_pos_x3 ] = 1;


			}


			acc_tick += delta_tick;
			if(acc_tick > 0.1 || bLoop == 0) {
				acc_tick = 0;
				drawGame(16,16,screen_buffer);

			}
			break;

	}


}

void rg_apply_mainTitle()
{
	switch(nStep) {
		case 0 :
			puts("press to start");
			nStep = 1;
			break;

		case 1 :
			//사용자 입력처리
			if(kbhit() != 0) {
				char ch = getch();
				nFSM = 1;
				nStep = 0;
			}
			break;
	}

}

int main()
{
	//버퍼초기화
	for(int i=0;i<256;i++) {
		screen_buffer[i] = 0;

	}

	set_conio_terminal_mode();

	acc_tick = last_tick = 0;
	system("clear");

	car_posy = 15;
	car_posx = 3;

	rock_pos_y = 0;
	rock_pos_x = rock_pos_table[ rock_cur_table_index ];
	rock_pos_x2 = rock_pos_table[ rock_cur_table_index ];

	while(bLoop) {

		//타이밍처리
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + (double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;
		last_tick = cur_tick;

		if(nFSM == 0) { //타이틀 메뉴상태
			rg_apply_mainTitle(delta_tick);	
		}
		else if(nFSM == 1) { //게임상태
			rg_PlayGame(delta_tick);
		}
		else {

		}


	}
	return 0;
}
