#pragma once
#include"Window.Graph.h"

//std
#include<vector>

//d3d11
#include<d3dcompiler.h>
#include<DirectXMath.h>

//direct XTK
#include<Effects.h>
#include<WICTextureLoader.h>

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

			class Buffer {
			private:
				ID3D11Buffer* VertexBuffer;
				ID3D11Buffer* IndexBuffer;
				UINT VertexCount;
				UINT IndexCount;
				friend GraphDirect3D;
			public:
				Buffer(Vertex* vertices, UINT vertex_count,
					UINT* indices = NULL, UINT index_count = 0);
				~Buffer();
			};

			class Shader {
			private:
				ID3D11VertexShader* VertexShader;
				ID3D11PixelShader*  PixelShader;
				ID3DBlob*           VertexShaderBlob;
				ID3DBlob*           PixelShaderBlob;
				ASNET::Graph::Word VertexShaderName;
				ASNET::Graph::Word PixelShaderName;
				friend class GraphDirect3D;
			public:
				Shader(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName);
				~Shader();
			};

			class ShaderDataBuffer {
			private:
				ID3D11Buffer* DataBuffer;
				void* Data;
			public:
				ShaderDataBuffer(void* data); //need change
				~ShaderDataBuffer();
			};

			class Texture {
			private:
			public:
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
				ID3D11InputLayout* g_inputlayout;
			public:
				GraphDirect3D(HWND hwnd, ASNET::Graph::Direct3D::Shader*
					Shader = NULL, bool IsWindowed = true);
				~GraphDirect3D();
			};
		}
	}
}