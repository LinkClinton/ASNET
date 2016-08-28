#pragma once
#include"ASNET.Direct3D.Mesh.h"


namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			class Model :public Mesh {
			private:
				std::wstring ModelName; //English
				std::wstring ModelComment; //the information about model

				friend class Direct3DModelLoader;
			public:
				Model(ASNET::Graph::Direct3D::GraphDirect3D* graph);
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
				static Value ValueRead(std::ifstream* file, UINT size);
				static void  ValueRuleOut(std::ifstream* file, UINT size);
				static void  StringRead(std::ifstream* file,std::wstring &str);
				static void  WideStringRead(std::ifstream* file, std::wstring &str);
			public:
				static void LoadPMXModel(ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Word filename, ASNET::Graph::Direct3D::Model* &model);
			};


		}
	}
}