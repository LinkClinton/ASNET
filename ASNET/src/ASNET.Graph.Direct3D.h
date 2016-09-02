#pragma once
#include"ASNET.Graph.h"

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
�������Ͷ�Ҫ����ʹ�õ�ʱ����ָ�룬Ȼ����Load���������������new
��˲�Ҫ����new���ڲ��õ�ʱ�����delete
Ȼ������������Ǽ̳���Graph�࣬�����ȫ���Դ���Graph��
*/
namespace ASNET {
	namespace Graph {
		namespace Direct3D {
		




			class GraphDirect3D;

			//����ṹ
			struct Vertex {
				float x, y, z; //λ��
				float r, g, b, a; //��ɫ
				float u, v; //��ͼ����
				float nx, ny, nz; //����
				//���캯��
				Vertex();
				//���캯��
				Vertex(float _x, float _y, float _z,
					float _u, float _v);
				//���÷���
				void Normal(float _nx, float _ny, float _nz);
				//������ɫ
				void Color(float _r, float _g, float _b, float _a);
			};

			//��������
			typedef UINT Index;

			//����
			class Buffer {
			private:
				GraphDirect3D* ParentGraph; //��Ⱦ�õ�ָ��ӿ�

				ID3D11Buffer*  VertexBuffer; //���㻺��
				ID3D11Buffer*  IndexBuffer; //��������
				UINT		   VertexCount; //�������
				UINT		   IndexCount; //��������
				friend class   Mesh;
				friend class   GraphDirect3D;
				friend class   Shader;
			public:
				//���캯��
				Buffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				//�����������ǵ�delete
				~Buffer();

				//�������������ܹ��Ի��������и���
				void UnLock(ASNET::Graph::Direct3D::Vertex* &vertices);
				//��������������
				void Lock();

				//���¹�������
				void reset(std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
					std::vector<ASNET::Graph::Direct3D::Index>  indices = std::vector<Index>());
			};



			//��ɫ�����ݻ���
			class ShaderDataBuffer {
			private:
				GraphDirect3D* ParentGraph; //��Ⱦ�õ�ָ��ӿ�

				ID3D11Buffer*  DataBuffer; //���ݻ���
				void* Data; //����ָ��
				friend class GraphDirect3D;
				friend class BasicEffect;
				friend class Shader;
			public:
				//���캯��
				ShaderDataBuffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				//�����������ǵ�delete
				~ShaderDataBuffer();
				//���ػ���
				operator ID3D11Buffer*(); 

				//�������ݵ����棬Ҫ������ָ�벻Ϊnullptr
				void UpDateBuffer();//need add a value

				//���¹����������ṹ��СҪ��16�ֽڵı���
				void reset(void* data, UINT datasize); //sizeof(data) MUST BE the multiples  of 16
			};

			//��ͼ
			class Texture {
			private:
				GraphDirect3D*            ParentGraph; //��Ⱦ�õ�ָ��ӿ�

				ID3D11ShaderResourceView* TexView; //��ͼ����
				ASNET::Graph::Word        FileName; //��ͼ�ļ���
				friend class GraphDirect3D;
				friend class Shader;
			public:
				//���캯��
				Texture(ASNET::Graph::Direct3D::GraphDirect3D* Graph);
				//�����������ǵ�delete
				~Texture();
				//������ͼ����
				operator ID3D11ShaderResourceView*();

				//���¼�����ͼ
				void reset(ASNET::Graph::Word filename);

			};


			//��ɫ��
			class Shader {
			private:
				GraphDirect3D*		ParentGraph; //��Ⱦ�õ�ָ�뻺��

