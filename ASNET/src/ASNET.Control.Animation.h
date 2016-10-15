#pragma once

#include"ASNET.Control.Type.h"

#include<map>

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
		protected:
			typedef std::map<float, ASNET::Control::KeyFrame> Frames;
			//�����ؼ�֡����
			Frames KeyFrames;
			//������ʱ��
			float Time;
			//�����Ƿ����
			bool  IsEnd;
		protected:
			//����ɫ�������Լ��㣬�Ի�ȡ���ʱ�����ɫ
			auto LinearComputeColor(ASNET::Control::Color front, ASNET::Control::Color back, float scale)->Color;
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