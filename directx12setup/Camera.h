#pragma once
#include "AGameObject.h"
#include "InputListener.h"

class Camera: public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	Camera(float width, float height);
	~Camera();

	void update(float deltaTime) override;
	void setDimensions(float width, float height);
	Matrix4x4 getViewMatrix();
	Matrix4x4 getProjMatrix();
	virtual void draw(int width, int height) override;
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mousepos) override;
	virtual void onLeftMouseUp(const Point& mousepos) override;
	virtual void onRightMouseDown(const Point& mousepos) override;
	virtual void onRightMouseUp(const Point& mousepos) override;

private:
	void updateViewMatrix();
	
	float ticks = 0.0f;
	bool mouseDown = false;
	float deltaTime = 0.0f;
	bool m_perspective_toggle = true;
	float m_width;
	float m_height;
	float m_near_plane = 0.1f;
	float fov = 1.57f;
	float forward = 0.0f;
	float rightward = 0.0f;
	Vector3D forwardDirection;
	Vector3D backwardDirection;
};

