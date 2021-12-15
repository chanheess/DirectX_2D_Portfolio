#pragma once
#include "./GameObjects/GameObject.h"
#include "./Systems/SingletonBase.h"

class Player : public GameObject , public SingletonBase<Player>, public CMemeoryPool<Player>
{
public:
	Player();
	~Player();

	void Update() override;
	void Render() override;
	void Dontmove(bool move) { dontmove = move; }
	bool Fake() { return fake; }	//����ũ���ΰ� ����
	int Nomove() { return noMove; }	//�����϶� Ÿ�Ӹ���Ʈ�϶��� ����ϰ�����
	void JumpControl(int frame); //����Ʈ����
	void JumpShoot(int pos);	//������
	void LayupDunk(int pos);	//���̾��� ��ũ��
	int BlockBallDirection() { return blockDirection; }	//����� ��ƨ��� ��ġ
	void Block();	//���
	bool Blocked() { return blocked; }	//��� ����
	bool BlockMotion() { return block; }	//������϶� ����
	bool Blocking() { return blocking; }	//��������� ����
	Vector3 BlockPos() { return blockPos; }	//�����ġ ����
	bool NoColi() { return noColi; }	//�浹���� ����
	int Dunkball() { return LayOrDunk; } //��ũ�� �� ���� ó���� ���ؼ� t/f �ѱ��
	void SlideLayDunk(); //���̾��� ���� ������ �̲��������� �� �������� �Ѿ
	void Breakthrough(); //����
	void Stopbreakth();	//���Ľ� �΋H���� ���߰�

	int LeRiPos() { return iLeRiPos; }//��ġ�� �����ΰ� �������ΰ� 1�� 2��

	Vector3 Shoot(); //����ġ�� �Ѱ��ֱ�
	void IsShoot(bool shoot) { shooting = shoot; }//���� �ϴ����ΰ�
	bool IsShooting() { return shooting; } //��ȯ��
	void IsHand(bool hand) { handBall = hand;}
	bool IsHanding() { return handBall; } //��ȯ��
	bool IsbreakthColing() { return breaker; } //��ȯ��
	void noChangeFalse(){ for (int i = 0; i < 5; i++) noChange[i] = false; }
	class GameObject* GetObj() { return reinterpret_cast<GameObject*>(objX); }

		
private:
	class ObjectX* objX;
	class p1color* p1;
	class Animator* anim;
	class Audio* jumpShootSound;
	class Audio* CvDunk;

	float speed;	//�ִϸ��̼Ǽӵ�
	float mSpeed;	//�����̴¼ӵ�
	float shootSpeed;	//����Ǽӵ�
	float hJump;	//��������
	float LayUpSpeed; //���̾� �ӵ�
	float breakthSpeed; //���� �ӵ�
	bool dontmove;	//���������ʰ�
	bool diago;	//�밢�� �Ǵ�
	bool handBall; //���ֳ� �Ǵ�
	bool shooting;	//��Ÿ�̹� �Ǵ�
	bool noStop; //���� ������ �ȸ��߰�
	bool objxFix;	//objxFix�� ����
	bool playmove;	//�� �����̴� �� �����̰�
	bool fixi;	//����ģ
	bool breaker;	//����
	bool block;	//���
	bool blocked;	//���Ÿ�̹�
	bool blocking;	//������ ���Ÿ�̹�
	bool noChange[5];	//������ �ٸ� ������� �ٲ�°� ����
	bool noColi;	//������ �и�����
	bool fake;	//����ũ�϶��� ���а�
	int blockDirection; //�����ġ	//1.�߾� 2.���� 3.��
	int LayOrDunk;	//1.���̾� 2.��ũ
	int noMove;	//������ �����ӹ���
	int noChangein;	//0.���ʻ��̵� 1.�������̵� 2.���ʴ밢 3.�����밢 4. �߾�
	int limitJump; //�������� ���� ���� ����ġ���� �۵�
	int posShoot; //������ġ	1.���̵� 2.�밢�� 3.�߾�
	int iLeRiPos; //���� ������
	int JumpOrLay; //���� �����Ҷ� �������ΰ� ���̾��ΰ� 1.jump 2.layup
	int breakth;	//���� ���ʻ��̵� 1.�� 2.�� �������̵� 3.�� 4.�� 
	int breakth2;	//������ġ������ �ӵ� ����


	Vector3 vec;
	Vector3 pos2;
	Vector3 pos2Save;  
	Vector3 objXPos;
	Vector3 scaleSave;
	Vector3 adjScale;
	Vector3 offset; 
	Vector3 breakpos;
	Vector3 FixPos;
	Vector3 blockPos;
};

