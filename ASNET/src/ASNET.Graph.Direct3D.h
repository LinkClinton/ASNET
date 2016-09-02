#pragma once
#include"ASNET.Graph.h"

//std
#include<vector>

//d3d11
#include<DirectXMath.h>
//#include<d3dcompiler.h>

//d3dx11

//这是个坑，目前没有啥好思路想架构,所以版本差别可能会很大
/*
自己挖了大坑，现在不知道怎么填了，这个类目前作为一个拓展类
可以在Window和Page里面声明，但是需要废除原本类里面的Graph类
这个类可以认为是Graph类的强大版本
Graph类有的这个类都有，其创建代码将放入Window::OnLoading中就好了
因为需要窗口的句柄，所以要窗口创建成功后才可以放入
所有类型都要求在使用的时候用指针，然后在Load代码里面会对其进行new
因此不要总是new，在不用的时候可以delete
然后就是由于其是继承了Graph类，因此完全可以代替Graph类
*/
namespace ASNET {
	namespace Graph {
		namespace Direct3D {
		




			class GraphDirect3D;

			//顶点结构
			struct Vertex {
				float x, y, z; //位置
				float r, g, b, a; //颜色
				float u, v; //贴图坐标
				float nx, ny, nz; //法线
				//构造函数
				Vertex();
				//构造函数
				Vertex(float _x, float _y, float _z,
					float _u, float _v);
				//设置法线
				void Normal(float _nx, float _ny, float _nz);
				//设置颜色
				void Color(float _r, float _g, float _b, float _a);
			};

			//顶点索引
			typedef UINT Index;

			//缓存
			class Buffer {
			private:
				GraphDirect3D* ParentGraph; //渲染用的指针接口

				ID3D11Buffer*  VertexBuffer; //顶点缓存
				ID3D11Buffer*  IndexBuffer; //索引缓存
				UINT		   VertexCount; //顶点个数
				UINT		   IndexCount; //索引个数
				friend class   Mesh;
				friend class   GraphDirect3D;
				friend class   Shader;
			public:
				//构造函数
				Buffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				//析构函数，记得delete
				~Buffer();

				//解锁缓存区，能够对缓存区进行更改
				void UnLock(ASNET::Graph::Direct3D::Vertex* &vertices);
				//重新锁定缓存区
				void Lock();

				//重新构建缓存
				void reset(std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
					std::vector<ASNET::Graph::Direct3D::Index>  indices = std::vector<Index>());
			};



			//着色器数据缓存
			class ShaderDataBuffer {
			private:
				GraphDirect3D* ParentGraph; //渲染用的指针接口

				ID3D11Buffer*  DataBuffer; //数据缓存
				void* Data; //数据指针
				friend class GraphDirect3D;
				friend class BasicEffect;
				friend class Shader;
			public:
				//构造函数
				ShaderDataBuffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				//析构函数，记得delete
				~ShaderDataBuffer();
				//返回缓存
				operator ID3D11Buffer*(); 

				//更新数据到缓存，要求数据指针不为nullptr
				void UpDateBuffer();//need add a value

				//重新构建，变量结构大小要是16字节的倍数
				void reset(void* data, UINT datasize); //sizeof(data) MUST BE the multiples  of 16
			};

			//贴图
			class Texture {
			private:
				GraphDirect3D*            ParentGraph; //渲染用的指针接口

				ID3D11ShaderResourceView* TexView; //贴图缓存
				ASNET::Graph::Word        FileName; //贴图文件名
				friend class GraphDirect3D;
				friend class Shader;
			public:
				//构造函数
				Texture(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				//析构函数，记得delete
				~Texture();
				//返回贴图缓存
				operator ID3D11ShaderResourceView*();

				//重新加载贴图
				void reset(ASNET::Graph::Word filename);

			};


			//着色器
			class Shader {
			private:
				GraphDirect3D*		ParentGraph; //渲染用的指针缓存

				ID3D11VertexShader* VertexShader; //顶点着色器
				ID3D11PixelShader*  PixelShader; //像素着色器
				ID3DBlob*           VertexShaderBlob; //顶点着色器信息
				ID3DBlob*           PixelShaderBlob; //像素着色器信息
				ASNET::Graph::Word  VertexShaderName; //顶点着色器文件名
				ASNET::Graph::Word  PixelShaderName; //像素着色器文件名
				char*				VertexShaderFunctionName; //顶点着色器入口函数名
				char*				PixelShaderFunctionName; //像素着色器入口函数名
				bool                IsCompile; //着色器是否是已经编译过的了

