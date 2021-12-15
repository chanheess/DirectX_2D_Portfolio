#pragma once
class Window
{
public:
	Window();
	~Window();
	virtual void Initialize() = 0;  //�ʱ�ȭ
	virtual void Release() = 0;		//����
	virtual void Update() = 0;		//������Ʈ
	virtual void PreRender() = 0;
	virtual void Render() = 0;		//����

	void Create(HINSTANCE hIns); //window â ����
	WPARAM Run(); //����
protected:
	class RenderTarget* rtt;
};

