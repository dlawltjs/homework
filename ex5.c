#include <stdio.h>
#include <stdlib.h>

#include "../mapEditor/map.h"

void map_drawTile_trn(_S_MAP_OBJECT *pObj,char *pTile_pal, char *pBuffer) 
{
	int nSize = pObj->m_header.m_nWidth * pObj->m_header.m_nHeight;
	pBuffer = malloc(nSize);

	for(int iy=0;iy < pObj->m_header.m_nHeight;iy++) {
		for(int ix=0;ix < pObj->m_header.m_nWidth;ix++) {
			pBuffer = pTile_pal[ pObj->m_pBuf[iy * pObj->m_header.m_nWidth + ix]];
		}
	}

}

int main()
{
	_S_MAP_OBJECT screenBuf;
	map_init(&screenBuf);
	map_new(&screenBuf,16,16);


	map_PutTile(&screenBuf,6,5,4);	
	map_PutTile(&screenBuf,5,5,4);	
	map_PutTile(&screenBuf,4,5,4);	
	map_PutTile(&screenBuf,6,6,4);	
	map_PutTile(&screenBuf,5,6,4);	
	map_PutTile(&screenBuf,4,6,4);	
	map_PutTile(&screenBuf,6,7,4);	
	map_PutTile(&screenBuf,5,7,4);	
	map_PutTile(&screenBuf,4,7,4);	
	
	_S_MAP_OBJECT humanObj;
	map_init(&humanObj);
	map_load(&humanObj,"human.dat");
	puts("-------------------");
	map_drawTile(&humanObj,5,5,&screenBuf);
	map_drawTile_trn(&screenBuf,Default_Tilepalete,&screenBuf);
	map_dump(&screenBuf,Default_Tilepalete);
	
	return 0;
}
