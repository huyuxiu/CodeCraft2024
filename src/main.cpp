#include "iointerface.h"
#include "model.h"
#include "control.h"

#include<iostream>

int main(){
	IO::init();
	bool flag2 = false;
	for(frameId;frameId<=15000;){
		IO::readFrame();
		/*        货物进机器人优先队列       */

		/*     判断机器人指令队列是否为空，空就A*     */

		/*      指令序列加入队列       */
		puts("OK");
		std::fflush(stdout);

	}
}