#pragma once

class GameManager
{
private :
	const Vector2 CURSOR_OFFSET = { 15.0f, -20.0f };

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
	Button* cursor;

public:
	static bool isDraw;
	static bool isGUI;
};