				ID3D11VertexShader* VertexShader; //������ɫ��
				ID3D11PixelShader*  PixelShader; //������ɫ��
				ID3DBlob*           VertexShaderBlob; //������ɫ����Ϣ
				ID3DBlob*           PixelShaderBlob; //������ɫ����Ϣ
				ASNET::Graph::Word  VertexShaderName; //������ɫ���ļ���
				ASNET::Graph::Word  PixelShaderName; //������ɫ���ļ���
				char*				VertexShaderFunctionName; //������ɫ����ں�����
				char*				PixelShaderFunctionName; //������ɫ����ں�����
				bool                IsCompile; //��ɫ���Ƿ����Ѿ����������

				std::vector<byte>   VertexShaderCode; //��ɫ�����룬��������Ѿ�������˵���ɫ��
				std::vector<byte>   PixelShaderCode; //��ɫ�����룬��������Ѿ�������˵���ɫ��
				friend class BasicEffect;
				friend class GraphDirect3D;
			public:
				//���캯��
				Shader(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName,
					bool IsCompiled = false,
					char* VertexFunctionName = "main",
					char* PixelFunctionName = "main");
				//��������
				~Shader();

				//���¼�����ɫ��
				void reset(ASNET::Graph::Word VertexShaderFileName,
					ASNET::Graph::Word PixelShaderFileName,
					bool IsCompiled = false,
					char* VertexFunctionName = "main",
					char* PixelFunctionName = "main");

				//����ɫ���������ݴ���������ɫ��
				void SendBufferToVertexShader(UINT buffer_id,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);
				//����ɫ���������ݴ���������ɫ��
				void SendBufferToPixelShader(UINT buffer_id,
					ASNET::Graph::Direct3D::ShaderDataBuffer* buffer);
				//����ͼ����������ɫ��
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
				ASNET::Graph::Direct3D::Shader* UsedShader; //ʹ�õ���ɫ����ָ��
			protected:
				ID3D11InputLayout*              InputLayout; //ʹ�õ�Layout
				ID3D11RasterizerState*			RasterizerState; //ʹ�õ�RasterizerState
				friend class BasicEffect; 
			protected:

				//����û�б������ɫ���ļ�
				void CompileShader(ASNET::Graph::Direct3D::Shader* shader); 
				//�����Ѿ�����õ���ɫ���ļ�
				void LoadShader(ASNET::Graph::Direct3D::Shader* shader);
				//����Layout
				void UpDateInputLayout(Shader* shader); 				

				//��ʼ������
				void Direct3DInitalize(); 

				friend class Direct3DModelLoader;
				friend class Mesh;
				friend class ShaderDataBuffer;
				friend class Texture;
				friend class Shader;
				friend class Buffer;
			public:
				//���캯��
				GraphDirect3D(HWND hwnd, ASNET::Graph::Direct3D::Shader*
					shader = nullptr, bool IsWindowed = true);
				//��������
				~GraphDirect3D();

				//����ʹ�õ���ɫ��,IsLoad=false�������ɫ�����б�����߼���
				void SetShader(ASNET::Graph::Direct3D::Shader* shader, bool IsLoad = false);
				//����CullMode
				void SetCullMode(ASNET::Graph::Direct3D::CullMode cullmode);
				//����FillMode
				void SetFillMode(ASNET::Graph::Direct3D::FillMode fillmode);
				//������ͼ
				void LoadTexture(ASNET::Graph::Direct3D::Texture* &texture,
					ASNET::Graph::Word filename);
				//���ػ���
				void LoadBuffer(ASNET::Graph::Direct3D::Buffer* &buffer,
					std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
					std::vector<ASNET::Graph::Direct3D::Index>  indices = std::vector<Index>(),
					bool CPUAcess = false); //only for vertex buffer

			
				//������ɫ������
				void LoadShaderDataBuffer(void* data, UINT datasize,
					ASNET::Graph::Direct3D::ShaderDataBuffer* &buffer);
				//���ƻ���
				void DrawBuffer(ASNET::Graph::Direct3D::Buffer* buffer,
					ASNET::Graph::Direct3D::PrimitiveType Type =
					ASNET::Graph::Direct3D::PrimitiveType::Triangle);

			
				

			};
		}
	}
}
