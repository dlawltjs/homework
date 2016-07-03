#ifndef __ENGIINE_2D__

#define __ENGIINE_2D__

void setColor(int fore_color,int backg_color)
{
	printf("%c[%d;%dm",0x1b,fore_color,backg_color);
}

void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1b,y,x);
}


int drawMyBox(int nXpos,int nYpos,int nColor,int size)
{
	int ix, iy;

	setColor(30,nColor);
	ix = 0;

	for(iy = 0;iy <= size;iy++) {
		for(ix = 0;ix <= size;ix++) {
			gotoxy(ix+nXpos,iy+nYpos);
			printf(" ");
		}

	}
	setColor(0,0);
}

//----------------타일맵 엔진
void map_printCell(int rawdata)
{
	switch(rawdata) {
		case 0: //공터
			setColor(33,40);
			printf(" ");
			break;

		case 1: //벽
			setColor(32,40);
			printf("▪");
			break;

		case 2: //문
			setColor(0,40);
			printf("M");
			break;

		case 3:
			setColor(33,40);
			printf("☺");
			break;

		case 4:
			setColor(0,40);
			printf(" ");
			break;

		case 5:
			setColor(35,40);
			printf("✿");
			break;

		default:
			setColor(0,0);
			printf(" ");
			break;

	}
	setColor(0,0);

}

void map_drawAll(int *pMap)
{
	int ix, iy;

	for(iy=0;iy<8;iy++) {
		for(ix=0;ix<8;ix++) {
			map_printCell(pMap[ix+iy*8]);

		}
		printf("\r\n");

	}


}

#endif
