#pragma once

#include"ASNET.Graph.h"

/*
* 关于动画
* 记录很多个时间段的变换，然后通过时间来取得变换的方法
* 这个类只是用来看看的
*/

namespace ASNET {
	namespace Graph {

		//基础的动画类，用于存储在某一个时间内的动画数据 
		class KeyFrame {
		public:
			float TimePos;

		};

		//描述一个动画
		class Animation {
		private:
			std::vector<KeyFrame> Frames;
		};


	}
}