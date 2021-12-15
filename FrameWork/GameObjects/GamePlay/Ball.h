#pragma once
#include "./GameObjects/GameObject.h"

class Ball : public GameObject
{
public:
	Ball();
	~Ball();

	void Update() override;
	void Render() override;

	void Fire(D3DXVECTOR3 pos, D3DXVECTOR3 dir);
	void Stop();
	void BallShootPos(int ball) { ballShootpos = ball; }
	void PlayerXPos(Vector3 ball) { playerXPos = ball; }
	void outhand(int hand) { outofhand = hand;}
	void BallBlocked(int ball) { ballBlocked = ball;}
	void Dunk(int ball) { if (ball == 2) bDunk = true; else false; }
	void IsBlocking(bool block) { bBlock = block; }
	bool IsFire() { return bFire; }
	bool IsBlocked() { return bBlock; }	//��ȯ
	int outBall() { return gravityCount; }
	int outhanding() { return outofhand; }
	void noGoalgra(int i) { if (i == 1) noGoalgravity = 5.0f;  else if (i == 2) noGoalgravity = 1.0f; }
	class GameObject* GetObj() { return reinterpret_cast<GameObject*>(objx); }

private:
	class ObjectX* objx;
	bool bFire;
	bool bBlock;
	bool bDunk;
	bool ballControl; //ballShootpos�� �ݺ��� ��Ʈ��
	bool LayupControl; //Layup�� ��� true
	int outofhand;	//�չۿ� ���� ������� 0. ù���� 1. �� 2. ��뿡�� ƨ�� 3. ������ 4. ���� 5. ���̾�
	int noMove;
	int ballBlocked;	//������ǰ� Ƣ��°� 1.�� 2.�� 3.�޴밢 4.���밢 5.���
	int ballShootpos;	//���� ���⸦ ���ϱ� ���� ��
	float ballspin;	//��ȸ��
	float noGoalgravity;	//����ϰ� ������ �߷°�ȭ
	float ballAngle;
	float ballPowerX;	//���Ǽ���
	float ballPowerY;	//���Ǽ���
	float gravity;	//���� �߷�
	float gravityplus;	//���� �߷��߰�
	float gravityMin;	//���� �����߷�
	int gravityCount;	//���� ��� Ƣ��� ���̻� Ƣ���� �ʰ�

	Vector3 direction;
	Vector3 playerXPos;
	Vector2 xy;
	Vector3 orgin; //��������
	Vector3 pos;	//����ġ
	Vector3 goalPos; //��� ��ġ
	Vector3 ballPos; //���Ƣ��� ������ġ
	Vector3 shootPos;
	Vector3 temp; //�÷��̾�� ����� �Ÿ�
	Vector3 objxSave;	//������Ʈ ��ġ���̺�
};