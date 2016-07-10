#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char *m_szName;
	void *node[8];
} _S_AREA;

int main()
{
	_S_AREA town = {
		"town",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};
	_S_AREA dungeon_1 = {
		"dungeon-1",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};
	_S_AREA home = {
		"home",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};


	town.node[0] = &dungeon_1;
	//dungeon_1.node[0] = &town;

	dungeon_1.node[0] = &home;
	home.node[0] = &town;

	_S_AREA *pCurrentArea = &town;

	int bLoop = 1;
	while(bLoop) {
		char szCmd[32];
		gets(szCmd);
		char *pTemp = strtok(szCmd," ");

		if(!strcmp(pTemp,"look")) {
			printf("당신은 %s 에 서있습니다. \r\n",pCurrentArea->m_szName);	


			for(int i=0;i<8;i++) {
				_S_AREA *pNode = pCurrentArea->node[i];

				if(pNode == NULL) break;

				_S_AREA *p2Node = pNode->node[i];

				if(p2Node == NULL) break;
				else {
					printf("당신은 %s, %s 으로 이동할 수 있습니다. \r\n\n",pNode->m_szName,p2Node->m_szName);

					if(!strcmp(pCurrentArea->m_szName,"town")) {
						pCurrentArea = pNode;
						pNode = p2Node;
						p2Node = pCurrentArea;
					}
					else if(!strcmp(pCurrentArea->m_szName,"dungeono-1")) {
						pNode = p2Node;
						p2Node = pCurrentArea;
						pCurrentArea = pNode;
					}
					else if(!strcmp(pCurrentArea->m_szName,"home")) {
						p2Node = pCurrentArea;
						pCurrentArea = pNode;
						pNode = p2Node;
					}


				}
			}
		}

		else if( !strcmp(pTemp,"move")) {
			char *pszArea = strtok(NULL,"");
			printf("%s 으로 이동합니다. \r\n\n",pszArea);
			for(int i=0;i<8;i++) {
				_S_AREA *pNode = pCurrentArea->node[i];
				if(pNode == NULL) break;

				//puts(pNode->m_szName);
				if(!strcmp(pNode->m_szName,pszArea)) {
					printf("이동성공! \r\n");
					
					pCurrentArea = pNode;
				}
			}

		}
		else if(!strcmp(pTemp,"exit")) {
			bLoop = 0;
		}
	}

}
