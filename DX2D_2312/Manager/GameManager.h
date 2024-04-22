#pragma once

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update();
	void Render();

private:
	void Create();
	void Delete();

	static void OnDraw() { isDraw = !isDraw; }

private:
	Scene* scene;

public:
	static bool isDraw;
};