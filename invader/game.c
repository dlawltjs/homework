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
#include "alien.h"

struct timespec work_timer;
double acc_tick,last_tick;
double acc_guid_delay_tick;
int bLoop = 1;
int nStep = 1;

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gPlasmaModel;
_S_MAP_OBJECT gAlienModel;
_S_MAP_OBJECT gMissileModel;

_S_Plane gPlayerObject;
_S_BULLET_OBJECT gBulletObjects[32];
_S_ALIEN_OBJECT gAlienObjects[8];
_S_BULLET_OBJECT gMissileObject[32];


int main()
{

	for(int i=0;i<2;i++)
	{
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],60,25);
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane1.dat");

	map_init(&gPlasmaModel);
	map_load(&gPlasmaModel,"plasma.dat");

	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien.dat");

	map_init(&gMissileModel);
	map_load(&gMissileModel,"bullet1.dat");

	Plane_init(&gPlayerObject,&gPlayerModel,30,20);

	gPlayerObject.m_nFSM = 1;

	for(int i=0;i<sizeof(gMissileObject)/sizeof(_S_BULLET_OBJECT);i++)
	{
		bullet_init(&gMissileObject[i],0,0,0,&gMissileModel);
	}

	for(int i=0;i<10;i++) 
	{
		bullet_init(&gBulletObjects[i],0,0,0,&gPlasmaModel);
	}

	double TablePosition[] = {0,8.0,16.0,24.0};

	for(int i=0;i<4;i++)
	{
		_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
		alien_init(pObj,&gAlienModel);
		pObj->m_fXpos = TablePosition[i];
		pObj->m_fYpos = 2;
		pObj->m_nFSM = 1;
		gAlienObjects[i].m_pBullet = &gBulletObjects[i];

	}


	system("clear");

	set_conio_terminal_mode();
	acc_tick=last_tick=0;
	acc_guid_delay_tick = 0;

	int shootx = 25;
	int shooty = 21;

	while(bLoop) {
		//타이밍처리 
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + 
			(double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;
		last_tick = cur_tick;

		//실시간 입력
		if(kbhit() != 0) {
			char ch = getch();
			if(ch == 'q') {
				bLoop = 0;
				puts("bye~ \r");
			}

			else if(ch == 'j') {

				for(int i=0;i<sizeof(gMissileObject)/sizeof(_S_BULLET_OBJECT);i++) {
					double vx,vy,c;
					vx = gAlienObjects[i].m_fXpos - gPlayerObject.m_fXpos;
					vy = gAlienObjects[i].m_fYpos - gPlayerObject.m_fYpos;
					c = sqrt(vx*vx+vy*vy);
					vx /= c;
					vy /= c;

					_S_BULLET_OBJECT *pObj = &gMissileObject[i];
					if(pObj->m_nFSM == 0) { //슬립상태라면..
						pObj->pfFire(pObj,gPlayerObject.m_fXpos,gPlayerObject.m_fYpos,5.0,vx,vy,10);
						break;
					}
				}

			}

			gPlayerObject.pfApply(&gPlayerObject,delta_tick,ch);	

		}

		for(int i=0;i<sizeof(gMissileObject)/sizeof(_S_BULLET_OBJECT);i++) {
			_S_BULLET_OBJECT *pObj = &gMissileObject[i];
			pObj->pfApply(pObj,delta_tick);

		}

		for(int i=0;i<4;i++ ) 
		{
			_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
			pObj->pfApply(pObj,delta_tick);

		}

		acc_guid_delay_tick += delta_tick;

		if(acc_guid_delay_tick > 1.8) {
			acc_guid_delay_tick = 0;

			for(int i=0;i<4;i++) {
				double bullet_pos_x = gBulletObjects[i].m_fXpos;
				double bullet_pos_y = gBulletObjects[i].m_fYpos;

				double target_pos_x = gPlayerObject.m_fXpos;
				double target_pos_y = gPlayerObject.m_fYpos;

				double vx = target_pos_x - bullet_pos_x;
				double vy = target_pos_y - bullet_pos_y;

				double dist = sqrt(vx*vx+vy*vy);

				vx /= dist;
				vy /= dist;

				gBulletObjects[i].m_fvx = vx;
				gBulletObjects[i].m_fvy = vy;
			}
		}


		for(int i=0;i<10;i++) {
			if(gBulletObjects[i].m_nFSM != 0) {
				double bullet_pos_x = gBulletObjects[i].m_fXpos;
				double bullet_pos_y = gBulletObjects[i].m_fYpos;

				double target_pos_x = gPlayerObject.m_fXpos;
				double target_pos_y = gPlayerObject.m_fYpos;

				double vx = target_pos_x - bullet_pos_x;
				double vy = target_pos_y - bullet_pos_y;
				double dist = sqrt(vx*vx+vy*vy);

				if(dist < 0.25) {
					gBulletObjects[i].m_nFSM = 0;
					gPlayerObject.m_nFSM = 0;
					gAlienObjects[i].m_nFSM = 0;
					
					setColor(37,41);
					printf("\n                        game over                           ");
					setColor(37,40);
					gotoxy(0,0);
				}
			}
		}

		for(int i=0;i<4;i++) {
			if(gMissileObject[i].m_nFSM != 0) {
				double bullet_pos_x = gMissileObject[i].m_fXpos;
				double bullet_pos_y = gMissileObject[i].m_fYpos;

				double target_pos_x = gAlienObjects[i].m_fXpos;
				double target_pos_y = gAlienObjects[i].m_fYpos;

				double vx = target_pos_x - bullet_pos_x;
				double vy = target_pos_y - bullet_pos_y;
				double dist = sqrt(vx*vx+vy*vy);

				if(dist < 5.0) {
					gAlienObjects[i].m_nFSM = 0;

				}
			}
		}	

		for(int i=0;i<10;i++) {
			gBulletObjects[i].pfApply(&gBulletObjects[i],delta_tick);

		}

		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);

			gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);

			for(int i=0;i<4;i++ ) 
			{
				_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}


			for(int i=0;i<10;i++) {
				gBulletObjects[i].pfDraw(&gBulletObjects[i],&gScreenBuf[1]);
			}

			for(int i=0;i<sizeof(gMissileObject)/sizeof(_S_BULLET_OBJECT);i++)
			{
				_S_BULLET_OBJECT *pObj = &gMissileObject[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}

			map_dump(&gScreenBuf[1],Default_Tilepalete);
			acc_tick = 0;

		}

	}

	return 0;

}
