#include "PhysicsPlane.h"

#include "PhysicsComponent.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"

PhysicsPlane::PhysicsPlane(std::string name, bool skipinit) :Plane(name, skipinit)
{
	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	Vertex plane_list[] =
	{
		{Vector3D(-0.5f,-0.0f,-0.5f),    Vector3D(1.0f,1.0f,1.0f),  Vector3D(1.0f,1.0f,1.0f) },
		{Vector3D(-0.5f,0.0f,0.5f),    Vector3D(1.0f,1.0f,1.0f), Vector3D(1.0f,1.0f,1.0f) },
		{ Vector3D(0.5f,-0.0f,-0.5f),   Vector3D(1.0f,1.0f,1.0f),  Vector3D(1.0f,1.0f,1.0f) },
		{ Vector3D(0.5f,0.0f,0.5f),     Vector3D(1.0f,1.0f,1.0f), Vector3D(1.0f,1.0f,1.0f) },
	};
	this->setPosition(0.0f, 0.0f, 0.0f);
	this->setScale( Vector3D(8.0f, 0.2f, 8.0f));
	this->vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	vertex_buffer->loadQuad(plane_list, sizeof(Vertex), ARRAYSIZE(plane_list), shaderByteCode, sizeShader);
	CBData cbData = {};
	cbData.m_time = 0;
	this->cosntant_buffer = GraphicsEngine::get()->createConstantBuffer();
	this->cosntant_buffer->load(&cbData, sizeof(CBData));
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
	this->localMatrix = allMatrix;
	this->attachComponent(new PhysicsComponent("PhysicsComponent", this));

	PhysicsComponent* component = (PhysicsComponent*)this->findComponentOfType(AComponentSystem::ComponentType::Physics, "PhysicsComponent");
	component->getRigidBody()->setType(BodyType::KINEMATIC);
}

PhysicsPlane::~PhysicsPlane()
{
}

void PhysicsPlane::draw(int width, int height)
{
	ShaderNames shaderNames;
	GraphicsEngine* graphics_engine = GraphicsEngine::get();
	DeviceContext* device_context = graphics_engine->getImmediateDeviceContext();

	device_context->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME));
	device_context->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));
	if (!this->matrixchanged) {
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
		this->localMatrix = allMatrix;
	}

	CBData cbData = {};
	cbData.m_world = this->localMatrix;
	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cbData.m_view = cameraMatrix;

	//cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	float aspectRatio = (float)width / (float)height;
	//cbData.m_proj.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);
	cbData.m_proj = SceneCameraHandler::getInstance()->getProjectionViewMatrix();
	this->cosntant_buffer->update(device_context, &cbData);
	device_context->setConstantBuffer(this->cosntant_buffer);
	device_context->setVertexBuffer(this->vertex_buffer);
	device_context->drawTriangleStrip(this->vertex_buffer->getSizeVertexList(), 0);
}