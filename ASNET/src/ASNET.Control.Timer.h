#pragma once
#include<chrono>
namespace ASNET {
	namespace Control {
		
		typedef std::chrono::high_resolution_clock Time;

		class Timer {
		private:
			Time::time_point LastTime; //�ϴμ�ʱ��ʱ��
			Time::time_point NowTime;  //���ڵ�ʱ��
			std::chrono::duration<float> Time; //ǰ����������ʱ��
			bool Started; //��ʱ��״̬
		public:
			Timer();
			//��ʼ��ʱ(Finish)
			void  Start();
			//������ʱ(Finish)
			void  End();
			//��ȡ��ʱ��״̬(Finish)
			bool  GetState();
			//��ȡ����ʱ��(Finish)
			float GetTime();
		};

	}
}