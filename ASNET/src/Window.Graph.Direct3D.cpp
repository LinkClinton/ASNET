#include"Window.Graph.Direct3D.h"


#pragma comment(lib,"D3DCompiler.lib")



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

void ASNET::Graph::Direct3D::Vertex::Normal(float _nx, float _ny, float _nz){
	nx = _nx;
	ny = _ny;
	nz = _nz;
}

void ASNET::Graph::Direct3D::Vertex::Color(float _r, float _g, float _b, float _a){
	r = _r;
	g = _g;
	b = _b;
	a = _a;
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
	std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
	std::vector<ASNET::Graph::Direct3D::Index>  indices){

	release(VertexBuffer);
	release(IndexBuffer);

	VertexCount = 0;
	IndexCount = 0;

	
	
	//ParentGraph->LoadBuffer(this, vertices, indices);
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

	//ParentGraph->LoadShaderDataBuffer(data, this);
}

ASNET::Graph::Direct3D::Texture::Texture(){
	ParentGraph = nullptr;

	release(Tex);
	release(TexView);

	FileName = nullptr;
}

ASNET::Graph::Direct3D::Texture::~Texture(){
	ParentGraph = nullptr;

	release(Tex);
	release(TexView);

	FileName = nullptr;
}

void ASNET::Graph::Direct3D::Texture::reset(ASNET::Graph::Word filename){
	release(Tex);
	release(TexView);

	FileName = filename;

	//LoadTexture
}

ASNET::Graph::Direct3D::Shader::Shader(
	ASNET::Graph::Word VertexShaderFileName, 
	ASNET::Graph::Word PixelShaderFileName,
	char* VertexFunctionName,
	char* PixelFunctionName){
	ParentDevice = nullptr;
	ParentContext = nullptr;
	ParentGraph = nullptr;

	release(VertexShader);
	release(PixelShader);

	release(VertexShaderBlob);
	release(PixelShaderBlob);

	VertexShaderName = VertexShaderFileName;
	PixelShaderName = PixelShaderFileName;
	VertexShaderFunctionName = VertexFunctionName;
	PixelShaderFunctionName = PixelFunctionName;
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
	VertexShaderFunctionName = nullptr;
	PixelShaderFunctionName = nullptr;
}

void ASNET::Graph::Direct3D::Shader::reset(
	ASNET::Graph::Word VertexShaderFileName,
	ASNET::Graph::Word PixelShaderFileName,
	char* VertexFunctionName,
	char* PixelFunctionName) {
	ParentDevice = nullptr;
	ParentContext = nullptr;
	ParentGraph = nullptr;

	release(VertexShader);
	release(PixelShader);

	release(VertexShaderBlob);
	release(PixelShaderBlob);

	VertexShaderName = VertexShaderFileName;
	PixelShaderName = PixelShaderFileName;
	VertexShaderFunctionName = VertexFunctionName;
	PixelShaderFunctionName = PixelFunctionName;

	ParentGraph->SetShader(this);
}

void ASNET::Graph::Direct3D::Shader::SendBufferToShader(UINT buffer_id, 
	ASNET::Graph::Direct3D::ShaderDataBuffer * buffer){
	ParentContext->VSSetConstantBuffers(buffer_id, 1, &buffer->DataBuffer);
}

void ASNET::Graph::Direct3D::Shader::SendTextureToShader(UINT texture_id,
	ASNET::Graph::Direct3D::Texture * texture){
	ParentContext->VSSetShaderResources(texture_id, 1, &texture->TexView);
}

void ASNET::Graph::Direct3D::GraphDirect3D::CompileShader(
	ASNET::Graph::Direct3D::Shader * shader) {
	ID3DBlob* ErrorBlob = nullptr;
	D3DCompileFromFile(shader->VertexShaderName, 0, 0,
		shader->VertexShaderFunctionName, "vs_5_0",
		0, 0, &shader->VertexShaderBlob, &ErrorBlob);
	g_device3d->CreateVertexShader(shader->VertexShaderBlob->GetBufferPointer(),
		shader->VertexShaderBlob->GetBufferSize(), nullptr, &shader->VertexShader);

	ErrorBlob = nullptr;

	D3DCompileFromFile(shader->PixelShaderName, 0, 0,
		shader->PixelShaderFunctionName, "ps_5_0",
		0, 0, &shader->PixelShaderBlob, &ErrorBlob);
	g_device3d->CreatePixelShader(shader->PixelShaderBlob->GetBufferPointer(),
		shader->PixelShaderBlob->GetBufferSize(), nullptr, &shader->PixelShader);
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetShader(
	ASNET::Graph::Direct3D::Shader * shader){
	CompileShader(shader);
	g_devicecontext3d->VSSetShader(shader->VertexShader, 0, 0);
	g_devicecontext3d->PSSetShader(shader->PixelShader, 0, 0);
	UsedShader = shader;

	shader->ParentContext = g_devicecontext3d;
	shader->ParentDevice = g_device3d;
	shader->ParentGraph = this;
}

void ASNET::Graph::Direct3D::GraphDirect3D::Direct3DInitalize(){
	D3D11_RASTERIZER_DESC RasterizerDesc;
	RasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	RasterizerDesc.FrontCounterClockwise = FALSE;
	RasterizerDesc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
	RasterizerDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
	RasterizerDesc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	RasterizerDesc.DepthClipEnable = TRUE;
	RasterizerDesc.ScissorEnable = FALSE;
	RasterizerDesc.MultisampleEnable = FALSE;
	RasterizerDesc.AntialiasedLineEnable = FALSE;
	g_device3d->CreateRasterizerState(&RasterizerDesc, &RasterizerState);
	g_devicecontext3d->RSSetState(RasterizerState);

	
	
	
}

ASNET::Graph::Direct3D::GraphDirect3D::GraphDirect3D(HWND hwnd, 
	ASNET::Graph::Direct3D::Shader * shader, bool IsWindowed){
	Initalize(hwnd, IsWindowed);
	if (shader)
		SetShader(shader);

	Direct3DInitalize();
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
	D3D11_RASTERIZER_DESC RasterizerDesc;
	RasterizerState->GetDesc(&RasterizerDesc);

	RasterizerDesc.CullMode = (D3D11_CULL_MODE)cullmode;

	g_device3d->CreateRasterizerState(&RasterizerDesc, &RasterizerState);
	g_devicecontext3d->RSSetState(RasterizerState);
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetFillMode(
	ASNET::Graph::Direct3D::FillMode fillmode){
	D3D11_RASTERIZER_DESC RasterizerDesc;
	RasterizerState->GetDesc(&RasterizerDesc);

	RasterizerDesc.FillMode = (D3D11_FILL_MODE)fillmode;

	g_device3d->CreateRasterizerState(&RasterizerDesc, &RasterizerState);
	g_devicecontext3d->RSSetState(RasterizerState);
}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadTexture(
	ASNET::Graph::Direct3D::Texture * &texture, ASNET::Graph::Word filename){
	if (texture) return;

	texture = new ASNET::Graph::Direct3D::Texture();
	texture->FileName = filename;
	texture->ParentGraph = this;
	
}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadBuffer(
	ASNET::Graph::Direct3D::Buffer * &buffer, 
	std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
	std::vector<ASNET::Graph::Direct3D::Index>  indices) {

}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadShaderDataBuffer(void * data,
	ASNET::Graph::Direct3D::ShaderDataBuffer * &buffer) {

}

void ASNET::Graph::Direct3D::GraphDirect3D::DrawBuffer(
	ASNET::Graph::Direct3D::Buffer * buffer, 
	ASNET::Graph::Direct3D::PrimitiveType Type){
}
