#pragma once
#include <random>
#include <vector>

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"
#include "SoundClass.h"
//#include "Quad.h"
//#include "Cube.h"
#include "IndexBuffer.h"
#include "AGameObject.h"
#include "Plane.h"
#include "TexturedCube.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	//void update();
	~AppWindow();

	//inherited via window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	//inherited via inputlistener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mousepos)  override;
	virtual void onLeftMouseUp(const Point& mousepos)  override;

	virtual void onRightMouseDown(const Point& mousepos)  override;
	virtual void onRightMouseUp(const Point& mousepos)  override;

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexBuffer* m_qvb;
	VertexBuffer* m_qgvb;
	VertexBuffer* pc_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	SoundClass* m_sound_class;
	IndexBuffer* m_ib;
	unsigned long m_old_time = 0;
	float m_angle = 0;
	bool movement = true;

private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;
	
	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float scale = 0.25f;
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	float m_width;
	float m_height;
	Matrix4x4 m_world_cam;

	int width;
	int height;
	std::vector<Cube*> Cubelist;
	Plane* planeObject;
	Texture* m_wood_tex;
	TexturedCube* textCube;
};


