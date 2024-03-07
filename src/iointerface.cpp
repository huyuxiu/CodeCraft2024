#include "iointerface.h"
#include "model.h"
#include<iostream>
#include<cstring>
namespace IO {
	void init() {
		//TODO 实现初始化地图的功能
		memset(map,' ',sizeof map);//地图初始化
		for(int i = 0;i<conVar::maxX+1;i++){
			for(int j = 0;j<conVar::maxY+1;j++){
				bool flag = map[i][j]==' ';
				scanf("%c",&map[i][j]);
			}
		}
		for(int i = 0;i<10;i++){
			/*     读取泊点信息     */
			int id, x, y, time, velocity;
			scanf("%d %d %d %d %d",&id,&x,&y,&time,&velocity);
			Berth[id].setId;
			Berth[id].setX;
			Berth[id].setY;
			Berth[id].setTime;
			Berth[id].setVelocity;
		}
		scanf("%d",&shipCapacity);
		for(int i =0;i<10;i++){
			ship[i].setCapacity(shipCapacity);
		}
		puts("OK");
	}
	void readFrame(){
		scanf("%d %d",&frameId,&money);
		scanf()
	}
	namespace ROBOT{
		void move(int id,int direction){
			printf("move %d %d\n",id,direction);
		}
		void get(int id){
			printf("get %d\n",id);
		}
		void pull(int id){
			printf("pull %d\n",id);
		}
	}
	namespace SHIP{
		void ship(int shipId,int berthId){
			printf("ship %d %d\n",shipId,berthId);
		}
		void go(int shipId){
			printf("go %d\n",shipId);
		}
	}
}