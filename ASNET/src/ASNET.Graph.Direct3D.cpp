#include "ASNET.Graph.Direct3D.h"

#include"D3DX11.h"

#pragma comment(lib,"d3dx11.lib")
//#pragma comment(lib,"D3DCompiler.lib")

#include<fstream>

template<typename T>
void release(T &Interface) {
	if (Interface)
		Interface->Release();
	Interface = nullptr;
}

ASNET::Graph::Direct3D::Vertex::Vertex(){
	x = 0;
	y = 0;
	z = 0;
	u = 0;
	v = 0;
	r = 0;
	g = 0;
	b = 0;
	a = 1;
	nx = 0;
	ny = 0;
	nz = 0;
	wx = 0;
	wy = 0;
	wz = 0;
	BoneIndices[0] = (byte)0;
	BoneIndices[1] = (byte)0;
	BoneIndices[2] = (byte)0;
	BoneIndices[3] = (byte)0;
}

ASNET::Graph::Direct3D::Vertex::Vertex(float _x, float _y, float _z,
	float _u, float _v){
	x = _x;
	y = _y;
	z = _z;
	u = _u;
	v = _v;
	r = 0;
	g = 0;
	b = 0;
	a = 1;
	nx = 0;
	ny = 0;
	nz = 0;
	wx = 0;
	wy = 0;
	wz = 0;
	BoneIndices[0] = (byte)0;
	BoneIndices[1] = (byte)0;
	BoneIndices[2] = (byte)0;
	BoneIndices[3] = (byte)0;
}

void ASNET::Graph::Direct3D::Vertex::Normal(
	float _nx, float _ny, float _nz){
	nx = _nx;
	ny = _ny;
	nz = _nz;
}

void ASNET::Graph::Direct3D::Vertex::Color(
	float _r, float _g, float _b, float _a){
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

void ASNET::Graph::Direct3D::Vertex::Weight(float weight,int count)
{
	switch (count)
	{
	case 0:
		wx = weight;
		break;
	case 1:
		wy = weight;
		break;
	case 2:
		wz = weight;
		break;
	default:
		break;
	}
}

ASNET::Graph::Direct3D::Buffer::Buffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph){
	ParentGraph = Graph;

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

void ASNET::Graph::Direct3D::Buffer::UnLock(
	ASNET::Graph::Direct3D::Vertex *& vertices){
	D3D11_MAPPED_SUBRESOURCE MapData;
	ParentGraph->g_devicecontext3d->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &MapData);
	vertices = reinterpret_cast<ASNET::Graph::Direct3D::Vertex*>(MapData.pData);
}

void ASNET::Graph::Direct3D::Buffer::Lock(){
	ParentGraph->g_devicecontext3d->Unmap(VertexBuffer, 0);
}



void ASNET::Graph::Direct3D::Buffer::reset(
	std::vector<ASNET::Graph::Direct3D::Vertex> vertices, 
	std::vector<ASNET::Graph::Direct3D::Index> indices){
	release(VertexBuffer);
	release(IndexBuffer);

	VertexCount = vertices.size();
	IndexCount = indices.size();

	D3D11_BUFFER_DESC vbDesc = { 0 };
	vbDesc.ByteWidth = (UINT)vertices.size() * sizeof(Vertex);
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vData = { 0 };
	vData.pSysMem = &vertices[0];
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;

	ParentGraph->g_device3d->CreateBuffer(&vbDesc, &vData, &VertexBuffer);
	if (!indices.empty()) {
		D3D11_BUFFER_DESC ibDesc = { 0 };
		ibDesc.ByteWidth = (UINT)(sizeof(Index) * indices.size());
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA iData = { 0 };
		iData.pSysMem = &indices[0];
		iData.SysMemPitch = 0;
		iData.SysMemSlicePitch = 0;

		ParentGraph->g_device3d->CreateBuffer(&ibDesc, &iData, &IndexBuffer);
	}
}

ASNET::Graph::Direct3D::ShaderDataBuffer::ShaderDataBuffer(ASNET::Graph::Direct3D::GraphDirect3D* Graph){
	ParentGraph = Graph;

	release(DataBuffer);

	Data = nullptr;
}

ASNET::Graph::Direct3D::ShaderDataBuffer::~ShaderDataBuffer(){
	ParentGraph = nullptr;

	release(DataBuffer);

	Data = nullptr;
}

ASNET::Graph::Direct3D::ShaderDataBuffer::operator ID3D11Buffer*(){
	return DataBuffer;
}

void ASNET::Graph::Direct3D::ShaderDataBuffer::UpDateBuffer(){
	if (Data)
		ParentGraph->g_devicecontext3d->UpdateSubresource(DataBuffer, 0, nullptr,
			Data, 0, 0);
}

