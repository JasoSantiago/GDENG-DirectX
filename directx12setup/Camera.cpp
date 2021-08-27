#include "Camera.h"

#include "EngineTIme.h"
#include "InputSystem.h"


Camera::Camera(std::string name): AGameObject(name)
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	this->setPosition(0.0f, 0.0f, -4.0f);
	//this->worldCameraMatrix.setTranslation(this->getLocalPosition());
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}

Camera::Camera(float width, float height): AGameObject("Camera")
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	this->setPosition(0.0f, 0.0f, -4.0f);
	//this->worldCameraMatrix.setTranslation(this->getLocalPosition());
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
	m_width = width;
	m_height = height;
	
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	this->deltaTime = deltaTime;

	Matrix4x4 temp(this->localMatrix);
	temp.inverse();

	Vector3D new_pos = temp.getZDirection() * (forward * 0.1f);
	new_pos += (temp.getXDirection() * (rightward * 0.1f));

	setPosition(localPosition + new_pos);
	
	this->updateViewMatrix();
}

void Camera::setDimensions(float width, float height)
{
	m_width = width;
	m_height = height;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

Matrix4x4 Camera::getProjMatrix()
{
	Matrix4x4 tempMatrix;
	float aspectRatio =m_width / m_height;
	if (m_perspective_toggle) {
		tempMatrix.setPerspectiveFovLH(fov - (m_near_plane * 0.5f), aspectRatio, m_near_plane, 1000.0f);
		return tempMatrix;
	}
	else
	{
		tempMatrix.setOrthoLH(aspectRatio, aspectRatio, -4.0f, 4.0f);
		return tempMatrix;
	}
}

void Camera::draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
}

void Camera::onKeyDown(int key)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = 10.0f;
	if (key == 'W')
	{
		forward = 1.0f;
		//z += deltaTime * moveSpeed;
		//this->setPosition(x, y, z);
		
	}
	else if (key == 'S')
	{
		forward = -1.0f;
			//z -= deltaTime * moveSpeed;
			//this->setPosition(x, y, z);
	}
	else if (key == 'A')
	{
		rightward = -1.0f;
			//x -= deltaTime * moveSpeed;
			//this->setPosition(x, y, z);

	}
	else if (key == 'D')
	{
		rightward = 1.0f;
			//x += deltaTime * moveSpeed;
			//this->setPosition(x, y, z);
	}
	else if(key == 'Q')
	{
		//y += deltaTime * moveSpeed;
		//this->setPosition(x, y, z);
	}

	else if (key == 'E')
	{
		//y -= deltaTime * moveSpeed;
		//this->setPosition(x, y, z);
	}
	else if(key == 'Z')
	{
		m_near_plane += EngineTime::getDeltaTime() * 1.0f;
		if(m_near_plane > 100.0f)
		{
			m_near_plane = 100.0f;
		}
	}
	else if(key == 'X')
	{
		m_near_plane -= EngineTime::getDeltaTime() * 1.0f;
		if(m_near_plane < 0.1f)
		{
			m_near_plane = 0.1f;
		}
	}
}

void Camera::onKeyUp(int key)
{
	if (key == 'W')
	{
		forward = 0.0f;

	}
	else if (key == 'S')
	{
		forward = 0.0f;
	}
	else if (key == 'A')
	{
		rightward = 0.0f;

	}
	else if (key == 'D')
	{
		rightward = 0.0f;

	}
	if(key == 'T')
	{
		m_perspective_toggle = !m_perspective_toggle;
	}
}

void Camera::onMouseMove(const Point& delta_mouse_pos)
{

	if (this->mouseDown) {
		Vector3D localRot = this->getRotation();
		float x = localRot.m_x;
		float y = localRot.m_y;
		float z = localRot.m_z;

		float speed = 0.005f;
		x += delta_mouse_pos.m_y * speed;
		y += delta_mouse_pos.m_x * speed;

		this->setRotation(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::onLeftMouseDown(const Point& mousepos)
{
}

void Camera::onLeftMouseUp(const Point& mousepos)
{
}

void Camera::onRightMouseDown(const Point& mousepos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point& mousepos)
{
	this->mouseDown = false;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getRotation();

	temp.setRotationX(localRot.m_x);
	worldCam *= temp;

	temp.setRotationY(localRot.m_y);
	worldCam *= temp;

	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;

	worldCam.inverse();
	this->localMatrix = worldCam;
}
