#pragma once
//GameObject -> ���� ��ġ�� ����
//Object-> ���� ��ġ�� ������ ����� �༮
//Component-> ��� 
enum class Tag
{
	Empty = 0,
	UserInterface,
};

class GameObject
{
public:
	GameObject(wstring name = L"GameObject");	//�̸��� �׳���������
	~GameObject();

	virtual void Ready();
	virtual void Update();
	virtual void Render();
	virtual void Insfactor();

	void Hierarchy();
	void AddComponent(class Component* comp);

	template<typename T>
	T* GetComponent()
	{
		if (components.count(typeid(T).name()) > 0)
			return dynamic_cast<T*>(components[typeid(T).name()]);

		return NULL;
	}
	class Transform* transform;
protected:
	wstring name;
	Tag tag;

	typedef pair<string, class Component*> Pair;
	map<string, class Component*> components;
	class Sprite* sprite;
	bool bActive;
private:
	class Gizmo* gizmo;
};
