#include "iointerface.h"
#include "model.h"
#include "util.h"
#include "const.h"

#include<iostream>
#include<cstring>
namespace IO {
    void init() {
		memset(map,' ',sizeof map); //地图初始化
		memset(block,-1,sizeof block); //连通图初始化
		/*      读取地图        */
		for(int i = 0; i < conVar::maxX+1; i++){
			scanf("%s",map[i]);
		}
	    /*     读取泊点信息     */
		for(int i = 0; i < conVar::maxBerth; i++){
			int id, x, y, time, velocity;
			scanf("%d %d %d %d %d",&id,&x,&y,&time,&velocity);
			berth[id].setId(id);
			Position pos(x,y);
			berth[id].setPos(pos);
			berth[id].setTransport_time(time);
			berth[id].setVelocity(velocity);
			berth[id].presure = 0;
		}

		/*     多源bfs，给每个点标记最近泊位id     */
		multiSourceBFS();

		/*     floodfill     */
	    for(int i = 0; i < 10; i++){
		    Position pos = berth[i].getPosition();
		    if(block[pos.x][pos.y] == -1){
				floodFill(pos,maxBlockId++);
		    }
			berth[i].setBlockId(block[pos.x][pos.y]);
	    }

		/*      给泊位分类       */
		clusteringBerth();

	    calCenterPos(); //计算泊位中心位置
		scanf("%d",&shipCapacity);
		for(int i = 0; i < conVar::maxShip; i++){
			ship[i].setCapacity(shipCapacity);
		}
		memset(shipTargetBerth,-1,sizeof shipTargetBerth);			//初始化船目标泊位数组
		memset(goodsTargetBerth, 0, sizeof goodsTargetBerth);		//初始化货物目标泊位数组

		getStarBerth();     //获取类内运输能力高的泊位

	    char ok[100];
	    scanf("%s", &ok);
		puts("OK");
		std::fflush(stdout);
	}
	void readFrame(){
		memset(robotMap,0,sizeof robotMap); //碰撞初始化
		scanf("%d %d",&frameId,&money);
		scanf("%d",&k);
		int x,y,value,status,carry,berthId;
		Position pos(0,0);
		for(int i = 0; i < k; i++){
			scanf("%d %d %d",&x,&y,&value);
			pos.x = x,pos.y = y;
			if(getBlockId(pos)==-1) continue;
			if(isCollision(pos)) continue;
			goods[goodsId].value = value,goods[goodsId].deathId = frameId+1000,goods[goodsId].pos = pos;

			if(berth[bestBerth[x][y].first].getBlockId()==block[x][y]){
				/*     判断泊位连通性     */
				goods[goodsId].berthDist = bestBerth[x][y].second.first;
				goods[goodsId].berthId = bestBerth[x][y].first;
				goods[goodsId].priority = calPriorityGoodsBerth(goods[goodsId]);
				goodsHeap[berth[goods[goodsId].berthId].getClassId()].push(goods[goodsId++]);//货物加到每一类的优先队列
			}

		}

		for(int i = 0;i<10;i++){
			/*       读取机器人状态       */
			scanf("%d %d %d %d",&carry,&x,&y,&status);
            pos.x = x,pos.y = y;
			robot[i].setId(i);
			robot[i].setPosition(pos);
			robot[i].setStatus(status);
			robot[i].setCarry(carry);
			if(frameId==1) robot[i].setBerthId(bestBerth[x][y].first);//TODO 后续得优化

			//robot[i].setClassId(berth[bestBerth[x][y].first].getClassId());//初始化分配类
			robotMap[x][y] = 1;
		}

        for(int i = 0;i<5;i++){
			/*     读取船只信息     */
			scanf("%d %d",&status,&berthId);
			ship[i].setBerthId(berthId);
			ship[i].setStatus(status);
        }
		char ok[100];
		scanf("%s",&ok);        //读帧结束
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