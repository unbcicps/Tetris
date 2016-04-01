#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int cria_tela(int l,int c,int L, int C){
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
return matriz[l][c];
}

int main(){

cria_tela(0,0,25,15);

return 0;
}
/*IMPRIME A MOLDURA DA MATRIZ NA TELA*/
