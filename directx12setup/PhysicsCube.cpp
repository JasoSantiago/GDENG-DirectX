#include "PhysicsCube.h"

#include "PhysicsComponent.h"
#include "ShaderLibrary.h"

PhysicsCube::PhysicsCube(std::string name, bool skipinit): Cube(name, skipinit)
{
	this->setPosition(0.0f, 8.0f, 0.0f);
	this->setScale(0.5f, 0.5f, 0.5f);
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
	this->attachPhysicsComponent();
}

PhysicsCube::~PhysicsCube()
{
	Cube::~Cube();
}

void PhysicsCube::draw(int width, int height)
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

	device_context->setIndexBuffer(this->index_buffer);
	device_context->setVertexBuffer(this->vertex_buffer);
	device_context->drawIndexedTriangleList(this->index_buffer->getSizeIndexList(), 0, 0);
}

void PhysicsCube::update(float delta_time)
{
	
}

void PhysicsCube::restoreState()
{
	Cube::restoreState();
	this->detachComponent(this->component);
	this->attachPhysicsComponent();
	
}

void PhysicsCube::attachPhysicsComponent()
{
	this->component = new PhysicsComponent("PhysicsComponent", this);
	this->attachComponent(this->component);

	this->component = (PhysicsComponent*)this->findComponentOfType(AComponentSystem::ComponentType::Physics, "PhysicsComponent");
	this->component->getRigidBody()->setMass(this->mass);
}
