#pragma once

class Device : public Singleton<Device>
{
private:
	friend class Singleton;

	Device();
	~Device();

public:
	void Clear();
	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }
	IDXGISwapChain* GetSwapChain() { return swapChain; }

private:
	ID3D11Device* device;//CPU->리소스로드, 객체 생성 등
	ID3D11DeviceContext* deviceContext;//GPU ->출력

	IDXGISwapChain* swapChain;//후면버퍼 관리
	ID3D11RenderTargetView* renderTargetView;//VRAM 후면버퍼 메모리 관리
};