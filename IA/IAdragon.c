#include "IA.h"

ESTADO fireCone(ESTADO e){
	if(e.jog.x>=e.dragon.pos.x+1-(e.jog.y-e.dragon.pos.y-1) && e.jog.x<=e,dragon.x+2+(e.jog.y-e.dragon.pos.y-1) && e.jog.y<e.dragon.pos.y+8){
		e.hp-=11;
	}
}
ESTADO Wing_attack (ESTADO e){
	if(e.jog.x>=1 && e.jog.x<=8 && e.jog.y>=e.dragon.pos.y+1 && e.jog.y<=e.dragon.pos.y+3){
		e.hp-=20;
	}
	return e;
}

ESTADO fireball_damage (ESTADO e){
 int i;
	for(i=0;i<e.dragon.num_fireballs;i++){
		if(e.dragon.fireballsCenters[i].x==e.jog.x && e.dragon.fireballsCenters[i].y==e.jog.y){
			e.hp-=19;
		}
	}
	return e;
}

ESTADO fireball_attack (ESTADO e){
   int i,x,y,b1,b2;
   POSICAO pos;
   y=e.dragon.pos.y+3;// minimo
   i=(rand() % 7)+1;
   e.dragon.num_fireballs=i;
   for(x=0;x<i;x++){
     do{
     	 b1=(rand() % 10);
     	 b2=(rand() % 10);
     }while(b1<y||b1>y+4||(b2<e.jog.x-2)|| b2>(e.jog.x+2)|| b2>9 || b2<0);
     e.dragon.firaballCenters[0].x=b1;
     e.dragon.fireballCenters[0].y=b2;
   }
   e=fireball_damage(e);
   return e;
}
ESTADO dragon_movement (ESTADO e){
	int flag=1;
	if (e.jog.x<=e.dragon.pos.x+1 && e.dragon.pos.x>0){
		e.dragon.pos.x-=1;
		flag=0;
	}
	if(flag && e.jog.x>=e.dragon.pos.x+2 && e.dragon.pos.x<9){
		e.dragon.pos.x+=1;
	}
	if(e.dragon.atack==1 && abs(e.jog.y-e.dragon.pos.y)>=1){
  e.dragon.pos.y+=1;
	}
	if(e.dragon.attack==2 && abs(e.jog.y-e.dragon.pos.y)==1 && e.dragon.pos.y>0){
		e.dragon.pos.y-=1;
	}
	if(e.dragon.attack==2 && abs(e.jog.y-e.dragon.pos.y)>3){
		e.dragon.pos.y+=1;
	}
	if(e.dragon.pos.y>3){
		e.dragon.pos.y-=1;
	}
	return e;
}
// 1-fireball;2-wingAttack;3-fireCone
ESTADO estrat_dragon (ESTADO e){
	int i;
	e=dragon_movement(e);
	if(e.turn!=1 && e.turn/2!=0){
   	e.dragao.hp=7*e.world_lvl;
   	srandom(time(NULL))
   	e.dragon.attack=(rand() % 3)+1;
 }
 if(e.turn !=0 && e.turn/2==0){
 	if(e.dragon.attack==1){
      	e=fireball_attack(e);
    }
    if(e.dragon.attack==2){
      	e=Wing_attack(e);
    }
    if(e.dragon.attack==3){
       e=fireCone(e);
    }
 }
 return e;
}