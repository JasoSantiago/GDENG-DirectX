#pragma once
#include "VertexBuffer.h"
class TexturedVertexBuffer : public VertexBuffer
{
public:
	TexturedVertexBuffer();
	~TexturedVertexBuffer();

	bool loadQuad(void* vertexList, UINT vertexSize, UINT listSize, void* shaderByteCode, UINT byteShaderSize);
};
