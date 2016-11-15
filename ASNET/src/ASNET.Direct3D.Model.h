#pragma once
#include"ASNET.Direct3D.Mesh.h"


/*
* �򵥵�ģ����
* ֧�ֵ���PMXģ�͸�ʽ�����ǽ���ֻ���䲿�������ܹ�ʹ�ã��Լ�������BUG
*/

namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			//�򵥵�ģ����
			class Model :public Mesh {
			protected:
				std::wstring ModelName; //English
				std::wstring ModelComment; //the information about model

				friend class Direct3DModelLoader;
				Model() = default;
				//���캯��
			public:
				Model(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				//��������
				~Model();
			};


			union Value {
				char    _char[4];
				wchar_t _wchar[2];
				int     _int;
				short   _short;
				byte    _byte[4];
				float   _float;
			};


			class Direct3DModelLoader {
			private:
				//�����ֽڶ�����Ϣ�����4�ֽ�
				static Value ValueRead(std::ifstream* file, UINT size);
				//�����ֽں�����Ϣ��������
				static void  ValueRuleOut(std::ifstream* file, UINT size);
				//����PMX��ʽ�ļ�����խ�ַ�����
				static void  StringRead(std::ifstream* file,std::wstring &str);
				//����PMX��ʽ�ļ�������ַ�����
				static void  WideStringRead(std::ifstream* file, std::wstring &str);
			public:
				//����PMX��ʽ��ģ��
				static void LoadPMXModel(ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Word filename, ASNET::Graph::Direct3D::Model* &model);
			};


		}
	}
}