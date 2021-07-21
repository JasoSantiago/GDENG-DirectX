#include "AppWindow.h"
#include "Windows.h"
#include <iostream>


__declspec(align(16))
struct constant
{
	float m_angle;
};

AppWindow::AppWindow()
{
	m_sound_class = 0;
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	/*m_sound_class = new SoundClass;
	if (!m_sound_class)
	{
	}
	if(m_sound_class->Initialize(this->m_hwnd))
	{
	}*/
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		{-0.6f, -0.25f, 0.0f,-0.9f, -0.55f, 0.0f, 1,0,0, 0,1,0},
		{-0.4f, 0.25f, 0.0f,-0.7f, 0.55f, 0.0f, 0,1,0, 1,1,0},
		{-0.2f, -0.25f, 0.0f, -0.5f, -0.55f, 0.0f,0,0,1, 1,0,0}
	};

	vertex quadlist[] =
	{
		{0.0f, -0.25f, 0.0f, -0.11f, -0.55f, 0.0f, 1,0,0, 0,1,0}, // bottom right
		{0.0f, 0.25f, 0.0f,  -0.055f,0.39f,0.0f,0,1,0, 1,1,0}, //upper left
		{0.25f, -0.25f, 0.0f,  0.345f,-0.38f,0.0f,0,0,1, 1,0,0},// lower left
		{0.25f, 0.25f, 0.0f,0.44f,0.385f,0.0f, 1,1,0, 0,0,1}//upper right
	};
	vertex greenquadlist[] = {
		{0.26f, -0.25f, 0.0f,0.10f, -0.055f, 0.0f,0,1,0, 1,0,0}, // bottom right
		{0.26f, 0.25f, 0.0f,0.10f, 0.39f, 0.0f, 0,1,0, 1,0,0}, //upper left
		{0.5f, -0.25f, 0.0f,0.75f, -0.365f, 0.0f, 0,1,0, 1,0,0},
		{0.5f, 0.25f, 0.0f,0.75f, 0.335f, 0.0f, 0,1,0, 1,0,0}
	};

	vertex pardcodequad[]
	{
	{-0.5f, -0.5f, 0.0f, -0.32f, -0.11f, 0.0f, 0, 0, 0, 0, 1, 0 },
	{ -0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 },
	{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },
	{ 0.5f,-0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_qvb = GraphicsEngine::get()->createVertexBuffer();
	m_qgvb = GraphicsEngine::get()->createVertexBuffer();
	pc_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);
	UINT quad_size_list = ARRAYSIZE(quadlist);
	UINT quad_green_size = ARRAYSIZE(greenquadlist);
	UINT pardecode_size_list = ARRAYSIZE(pardcodequad);
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	m_vb->loadQuad(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	m_qvb->loadQuad(quadlist, sizeof(vertex), quad_size_list, shader_byte_code, size_shader);
	m_qgvb->loadQuad(greenquadlist, sizeof(vertex), quad_green_size, shader_byte_code, size_shader);
	//pc_vb->loadQuad(pardcodequad, sizeof(vertex), pardecode_size_list, shader_byte_code, size_shader);
	Quad::createQuad(pardcodequad, pc_vb, shader_byte_code, size_shader, pardecode_size_list);
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;
	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	//unsigned long new_time = 0;
	//if (m_old_time)
	//	//new_time = ::GetTickCount() - m_old_time;
	//new_time = 
	//m_delta_time = new_time / 1000.0f;
	//m_old_time = ::GetTickCount();

	m_angle += 2.0f * EngineTime::getDeltaTime();;

	

	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	/*GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_qvb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_qvb->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_qgvb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_qgvb->getSizeVertexList(), 0);*/

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(pc_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(pc_vb->getSizeVertexList(), 0);
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	m_qvb->release();
	m_qgvb->release();
	//m_sound_class->release();
	GraphicsEngine::get()->release();
}