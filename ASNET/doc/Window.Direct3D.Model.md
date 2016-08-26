```cpp
        class Direct3DModelLoader { //模型的导入类
			public:
				static void LoadPMDModel(
					ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Word filename, PMDModel* &model);
				//导入PMD格式的模型
				//@graph      创建模型的接口
				//@filename   模型的文件名
				//@model      模型格式，创建之前请保证其是nullptr


			};


```

>概述：基本上就是一个辅助导入模型的类，但是目前并不完善  
比如不支持动画以及导入后可能出现绘制错误，以及支持的模型格式还只有一个