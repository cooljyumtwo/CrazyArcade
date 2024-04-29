class MapSelectButton : public Button
{
public:
	MapSelectButton(wstring textureFile, int key = 0);
	~MapSelectButton();

	void Update() override;
	void Render() override;

	ImageFont* GetFont() { return font; }
	int GetKey() { return key; }
	void SetFont(int num = 0);
private:
	ImageFont* font;
	int key;
};