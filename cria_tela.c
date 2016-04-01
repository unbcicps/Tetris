	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	void mostra_tela(void *cria_tela){
			
			char Enter;
			do{
				printf("\tAperte em qualquer tecla e/ou Enter Para começar\n");
					Enter = getchar();
						printf("\n");
			}while(Enter != '\n');						
/****************************************Fazer (Função que dá GAME OVER ao perder o jogo)**********************************************/

	}
/****************************************Fazer (Função do TEMPO)***********************************************************************/

	void *cria_tela(int l,int c,int L, int C){
	char matriz[L][C];
		for(l=0;l!=L;l++){
			for(c=0;c!=C;c++){
				matriz[l][c] = 'o';
		}
	}

		for(l=0;l!=L;l++){
			for(c=0;c!=C;c++){
				if((l==0)||(l==L-1)||(c==0)||(c==C-1)||(l==4)){
					printf("%c ",matriz[l][c]);
			}else{
				printf("  ");
		}}
			printf("\n");
		}
	return 0;
	}

	int main(){
	
	mostra_tela(*cria_tela);
	cria_tela(0,0,25,15);

	return 0;
	}
