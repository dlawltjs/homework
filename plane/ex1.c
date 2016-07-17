#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"

#include "plane.h"
#include "bullet.h"


struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuffer;
_S_MAP_OBJECT gBackBuffer;
_S_MAP_OBJECT gF22Raptor;
_S_MAP_OBJECT gF22Bullet;


//게임오브젝트 선언
_S_Plane gPlayerPlane;
S_BULLET_OBJECT g_bullets[32];

S_BULLET_OBJECT gmissile;
_S_MAP_OBJECT gBulletModel;

int main()
{
	set_conio_terminal_mode();
	acc_tick = last_tick = 0;
	system("clear");

	map_init(&gScreenBuffer);
	map_new(&gScreenBuffer,50,23);

	map_init(&gBackBuffer);
	map_new(&gBackBuffer,50,23);

	map_init(&gF22Raptor);
	map_load(&gF22Raptor,"plane1.dat");

	map_init(&gF22Bullet);
	map_load(&gF22Bullet,"bullet1.dat");

	Plane_init(&gPlayerPlane,&gF22Raptor,22,17);	

	map_init(&gBulletModel);
	map_load(&gBulletModel,"plasma.dat");
	bullet_init(&gmissile,0,0,0,&gBulletModel);
	


	for(int i=0;i<sizeof(g_bullets)/sizeof(S_BULLET_OBJECT);i++)
	{
		bullet_init(&g_bullets[i],0,0,0,&gF22Bullet);
	}

	int shootx = 25;
	int shooty = 21;
	
	int fire_x = 25;
	int fire_y = 0;


	while(bLoop) {

		//타이밍처리
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + (double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;
		last_tick = cur_tick;

		double vx,vy,c;
		//실시간입력	
		if(kbhit() != 0) {
			char ch = getch();
			if(ch == 'q') {
				bLoop = 0;
				puts("bye~\r");
			}

			else if(ch == 'j') {
				for(int i=0;i<sizeof(g_bullets)/sizeof(S_BULLET_OBJECT);i++) {
					double vx,vy,c;
					vx = gPlayerPlane.m_nXpos - shootx;
					vy = gPlayerPlane.m_nYpos - shooty;
					c = sqrt(vx*vx+vy*vy);
					vx /= c;
					vy /= c;

					S_BULLET_OBJECT *pObj = &g_bullets[i];
					if(pObj->m_nFSM == 0) { //슬립상태라면..
						setColor(33,40);
						bullet_fire(pObj,gPlayerPlane.m_nXpos,gPlayerPlane.m_nYpos,5.0,vx,vy,10);
						setColor(0,0);
						break;
					}
				}


			}

			else if(ch == 'k') {
				double vx,vy,c;
				vx = gPlayerPlane.m_nXpos - fire_x;
				vy = gPlayerPlane.m_nYpos - fire_y;
				c = sqrt(vx*vx+vy*vy);
				vx /= c;
				vy /= c;

				bullet_fire(&gmissile,fire_x,fire_y,5.0,vx,vy,10);
			

			}
		
			Plane_Apply(&gPlayerPlane,delta_tick,ch);
			

		}

		for(int i=0;i<sizeof(g_bullets)/sizeof(S_BULLET_OBJECT);i++) {
			S_BULLET_OBJECT *pObj = &g_bullets[i];
			bullet_apply(pObj,delta_tick);

		}

		bullet_apply(&gmissile,delta_tick);

		//타이밍계산
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {

			map_drawTile(&gBackBuffer,0,0,&gScreenBuffer); //클리어

			//map_drawTile_trn(&gF22Raptor,xpos,ypos,&gScreenBuffer); //오브젝트 출력
			Plane_Draw(&gPlayerPlane,&gScreenBuffer);
		
			bullet_draw(&gmissile,&gScreenBuffer);

			for(int i=0;i<sizeof(g_bullets)/sizeof(S_BULLET_OBJECT);i++)
			{
				S_BULLET_OBJECT *pObj = &g_bullets[i];

					bullet_draw(pObj,&gScreenBuffer);
			}
			
			gotoxy(0,0);
			map_dump(&gScreenBuffer,Default_Tilepalete);
			
			puts("move : w,a,s,d \r");
			puts("quit : q \r");
			
			acc_tick = 0;
		}

	}

	return 0;
}
