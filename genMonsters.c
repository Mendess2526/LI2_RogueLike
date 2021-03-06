#include "genMonsters.h"

ESTADO genBoss(ESTADO e){
	e.dragon.side = 0;
	e.dragon.pos.x = (SIZE / 2) - 2;
	e.dragon.pos.y = 1;
	e.dragon.attack = 0;
	e.dragon.num_fireballs = 0;
	e.dragon.hp = MON_HP_DRAGON;
	e.dragon.poison = 0;
	return e;
}
ESTADO genBossBattle(ESTADO e){
	e.jog.x=5;
	e.jog.y=9;
	e.saida.x=SIZE+2;
	e.saida.y=SIZE+2;
	return genBoss(e);
}
int getNumMonst(int world_lvl){
	int num_monstros = (world_lvl/3)+4;
	return ((num_monstros>MAX_MONSTROS) ? MAX_MONSTROS : num_monstros);
}
int getMonsterHP(int type){
	int monHp = 0;
	switch(type){
		case 0: monHp = MON_HP_WOLF;
				break;
		case 1: monHp = MON_HP_BAT;
				break;
		case 2: monHp = MON_HP_OGRE;
				break;
		case 3: monHp = MON_HP_ARCHER;
				break;
	}
	return monHp;
}
ESTADO placeMonster(ESTADO e, int type){
	POSICAO p;
	int placed=0, i=0;
	while(!placed && i<20){
		i++;
		p.x=rand() % SIZE;
		p.y=rand() % (SIZE-2);
		if (!pos_ocupada(e,p) && !com_chest(e,p)){
			placed=1;
			e.monstros[e.num_monstros].x=p.x;
			e.monstros[e.num_monstros].y=p.y;
			e.monstros[e.num_monstros].monType=type;
			e.monstros[e.num_monstros].hp=getMonsterHP(type);
			e.monstros[e.num_monstros].poison=0;
		}
	}
	e.num_monstros++;
	return e;
}
ESTADO placeOgre(ESTADO e){
	e=placeMonster(e,2);
	CHEST chest;
	chest.pos.x=e.monstros[0].x;
	chest.pos.y=e.monstros[0].y;
	chest=genChest(e,chest);
	e.num_chests++;
	e.chests[0]=chest;
	return e;
}
CHEST genChest(ESTADO e,CHEST chest){
	if(      pos_completamente_livre(e,chest.pos.x,chest.pos.y-1)){
		chest.pos.y--;
	}else if(pos_completamente_livre(e,chest.pos.x+1,chest.pos.y)){
		chest.pos.x++;
	}else if(pos_completamente_livre(e,chest.pos.x-1,chest.pos.y)){
		chest.pos.x--;
	}else if(pos_completamente_livre(e,chest.pos.x,chest.pos.y+1)){
		chest.pos.y++;
	}
	int r = rand() % 60;
	if(r<30){
		chest.item=generateScroll();
	}else if(r<45){
		chest.item=generateSword(e.world_lvl+10);
	}else{
		chest.item=generateArmour(e.world_lvl+10);
	}
	return chest;
}
ESTADO genMonsters(ESTADO e){
	e.num_chests=0;
	if(e.isInBossBattle){
		e=genBossBattle(e);
	}else{
		if(e.world_lvl>4 && (e.world_lvl>11 || e.world_lvl % 2)){
			e=placeOgre(e);
		}
		if(e.world_lvl>7 && (e.world_lvl>20 || !((e.world_lvl+1) % 3))){
			e=placeMonster(e,3);
		}
		int range;
		if(e.world_lvl>2){
			range=2;
		}else{
			range=1;
		}
		int target_num_monst = getNumMonst(e.world_lvl);
		int i=e.num_monstros;
		while(i<target_num_monst){
			int type = rand() % range;
			e=placeMonster(e,type);
			i++;
		}
	}
	return e;
}