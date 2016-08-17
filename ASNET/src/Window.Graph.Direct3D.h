#pragma once
#include"Window.Graph.h"

//std
#include<vector>

//d3d11
#include<d3dcompiler.h>
#include<DirectXMath.h>


//这是个坑，目前没有啥好思路想架构,所以版本差别可能会很大
namespace ASNET {
	namespace Graph {
		namespace Direct3D {			
			typedef ID3D11Device		GraphDevice;
			typedef ID3D11DeviceContext GraphContext;
			
			class GraphDirect3D;

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
				GraphDirect3D* ParentGraph;

				ID3D11Buffer*  VertexBuffer;
				ID3D11Buffer*  IndexBuffer;
				UINT		   VertexCount;
				UINT		   IndexCount;
				friend class   GraphDirect3D;
				friend class   Shader;
			public:
				Buffer();
				~Buffer();

				void reset(ASNET::Graph::Direct3D::Vertex* vertices, UINT vertices_count,
					ASNET::Graph::Direct3D::Index*  indices = NULL, UINT indices_count = 0);
			};


			class ShaderDataBuffer {
			private:
				GraphDirect3D* ParentGraph;

				ID3D11Buffer*  DataBuffer;
				void* Data;
				friend class GraphDirect3D;
				friend class Shader;
			public:
				ShaderDataBuffer();
				~ShaderDataBuffer();

				void UpDateBuffer();

				void reset(void* data); //sizeof(data) MUST BE the multiples  of 16
			};

			class Texture {
			private:
				GraphDirect3D*            ParentGraph;

				ID3D11ShaderResourceView* Tex;
				ASNET::Graph::Word        FileName;
				friend class GraphDirect3D;
				friend class Shader;
			public:
				Texture();
				~Texture();

				void reset(ASNET::Graph::Word filename);
				
			};

		

			class Shader {
			private:
				GraphDevice*	    ParentDevice;
				GraphContext*       ParentContext;
				GraphDirect3D*		ParentGraph;

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

				void reset(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName);

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
				void SetShader(ASNET::Graph::Direct3D::Shader* shader);

				friend class ShaderDataBuffer;
				friend class Texture;
				friend class Shader;
				friend class Buffer;
			public:
				GraphDirect3D(HWND hwnd, ASNET::Graph::Direct3D::Shader*
					shader = NULL, bool IsWindowed = true);
				~GraphDirect3D();

				void SetCullMode(ASNET::Graph::Direct3D::CullMode cullmode);

				void SetFillMode(ASNET::Graph::Direct3D::FillMode fillmode);

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


				//if shader is not null, you can't used it 
				//you should use the SendBufferToShader 
				void SetViewMatrix(DirectX::XMMATRIX* view);

				void SetProjMatrix(DirectX::XMMATRIX* proj);

				void SetWorldMatrix(DirectX::XMMATRIX* world);
			};
		}
	}
}