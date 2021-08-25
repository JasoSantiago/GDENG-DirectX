#include "AppWindow.h"
#include <Windows.h>

#include "GameObjectManager.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "UIManager.h"
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_dx11.h"
#include "imGUI/imgui_impl_win32.h"


AppWindow::AppWindow()
{
}



AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	uniform_real_distribution<float> distr(-0.75, 0.75);
	uniform_real_distribution<float> distr2(-3.75, 3.75);
	Window::onCreate();

	InputSystem::initialize();
	SceneCameraHandler::initialize();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	SceneCameraHandler::getInstance()->getSceneCamera()->setDimensions(m_width, m_height);
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	GameObjectManager::initialize();

	this->planeObject = new Plane("Plane", shader_byte_code, size_shader);
	planeObject->setPosition(0, -0.5, 0.0f);
	planeObject->setScale(0.5f, 0.5f, 0.5f);
	GraphicsEngine::get()->releaseCompiledShader();
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	UIManager::initialize(this->m_hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();
	SceneCameraHandler::getInstance()->update();
	//CLEAR THE RENDER TARGET
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(m_width, m_height);

	planeObject->update(EngineTime::getDeltaTime());
	planeObject->draw(m_width, m_height, this->m_vs, this->m_ps);

	GameObjectManager::getInstance()->updateAll();
	GameObjectManager::getInstance()->renderAll(m_width, m_height, m_vs, m_ps);
	UIManager::getInstance()->drawAllUI();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	
	Window::onDestroy();
	//m_vb->release();
	//m_ib->release();
	//m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
}

void AppWindow::onLeftMouseDown(const Point& mousepos)
{	
}

void AppWindow::onLeftMouseUp(const Point& mousepos)
{
}

void AppWindow::onRightMouseDown(const Point& mousepos)
{
}

void AppWindow::onRightMouseUp(const Point& mousepos)
{
}
