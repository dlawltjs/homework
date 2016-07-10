#ifndef __RGAME_H__
#define __RGAME_H__

void drawGame(int mx, int my, char *pBuf)
{
	//렌더링
	gotoxy(1,1);
	int x, y;
	for(y=0;y<my;y++) {
		for(x=0;x<my;x++) {
			switch( pBuf[mx*y + x]) {
				case 0:
					putchar('.');
					break;

				case 1:
					setColor(35,40);
					putchar('#');
					setColor(0,0);
					break;

				case 2:
					setColor(33,40);
					putchar('A');
					setColor(0,0);
					break;
			}
		}
		printf("\r\n");
	}

}




#endif
