#include "iointerface.h"
#include "model.h"
#include<iostream>
#include<cstring>
namespace IO {
	void init() {
		//TODO 实现初始化地图的功能
		scanf("%d %d",&frameId,&moeney);
		memset(map,' ',sizeof map);//地图初始化
		int R = 0;//Robot编号
		for(int i = 0;i<conVar::maxX+1;i++){
			for(int j = 0;j<conVar::maxY+1;j++){
				bool flag = map[i][j]==' ';
				scanf("%c",&map[i][j]);
				if(map[i][j]=='A'){
					/*     设置机器人位置     */
					robot[R].setId(R);
					Position p(i,j);
					robot[R].setPosition(p);
					R++;
				}
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
		puts("OK");
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