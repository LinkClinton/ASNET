#pragma once
#include<chrono>
namespace ASNET {
	namespace Control {
		
		//ʱ���࣬����ֻ�Ǽ򵥵ļ�ʱ���ѣ����Բ�����Ҫ�̳л����Լ�����

		typedef std::chrono::high_resolution_clock Time;

		//�򵥵�Timer��
		class Timer {
		private:
			Time::time_point LastTime; //�ϴμ�ʱ��ʱ��
			Time::time_point NowTime;  //���ڵ�ʱ��
			std::chrono::duration<float> Time; //ǰ����������ʱ��
			bool Started; //��ʱ��״̬
		public:
			//Ĭ�Ϲ��캯��
			Timer();
			//��ʼ��ʱ
			void  Start();
			//������ʱ
			void  End();
			//��ȡ��ʱ��״̬
			bool  GetState();
			//��ȡ����ʱ��
			float GetTime();
		};

	}
}