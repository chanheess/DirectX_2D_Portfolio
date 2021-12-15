#pragma once
#include "Scene.h"
class Scenes
{
public:
	static Scenes* Get();
	static void Delete();

	void Update();
	void Render();

	void AddScene(wstring key, Scene* scene);
	void ChangScene(wstring key);

	Scene* GetScene(wstring key);

private:
	~Scenes();
	Scenes();
private:
	static Scenes * instance;
private:
	Scene * nowScene; //�÷����� ���
	Scene * releaseScene; //������ ��

	map<wstring, Scene*> sceneMap;
};

