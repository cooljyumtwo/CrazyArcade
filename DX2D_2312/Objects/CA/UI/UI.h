#pragma once

class UI
{
protected:
	const wstring PATH = L"ResourcesCA/Textures/UI/";

public:
	virtual ~UI() = default;

	virtual void Update() = 0;

	virtual void PreRender() {}
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual void Start() {}
	virtual void End() {}
};