#pragma once
#include"ASNET.Direct3D.Mesh.h"


/*
* 简单的模型类
* 支持导入PMX模型格式，但是仅仅只是其部分内容能够使用，以及可能有BUG
*/

namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			//简单的模型类
			class Model :public Mesh {
			protected:
				std::wstring ModelName; //English
				std::wstring ModelComment; //the information about model

				friend class Direct3DModelLoader;
				Model() = default;
				//构造函数
			public:
				Model(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				//析构函数
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
				//按照字节读入信息，最高4字节
				static Value ValueRead(std::ifstream* file, UINT size);
				//按照字节忽略信息，无上限
				static void  ValueRuleOut(std::ifstream* file, UINT size);
				//对于PMX格式文件读入窄字符函数
				static void  StringRead(std::ifstream* file,std::wstring &str);
				//对于PMX格式文件读入宽字符函数
				static void  WideStringRead(std::ifstream* file, std::wstring &str);
			public:
				//加载PMX格式的模型
				static void LoadPMXModel(ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Word filename, ASNET::Graph::Direct3D::Model* &model);
			};


		}
	}
}