#pragma once

#include<ASNET.Control.h>

namespace ASNET {
	namespace Control {
		
		//�ؼ��Ķ���
		class KeyFrame :public ASNET::Graph::KeyFrame {
		public:
			ASNET::Control::Color TextColor; //�ı�����ɫ������еĻ�
			ASNET::Control::Color BackGroundColor; //��������ɫ������еĻ�
			//���캯��
			KeyFrame();
		};

		//����
		class Animation {
		private:
			//�����ؼ�֡����
			std::vector<KeyFrame> Frames;
		public:
			auto GetStartTime()->float;
			auto GetEndTime()->float;
		
		};


	}
}