#pragma once
#include"Window.Graph.h"

//std
#include<vector>

//d3d11
#include<d3dcompiler.h>
#include<DirectXMath.h>


//这是个坑，目前没有啥好思路想架构
namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			struct Vertex {
				float x, y, z;
				float r, g, b, a;
				float u, v;
				float nx, ny, nz;
				Vertex(float _x, float _y, float _z,
					float _u, float _v);
			}; 

			typedef UINT Index;

			class Buffer {
			private:
				ID3D11Buffer* VertexBuffer;
				ID3D11Buffer* IndexBuffer;
				UINT VertexCount;
				UINT IndexCount;
				friend class GraphDirect3D;
				friend class Shader;
			public:
				Buffer(UINT vertices_count,
					UINT indices_count = 0);
				~Buffer();
			};


			class ShaderDataBuffer {
			private:
				ID3D11Buffer* DataBuffer;
				void* Data;
				friend class GraphDirect3D;
				friend class Shader;
			public:
				ShaderDataBuffer(void* data); //sizeof(data) MUST BE the multiples  of 16
				~ShaderDataBuffer();

				void UpDateBuffer();
			};

			class Texture {
			private:
				ID3D11ShaderResourceView* Tex;
				friend class GraphDirect3D;
				friend class Shader;
			public:
				Texture(ASNET::Graph::Word filename);
				~Texture();
			};

			typedef ID3D11Device		GraphDevice;
			typedef ID3D11DeviceContext GraphContext;

			class Shader {
			private:
				GraphDevice*	    ParentDevice;
				GraphContext*       ParentContext;

				ID3D11VertexShader* VertexShader;
				ID3D11PixelShader*  PixelShader;
				ID3DBlob*           VertexShaderBlob;
				ID3DBlob*           PixelShaderBlob;
				ASNET::Graph::Word  VertexShaderName;
				ASNET::Graph::Word  PixelShaderName;
				friend class GraphDirect3D;
			public:
				Shader(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName);
				~Shader();

				void SendBufferToShader(UINT buffer_id, 
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

			class GraphDirect3D:public ASNET::Graph::Graph {
			protected:
				ID3D11InputLayout*			g_inputlayout;
				ID3D11RasterizerState*		g_rasterizerstate;
			public:
				GraphDirect3D(HWND hwnd, ASNET::Graph::Direct3D::Shader*
					Shader = NULL, bool IsWindowed = true);
				~GraphDirect3D();


				void SetCullMode(ASNET::Graph::Direct3D::CullMode cullmode);

				void SetFillMode(ASNET::Graph::Direct3D::FillMode fillmode);

				void ResetShader(ASNET::Graph::Direct3D::Shader* shader);

				void LoadTexture(ASNET::Graph::Direct3D::Texture* texture,
					ASNET::Graph::Word filename);

				void LoadBuffer(ASNET::Graph::Direct3D::Buffer* buffer,
					ASNET::Graph::Direct3D::Vertex* vertices, UINT vertices_count,
					ASNET::Graph::Direct3D::Index*  indices = NULL, UINT indices_count = 0);

				void LoadShaderDataBuffer(void* data,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);

				void DrawBuffer(ASNET::Graph::Direct3D::Buffer* buffer,
					ASNET::Graph::Direct3D::PrimitiveType Type =
					ASNET::Graph::Direct3D::PrimitiveType::Triangle);


			};
		}
	}
}