void ASNET::Graph::Direct3D::ShaderDataBuffer::reset(void * data, UINT datasize){
	release(DataBuffer);

	Data = data;

	CD3D11_BUFFER_DESC constantBufferDesc(
		datasize,
		D3D11_BIND_CONSTANT_BUFFER
	);

	ParentGraph->g_device3d->CreateBuffer(&constantBufferDesc, nullptr, &DataBuffer);

	UpDateBuffer();
}

ASNET::Graph::Direct3D::Texture::Texture(ASNET::Graph::Direct3D::GraphDirect3D* Graph){
	ParentGraph = Graph;

	release(TexView);

	FileName.clear();
}

ASNET::Graph::Direct3D::Texture::~Texture(){
	ParentGraph = nullptr;

	release(TexView);

	FileName.clear();
}

ASNET::Graph::Direct3D::Texture::operator ID3D11ShaderResourceView*(){
	return TexView;
}

void ASNET::Graph::Direct3D::Texture::reset(
	ASNET::Graph::Word filename){
	release(TexView);

	FileName = filename;

	//need get it out 
	D3DX11CreateShaderResourceViewFromFile(ParentGraph->g_device3d,
		&FileName[0], 0, 0, &TexView, 0);
}

ASNET::Graph::Direct3D::Shader::Shader(
	ASNET::Graph::Word VertexShaderFileName, 
	ASNET::Graph::Word PixelShaderFileName, 
	bool IsCompiled,
	char * VertexFunctionName, 
	char * PixelFunctionName){
	ParentGraph = nullptr;


	VertexShaderName = VertexShaderFileName;
	PixelShaderName = PixelShaderFileName;

	VertexShaderFunctionName = VertexFunctionName;
	PixelShaderFunctionName = PixelFunctionName;

	VertexShaderCode.clear();
	PixelShaderCode.clear();

	IsCompile = IsCompiled;
}


ASNET::Graph::Direct3D::Shader::~Shader(){
	ParentGraph = nullptr;

	release(VertexShader);
	release(PixelShader);

	release(VertexShaderBlob);
	release(PixelShaderBlob);

	VertexShaderName.clear();
	PixelShaderName.clear();

	VertexShaderFunctionName = nullptr;
	PixelShaderFunctionName = nullptr;

	VertexShaderCode.clear();
	PixelShaderCode.clear();
}

void ASNET::Graph::Direct3D::Shader::reset(
	ASNET::Graph::Word VertexShaderFileName, 
	ASNET::Graph::Word PixelShaderFileName, 
	bool IsCompiled,
	char * VertexFunctionName, 
	char * PixelFunctionName){
	release(VertexShader);
	release(PixelShader);

	release(VertexShaderBlob);
	release(PixelShaderBlob);

	IsCompile = IsCompiled;

	VertexShaderName = VertexShaderFileName;
	PixelShaderName = PixelShaderFileName;

	VertexShaderFunctionName = VertexFunctionName;
	PixelShaderFunctionName = PixelFunctionName;

	VertexShaderCode.clear();
	PixelShaderCode.clear();

	ParentGraph->SetShader(this);

}

void ASNET::Graph::Direct3D::Shader::SendBufferToVertexShader(
	UINT buffer_id, ASNET::Graph::Direct3D::ShaderDataBuffer * buffer){
	ParentGraph->g_devicecontext3d->VSSetConstantBuffers(
		buffer_id, 1, &buffer->DataBuffer);
}

void ASNET::Graph::Direct3D::Shader::SendBufferToPixelShader(
	UINT buffer_id, ASNET::Graph::Direct3D::ShaderDataBuffer * buffer){
	ParentGraph->g_devicecontext3d->PSSetConstantBuffers(
		buffer_id, 1, &buffer->DataBuffer);
}

void ASNET::Graph::Direct3D::Shader::SendTextureToShader(
	UINT texture_id, ASNET::Graph::Direct3D::Texture * texture){
	
	ParentGraph->g_devicecontext3d->PSSetShaderResources(texture_id,
		1, &texture->TexView);
	
}

