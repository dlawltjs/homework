#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int bLoop = 1;
	char *strLine[128] = {0};
	int nTailIndex = 0;

	puts("\nmyeditor version 1.0");

	while(bLoop) {
		char *pTemp;
		char strCmd[128];
		gets(strCmd);

		pTemp = strtok(strCmd," ");
		
		if(!strcmp(pTemp,"exit")) {
			bLoop = 0;

		}
		else if(!strcmp(pTemp,"push")) {
			//push 원하는 문자열 입력
			pTemp = strtok(NULL,"");
			
			char *pstr = (char *)malloc(strlen(pTemp)+1);
			strcpy(pstr,pTemp);
			strLine[nTailIndex++] = pstr;
			
		}
		else if(!strcmp(pTemp,"pop")) {
			nTailIndex--;
			free(strLine[nTailIndex]);
			strLine[nTailIndex] = 0x00;
			
		}
		else if(!strcmp(pTemp,"del")) {
			free(strLine[0]);	
			for(int i=0;i<nTailIndex;i++) {
				strLine[i] = strLine[i+1];
			}
			nTailIndex--;
		}
		else if(!strcmp(pTemp,"ins")) {
			//ins 2 원하는 문자열 입력
			int nIndex = atoi(strtok(NULL," "));
			pTemp = strtok(NULL,"");
			printf("%d, %s 추가 \r\n",nIndex,pTemp);

			int i;	
			for(i=nTailIndex;i>nIndex;i--) {
				strLine[i] = strLine[i-1];
			}
	
			char *pstr = (char *)malloc(strlen(pTemp)+1);
			strcpy(pstr,pTemp);
			strLine[i] = pstr;
			nTailIndex++;
			
		}
		else if(!strcmp(pTemp,"rm")) {
			//rm 1
			int nIndex = atoi(strtok(NULL," "));
			free(strLine[nIndex]);	
			
			for(int i=nIndex;i<nTailIndex;i++) {
				strLine[i] = strLine[i+1];
			}
			nTailIndex--;
			strLine[nTailIndex] = 0x00;
		}
		else if(!strcmp(pTemp,"set")) {
			//set 1 new string
			int nIndex = atoi(strtok(NULL," "));
			free(strLine[nIndex]);
			pTemp = strtok(NULL,"");
			char *pstr = (char *)malloc(strlen(pTemp)+1);
			strcpy(pstr,pTemp);
			strLine[nIndex] = pstr;

		}
		else if(!strcmp(pTemp,"reverse")) {
			char *pstr = (char *)malloc(strlen(pTemp)+1);

			for(int i=0;i<nTailIndex/2;i++) {
				pstr = strLine[i];
				strLine[i] = strLine[(nTailIndex - 1) - i];
				strLine[(nTailIndex - 1) - i] = pstr;


			}
		}
		else if(!strcmp(pTemp,"dump")) {

			puts("---------------------");
			for(int i=0;strLine[i] != 0x00;i++) {
				puts(strLine[i]);

			}
			puts("---------------------");

		}
	
	
	
	}

	return 0;
}
