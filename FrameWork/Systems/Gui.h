#pragma once
struct GuiText
{
	D3DXVECTOR2 Position;
	D3DXCOLOR color;
	string Content;

	GuiText() {}
};

class Gui
{
public:
	static void Create();
	static void Delete();
	static Gui* Get();

	static LRESULT MsgProc(HWND handle, UINT message,WPARAM wParam, LPARAM lParam);

	void Update();
	void Render();

	void AddWidget(class Widget* widget);

	void RenderText(GuiText& text);
	void RenderText(float x, float y, string context);
	void RenderText(float x, float y, float r, float g, float b, string context);
	void RenderText(D3DXVECTOR2 position, D3DXCOLOR color, string context);

private:
	Gui();
	~Gui();

	void ApplyStyle();
	void DockingPannel();

private:
	static Gui* instance;
	vector<class Widget*> widgets;

	vector<GuiText> texts;
};

