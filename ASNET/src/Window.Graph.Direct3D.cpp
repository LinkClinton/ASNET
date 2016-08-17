#include"Window.Graph.Direct3D.h"

template<typename T>
void release(T &Interface) {
	if (Interface)
		Interface->Release();
	Interface = NULL;
}

ASNET::Graph::Direct3D::Vertex::Vertex(
	float _x, float _y, float _z, 
	float _u, float _v){
	x = _x;
	y = _y;
	z = _z;
	u = _u;
	v = _v;
}

ASNET::Graph::Direct3D::Buffer::Buffer(){
	ParentGraph = nullptr;

	release(VertexBuffer);
	release(IndexBuffer);

	VertexCount = 0;
	IndexCount = 0;
}

ASNET::Graph::Direct3D::Buffer::~Buffer(){
	ParentGraph = nullptr;

	release(VertexBuffer);
	release(IndexBuffer);

	VertexCount = 0;
	IndexCount = 0;
}

void ASNET::Graph::Direct3D::Buffer::reset(
	ASNET::Graph::Direct3D::Vertex * vertices, UINT vertices_count, 
	ASNET::Graph::Direct3D::Index * indices, UINT indices_count){

	release(VertexBuffer);
	release(IndexBuffer);

	VertexCount = 0;
	IndexCount = 0;
	
	ParentGraph->LoadBuffer(this, vertices,
		vertices_count, indices, indices_count);
}

ASNET::Graph::Direct3D::ShaderDataBuffer::ShaderDataBuffer(){
	ParentGraph = nullptr;

	release(DataBuffer);

	Data = nullptr;
}

ASNET::Graph::Direct3D::ShaderDataBuffer::~ShaderDataBuffer(){
	ParentGraph = nullptr;

	release(DataBuffer);

	Data = nullptr;
}

void ASNET::Graph::Direct3D::ShaderDataBuffer::UpDateBuffer(){
	ParentGraph->g_devicecontext3d->UpdateSubresource(DataBuffer, 0, nullptr, Data, 0, 0);
}

void ASNET::Graph::Direct3D::ShaderDataBuffer::reset(void * data){
	release(DataBuffer);

	Data = nullptr;

	ParentGraph->LoadShaderDataBuffer(data, this);
}

ASNET::Graph::Direct3D::Texture::Texture(){
	ParentGraph = nullptr;

	release(Tex);

	FileName = nullptr;
}

ASNET::Graph::Direct3D::Texture::~Texture(){
	ParentGraph = nullptr;

	release(Tex);

	FileName = nullptr;
}

void ASNET::Graph::Direct3D::Texture::reset(ASNET::Graph::Word filename){
	release(Tex);

	FileName = nullptr;

	ParentGraph->LoadTexture(this, filename);
}

ASNET::Graph::Direct3D::Shader::Shader(ASNET::Graph::Word VertexShaderFileName, 
	ASNET::Graph::Word PixelShaderFileName){
	ParentDevice = nullptr;
	ParentContext = nullptr;
	ParentGraph = nullptr;

	release(VertexShader);
	release(PixelShader);

	release(VertexShaderBlob);
	release(PixelShaderBlob);

	VertexShaderName = VertexShaderFileName;
	PixelShaderName = PixelShaderFileName;
}

ASNET::Graph::Direct3D::Shader::~Shader(){
	ParentDevice = nullptr;
	ParentContext = nullptr;
	ParentGraph = nullptr;

	release(VertexShader);
	release(PixelShader);

	release(VertexShaderBlob);
	release(PixelShaderBlob);

	VertexShaderName = nullptr;
	PixelShaderName = nullptr;
}

void ASNET::Graph::Direct3D::Shader::reset(ASNET::Graph::Word VertexShaderFileName,
	ASNET::Graph::Word PixelShaderFileName){
	ParentDevice = nullptr;
	ParentContext = nullptr;
	ParentGraph = nullptr;

	release(VertexShader);
	release(PixelShader);

	release(VertexShaderBlob);
	release(PixelShaderBlob);

	VertexShaderName = nullptr;
	PixelShaderName = nullptr;

	ParentGraph->SetShader(this);
}

void ASNET::Graph::Direct3D::Shader::SendBufferToShader(UINT buffer_id, 
	ASNET::Graph::Direct3D::ShaderDataBuffer * buffer){
	ParentContext->VSSetConstantBuffers(buffer_id, 1, &buffer->DataBuffer);
}

void ASNET::Graph::Direct3D::Shader::SendTextureToShader(UINT texture_id,
	ASNET::Graph::Direct3D::Texture * texture){
	ParentContext->VSSetShaderResources(texture_id, 1, &texture->Tex);
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetShader(
	ASNET::Graph::Direct3D::Shader * shader){
}

ASNET::Graph::Direct3D::GraphDirect3D::GraphDirect3D(HWND hwnd, 
	ASNET::Graph::Direct3D::Shader * shader, bool IsWindowed){
	Initalize(hwnd, IsWindowed);
	SetShader(shader);
}

ASNET::Graph::Direct3D::GraphDirect3D::~GraphDirect3D() {
	release(g_device2d);
	release(g_device3d);

	release(g_devicecontext2d);
	release(g_devicecontext3d);

	release(g_factory);
	release(g_writefactory);
	release(g_rendertargetview);
	release(g_depthstencilview);
	release(g_swapchain);
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetCullMode(
	ASNET::Graph::Direct3D::CullMode cullmode){
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetFillMode(
	ASNET::Graph::Direct3D::FillMode fillmode){
}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadTexture(
	ASNET::Graph::Direct3D::Texture * texture, ASNET::Graph::Word filename){
}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadBuffer(
	ASNET::Graph::Direct3D::Buffer * buffer, ASNET::Graph::Direct3D::Vertex * vertices,
	UINT vertices_count, ASNET::Graph::Direct3D::Index * indices, UINT indices_count) {

}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadShaderDataBuffer(void * data,
	ASNET::Graph::Direct3D::ShaderDataBuffer * buffer) {
}

void ASNET::Graph::Direct3D::GraphDirect3D::DrawBuffer(
	ASNET::Graph::Direct3D::Buffer * buffer, 
	ASNET::Graph::Direct3D::PrimitiveType Type){
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetViewMatrix(DirectX::XMMATRIX * view){
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetProjMatrix(DirectX::XMMATRIX * proj){
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetWorldMatrix(DirectX::XMMATRIX * world){
}
