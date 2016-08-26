```cpp
            struct Vertex {//顶点信息
				float x, y, z; //3维坐标
				float r, g, b, a;  //颜色信息
				float u, v; //贴图坐标
				float nx, ny, nz; //法线
				Vertex(); //构造函数
				Vertex(float _x, float _y, float _z, //构造函数
					float _u, float _v);
				void Normal(float _nx, float _ny, float _nz); //设置法线
				void Color(float _r, float _g, float _b, float _a); //设置颜色
			};
```

>概述：3维顶点的信息，很NC的加了颜色没加切线

```cpp
typedef UINT Index; //顶点数据格式，直接用UINT
```

>概述：有什么好说的

```cpp
            class Buffer { //缓存类型，创建的话请保证其是nullptr
			private:
				GraphDirect3D* ParentGraph;//创建他的接口指针

				ID3D11Buffer*  VertexBuffer; //顶点缓存
				ID3D11Buffer*  IndexBuffer; //索引缓存
				UINT		   VertexCount; //顶点个数
				UINT		   IndexCount; //索引个数
			public:
				Buffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph); 
				//构造函数，表示不是给使用者的
				~Buffer();
				//析构函数，记得用完不用了delete

				void UnLock(ASNET::Graph::Direct3D::Vertex* &vertices);
				//在创建的时候允许CPU访问的情况下才可以使用，得到顶点数据的指针
				//可以通过这个修改缓存中的顶点数据
				void Lock();
				//将顶点数据锁定


				void reset(std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
					std::vector<ASNET::Graph::Direct3D::Index>  indices);
					//在创建后，如果要重新创建可以使用此函数
			};
```

>概述：就是将缓存封装了下，理解DirectX或者OpenGL的应该都能理解

```cpp
        	class ShaderDataBuffer {//着色器常量缓存类型，创建的话请保证其是nullptr
			private:
				GraphDirect3D* ParentGraph; //创建他的接口指针

				ID3D11Buffer*  DataBuffer; //着色器常量缓存
				void* Data; //指向缓存存储的数据的指针
			public:
				ShaderDataBuffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				//构造函数，不是给使用者用的
				~ShaderDataBuffer();
                //记得delete
			
			
				void UpDateBuffer();//need add a value
                //在数据更新后，我们可以更新这个缓存
                //但是Data必须不是nullptr
                
                
				void reset(void* data, UINT datasize); 
				//在创建后重新创建一次，datasize必须是16的倍数
			};
```

>概述：如果用过着色器的话，我们需要将什么矩阵或者什么数据传给着色器，因此
就出现了着色器常量缓存，可以通过这样的方式给着色器传信息

```cpp
            class Texture {//贴图资源类型，创建的话请保证其是nullptr
			private:
				GraphDirect3D*            ParentGraph;//创建他的接口指针

				ID3D11ShaderResourceView* TexView; //贴图资源
				ASNET::Graph::Word        FileName; //贴图的文件路径和名字
			public:
				Texture(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				//构造函数，不是给使用者用的
				~Texture();
				//记得delete

				void reset(ASNET::Graph::Word filename);
				//在创建后打算重新构建可以用这个函数
				//filename文件名

			};
```

>概述：其实就是加载贴图的，主流格式一般都支持，用的是D3DX11的库，不支持TGA格式

```cpp
            class Shader { //着色器类型，这次不用保证nullptr
			private:
				GraphDirect3D*		ParentGraph; //在加载他后的渲染器指针

				ID3D11VertexShader* VertexShader; //顶点着色器
				ID3D11PixelShader*  PixelShader; //像素着色器
				ID3DBlob*           VertexShaderBlob; //忽视
				ID3DBlob*           PixelShaderBlob; //忽视
				ASNET::Graph::Word  VertexShaderName; //顶点着色器的文件名字
				ASNET::Graph::Word  PixelShaderName; //像素着色器的文件名字
				char*				VertexShaderFunctionName; 
				//使用的顶点着色器的主函数的名字
				char*				PixelShaderFunctionName;
				//使用的像素着色器的主函数名字
				bool                IsCompile;
				//在加载的时候着色器是否被编译了

				std::vector<byte>   VertexShaderCode;
				//如果顶点着色器之前就编译好了，那么就直接读入着色器
				std::vector<byte>   PixelShaderCode;
				//如果像素着色器之前就编辑好了，那么就直接读入着色器
			public:
				Shader(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName,
					bool IsCompiled = false,
					char* VertexFunctionName = "main",
					char* PixelFunctionName = "main");
				//构造函数，这会是使用者要用的了
				//VertexShaderFileName，使用的顶点着色器的文件名
				//PixelShaderFileName，使用的像素着色器的文件名
				//IsCompiled，着色器是否是编译好了的
				//VertexFunctionName，使用的顶点着色器的主函数的名字
				//PixelFunctionName，使用的像素着色器的主函数名字
				~Shader();
				//不用delete

				void reset(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName,
					bool IsCompiled = false,
					char* VertexFunctionName = "main",
					char* PixelFunctionName = "main");
				//重新加载着色器

				void SendBufferToVertexShader(UINT buffer_id,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);
				//将着色器常量缓存传给顶点着色器
				//buffer_id是在着色器的编号，会HLSL的话就知道了

				void SendBufferToPixelShader(UINT buffer_id,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);
				//发给像素着色器

				void SendTextureToShader(UINT texture_id,
					ASNET::Graph::Direct3D::Texture* texture);
				//将贴图传给着色器
				//texture_id是贴图在像素着色器里面的编号
			};
```

