#pragma once


class Vector2D
{
public:
	Vector2D() :m_x(0), m_y(0)
	{

	}

	Vector2D(float x, float y) :m_x(x), m_y(y)
	{

	}

	Vector2D(const Vector2D& vector) :m_x(vector.m_x), m_y(vector.m_y)
	{

	}
	~Vector2D()
	{

	}

	Vector2D operator *(float num)
	{
		return Vector2D(m_x * num, m_y * num);
	}

	Vector2D operator +(Vector2D vec)
	{
		return Vector2D(m_x + vec.m_x, m_y + vec.m_y);
	}

	void operator +=(Vector2D vec)
	{
		m_x += vec.m_x;
		m_y += vec.m_y;

	}

	static Vector2D zeros()
	{
		Vector2D temp = Vector2D();
		return temp;
	}

	static Vector2D ones()
	{
		Vector2D temp = Vector2D(1.0f, 1.0f);
		return temp;
	}

	float getX()
	{
		return m_x;
	}
	float getY()
	{
		return m_y;
	}
public:
	float m_x, m_y;
};