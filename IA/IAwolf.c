//#define DEBUG
#include <stdio.h>
#include "IAwolf.h"

ESTADO persegue_wolf_SE (ESTADO e,int i,POSICAO p,int a[SIZE][SIZE]){
	int x,y,flag;
	POSICAO pos;
	flag=1;
	for(x=p.x+1;x>=p.x-1 && flag;x--){
		for(y=p.y+1;y>=p.y-1 && flag;y--){
			pos.x=x;
			pos.y=y;
			if(a[x][y]<=a[p.x][p.y] && !com_monstros(e,pos) && !com_pedras(e,pos)){
				e.monstros[i].x=x;
				e.monstros[i].y=y;
				flag=0;
			}
		}
	}
	return e;
}
ESTADO persegue_wolf_NE (ESTADO e,int i,POSICAO p,int a[SIZE][SIZE]){
	int x,y,flag;
	POSICAO pos;
	flag=1;
	for(x=p.x+1;x>=p.x-1 && flag;x--){
		for(y=p.y-1;y<=p.y+1 && flag;y++){
			pos.x=x;
			pos.y=y;
			if(a[x][y]<=a[p.x][p.y] && !com_monstros(e,pos) && !com_pedras(e,pos)){
				e.monstros[i].x=x;
				e.monstros[i].y=y;
				flag=0;
			}
		}
	}
	return e;
}
ESTADO persegue_wolf_SO (ESTADO e,int i,POSICAO p,int a[SIZE][SIZE]){
	int x,y,flag;
	POSICAO pos;
	flag=1;
	for(x=p.x-1;x<=p.x+1 && flag;x++){
		for(y=p.y+1;y>=p.y-1 && flag;y--){
			pos.x=x;
			pos.y=y;
			if(a[x][y]<=a[p.x][p.y] && !com_monstros(e,pos) && !com_pedras(e,pos)){
				e.monstros[i].x=x;
				e.monstros[i].y=y;
				flag=0;
			}
		}
	}
	return e;
}
ESTADO persegue_wolf_NO (ESTADO e,int i,POSICAO p,int a[SIZE][SIZE]){
	int x,y,flag;
	POSICAO pos;
	flag=1;
	for(x=p.x-1;x<=p.x+1 && flag;x++){
		for(y=p.y-1;y<=p.y+1 && flag;y++){
			pos.x=x;
			pos.y=y;
			if(a[x][y]<=a[p.x][p.y] && !com_monstros(e,pos) && !com_pedras(e,pos)){
				e.monstros[i].x=x;
				e.monstros[i].y=y;
				flag=0;
			}
		}
	}
	return e;
}
ESTADO persegue_wolf (ESTADO e,int i,POSICAO p,int a[SIZE][SIZE]){
	int flag=1;
	/* // implementar modo mais inteligente no nivel 8
	if(e.world_lvl>10) {
		e=persegue_wolf1(e,i,p,a);
		flag=0;
	}
	*/
	if(flag && p.x<e.jog.x && p.y<e.jog.y){
		e=persegue_wolf_SE(e,i,p,a);
		flag=0;
	}
	if(flag && p.x<e.jog.x && p.y>e.jog.y){
		e=persegue_wolf_NE(e,i,p,a);
		flag=0;
	}
	if(flag && p.x>e.jog.x && p.y<e.jog.y){
		e=persegue_wolf_SO(e,i,p,a);
		flag=0;
	}
	if(flag && p.x>e.jog.x && p.y>e.jog.y){
		e=persegue_wolf_NO(e,i,p,a);
		flag=0;
	}
	return e;
}
ESTADO defesa_WOLF_NE (ESTADO e, int i,POSICAO p,int a[SIZE][SIZE]){
	int x,y,d,flag;
	POSICAO pos;
	flag=1;
	d= a[p.x][p.y]/2; // o monstro deve ir para d para intersetar o jogador;
	for(x=p.x-1;x<=p.x+1 && flag;x++){
		for(y=p.y-1;y<=p.y+1 && flag;y++){
			pos.x=x;
			pos.y=y;
			if(a[x][y]>=d && a[x][y]<a[p.x][p.y] && !com_monstros(e,pos)){
				e.monstros[i].x=x;
				e.monstros[i].y=y;
				flag=0;
			}
		}
	}
	return e;
}
ESTADO defesa_WOLF_NO (ESTADO e, int i,POSICAO p,int a[SIZE][SIZE]){
	int x,y,d,flag;
	POSICAO pos;
	flag=1;
	d= a[p.x][p.y]/2; // o monstro deve ir para d para intersetar o jogador;
	for(x=p.x+1;x>=p.x-1 && flag;x--){
		for(y=p.y-1;y<=p.y+1 && flag;y++){
			pos.x=x;
			pos.y=y;
			if(a[x][y]>=d && a[x][y]<a[p.x][p.y] && !com_monstros(e,pos)){
				e.monstros[i].x=x;
				e.monstros[i].y=y;
				flag=0;
			}
		}
	}
	return e;
}
ESTADO defesa_WOLF_SE (ESTADO e, int i,POSICAO p,int a[SIZE][SIZE]){
	int x,y,d,flag;
	POSICAO pos;
	flag=1;
	d= a[p.x][p.y]/2; // o monstro deve ir para d para intersetar o jogador;
	for(x=p.x+1;x>=p.x-1 && flag;x--){
		for(y=p.y+1;y>=p.y-1 && flag;y--){
			pos.x=x;
			pos.y=y;
			if(a[x][y]>=d && a[x][y]<a[p.x][p.y] && !com_monstros(e,pos)){
				e.monstros[i].x=x;
				e.monstros[i].y=y;
				flag=0;
			}
		}
	}
	return e;
}
ESTADO defesa_WOLF_SO (ESTADO e, int i,POSICAO p,int a[SIZE][SIZE]){
	int x,y,d,flag;
	POSICAO pos;
	flag=1;
	d= a[p.x][p.y]/2; // o monstro deve ir para d para intersetar o jogador;
	for(x=p.x-1;x<=p.x+1 && flag;x++){
		for(y=p.y+1;y>=p.y-1 && flag;y--){
			pos.x=x;
			pos.y=y;
			if(a[x][y]>=d && a[x][y]<a[p.x][p.y] && !com_monstros(e,pos)){
				e.monstros[i].x=x;
				e.monstros[i].y=y;
				flag=0;
			}
		}
	}
	return e;
}
void distancia_WOLF (ESTADO e,int a[SIZE][SIZE],int x,int y,int i){
		int a1,a2;
		POSICAO pos;
		if(x<10 && x>=0 && y<10 && y>=0){
			pos.x=x;
			pos.y=y;
			if(!com_pedras(e,pos) && i<a[x][y] && !com_monstros(e,pos)){
				a[x][y]=i;
				i++;
				for(a1=x-1;a1<=x+1;a1++){
					for(a2=y-1;a2<=y+1;a2++){
						if(a1!=x || a2!=y){
							distancia_WOLF(e,a,a1,a2,i);
						}
					}
				}
			}
		}
}
void preenche_matriz(int a[SIZE][SIZE]){
	int x,y;
	for(x=0;x<10;x++){
		for(y=0;y<10;y++){
			a[x][y]=50;
		}
	}
}
ESTADO estrat_wolf (ESTADO e,int i,POSICAO p){
	int flag=1;
	int a[SIZE][SIZE];
	preenche_matriz(a);
	distancia_WOLF(e,a,e.jog.x,e.jog.y,0);
	if (existe_jogador(e,p)){
		e=ataca_jogador(e,WOLF_DMG);
		flag=0;
	} // J M →ŧ
	if(flag && BLOQUEAVEL_NE){
		e=defesa_WOLF_NE(e,i,p,a);
		flag=0;
	} // J M←ŧ
	if(flag && BLOQUEAVEL_NO){
		e= defesa_WOLF_NO(e,i,p,a);
		flag=0;
	} // J M←↓
	if(flag && BLOQUEAVEL_SE){
		e=defesa_WOLF_SE(e,i,p,a);
		flag=0;
	} // J M→↓
	if(flag && BLOQUEAVEL_SO){
		e=defesa_WOLF_SO(e,i,p,a);
		flag=0;
	} // na persegue dá-se primasia as diagonais
	if(flag) e=persegue_wolf(e,i,p,a);
	return e;
}