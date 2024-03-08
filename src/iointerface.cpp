#include "iointerface.h"
#include "model.h"
#include "util.h"

#include<iostream>
#include<cstring>
namespace IO {
	void init() {
		//TODO 实现初始化地图的功能
		memset(map,' ',sizeof map);//地图初始化
		for(int i = 0;i<conVar::maxX+1;i++){
			scanf("%s",map[i]);
		}
		for(int i = 0;i<10;i++){
			/*     读取泊点信息     */
			int id, x, y, time, velocity;
			scanf("%d %d %d %d %d",&id,&x,&y,&time,&velocity);
			berth[id].setId;
			Position pos(x,y);
			berth[id].setPos(pos);
			berth[id].setTime;
			berth[id].setVelocity;
		}
		scanf("%d",&shipCapacity);
		for(int i =0;i<10;i++){
			ship[i].setCapacity(shipCapacity);
		}
		puts("OK");
	}
	void readFrame(){
		scanf("%d %d",&frameId,&money);
		scanf("%d",&k);
		int x,y,value;

		for(int i =0;i<k;i++){
			scanf("%d %d %d",&x,&y,&value);
			map[x][y] = goodsId;                  //货物放到地图中
			Position pos(x,y);
			goods[goodsId].value = value;
			goods[goodsId].pos = pos;
			int minDist = 1e8;
			int minId = 0;
			for(int j = 0;j<10;i++){
				int md = manhattanDist(berth[j].getPosition(),pos)+berth[i].getVelocity();
				if(md<minDist){
					minDist = md;
					minId = j;
				}
			}

			goods[i].berthId = minId;
			goods[i].berthShipDist = minDist;

			goodsId++;
		}
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