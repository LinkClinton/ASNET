#pragma once

#include<ASNET.Control.h>

namespace ASNET {
	namespace Control {
		
		//控件的动画
		class KeyFrame :public ASNET::Graph::KeyFrame {
		public:
			ASNET::Control::Color TextColor; //文本的颜色，如果有的话
			ASNET::Control::Color BackGroundColor; //背景的颜色，如果有的话
			//构造函数
			KeyFrame();
		};

		//动画
		class Animation {
		private:
			//动画关键帧集合
			std::vector<KeyFrame> Frames;
		public:
			auto GetStartTime()->float;
			auto GetEndTime()->float;
		
		};


	}
}