#pragma once

struct Vector2 : public Float2
{
	Vector2(float x = 0.0f, float y = 0.0f) : Float2(x, y)
	{
	}	

	Vector2 operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2 operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}
	Vector2 operator/(const Vector2& v) const
	{
		return Vector2(x / v.x, y / v.y);
	}

	void operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
	}
	void operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	Vector2 operator*(const float& s) const
	{
		return Vector2(x * s, y * s);
	}
	Vector2 operator/(const float& s) const
	{
		return Vector2(x / s, y / s);
	}

	void operator*=(const float& s)
	{
		x *= s;
		y *= s;
	}
	void operator/=(const float& s)
	{
		x /= s;
		y /= s;
	}

	Vector2 operator*(const Matrix& m) const
	{
		XMVECTOR coord = XMLoadFloat2(this);

		//XMVector2TransformNormal
		coord = XMVector2TransformCoord(coord, m);

		Vector2 result;
		XMStoreFloat2(&result, coord);

		return result;
	}

	float Magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	void Normalize()
	{
		float length = Magnitude();

		x /= length;
		y /= length;
	}

	float Angle() const
	{
		return atan2(y, x);
	}

	Vector2 Normalized() const
	{
		float length = Magnitude();

		return Vector2(x / length, y / length);
	}

	static float Cross(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	static float Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	static Vector2 Left() { return Vector2(-1.0f, 0.0f); }
	static Vector2 Right() { return Vector2(+1.0f, 0.0f); }
	static Vector2 Up() { return Vector2(0.0f, +1.0f); }
	static Vector2 Down() { return Vector2(0.0f, -1.0f); }
};