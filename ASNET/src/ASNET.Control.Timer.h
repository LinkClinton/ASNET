#pragma once
#include<chrono>
namespace ASNET {
	namespace Control {
		
		typedef std::chrono::high_resolution_clock Time;

		class Timer {
		private:
			Time::time_point LastTime; //上次计时的时间
			Time::time_point NowTime;  //现在的时间
			std::chrono::duration<float> Time; //前面两者相差的时间
			bool Started; //计时器状态
		public:
			Timer();
			//开始计时(Finish)
			void  Start();
			//结束计时(Finish)
			void  End();
			//获取计时器状态(Finish)
			bool  GetState();
			//获取经过时间(Finish)
			float GetTime();
		};

	}
}