				std::vector<byte>   VertexShaderCode; //着色器代码，仅仅针对已经编译过了的着色器
				std::vector<byte>   PixelShaderCode; //着色器代码，仅仅针对已经编译过了的着色器
				friend class BasicEffect;
				friend class GraphDirect3D;
			public:
				//构造函数
				Shader(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName,
					bool IsCompiled = false,
					char* VertexFunctionName = "main",
					char* PixelFunctionName = "main");
				//析构函数
				~Shader();

				//重新加载着色器
				void reset(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName,
					bool IsCompiled = false,
					char* VertexFunctionName = "main",
					char* PixelFunctionName = "main");

				//将着色器缓存数据传给顶点着色器
				void SendBufferToVertexShader(UINT buffer_id,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);
				//将着色器缓存数据传给像素着色器
				void SendBufferToPixelShader(UINT buffer_id,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);
				//将贴图传给像素着色器
				void SendTextureToShader(UINT texture_id,
					ASNET::Graph::Direct3D::Texture* texture);
			};

			//Cull
			enum class CullMode {
				CullNone = 1,
				CullFront = 2,
				CullBack = 3
			};
			
			//Fill
			enum class FillMode {
				FillWireFrame = 2,
				FillSolid = 3
			};

			//DrawMode
			enum class PrimitiveType {
				Unknown = 0,
				Point = 1,
				Line = 2,
				LineStrip = 3,
				Triangle = 4,
				TriangleStrip = 5,
			};  // enum class PrimitiveType

			//Direct3D
			class GraphDirect3D :public ASNET::Graph::Graph {
			protected:
				ASNET::Graph::Direct3D::Shader* UsedShader; //使用的着色器的指针
			protected:
				ID3D11InputLayout*              InputLayout; //使用的Layout
				ID3D11RasterizerState*			RasterizerState; //使用的RasterizerState
				friend class BasicEffect; 
			protected:

				//编译没有编译好着色器文件
				void CompileShader(ASNET::Graph::Direct3D::Shader* shader); 
				//加载已经编译好的着色器文件
				void LoadShader(ASNET::Graph::Direct3D::Shader* shader);
				//更新Layout
				void UpDateInputLayout(Shader* shader); 				

				//初始化函数
				void Direct3DInitalize(); 

				friend class Direct3DModelLoader;
				friend class Mesh;
				friend class ShaderDataBuffer;
				friend class Texture;
				friend class Shader;
				friend class Buffer;
			public:
				//构造函数
				GraphDirect3D(HWND hwnd, ASNET::Graph::Direct3D::Shader*
					shader = nullptr, bool IsWindowed = true);
				//析构函数
				~GraphDirect3D();

				//设置使用的着色器,IsLoad=false将会对着色器进行编译或者加载
				void SetShader(ASNET::Graph::Direct3D::Shader* shader, bool IsLoad = false);
				//设置CullMode
				void SetCullMode(ASNET::Graph::Direct3D::CullMode cullmode);
				//设置FillMode
				void SetFillMode(ASNET::Graph::Direct3D::FillMode fillmode);
				//加载贴图
				void LoadTexture(ASNET::Graph::Direct3D::Texture* &texture,
					ASNET::Graph::Word filename);
				//加载缓存
				void LoadBuffer(ASNET::Graph::Direct3D::Buffer* &buffer,
					std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
					std::vector<ASNET::Graph::Direct3D::Index>  indices = std::vector<Index>(),
					bool CPUAcess = false); //only for vertex buffer

			
				//加载着色器缓存
				void LoadShaderDataBuffer(void* data, UINT datasize,
					ASNET::Graph::Direct3D::ShaderDataBuffer* &buffer);
				//绘制缓存
				void DrawBuffer(ASNET::Graph::Direct3D::Buffer* buffer,
					ASNET::Graph::Direct3D::PrimitiveType Type =
					ASNET::Graph::Direct3D::PrimitiveType::Triangle);

			
				

			};
		}
	}
}
