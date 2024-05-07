class MapSelectButton : public Button
{
public:
	MapSelectButton(wstring textureFile, int key = 0);
	~MapSelectButton();

	void Update() override;
	void Render() override;

	int GetKey() { return key; }

	ImageFont* GetFont() { return font; }
	void SetFont(int num = 0);

private:
	ImageFont* font;
	int key;
};