void ASNET::Graph::Direct3D::GraphDirect3D::CompileShader(
	ASNET::Graph::Direct3D::Shader * shader){

	ID3DBlob* ErrorBlob = nullptr;

	D3DX11CompileFromFile(&shader->VertexShaderName[0], 0, 0,
		shader->VertexShaderFunctionName, "vs_5_0", 0, 0, 0,
		&shader->VertexShaderBlob, &ErrorBlob, 0);
	
	g_device3d->CreateVertexShader(shader->VertexShaderBlob->GetBufferPointer(),
		shader->VertexShaderBlob->GetBufferSize(), nullptr, &shader->VertexShader);

	ErrorBlob = nullptr;

	D3DX11CompileFromFile(&shader->PixelShaderName[0], 0, 0,
		shader->PixelShaderFunctionName, "ps_5_0", 0, 0, 0,
		&shader->PixelShaderBlob, &ErrorBlob, 0);

	g_device3d->CreatePixelShader(shader->PixelShaderBlob->GetBufferPointer(),
		shader->PixelShaderBlob->GetBufferSize(), nullptr, &shader->PixelShader);
}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadShader(
	ASNET::Graph::Direct3D::Shader * shader){
	std::ifstream vertexfile;
	std::ifstream pixelfile;

	vertexfile.open(shader->VertexShaderName, std::ios::binary);
	byte code = 0;
	while (!vertexfile.eof()) {
		code = vertexfile.get();
		shader->VertexShaderCode.push_back(code);
	}
	vertexfile.close();
	
	shader->VertexShaderCode.pop_back();

	g_device3d->CreateVertexShader(&shader->VertexShaderCode[0],
		shader->VertexShaderCode.size(), nullptr, &shader->VertexShader);
	
	pixelfile.open(shader->PixelShaderName, std::ios::binary);
	code = 0;
	while (!pixelfile.eof()) {
		code = pixelfile.get();
		shader->PixelShaderCode.push_back(code);
	}
	pixelfile.close();

	shader->PixelShaderCode.pop_back();

	g_device3d->CreatePixelShader(&shader->PixelShaderCode[0],
		shader->PixelShaderCode.size(), nullptr, &shader->PixelShader);
	

}

