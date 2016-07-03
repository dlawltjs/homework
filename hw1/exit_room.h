#ifndef __EXIT_ROOM_H__
#define __EXIT_ROOM_H__

int buffer_map[64];
int buffer_map2[64];
int key_status;

int nFSM = 0; //0:준비 1:게임 플레이 2:레벨클리어 3:게임오버 

int player_xpos;
int player_ypos;
int player_inven; //0:없음 1:키보유 

void move_player(char cmd)
{
	int old_xpos = player_xpos;
	int old_ypos = player_ypos;

	system("clear");

	switch(cmd)
	{
		case 'i':
			printf("위로 한칸 이동했습니다.\r\n");
			player_ypos -=1;
			break;
		
		case 'j':
			printf("왼쪽으로 한칸 이동했습니다.\r\n");
			player_xpos -=1;
			break;
		
		case 'k':
			printf("오른쪽으로 한칸 이동했습니다.\r\n");
			player_xpos += 1;
			break;
		
		case 'm':
			printf("아래로 한칸 이동했습니다.\r\n");
			player_ypos += 1;
			break;
	}

	switch( buffer_map[ player_xpos + player_ypos*8 ] ) {
		case 0: //공간
			break;

		case 1: //벽
			player_ypos = old_ypos;
			player_xpos = old_xpos;
			break;

		case 2: //문 
			printf("미션 클리어~~ \r\n");
			nFSM = 2;
			break;

		case 4:
			if(player_inven ==1) {
				printf("미션클리어~~ \r\n");
				player_xpos = 2;
				player_ypos = 6;
				nFSM = 2;
			}
			else {
				player_ypos = old_ypos;
				player_xpos = old_xpos;

			}
			break;

		case 5: //
			printf("키를 얻었습니다. \r\n");
			player_inven = 1;
			key_status = player_xpos + player_ypos*8;		
			break;

	}

	buffer_map[ player_xpos + player_ypos*8 ] = 3;
	
	switch(player_inven){
		case 1:
		buffer_map[ key_status ] = 0;
		buffer_map[ player_xpos + player_ypos*8 ] = 3;

		if(buffer_map[player_xpos + player_ypos*8 ] == 4) {
			nFSM = 2;
		}
		break;
	}
}

#endif

