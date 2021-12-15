#pragma once
#include "Scene.h"
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	virtual void Ready() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	Vector3 vec;
	Vector3 GoalInPos;
	Vector3 playerPos;
	Vector3 playerPos2;
	Vector3 playerObjxPos;
	Vector3 playerObjxPos2;
	Vector3 ballPos;
	Vector3 ballObjxPos;
	Vector3 enemyPos;

	Vector2 P1LeftUpColi;
	Vector2 P1LeftDownColi;
	Vector2 P1RightUpColi;
	Vector2 P1RightDownColi;
	Vector2 P2LeftUpColi;
	Vector2 P2LeftDownColi;
	Vector2 P2RightUpColi;
	Vector2 P2RightDownColi;

	int randomShoot[100];	//��Ȯ��
	int player1Point;	//����
	int player2Point;	//����
	bool p1Shoot;	//���� �����i��
	bool p2Shoot;
	float nowTime;		//���� �ð�
	float startTime;	//���� �ð�
	float playTime;		//������ �÷���Ÿ��
	float playCountTime;	//������ �����ð�
	float gameSet;	//�������
	bool gameSetting;	//�������
	float delayTime;	//���� �� �Ŀ� ��麯ȯ�ð�
	bool timeStopper;	//�ð� ���߱�
	bool onemore;	//�����ѹ���������
	bool goalanddnogoal;	//���°ų� �ñ�� on
	bool noReplay; //�ι��̻�����ȵǰ�
	
	class MapBackground* map;

	//Ŭ������ ��� �ɵ�
	class Goaldae2* frontGoaldae;
	class Goaldae* backGoaldae;

	class Ball* ball;
	class ObjectX* objX;

	//Ŭ������ ��� �ɵ�
	class Audio* endplay;
	class Audio* countdown;
	class Audio* rimout;
	class Audio* Block;
	class Audio* CvBlock;
	class Audio* Dunk;
	class Audio* GoalIn;
	class Audio* NoGoal;


	//Ŭ������ ��� �ɵ�
	class score* scoreboard;
	class score* start;
	class score* win[2];
	class score* scoreNum[11];
	class score* scoreNum2[11];
	class score* timeNum[11];
};

