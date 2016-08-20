#pragma once
#include<DirectXMath.h>


#include"ASNET.Graph.Direct3D.h"
#include"ASNET.Direct3D.Model.PMD.h"


namespace ASNET {
	namespace Graph {
		namespace Direct3D {
			
			


			class Direct3DModelLoader {
			public:
				static void LoadPMDModel(
					ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Word filename, PMDModel* &model);


			};


		}
	}
}