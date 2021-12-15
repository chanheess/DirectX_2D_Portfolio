#pragma once
#include "./Systems/Gui.h"
#include "./GameObjects/GameObject.h"
class ProgressBar : public GameObject
{
public:
	ProgressBar(wstring name = L"ProgressBar");
	~ProgressBar();

	void Update();
	void Render();

	void SetGauge(float gauge);
private:
	class GameObject* back;  //�޸� �̹���
	class GameObject* front; //�ո� �̹���

	float nowGauge;
	float totalGauge;
};

