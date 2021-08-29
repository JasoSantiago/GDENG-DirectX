#include "TexturedCube.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"
#include "TextureManager.h"

TexturedCube::TexturedCube(std::string name) :Cube(name,true)
{
	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	this->m_tex = TextureManager::getInstance()->createTextureFromFile(L"wood.jpg");
	Vector3D positionList[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};
Vector2D textcoordList[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

Vertex vertexList[] =
{

		{ positionList[0],textcoordList[1] },
		{ positionList[1],textcoordList[0] },
		{ positionList[2],textcoordList[2] },
		{ positionList[3],textcoordList[3] },


		{ positionList[4],textcoordList[1] },
		{ positionList[5],textcoordList[0] },
		{ positionList[6],textcoordList[2] },
		{ positionList[7],textcoordList[3] },


		{ positionList[1],textcoordList[1] },
		{ positionList[6],textcoordList[0] },
		{ positionList[5],textcoordList[2] },
		{ positionList[2],textcoordList[3] },

		{ positionList[7],textcoordList[1] },
		{ positionList[0],textcoordList[0] },
		{ positionList[3],textcoordList[2] },
		{ positionList[4],textcoordList[3] },

		{ positionList[3],textcoordList[1] },
		{ positionList[2],textcoordList[0] },
		{ positionList[5],textcoordList[2] },
		{ positionList[4],textcoordList[3] },

		{ positionList[7],textcoordList[1] },
		{ positionList[6],textcoordList[0] },
		{ positionList[1],textcoordList[2] },
		{ positionList[0],textcoordList[3] }
};

	this->vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	//Quad::createQuad(vertex_list, vertex_buffer, shaderByteCode, sizeShader, ARRAYSIZE(vertex_list));
	this->vertex_buffer->loadTexturedQuad(vertexList, sizeof(Vertex), ARRAYSIZE(vertexList), shaderByteCode, sizeShader);



	unsigned int index_list[] =
	{
		 0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE

		4,5,6,
		6,7,4,

		//TOP SIDE
		8,9,10,
		10,11,8,

		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	index_buffer = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	index_buffer->load(index_list, size_index_list);
	CBData cbData = {};
	cbData.m_time = 0;
	this->cosntant_buffer = GraphicsEngine::get()->createConstantBuffer();
	this->cosntant_buffer->load(&cbData, sizeof(CBData));
	
}

TexturedCube::~TexturedCube()
{
	this->vertex_buffer->release();
	this->index_buffer->release();
	AGameObject::~AGameObject();
}

void TexturedCube::update(float deltaTime)
{
}

void TexturedCube::draw(int width, int height)
{
	ShaderNames shaderNames;
	GraphicsEngine* graphics_engine = GraphicsEngine::get();
	DeviceContext* device_context = graphics_engine->getImmediateDeviceContext();


	device_context->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME));
	device_context->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));



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
	device_context->setTexture(this->m_tex);
	device_context->setIndexBuffer(this->index_buffer);
	device_context->setVertexBuffer(this->vertex_buffer);
	device_context->drawIndexedTriangleList(this->index_buffer->getSizeIndexList(), 0, 0);
}
