#pragma once
#include<chrono>
namespace ASNET {
	namespace Control {
		
		//时间类，由于只是简单的计时而已，所以并不需要继承基类以及界面

		typedef std::chrono::high_resolution_clock Time;

		//简单的Timer类
		class Timer {
		private:
			Time::time_point LastTime; //上次计时的时间
			Time::time_point NowTime;  //现在的时间
			std::chrono::duration<float> Time; //前面两者相差的时间
			bool Started; //计时器状态
		public:
			//默认构造函数
			Timer();
			//开始计时
			void  Start();
			//结束计时
			void  End();
			//获取计时器状态
			bool  GetState();
			//获取经过时间
			float GetTime();
		};

	}
}