void ASNET::Graph::Direct3D::GraphDirect3D::UpDateInputLayout(Shader * shader){
	release(InputLayout);

	D3D11_INPUT_ELEMENT_DESC InputDesc[6];

	InputDesc[0] = { "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA,0 };
	InputDesc[1] = { "COLOR",   0,DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12, D3D11_INPUT_PER_VERTEX_DATA ,0 };
	InputDesc[2] = { "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,   0,28,D3D11_INPUT_PER_VERTEX_DATA,0 };
	InputDesc[3] = { "NORMAL",  0,DXGI_FORMAT_R32G32B32_FLOAT,0,36,D3D11_INPUT_PER_VERTEX_DATA,0 };
	InputDesc[4] = { "WEIGHTS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	InputDesc[5] = { "BONEINDICES",  0, DXGI_FORMAT_R8G8B8A8_UINT,   0, 60, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	

	if (!shader->IsCompile)
		g_device3d->CreateInputLayout(InputDesc, 6,
			shader->VertexShaderBlob->GetBufferPointer(),
			shader->VertexShaderBlob->GetBufferSize(),
			&InputLayout);
	else
		g_device3d->CreateInputLayout(InputDesc, 6,
			&shader->VertexShaderCode[0],
			shader->VertexShaderCode.size(),
			&InputLayout);
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetShader(
	ASNET::Graph::Direct3D::Shader * shader, bool IsLoad) {
	if (!IsLoad) {
		if (!shader->IsCompile)
			CompileShader(shader);
		else
			LoadShader(shader);
	}

	g_devicecontext3d->VSSetShader(shader->VertexShader, 0, 0);
	g_devicecontext3d->PSSetShader(shader->PixelShader, 0, 0);

	UpDateInputLayout(shader);
	UsedShader = shader;

	shader->ParentGraph = this;
}

void ASNET::Graph::Direct3D::GraphDirect3D::Direct3DInitalize(){
	D3D11_RASTERIZER_DESC RasteDesc;
	RasteDesc.FillMode = D3D11_FILL_SOLID;
	RasteDesc.CullMode = D3D11_CULL_NONE;
	RasteDesc.FrontCounterClockwise = FALSE;
	RasteDesc.DepthBias = 0;
	RasteDesc.SlopeScaledDepthBias = 0.0f;
	RasteDesc.DepthBiasClamp = 0.0f;
	RasteDesc.DepthClipEnable = TRUE;
	RasteDesc.ScissorEnable = FALSE;
	RasteDesc.MultisampleEnable = FALSE;
	RasteDesc.AntialiasedLineEnable = FALSE;

	g_device3d->CreateRasterizerState(&RasteDesc, &RasterizerState);
	g_devicecontext3d->RSSetState(RasterizerState);
}

ASNET::Graph::Direct3D::GraphDirect3D::GraphDirect3D(
	HWND hwnd, ASNET::Graph::Direct3D::Shader * shader, 
	bool IsWindowed){
	Initalize(hwnd, IsWindowed);
	if (shader)
		SetShader(shader);
	Direct3DInitalize();
	
}

ASNET::Graph::Direct3D::GraphDirect3D::~GraphDirect3D(){
	release(InputLayout);
	release(RasterizerState);
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetCullMode(
	ASNET::Graph::Direct3D::CullMode cullmode){
	D3D11_RASTERIZER_DESC RasteDesc;
	RasterizerState->GetDesc(&RasteDesc);
	
	RasteDesc.CullMode = (D3D11_CULL_MODE)cullmode;

	release(RasterizerState);

	g_device3d->CreateRasterizerState(&RasteDesc, &RasterizerState);
	g_devicecontext3d->RSSetState(RasterizerState);
}

void ASNET::Graph::Direct3D::GraphDirect3D::SetFillMode(
	ASNET::Graph::Direct3D::FillMode fillmode){
	D3D11_RASTERIZER_DESC RasteDesc;
	RasterizerState->GetDesc(&RasteDesc);

	RasteDesc.FillMode = (D3D11_FILL_MODE)fillmode;

	release(RasterizerState);

	g_device3d->CreateRasterizerState(&RasteDesc, &RasterizerState);
	g_devicecontext3d->RSSetState(RasterizerState);
}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadTexture(
	ASNET::Graph::Direct3D::Texture *& texture, ASNET::Graph::Word filename){
	if (texture) return;
	texture = new ASNET::Graph::Direct3D::Texture(this);
	texture->FileName = filename;
	texture->ParentGraph = this;

	D3DX11CreateShaderResourceViewFromFile(g_device3d,
		&texture->FileName[0], 0, 0, &texture->TexView, 0);
}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadBuffer(
	ASNET::Graph::Direct3D::Buffer *& buffer,
	std::vector<ASNET::Graph::Direct3D::Vertex> vertices,
	std::vector<ASNET::Graph::Direct3D::Index> indices, bool CPUAcess) {
	if (buffer) return;
	buffer = new ASNET::Graph::Direct3D::Buffer(this);

	buffer->VertexCount = vertices.size();
	buffer->IndexCount = indices.size();
	buffer->ParentGraph = this;

	D3D11_BUFFER_DESC vbDesc = { 0 };
	vbDesc.ByteWidth = (UINT)vertices.size() * sizeof(Vertex);
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (CPUAcess) {
		vbDesc.Usage = D3D11_USAGE_DYNAMIC;
		vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
		vbDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vData = { 0 };
	vData.pSysMem = &vertices[0];
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;

	g_device3d->CreateBuffer(&vbDesc, &vData, &buffer->VertexBuffer);
	if (!indices.empty()) {
		D3D11_BUFFER_DESC ibDesc = { 0 };
		ibDesc.ByteWidth = (UINT)sizeof(Index) * indices.size();
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA iData = { 0 };
		iData.pSysMem = &indices[0];
		iData.SysMemPitch = 0;
		iData.SysMemSlicePitch = 0;

		g_device3d->CreateBuffer(&ibDesc, &iData, &buffer->IndexBuffer);
	}

}

void ASNET::Graph::Direct3D::GraphDirect3D::LoadShaderDataBuffer(
	void * data, UINT datasize,
	ASNET::Graph::Direct3D::ShaderDataBuffer *& buffer){
	if (buffer) return;
	buffer = new ASNET::Graph::Direct3D::ShaderDataBuffer(this);
	buffer->Data = data;
	buffer->ParentGraph = this;

	CD3D11_BUFFER_DESC constantBufferDesc(
		datasize,
		D3D11_BIND_CONSTANT_BUFFER
	);

	g_device3d->CreateBuffer(&constantBufferDesc, nullptr, &buffer->DataBuffer);

	buffer->UpDateBuffer();
}

void ASNET::Graph::Direct3D::GraphDirect3D::DrawBuffer(
	ASNET::Graph::Direct3D::Buffer * buffer, 
	ASNET::Graph::Direct3D::PrimitiveType Type){
	g_devicecontext3d->IASetInputLayout(InputLayout);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_devicecontext3d->IASetVertexBuffers(0, 1, &buffer->VertexBuffer, &stride, &offset);
	if (buffer->IndexBuffer)
		g_devicecontext3d->IASetIndexBuffer(buffer->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	g_devicecontext3d->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)Type);
	if (buffer->IndexBuffer)
		g_devicecontext3d->DrawIndexed(buffer->IndexCount, 0, 0);
	else g_devicecontext3d->Draw(buffer->VertexCount, 0);
}

