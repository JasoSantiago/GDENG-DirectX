#include "AppWindow.h"
#include <Windows.h>
#include "GameObjectManager.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "MeshManager.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"
#include "UIManager.h"
#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_dx11.h"
#include "imGUI/imgui_impl_win32.h"
#include "TextureManager.h"
#include "Texture.h"


AppWindow::AppWindow()
{
}



AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//rndommizing positions
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(-0.75, 0.75);
	std::uniform_real_distribution<float> distr2(-3.75, 3.75);

	Window::onCreate();

	InputSystem::initialize();
	SceneCameraHandler::initialize();
	GraphicsEngine::get()->init();
	ShaderLibrary::initialize();
	MeshManager::initialize();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	SceneCameraHandler::getInstance()->getSceneCamera()->setDimensions(m_width, m_height);
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GameObjectManager::initialize();
	TextureManager::initialize();

	m_mgb = new MeshGameObject("teapot", L"teapot.obj", L"brick.png");
	m_mgb1 = new MeshGameObject("bunny", L"bunny.obj", L"");
	m_mgb2 = new MeshGameObject("armadillo", L"armadillo.obj", L"");

	m_mgb->setPosition(0.0f, 0.0f, 0.0f);
	m_mgb1->setPosition(1.0f, 0.0f, 0.0f);
	m_mgb2->setPosition(-1.0f, 0.0f, 0.0f);
	m_mgb->setScale(1.0f, 1.0f, 1.0f);
	m_mgb1->setScale(1.0f, 1.0f, 1.0f);
	m_mgb2->setScale(1.0f, 1.0f, 1.0f);
	GameObjectManager::getInstance()->addObject(m_mgb);
	GameObjectManager::getInstance()->addObject(m_mgb1);
	GameObjectManager::getInstance()->addObject(m_mgb2);
	GraphicsEngine::get()->releaseCompiledShader();
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	GraphicsEngine::get()->releaseCompiledShader();


	UIManager::initialize(this->m_hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();
	SceneCameraHandler::getInstance()->update();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);


	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(m_width, m_height);;
	GameObjectManager::getInstance()->updateAllObjects();
	GameObjectManager::getInstance()->renderAllObjects(m_width, m_height);
	UIManager::getInstance()->drawAllUI();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	ShaderLibrary::destroy();
	SceneCameraHandler::destroy();
	TextureManager::destroy();
	MeshManager::destroy();
	GameObjectManager::destroy();
	Window::onDestroy();
	InputSystem::getInstance()->removeListener(this);
	InputSystem::getInstance()->destroy();
	/*this->m_vb->release();
	this->m_ib->release();
	this->m_cb->release();*/
	this->m_swap_chain->release();
	//this->vertexShader->release();
	//this->pixelShader->release();

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
