#pragma once
#include <bitset> //bit���� ������ Ÿ�� (0, 1)
//0000 0000 

class Input
{
public:
	static Input* Get();
	static void Delete();

	bool Key(int key);			//������ ������(��������)
	bool KeyDown(int key);		//ó�� ��������(1��)
	bool KeyUp(int key);		//ó�� ������(1��)
	bool Toggle(int key);		//���(cap lock, number lock...)

	void Update();

	void Position(D3DXVECTOR3* vec) { *vec = mouse; } //Get �Լ�;
	void Position(D3DXVECTOR3& vec) { mouse = vec; } //Set �Լ�;

	D3DXVECTOR3 ScreenPosition() { return sreenMouse; }
private:
	Input();
	~Input();

	static Input* instance;
private:
	bitset<256> up;
	bitset<256> down;

	D3DXVECTOR3 mouse;//â
	D3DXVECTOR3 sreenMouse; //ȭ�� ����

	float width, height;
};

