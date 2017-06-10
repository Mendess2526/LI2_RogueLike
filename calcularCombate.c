#include "calcularCombate.h"

int samePos(POSICAO monPos, MSTR monster){
	return monPos.x == monster.x && monPos.y == monster.y;
}
void killMonster(int i, MSTR monstros[], int num_monstros){
	monstros[i]=monstros[num_monstros];
}
void dropItem(CHEST droppedItems[], int *item, POSICAO pos){
	int j=0;
	while(droppedItems[j].item!=0 && j<MAX_DROPPED_ITEMS){
		j++;
	}
	if(j==MAX_DROPPED_ITEMS){
		perror("Not enough space to drop item!");
	}else{
		droppedItems[j].item = *item;
		droppedItems[j].pos = pos;
		*item=0;
	}
}
void dropItemFromMSTR(int lootTable[], CHEST droppedItems[], int x, int y){
	int chance = rand() % 2;
	if(chance==0){
		int i=0;
		while(lootTable[i]==0 && i<LOOT_TABLE_SIZE){
			i++;
		}
		if(i!=LOOT_TABLE_SIZE){
			POSICAO pos = {x,y};
			dropItem(droppedItems,&lootTable[i],pos);
		}
	}
}
int calcPlayerDmg(int classe, INVT bag){
	int weaponDmgs[] = WEAPON_DMG_ARRAY;
	int plrDmgs[] = BASE_DMG_ARRAY;
	return weaponDmgs[bag.weapon-9] + plrDmgs[classe];
}
int updateScore(int type){
	int scores[] = SCORE_GAIN_ARRAY;
	return scores[type];
}
int goldDrop(int type){
	int goldGains[] = GOLD_DROP_ARRAY;
	return goldGains[type];
}
POSICAO calculaRangedAtackPos(POSICAO p,int act){
	act-=20;
	int x[10]={5,-1, 0, 1,-2, 5, 2,-1, 0, 1};
	/*         0  1  2  3  4  5  6  7  8  9 */
	int y[10]={5, 1, 2, 1, 0, 5, 0,-1,-2,-1};

	if(act!=0 && act!=5){
		p.x+=x[act];
		p.y+=y[act];
	}
	return p;
}
int getMonstro(ESTADO e,POSICAO p){
	int i, found;
	i=found=0;
	while(!found && i<e.num_monstros){
		if(samePos(p,e.monstros[i])){
			found=1;
		}else{
			i++;
		}
	}
	return i;
}
int hitMonster(ESTADO *e, POSICAO target, int dmg){
	int monIdx = getMonstro(*e,target);
	if(monIdx < e->num_monstros){
		e->monstros[monIdx].hp-=dmg;
		if(e->monstros[monIdx].hp<1){
			e->score+=updateScore(e->monstros[monIdx].monType);
			e->bag.gold+=goldDrop(e->monstros[monIdx].monType);
			dropItemFromMSTR(e->lootTable,e->droppedItems,e->monstros[monIdx].x, e->monstros[monIdx].y);
			killMonster(monIdx,e->monstros,--e->num_monstros);
		}
	}
	return monIdx < e->num_monstros;
}
ESTADO calcularCombate(ESTADO e){
	POSICAO mon = {-1,-1};
	char plrDmg;
	if(e.action<20){
		mon = calcularNovaPosicao(e.jog,e.action-10);	
	}else if(e.action<30){
		mon = calculaRangedAtackPos(e.jog,e.action);
	}
	plrDmg = calcPlayerDmg(e.classe,e.bag);
	if(!hitMonster(&e,mon,plrDmg)){
		perror("Couldn't find monster");
	}
	return e;
}