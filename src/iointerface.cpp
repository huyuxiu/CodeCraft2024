#include "iointerface.h"
#include "model.h"
#include<iostream>
namespace IO {
	void init() {
		//TODO 实现初始化地图的功能
		int R = 0;//Robot编号
		int B = 0;//Berth编号
		for(int i = 0;i<conVar::maxX+1;i++){
			for(int j = 0;j<conVar::maxY+1;j++){
				scanf("%c",&map[i][j]);
				if(map[i][j]=='A'){
					/*     设置机器人位置     */
					robot[R].setId(R);
					Position p(i,j);
					robot[R].setPosition(p);
					R++;
				}
				if(map[i][j]=='B'&&map[i][j]!='B'){
					/*      设置泊点编号       */
					Position p(i,j);
					Berth[B].setPosition(p);
					for(int t = i;t<i+4;t++){
						for(int c = j;c<j+4;c++){
							map[t][c] = 'B';
						}
					}
				}
			}
		}
		puts("OK");
	}
}