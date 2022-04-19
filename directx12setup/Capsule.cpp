#include "Capsule.h"

#include "GameObjectManager.h"
#include "LoadedMeshObject.h"
#include "GraphicsEngine.h"
#include "TextureComponent.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "BoundingBox.h"
#include "VertexBuffer.h"

Capsule::Capsule(std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot, bool hasPhysics): AGameObject(name, AGameObject::PrimitiveType::CAPSULE)
{
	this->localPosition = pos;
	this->localScale = scale;
	this->localRotation = rot;

	m_default_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\blank.png");
	m_mesh = GraphicsEngine::getInstance()->getMeshManager()->creatMeshFromFile(L"Assets\\Meshes\\Capsule.png");

	if (this->hasPhysics)
		this->attachComponent(new PhysicsComponent("cubePhysics", this));
	m_default_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\blank.jpg");

	edges[0] = Vector3D(-this->localScale.x / 2.0f, -this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[1] = Vector3D(-this->localScale.x / 2.0f, this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[2] = Vector3D(this->localScale.x / 2.0f, this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[3] = Vector3D(this->localScale.x / 2.0f, -this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[4] = Vector3D(this->localScale.x / 2.0f, -this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[5] = Vector3D(this->localScale.x / 2.0f, this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[6] = Vector3D(-this->localScale.x / 2.0f, this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[7] = Vector3D(-this->localScale.x / 2.0f, -this->localScale.y / 2.0f, this->localScale.z / 2.0f);

	collisionBox = new BoundingBox(this->localPosition, this->localRotation, 1.0f * this->localScale.x, 1.0f * this->localScale.y, 1.0f * this->localScale.z);

	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = graphEngine->createVertexShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();
}

Capsule::~Capsule()
{
}

void Capsule::setColors(Vector3D color)
{
}

void Capsule::update(float deltaTime)
{
}

void Capsule::draw(ConstantBuffer* cb)
{
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	std::vector<AComponent*> renderComponentList = getComponentsOfType(AComponent::ComponentType::Renderer);
	if (renderComponentList.size() > 0)
	{
		TextureComponent* texComp = (TextureComponent*)renderComponentList[0];
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, texComp->getTexture());
	}
	else
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_default_tex);



	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Capsule::setPosition(float x, float y, float z)
{
	AGameObject::setPosition(x, y, z);
}

void Capsule::setPosition(Vector3D pos)
{
	AGameObject::setPosition(pos);
}

void Capsule::setScale(float x, float y, float z)
{
	AGameObject::setScale(x, y, z);
}

void Capsule::setScale(Vector3D scale)
{
	AGameObject::setScale(scale);
}

void Capsule::setRotation(float x, float y, float z)
{
	AGameObject::setRotation(x, y, z);
}

void Capsule::setRotation(Vector3D rot)
{
	AGameObject::setRotation(rot);
}

Vector3D* Capsule::getVertexWorldPositions()
{
	Vector3D worldLocations[] = {
		Quaternion::rotatePointEuler(edges[0], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[1], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[2], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[3], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[4], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[5], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[6], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[7], this->localRotation) + this->localPosition,
	};

	return worldLocations;
}

void Capsule::attachPhysicsComponent()
{
}

float Capsule::checkRaycast(Vector3D rayOrigin, Vector3D rayDirection)
{
	return collisionBox->checkRaycast(rayOrigin, rayDirection);
}

void Capsule::updateVertexLocations()
{
	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	Vector3D* worldLocations = getVertexWorldPositions();

	Vector3D positionList[] = {
		worldLocations[0],
		worldLocations[1],
		worldLocations[2],
		worldLocations[3],

		worldLocations[4],
		worldLocations[5],
		worldLocations[6],
		worldLocations[7],
	};

	Vector2D texcoordList[] = {
		Vector2D(0,0),
		Vector2D(0,1),
		Vector2D(1,0),
		Vector2D(1,1)
	};

	vertex vertexList[] = {
		{ positionList[0],texcoordList[1] },
		{ positionList[1],texcoordList[0] },
		{ positionList[2],texcoordList[2] },
		{ positionList[3],texcoordList[3] },


		{ positionList[4],texcoordList[1] },
		{ positionList[5],texcoordList[0] },
		{ positionList[6],texcoordList[2] },
		{ positionList[7],texcoordList[3] },


		{ positionList[1],texcoordList[1] },
		{ positionList[6],texcoordList[0] },
		{ positionList[5],texcoordList[2] },
		{ positionList[2],texcoordList[3] },

		{ positionList[7],texcoordList[1] },
		{ positionList[0],texcoordList[0] },
		{ positionList[3],texcoordList[2] },
		{ positionList[4],texcoordList[3] },

		{ positionList[3],texcoordList[1] },
		{ positionList[2],texcoordList[0] },
		{ positionList[5],texcoordList[2] },
		{ positionList[4],texcoordList[3] },

		{ positionList[7],texcoordList[1] },
		{ positionList[6],texcoordList[0] },
		{ positionList[1],texcoordList[2] },
		{ positionList[0],texcoordList[3] }
	};

	UINT size_list = ARRAYSIZE(vertexList);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	delete m_vb;
	m_vb = graphEngine->createVertexBuffer(vertexList, sizeof(vertex), size_list, shader_byte_code, size_shader);
}
