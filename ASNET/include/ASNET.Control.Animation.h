#pragma once

#include"ASNET.Graph.h"

#include<map>

namespace ASNET {
	namespace Control {
		
		
		//�ؼ�֡���������ڿؼ�
		//�̳��Թؼ�֡����
		class KeyFrame :public ASNET::Graph::KeyFrame {
		public:
			ASNET::Graph::Color TextColor; //�ı�����ɫ������еĻ�
			ASNET::Graph::Color BackGroundColor; //��������ɫ������еĻ�
			
			//���캯��
			KeyFrame();
		};

		//����������һ�鶯�������ڿؼ�
		class Animation {
		protected:
			typedef std::map<float, ASNET::Control::KeyFrame> Frames;
			//�����ؼ�֡����
			Frames KeyFrames;
			//������ʱ��
			float Time;
			//�����Ƿ����
			bool  IsEnd;
		protected:
			auto LinearComputeColor(ASNET::Graph::Color front, ASNET::Graph::Color back, float scale)->ASNET::Graph::Color;
		public:
			Animation();
			//��ȡ������ʼ��ʱ��
			auto GetStartTime()->float;
			//��ȡ����������ʱ��
			auto GetEndTime()->float;
			//��ȡ��������
			auto GetKeyFrame()->ASNET::Control::KeyFrame;
			//��ȡ��ĳ��ʱ��Ķ�������
			auto GetKeyFrame(float TimePos)->ASNET::Control::KeyFrame;
			//����һ���ؼ�֡
			void AddFrame(ASNET::Control::KeyFrame Frame);
			//��ʼ����
			void Start();
			//������ã���λs
			void Pass(float PassTime);
			//ǿ�н�������
			void Stop();
			//��ȡ���ڴ��ڵ�ʱ��
			auto GetTime()->float;
			//�����Ƿ����
			bool End();

			



		};


	}
}