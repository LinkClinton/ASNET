```cpp
            union PMDFloat{
				float _float;
				char  _char[4];
			};

			union PMDDword {
				DWORD _Dwrod;
				char  _char[4];
			};

			union PMDWord {
				WORD _Word;
				char _char[2];
			};

			union PMDShort {
				short _short;
				char  _char[2];
			};
			//对应的数据格式，我们在读入2进制的情况下将其使用union
			//使其能够一个字节一个字节的使用
```

>概述：因为模型是2进制格式，所以我们需要一个字节一个字节的读入模型，因此才有这些结构

```cpp
            struct PMDModelPart { //模型的部分，很多模型都将其分为很多部分
				DirectX::XMFLOAT4  Ambient;   //对环境光的吸收
				DirectX::XMFLOAT4  Diffuse;  //对漫反射光的吸收
				DirectX::XMFLOAT4  Specular; //对镜面光的吸收，第4位在模型中没有用到
				//具体参见MMD中的PMD模型格式，如果有什么错误的地方请指出

				float Alphadif; //不晓得
				float Spemat; //不晓得
				
				std::wstring	   TextureName; //使用的贴图的名字


				UINT StartFace; //对于每一个部分其使用的顶点起始位置
				UINT EffectCount; //对于每一个部分其使用的顶点的个数
				UINT TextureID; //无用

				ASNET::Graph::Direct3D::Texture* Texture; //贴图指针
				operator ASNET::Graph::Direct3D::Material(); //返回其材质信息
				PMDModelPart(); //构造函数，
				~PMDModelPart(); //析构函数，记得delete
			};
```

>概述：在MMD中他们称作材质，其实就是模型的一部分，同时方便了模型的动画以及骨骼

```cpp
        class PMDModel { //PMD格式的模型，在创建的时候保证他是nullptr
			private:
				static const int PMDModelVertexLimit = 666233; //限制了顶点个数
				static const int PMDModelIndexLimit = 666233;  //限制了索引个数
				static const int PMDModelMaterialLimit = 233; //限制了模型部分个数
				static const int PMDModelBitsLimit = 23333333;  //限制了模型大小？
			private:
				ASNET::Graph::Direct3D::GraphDirect3D* ParentGraph; //创建模型的指针

				ASNET::Graph::Direct3D::Buffer* Buffer;  //一个模型对应的缓存

				
				UINT VertexNum;  //顶点个数 
				UINT IndexNum;  //索引个数
				UINT ModelPartsNum;  //模型部分个数

				
				std::vector<ASNET::Graph::Direct3D::Vertex>			vertices;
				//顶点信息
				std::vector<ASNET::Graph::Direct3D::Index>			indices;
				//索引信息
				std::vector<ASNET::Graph::Direct3D::PMDModelPart>	ModelParts;
				模型部分信息

				

				std::map<std::wstring,
					ASNET::Graph::Direct3D::Texture*>				Textures;
				//贴图资源，通过一个map对字符串进行hash
				//防止了重复载入贴图

			
				std::wstring										FilePath;
				//文件路径，不含文件名字，方便在加载模型的时候加载模型的贴图
			public:
				static float PMDFloatRead(std::ifstream* file);
				static short PMDShortRead(std::ifstream* file);
				static DWORD PMDDwordRead(std::ifstream* file);
				static WORD  PMDWordRead(std::ifstream* file);
				static void  PMDRuleOut(std::ifstream* file, int num);
				//读取2进制文件的函数
				//PMDRuleOut函数是过滤字节的
			public:
			    PMDModel(ASNET::Graph::Direct3D::GraphDirect3D* graph);
			    //构造函数，不是给使用者用的
				~PMDModel(); //记得delete
				void Draw(int texture_id = 0); //直接绘制模型
				//texture_id 是自己的着色器中贴图用的编号
				
				void Draw(ASNET::Graph::Direct3D::BasicEffect* effect);
				//使用BasicEffect类对其进行绘制，具体参见BasicEffect类


				void PrepareDraw(); //准备绘制，将在绘制前的准备做好
				void DrawPart(int index);  //绘制模型的某一个部分
				//index 模型部分对应的索引
				//这两个函数其实是为了方便于着色器的设置来使用的
				//通过分开步骤，使着色器能够方便的使用
				
				
				auto ModelPatsNum()->int;
				//返回模型部分有多少个
				
				void Release();
				//释放资源
				//类似reset
				//你可以Release，然后让模型指针指向nullptr
				//然后再去创建
				
			};
```

>概述：其实就是一个导入模型的简单的类而已，由于作者的水平不够也就只能那么低级了
似乎在Extend里面所有代码的都写的很死啊