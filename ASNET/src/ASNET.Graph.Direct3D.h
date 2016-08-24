#pragma once
#include"ASNET.Graph.h"
#include"ASNET.Direct3D.Effect.h"
//std
#include<vector>

//d3d11
#include<DirectXMath.h>
//#include<d3dcompiler.h>

//d3dx11

//���Ǹ��ӣ�Ŀǰû��ɶ��˼·��ܹ�,���԰汾�����ܻ�ܴ�
/*
�Լ����˴�ӣ����ڲ�֪����ô���ˣ������Ŀǰ��Ϊһ����չ��
������Window��Page����������������Ҫ�ϳ�ԭ���������Graph��
����������Ϊ��Graph���ǿ��汾
Graph���е�����඼�У��䴴�����뽫����Window::OnLoading�оͺ���
��Ϊ��Ҫ���ڵľ��������Ҫ���ڴ����ɹ���ſ��Է���
ͬʱ������ӹ̶��ܵ����뷨�����Ժ���ܻ����
�������Ͷ�Ҫ����ʹ�õ�ʱ����ָ�룬Ȼ����Load���������������new
��˲�Ҫ����new���ڲ��õ�ʱ�����delete
*/
namespace ASNET {
	namespace Graph {
		namespace Direct3D {
		




			class GraphDirect3D;

			struct Vertex {
				float x, y, z;
				float r, g, b, a;
				float u, v;
				float nx, ny, nz;
				Vertex();
				Vertex(float _x, float _y, float _z,
					float _u, float _v);
				void Normal(float _nx, float _ny, float _nz);
				void Color(float _r, float _g, float _b, float _a);
			};

			typedef UINT Index;

			class Buffer {
			private:
				GraphDirect3D* ParentGraph;

				ID3D11Buffer*  VertexBuffer;
				ID3D11Buffer*  IndexBuffer;
				UINT		   VertexCount;
				UINT		   IndexCount;
				friend class   PMDModel;
				friend class   GraphDirect3D;
				friend class   Shader;
			public:
				Buffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				~Buffer();

				void reset(std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
					std::vector<ASNET::Graph::Direct3D::Index>  indices = std::vector<Index>());
			};


			class ShaderDataBuffer {
			private:
				GraphDirect3D* ParentGraph;

				ID3D11Buffer*  DataBuffer;
				void* Data;
				friend class GraphDirect3D;
				friend class BasicEffect;
				friend class Shader;
			public:
				ShaderDataBuffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				~ShaderDataBuffer();

				operator ID3D11Buffer*();

				void UpDateBuffer();//need add a value

				void reset(void* data, UINT datasize); //sizeof(data) MUST BE the multiples  of 16
			};

			class Texture {
			private:
				GraphDirect3D*            ParentGraph;

				ID3D11ShaderResourceView* TexView;
				ASNET::Graph::Word        FileName;
				friend class GraphDirect3D;
				friend class Shader;
			public:
				Texture(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				~Texture();

				operator ID3D11ShaderResourceView*();

				void reset(ASNET::Graph::Word filename);

			};



			class Shader {
			private:
				GraphDirect3D*		ParentGraph;

				ID3D11VertexShader* VertexShader;
				ID3D11PixelShader*  PixelShader;
				ID3DBlob*           VertexShaderBlob;
				ID3DBlob*           PixelShaderBlob;
				ASNET::Graph::Word  VertexShaderName;
				ASNET::Graph::Word  PixelShaderName;
				char*				VertexShaderFunctionName;
				char*				PixelShaderFunctionName;
				bool                IsCompile;

				std::vector<byte>   VertexShaderCode;
				std::vector<byte>   PixelShaderCode;
				friend class BasicEffect;
				friend class GraphDirect3D;
			public:
				Shader(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName,
					bool IsCompiled = false,
					char* VertexFunctionName = "main",
					char* PixelFunctionName = "main");
				~Shader();

				void reset(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName,
					bool IsCompiled = false,
					char* VertexFunctionName = "main",
					char* PixelFunctionName = "main");

				void SendBufferToVertexShader(UINT buffer_id,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);

				void SendBufferToPixelShader(UINT buffer_id,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);

				void SendTextureToShader(UINT texture_id,
					ASNET::Graph::Direct3D::Texture* texture);
			};

			enum class CullMode {
				CullNone = 1,
				CullFront = 2,
				CullBack = 3
			};

			enum class FillMode {
				FillWireFrame = 2,
				FillSolid = 3
			};

			enum class PrimitiveType {
				Unknown = 0,
				Point = 1,
				Line = 2,
				LineStrip = 3,
				Triangle = 4,
				TriangleStrip = 5,
			};  // enum class PrimitiveType

			class GraphDirect3D :public ASNET::Graph::Graph {
			protected:
				ASNET::Graph::Direct3D::Shader* UsedShader;
			protected:
				ID3D11InputLayout*              InputLayout;
				ID3D11RasterizerState*			RasterizerState;
				friend class BasicEffect;
			protected:


				void CompileShader(ASNET::Graph::Direct3D::Shader* shader);
				void LoadShader(ASNET::Graph::Direct3D::Shader* shader);
				void UpDateInputLayout(Shader* shader);
				void SetShader(ASNET::Graph::Direct3D::Shader* shader);

				void Direct3DInitalize();

				friend class Direct3DModelLoader;
				friend class PMDModel;
				friend class ShaderDataBuffer;
				friend class Texture;
				friend class Shader;
				friend class Buffer;
			public:
				GraphDirect3D(HWND hwnd, ASNET::Graph::Direct3D::Shader*
					shader = nullptr, bool IsWindowed = true);
				~GraphDirect3D();

				void SetCullMode(ASNET::Graph::Direct3D::CullMode cullmode);

				void SetFillMode(ASNET::Graph::Direct3D::FillMode fillmode);

				void LoadTexture(ASNET::Graph::Direct3D::Texture* &texture,
					ASNET::Graph::Word filename);

				void LoadBuffer(ASNET::Graph::Direct3D::Buffer* &buffer,
					std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
					std::vector<ASNET::Graph::Direct3D::Index>  indices = std::vector<Index>());

				void LoadShaderDataBuffer(void* data, UINT datasize,
					ASNET::Graph::Direct3D::ShaderDataBuffer* &buffer);

				void DrawBuffer(ASNET::Graph::Direct3D::Buffer* buffer,
					ASNET::Graph::Direct3D::PrimitiveType Type =
					ASNET::Graph::Direct3D::PrimitiveType::Triangle);

				void DrawBuffer(ASNET::Graph::Direct3D::Buffer* buffer,
					ASNET::Graph::Direct3D::BasicEffect* effect,
					ASNET::Graph::Direct3D::PrimitiveType Type =
					ASNET::Graph::Direct3D::PrimitiveType::Triangle);
				

			};
		}
	}
}
