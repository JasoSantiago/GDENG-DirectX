#include "Cube.h"


Cube::Cube(std::string name, void* shaderByteCode, size_t sizeShader, bool skipinit): AGameObject(name)
{
	if(skipinit)
	{
		return;
	}

	std::cout << "created Cube";
	Vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	this->vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	//Quad::createQuad(vertex_list, vertex_buffer, shaderByteCode, sizeShader, ARRAYSIZE(vertex_list));
	vertex_buffer->loadQuad(vertex_list, sizeof(Vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	index_buffer = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	index_buffer->load(index_list, size_index_list);
	CBData cbData = {};
	cbData.m_time = 0;
	this->cosntant_buffer = GraphicsEngine::get()->createConstantBuffer();
	this->cosntant_buffer->load(&cbData, sizeof(CBData)); 

}

Cube::~Cube()
{
	this->vertex_buffer->release();
	this->index_buffer->release();
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	/*this->deltaTime = deltaTime;
	this->ticks += deltaTime;
	float rotSpeed = this->ticks * this->speed;*/
	this->setRotation(this->rot_x, this->rot_y, 0.0f);
}

void Cube::draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
	GraphicsEngine* graphics_engine = GraphicsEngine::get();
	DeviceContext* device_context = graphics_engine->getImmediateDeviceContext();

	CBData cbData = {};

	if(this->deltaPos > 1.0f)
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

	device_context->setIndexBuffer(this->index_buffer);
	device_context->setVertexBuffer(this->vertex_buffer);
	device_context->drawIndexedTriangleList(this->index_buffer->getSizeIndexList(), 0, 0);
}


void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

void Cube::rotateCubex(float value, float deltaTime)
{
	this->rot_x += value * deltaTime;
}

void Cube::rotateCubey(float value, float deltaTime)
{
	this->rot_y += value * deltaTime;
}
