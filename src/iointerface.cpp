#include "iointerface.h"
#include "model.h"
#include "util.h"
#include "const.h"

#include<iostream>
#include<cstring>
namespace IO {
    void init() {
		//TODO 实现初始化地图的功能
		memset(map,' ',sizeof map);//地图初始化
		memset(block,-1,sizeof block);
		for(int i = 0;i<conVar::maxX+1;i++){
			scanf("%s",map[i]);
		}
		for(int i = 0;i<10;i++){
			/*     读取泊点信息     */
			int id, x, y, time, velocity;
			scanf("%d %d %d %d %d",&id,&x,&y,&time,&velocity);
			berth[id].setId(id);
			Position pos(x,y);
			berth[id].setPos(pos);
			berth[id].setTransport_time(time);
			berth[id].setVelocity(velocity);
			berth[id].presure = 0;

		}

		/*     多源bfs，给每个点标记泊位id     */
		multiSourceBFS();
		/*     floodfill     */
		berth[0].setBlockId(0);         //最先开始floodfill的泊位设置联通块id为0
	    for(int i =0;i<10;i++){
		    Position pos = berth[i].getPosition();
		    if(block[pos.x][pos.y]==-1){
				floodFill(pos,i);
		    }
			else{
				berth[i].setBlockId(block[pos.x][pos.y]);
			}
	    }


		scanf("%d",&shipCapacity);
		for(int i =0;i<5;i++){
			ship[i].setCapacity(shipCapacity);
		}
		memset(shipTargetBerth,0,sizeof shipTargetBerth);
	    char ok[100];
	    scanf("%s",&ok);        //读帧结束

		//多源bfs初始化地图上所有点到所有泊位的距离
		puts("OK");
		std::fflush(stdout);

	}
	void readFrame(){
		scanf("%d %d",&frameId,&money);
		scanf("%d",&k);
		int x,y,value,status,carry,berthId;
		Position pos(0,0);
		for(int i =0;i<k;i++){
			scanf("%d %d %d",&x,&y,&value);
			pos.x = x,pos.y = y;
			if(getBlockId(pos)==-1) continue;
			if(isCollision(pos)) continue;
			goods[goodsId].value = value,goods[goodsId].deathId = frameId+1000,goods[goodsId].pos = pos;
			int minPri = -1;
			int minId = 0;
			for(int j = 0;j<10;j++){
				if(berth[bestBerth[x][y].first].getBlockId()==block[x][y]){
					/*     判断泊位连通性     */
					goods[goodsId].berthDist = bestBerth[x][y].second;
					goods[goodsId].priority = calPriorityGoodsBerth(value,goods[goodsId].berthDist);
					//goodsHeap[class].push(goods[goodsId++]);//TODO
					break;
				}

			}



//			if(value>maxValue){
//				maxValue = value;
//				goods[goodsId].priority = -1;//优先去拿最贵的货
//			}


		}

		for(int i = 0;i<10;i++){
			/*       读取机器人状态       */
			scanf("%d %d %d %d",&carry,&x,&y,&status);
            pos.x = x,pos.y = y;
			robot[i].setId(i);
			robot[i].setPosition(pos);
			robot[i].setStatus(status);
			robot[i].setCarry(carry);
			robot[i].setBerthId(bestBerth[x][y].second);//TODO 后续得优化
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