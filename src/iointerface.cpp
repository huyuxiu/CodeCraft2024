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
		}
		scanf("%d",&shipCapacity);
		for(int i =0;i<10;i++){
			ship[i].setCapacity(shipCapacity);
		}
		scanf("%d",&shipCapacity);
	    char ok[100];
	    scanf("%s",&ok);        //读帧结束
		puts("OK");
		std::fflush(stdout);
	}
	void readFrame(){
		scanf("%d %d",&frameId,&money);
		scanf("%d",&k);
		int x,y,value,status,carry,berthId;

		for(int i =0;i<k;i++){
			scanf("%d %d %d",&x,&y,&value);
			Position pos(x,y);
			Goods g(value,pos,frameId+1000);
			goods[i] = g;
			int minPri = 1e8;
			int minId = 0;
			for(int j = 0;j<10;j++){
				int pri = priorityGoodsBerthSHip(goods[i],berth[j]);  //泊点优先级,优先级越小运送到泊点代价越小
				if(pri<minPri){
					minPri = pri;
					minId = j;
				}
			}
			goods[i].berthId = minId;
			goods[i].priority = minPri;
			goodsHeap.push(g);
		}

		for(int i = 0;i<10;i++){
			/*       读取机器人状态       */
			scanf("%d %d %d %d",&carry,&x,&y,&status);
            Position pos(x,y);
			Robot r(i,pos,status,carry);
            robot[i] = r;
		}

        for(int i = 0;i<5;i++){
			/*     读取船只信息     */
			scanf("%d %d",&status,&berthId);
			Ship sp(i,status,berthId);
			ship[i] = sp;
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