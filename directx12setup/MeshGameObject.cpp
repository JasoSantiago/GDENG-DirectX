#include "MeshGameObject.h"



MeshGameObject::MeshGameObject(std::string name, std::wstring filePath, std::wstring tex): AGameObject(name)
{
	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.MESH_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);
	this->mesh = MeshManager::getInstance()->createMeshFromFile(filePath.c_str());
	if(!tex.empty())
		this->m_tex = TextureManager::getInstance()->createTextureFromFile(tex.c_str());
	this->vertex_buffer = mesh->getVertexBuffer();
	this->index_buffer = mesh->getIndexBuffer();
	CBData cbData = {};
	cbData.m_time = 0;
	this->cosntant_buffer = GraphicsEngine::get()->createConstantBuffer();
	this->cosntant_buffer->load(&cbData, sizeof(CBData));
}

MeshGameObject::~MeshGameObject()
{
}

void MeshGameObject::draw(int width, int height)
{
	ShaderNames shaderNames;
	GraphicsEngine* graphics_engine = GraphicsEngine::get();
	DeviceContext* device_context = graphics_engine->getImmediateDeviceContext();


	device_context->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME));
	device_context->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEAPOT_PIXEL_SHADER_NAME));
	CBData cbData = {};

	if (this->deltaPos > 1.0f)
	{
		this->deltaPos = 0.0f;
	}
	else
	{
		this->deltaPos += this->deltaPos * 0.1f;
	}

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity();
	scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getRotation();
	Matrix4x4 zMatrix;
	zMatrix.setRotationZ(rotation.m_z);
	Matrix4x4 yMatrix;
	yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 xMatrix;
	xMatrix.setRotationX(rotation.m_x);

	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	yMatrix *= zMatrix;
	xMatrix *= yMatrix;
	rotMatrix *= xMatrix;
	scaleMatrix *= rotMatrix;
	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;
	//allMatrix.printMatrix();
	cbData.m_world = allMatrix;
	//cbData.m_view.setIdentity();
	//cbData.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cbData.m_view = cameraMatrix;

	//cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	float aspectRatio = (float)width / (float)height;
	//cbData.m_proj.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);
	cbData.m_proj = SceneCameraHandler::getInstance()->getProjectionViewMatrix();
	this->cosntant_buffer->update(device_context, &cbData);
	device_context->setConstantBuffer(this->cosntant_buffer);
	if(m_tex != nullptr)
		device_context->setTexture(this->m_tex);
	device_context->setIndexBuffer(this->mesh->getIndexBuffer());
	device_context->setVertexBuffer(this->mesh->getVertexBuffer());
	device_context->drawIndexedTriangleList(this->mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
}

void MeshGameObject::update(float deltaTime)
{
}
