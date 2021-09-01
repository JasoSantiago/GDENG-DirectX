#include "Plane.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"

Plane::Plane(std::string name, bool skipinit): AGameObject(name)
{
	if(skipinit)
	{
		return;
	}
	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	Vertex plane_list[] =
	{
		{Vector3D(-3.0f,-0.0f,-3.0f),    Vector3D(1.0f,1.0f,1.0f),  Vector3D(1.0f,1.0f,1.0f) },
		{Vector3D(-3.0f,0.0f,3.0f),    Vector3D(1.0f,1.0f,1.0f), Vector3D(1.0f,1.0f,1.0f) },
		{ Vector3D(3.0f,-0.0f,-3.0f),   Vector3D(1.0f,1.0f,1.0f),  Vector3D(1.0f,1.0f,1.0f) },
		{ Vector3D(3.0f,0.f,3.0f),     Vector3D(1.0f,1.0f,1.0f), Vector3D(1.0f,1.0f,1.0f) },
	};

	this->vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	vertex_buffer->loadQuad(plane_list, sizeof(Vertex), ARRAYSIZE(plane_list),shaderByteCode,sizeShader);
	CBData cbData = {};
	cbData.m_time = 0;
	this->cosntant_buffer = GraphicsEngine::get()->createConstantBuffer();
	this->cosntant_buffer->load(&cbData, sizeof(CBData));
}

Plane::~Plane()
{
	this->vertex_buffer->release();
	AGameObject::~AGameObject();
}

void Plane::update(float deltaTime)
{
}

void Plane::draw(int width, int height)
{
	ShaderNames shaderNames;
	GraphicsEngine* graphics_engine = GraphicsEngine::get();
	DeviceContext* device_context = graphics_engine->getImmediateDeviceContext();

	device_context->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME));
	device_context->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));

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
	device_context->setConstantBuffer( this->cosntant_buffer);


	device_context->setVertexBuffer(this->vertex_buffer);
	device_context->drawTriangleStrip(this->vertex_buffer->getSizeVertexList(), 0);

	
}
