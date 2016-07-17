#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"
#include "plane.h"

void Plane_init(_S_Plane *pObj,_S_MAP_OBJECT *pBody,int x,int y)
{
	pObj->m_pBody = pBody;
	pObj->m_nYpos = y;
	pObj->m_nXpos = x;

}

void Plane_Apply(_S_Plane *pObj,double deltaTick,char key_input)
{
	switch(key_input)
	{
		case 'a':
			pObj->m_nXpos -= 1;
			break;

		case 'd':
			pObj->m_nXpos += 1;
			break;

		case 'w':
			pObj->m_nYpos -= 1;
			break;

		case 's':
			pObj->m_nYpos += 1;
			break;

	}

}

void Plane_Draw(_S_Plane *pObj,_S_MAP_OBJECT *pBuff)
{
	map_drawTile_trn(pObj->m_pBody,pObj->m_nXpos,pObj->m_nYpos,pBuff);
}


