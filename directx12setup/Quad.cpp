#include "Quad.h"


Quad::Quad()
{
}

Quad::~Quad()
{
}

void Quad::createQuad(vertex list[], VertexBuffer* mq_vb, void* shader_byte_code, size_t size_shader, UINT sizeList)
{
	mq_vb->loadQuad(list, sizeof(vertex), sizeList, shader_byte_code, size_shader);
}

void Quad::onUpdate(VertexBuffer* mq_vb)
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(mq_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(mq_vb->getSizeVertexList(), 0);
}