>概述：基础的着色器的封装，支持加载编译好的着色器。基本是将数据传给着色器是这事情

```cpp
            enum class CullMode { //绘制的时候的消隐
				CullNone = 1, //无
				CullFront = 2, //前
				CullBack = 3 //背部
			};

			enum class FillMode { //绘制模式
				FillWireFrame = 2, //线框
				FillSolid = 3 //颜色
			};

			enum class PrimitiveType {
				Unknown = 0,
				Point = 1,
				Line = 2,
				LineStrip = 3,
				Triangle = 4,
				TriangleStrip = 5,
			};  // enum class PrimitiveType
```

>概述：用来设置绘制的模式

```cpp
            class GraphDirect3D :public ASNET::Graph::Graph {//继承了Graph，差不多
			protected:
				ASNET::Graph::Direct3D::Shader* UsedShader; //使用的着色器指针
			protected:
				ID3D11InputLayout*              InputLayout; //输出布局
				ID3D11RasterizerState*			RasterizerState; //输出模式
			protected:


				void CompileShader(ASNET::Graph::Direct3D::Shader* shader);
				//编译着色器，如果没有被编译
				void LoadShader(ASNET::Graph::Direct3D::Shader* shader);
				//加载着色器，如果被编译
				void UpDateInputLayout(Shader* shader);
				//在着色器改变后更新Layout
				void SetShader(ASNET::Graph::Direct3D::Shader* shader);
				//设置着色器，会将其编译或者加载

				void Direct3DInitalize(); //初始化自己
			public:
				GraphDirect3D(HWND hwnd, ASNET::Graph::Direct3D::Shader*
					shader = nullptr, bool IsWindowed = true);
				//构造函数
				//hwnd窗口句柄
				//Shader用的着色器的指针
				//IsWindowed是否是窗口模式
				~GraphDirect3D();
				//记得delete

				void SetCullMode(ASNET::Graph::Direct3D::CullMode cullmode);
				//设置Cull模式，初始CULL_NONE

				void SetFillMode(ASNET::Graph::Direct3D::FillMode fillmode);
				//设置绘制的格式，初始FillSolid

				void LoadTexture(ASNET::Graph::Direct3D::Texture* &texture,
					ASNET::Graph::Word filename);
				//加载贴图
				//texture贴图指针
				//filename文件名

				void LoadBuffer(ASNET::Graph::Direct3D::Buffer* &buffer,
					std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
					std::vector<ASNET::Graph::Direct3D::Index>  indices ,
					bool CPUAcess = false); //only for vertex buffer
				//加载缓存
				//buffer是要被加载的缓存
				//vertices顶点数据
				//indices索引数据
				//CPUAcess CPU是否可以访问

			

				void LoadShaderDataBuffer(void* data, UINT datasize,
					ASNET::Graph::Direct3D::ShaderDataBuffer* &buffer);
				//加载着色器常量缓存
				//data是数据指针
				//datasize是数据字节大小，16的倍数必须
				//buffer是要被加载的缓存

				void DrawBuffer(ASNET::Graph::Direct3D::Buffer* buffer,
					ASNET::Graph::Direct3D::PrimitiveType Type =
					ASNET::Graph::Direct3D::PrimitiveType::Triangle);
                //绘制缓存
                //buffer是缓存
                //Type是连接点的模式
			
				

			};
```
>概述：一个简单的接口，可以方便导入资源而已