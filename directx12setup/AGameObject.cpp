#include "AGameObject.h"


AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->localRotation = Vector3D::zeros();
	this->localPosition = Vector3D::zeros();
	this->localScale = Vector3D::ones();
}

AGameObject::~AGameObject()
{
}

void AGameObject::update(float deltaTime)
{
}

void AGameObject::draw(int width, int height)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
	this->matrixchanged = false;
}

void AGameObject::setPosition(Vector3D position)
{
	this->localPosition = Vector3D(position);
	this->matrixchanged = false;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
	this->matrixchanged = false;
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = Vector3D(scale);
	this->matrixchanged = false;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float m_x, float m_y, float m_z)
{
	this->localRotation = Vector3D(m_x, m_y, m_z);
	this->matrixchanged = false;
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = Vector3D(rot);
	this->matrixchanged = false;
}

Vector3D AGameObject::getRotation()
{
	return this->localRotation;
}

std::string AGameObject::getName()
{
	return this->name;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D::ones());
	Vector3D rotation = this->getRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);

	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	yMatrix *= zMatrix;
	xMatrix *= yMatrix;
	rotMatrix *= xMatrix;
	scaleMatrix *= rotMatrix;
	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;

	return allMatrix.getMatrix();
}

void AGameObject::setLocalMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setIdentity(); newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setIdentity(); transMatrix.setTranslation(this->localPosition);
	transMatrix *= newMatrix;
	scaleMatrix *= transMatrix;
	this->localMatrix = scaleMatrix;
	this->matrixchanged = true;
}

bool AGameObject::isEnabled()
{
	return this->enabled;
}

void AGameObject::setEnabled(bool flag)
{
	this->enabled = flag;
}

void AGameObject::attachComponent(AComponentSystem* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponentSystem* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponentSystem* AGameObject::findComponentOfType(AComponentSystem::ComponentType type, std::string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return nullptr;
}

Matrix4x4 AGameObject::getMatrix()
{
	return this->localMatrix;
}

void AGameObject::saveState()
{
	this->storedPosition = this->localPosition;
	this->storedRotation = this->localRotation;
	this->storedScale = this->localScale;
	this->storedMatrix.setIdentity();
	this->storedMatrix = this->localMatrix;
}

void AGameObject::restoreState()
{
	this->localPosition = this->storedPosition;
	this->localRotation = this->storedRotation;
	this->localScale = this->storedScale;
	this->localMatrix = this->storedMatrix;
}
