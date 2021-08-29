#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "ConstantBuffer.h"
#include "Mesh.h"
#include "Texture.h"
#include "MeshManager.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"
#include "TextureManager.h"
#include "DeviceContext.h"

class MeshGameObject : public AGameObject
{
public:
	MeshGameObject(std::string name, std::wstring filePath, std::wstring tex);
	~MeshGameObject();
	void draw(int width, int height) override;
	void update(float deltaTime) override;
private:

	Mesh* mesh;
	Texture* m_tex;
	VertexBuffer* vertex_buffer;
	IndexBuffer* index_buffer;
	ConstantBuffer* cosntant_buffer;
	float deltaPos = 0.0f;
};

