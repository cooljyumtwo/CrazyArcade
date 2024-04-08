#pragma once
//Global Buffer

class ColorBuffer : public ConstBuffer
{
public:	
	ColorBuffer() : ConstBuffer(&color, sizeof(Float4))
	{
	}

	void SetColor(float r, float g, float b, float a = 1.0f)
	{
		color = { r, g, b, a };
	}

	void SetColor(Float4 color)
	{
		this->color = color;
	}

	Float4 GetColor() { return color; }

private:
	Float4 color = { 1, 1, 1, 1 };
};

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer() : ConstBuffer(&matrix, sizeof(Matrix))
	{
		matrix = XMMatrixIdentity();
	}

	void Set(Matrix value)
	{
		matrix = XMMatrixTranspose(value);
	}

private:
	Matrix matrix;
};

//상수버퍼는 16의 배수로만 넘겨야 한다.
class FloatValueBuffer : public ConstBuffer
{
public:
	FloatValueBuffer() : ConstBuffer(values, sizeof(float) * 4)
	{
	}

	float* Get() { return values; }

private:
	float values[4] = {};
};

class IntValueBuffer : public ConstBuffer
{
public:
	IntValueBuffer() : ConstBuffer(values, sizeof(int) * 4)
	{
	}

	int* Get() { return values; }

private:
	int values[4] = {};
};

class FrameBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Vector2 maxFrame;
		Vector2 curFrame;
	};

public:
	FrameBuffer() : ConstBuffer(&data, sizeof(Data))
	{
	}

	void SetMaxFrame(Vector2 maxFrame) { data.maxFrame = maxFrame; }
	void SetCurFrame(Vector2 curFrame) { data.curFrame = curFrame; }

private:
	Data data;
};

class OutlineBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Float4 color = { 1, 0, 0, 1 };
		Vector2 imageSize;
		float weight = 1;

		float padding;
	};

public:
	OutlineBuffer() : ConstBuffer(&data, sizeof(Data))
	{
	}

	Data& GetData() { return data; }

private:
	Data data;
};

class LightBuffer : public ConstBuffer
{
private:
	struct Data
	{		
		Vector2 imageSize;
		Vector2 lightPos;

		float range;
		float attenuation;

		float padding[2];
	};

public:
	LightBuffer() : ConstBuffer(&data, sizeof(Data))
	{
	}

	Data& GetData() { return data; }

private:
	Data data;
};