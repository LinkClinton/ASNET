#pragma once

#include"ASNET.Graph.h"

/*
* ���ڶ���
* ��¼�ܶ��ʱ��εı任��Ȼ��ͨ��ʱ����ȡ�ñ任�ķ���
* �����ֻ������������
*/

namespace ASNET {
	namespace Graph {

		//�����Ķ����࣬���ڴ洢��ĳһ��ʱ���ڵĶ������� 
		class KeyFrame {
		public:
			float TimePos;

		};

		//����һ������
		class Animation {
		private:
			std::vector<KeyFrame> Frames;
		};


	}
}