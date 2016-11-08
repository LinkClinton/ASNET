#pragma once

#include"ASNET.Graph.h"

#include<map>

namespace ASNET {
	namespace Control {
		
		
		//关键帧动画，用于控件
		//继承自关键帧基类
		class KeyFrame :public ASNET::Graph::KeyFrame {
		public:
			ASNET::Graph::Color TextColor; //文本的颜色，如果有的话
			ASNET::Graph::Color BackGroundColor; //背景的颜色，如果有的话
			
			//构造函数
			KeyFrame();
		};

		//动画，描述一组动画，用于控件
		class Animation {
		protected:
			typedef std::map<float, ASNET::Control::KeyFrame> Frames;
			//动画关键帧集合
			Frames KeyFrames;
			//经过的时间
			float Time;
			//动画是否结束
			bool  IsEnd;
		protected:
			auto LinearComputeColor(ASNET::Graph::Color front, ASNET::Graph::Color back, float scale)->ASNET::Graph::Color;
		public:
			Animation();
			//获取动画开始的时间
			auto GetStartTime()->float;
			//获取动画结束的时间
			auto GetEndTime()->float;
			//获取动画数据
			auto GetKeyFrame()->ASNET::Control::KeyFrame;
			//获取在某个时间的动画数据
			auto GetKeyFrame(float TimePos)->ASNET::Control::KeyFrame;
			//增加一个关键帧
			void AddFrame(ASNET::Control::KeyFrame Frame);
			//开始动画
			void Start();
			//经过多久，单位s
			void Pass(float PassTime);
			//强行结束动画
			void Stop();
			//获取现在处于的时间
			auto GetTime()->float;
			//动画是否结束
			bool End();

			



		};


	}
}