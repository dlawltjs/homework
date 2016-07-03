#include <stdio.h>
#include <stdlib.h>
#include "../engine2d.h"
#include "exit_room.h"

/*
1 : 벽 #
2 : 열린문 M
3 : 게이머 A
4 : 잠긴문 m
5 : 키 K
 
*/


int world_map[] = {
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,1,0,0,0,1,
	1,0,0,1,0,0,0,4,
	1,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,5,0,1,
	1,1,1,1,1,1,1,1
};

int world_map2[] = {
	1,1,1,1,1,1,1,1,
	1,5,0,0,0,0,0,1,
	1,1,1,1,0,0,0,1,
	1,0,0,1,0,0,0,4,
	1,0,0,0,0,1,0,1,
	1,0,0,1,1,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1
};

int game_version = 1;
char *game_name = "방탈출게임";

int player_inven; //0:없음, 1:키보유

int main()
{
	system("clear");

	char cmd;
	int bLoop = 1;

	while (bLoop) {
		switch(nFSM) {
			case 0:
				printf("%s의 세계에 오신것을 환영합니다! v.%d \r\n",game_name,game_version);
				printf("select => [p,x] \r\n");
				break;

			case 1:
				printf("\r\n명령을 선택하세요.\r\ni(up),j(left),k(rignt),\r\nm(down),s(show map),x(exit)\r\n");
				break;

			case 2:
				game_version = 2;
				printf("다음스테이지! v.%d \r\n",game_version);
				printf("\r\n명령을 선택하세요.\r\ni(up),j(left),k(rignt),\r\nm(down),s(show map),x(exit)\r\n");
				break;
		}


		//버퍼초기화
		for(int i=0;i<64;i++) {
			buffer_map[i] = world_map[i];
			buffer_map2[i] = world_map2[i];
		}

		scanf("%c",&cmd);
		getchar();

		if(nFSM == 0) {
			switch(cmd) {
				case 'p' : //게임스타트
					nFSM = 1;
					player_ypos = 5;
					player_xpos = 1;
					player_inven = 0;
					printf("\r\n게임을 시작합니다.");
					break;

				case 'x' : //게임종료
					bLoop = 0;
					printf("bye bye~ \r\n");
					break;
						
			}
		}
		else if(nFSM == 1) { //게임플레이 중일때..
			move_player(cmd);
			switch(cmd) {
				case 's':
						map_drawAll(buffer_map);
					break;

				case 'x':
					printf("bye bye~ \r\n");
					bLoop = 0;
					break;

			}

		}
		else if(nFSM == 2) {
			//nFSM = 1;

			for(int i=0;i<64;i++) {
				buffer_map[i] = buffer_map2[i];
			}
			move_player(cmd);
			switch(cmd) {
				case 's':
					map_drawAll(buffer_map);
					break;

				case 'x':
					printf("bye bye~ \r\n");
					bLoop = 0;
					break;

			}


		}



	}

	return 0;
}

