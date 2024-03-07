#ifndef IOINTERFACE_H
#define IOINTERFACE_H
#include "model.h"

namespace IO{
	/*     判题器交互接口     */
	void init();                          //初始化地图、机器人
	void readFrame();                     //更改场面信息
	namespace ROBOT{
		/*     实现机器人控制     */
		void move(int id,int direction);
		void get(int id);
		void pull(int id);
	}

	namespace SHIP{
		/*     实现船只控制     */
		void ship(int shipId,int berthId);
		void go(int shipId);
	}
}

#endif //IOINTERFACE_H
