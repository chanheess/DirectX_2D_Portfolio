#include "stdafx.h"
#include "PlayScene.h"
#include "./Components/Objects/Transform.h"
#include "./Components/Animation/Sprite.h"
#include "./GameObjects/CameraObj.h"
#include "./GameObjects/Map/MapBackground.h"
#include "./GameObjects/Map/Goaldae.h"
#include "./GameObjects/Map/Goaldae2.h"
#include "./GameObjects/GamePlay/Ball.h"
#include "./GameObjects/GamePlay/score.h"
#include "./GameObjects/GamePlay/ObjectX.h"
#include "./Components./Etc/Audio.h"


PlayScene::PlayScene()
{
	map = new MapBackground;
	ball = new Ball;
	backGoaldae = new Goaldae;
	frontGoaldae = new Goaldae2;

	scoreboard = new score;
	scoreboard->transform->Position(638, 765);
	scoreboard->transform->Scale(Vector3(477, 71, 0));
	scoreboard->AddComponent(new Sprite(L"score.png", 0, 0, 477, 71));
	start = new score;
	start->transform->Position(638, 450);
	start->transform->Scale(Vector3(169, 45, 0));
	start->AddComponent(new Sprite(L"score.png", 307, 78, 476, 123));
	win[0] = new score;
	win[0]->transform->Position(638, 450);
	win[0]->transform->Scale(Vector3(220, 60, 0));
	win[0]->AddComponent(new Sprite(L"score.png", 0, 190, 220, 250));
	win[1] = new score;
	win[1]->transform->Position(638, 450);
	win[1]->transform->Scale(Vector3(236, 60, 0));
	win[1]->AddComponent(new Sprite(L"score.png", 0, 257, 236, 318));

	//���ӽ��ھ� �� Ÿ��
	{
		int x = 0;
		int w = x + 30;
		int x2 = 0;
		int w2 = x2 + 56;
		for (int i = 0; i < 10; i++)
		{
			scoreNum[i] = new score;
			scoreNum[i]->transform->Position(500, 750);
			scoreNum[i]->transform->Scale(Vector3(30, 33, 0));
			scoreNum[i]->AddComponent(new Sprite(L"score.png", x, 79, w, 112));
			scoreNum2[i] = new score;
			scoreNum2[i]->transform->Position(805, 750);
			scoreNum2[i]->transform->Scale(Vector3(30, 33, 0));
			scoreNum2[i]->AddComponent(new Sprite(L"score.png", x, 79, w, 112));
			timeNum[i] = new score;
			timeNum[i]->transform->Position(648, 765);
			timeNum[i]->transform->Scale(Vector3(56 * 0.7f, 59 * 0.7f, 0));
			timeNum[i]->AddComponent(new Sprite(L"score.png", x2, 125, w2, 186));

			//���� ���ھ�� �ð� png ��ġ����
			x += 30;
			w += 30;
			x2 += 56;
			w2 += 56;
		}
		scoreNum[10] = new score;
		scoreNum[10]->transform->Position(470, 750);
		scoreNum[10]->transform->Scale(Vector3(30, 33, 0));
		scoreNum[10]->AddComponent(new Sprite(L"score.png", 30, 79, 60, 112));
		scoreNum2[10] = new score;
		scoreNum2[10]->transform->Position(775, 750);
		scoreNum2[10]->transform->Scale(Vector3(30, 33, 0));
		scoreNum2[10]->AddComponent(new Sprite(L"score.png", 30, 79, 60, 112));
		timeNum[10] = new score;
		timeNum[10]->transform->Position(613, 765);
		timeNum[10]->transform->Scale(Vector3(56 * 0.7f, 59 * 0.7f, 0));
		timeNum[10]->AddComponent(new Sprite(L"score.png", 56, 125, 112, 186));
	}
	//sound
	endplay = new Audio();
	endplay->Set(L"endplay.wav", true, false);
	countdown = new Audio();
	countdown->Set(L"countdown.wav", true, false);
	rimout = new Audio();
	rimout->Set(L"rimout.wav", true, false);
	Block = new Audio();
	Block->Set(L"Block.wav", true, false);
	CvBlock = new Audio();
	CvBlock->Set(L"CvBlock.wav", true, false);
	Dunk = new Audio();
	Dunk->Set(L"Dunk.wav", true, false);
	GoalIn = new Audio();
	GoalIn->Set(L"Goalin.wav", true, false);
	NoGoal = new Audio();
	NoGoal->Set(L"NoGoal.wav", true, false);
	//
	objX = new ObjectX;
	objX->transform->Position(638, 645);
	GoalInPos = objX->transform->Position();
	PLAYER;
	PLAYER2;
	TIMEMANAGER->SetFrame(FIXFRAME);

	startTime = 0;
	delayTime = 0;
	playTime = 0;
	playCountTime = 0;
	timeStopper = false;
	player1Point = 0;
	player2Point = 0;
	p1Shoot = false;
	p2Shoot = false;
	onemore = false;
	goalanddnogoal = false;
	gameSet = 0;
	gameSetting = false;
	noReplay = false;
}


PlayScene::~PlayScene()
{
}

void PlayScene::Ready()
{
}

void PlayScene::Update()
{
	if(player1Point >= 15)
		win[0]->Update();
	else if (player2Point >= 15)
		win[1]->Update();
	else
	{
		PLAYER->Update();
		PLAYER2->Update();
		start->Update();
		nowTime = TIMEMANAGER->GetWorldTime();
		for (int i = 0; i < 11; i++)
		{
			scoreNum[i]->Update();
			scoreNum2[i]->Update();
			timeNum[i]->Update();
		}
	}

	scoreboard->Update();
	map->Update();
	frontGoaldae->Update();
	backGoaldae->Update();
	ball->Update();

	//�÷��̾�� ���� ��ġ�� x�ప ����
	playerPos = PLAYER->transform->Position();
	playerPos2 = PLAYER2->transform->Position();
	playerObjxPos = PLAYER->GetObj()->transform->Position();
	playerObjxPos2 = PLAYER2->GetObj()->transform->Position();
	ballPos = ball->transform->Position();
	ballObjxPos = ball->GetObj()->transform->Position();

	//���� ��ҳ�
	if (PLAYER->IsHanding() == true)
		ball->PlayerXPos(playerObjxPos);
	else if (PLAYER2->IsHanding() == true)
		ball->PlayerXPos(playerObjxPos2);

	//���� ���� ������ Ÿ��
	if (((delayTime + 5) <= nowTime) && delayTime != 0)
	{
		if (p1Shoot == true && PLAYER->Nomove() == 0)
		{
			if (PLAYER2->BlockMotion() == false)
			{
				ball->outhand(3);
				PLAYER2->Dontmove(true);
				PLAYER2->IsHand(true);
				p1Shoot = false;
				delayTime = 0;
			}
			PLAYER->Dontmove(true);
		}
		if (p2Shoot == true && PLAYER2->Nomove() == 0)
		{
			if (PLAYER->BlockMotion() == false)
			{
				ball->outhand(3);
				PLAYER->Dontmove(true);
				PLAYER->IsHand(true);
				p2Shoot = false;
				delayTime = 0;
			}
			PLAYER2->Dontmove(true);
		}
		startTime = nowTime;
	}

	//�������� ���ݰ� ���ӽ���
	if (((startTime + 3) <= nowTime) && (PLAYER->IsHanding() == true)
		&& (PLAYER2->IsHanding() == false) && startTime != 0)
	{
		playerPos.x = 638;
		playerPos.y = 110;
		PLAYER->transform->Position(playerPos);
		playerPos2.x = 638;
		playerPos2.y = 255;
		PLAYER2->transform->Position(playerPos2);
		timeStopper = true;
		if ((startTime + 6) <= nowTime)
		{
			PLAYER->Dontmove(false);
			PLAYER2->Dontmove(false);
			ball->IsBlocking(false);
			startTime = 0;
			playTime = 0;
			timeStopper = false;
			playTime = nowTime + 18.3;
			onemore = false;
			noReplay = false;
		}
	}
	else if (((startTime + 3) <= nowTime) && (PLAYER2->IsHanding() == true)
		&& (PLAYER->IsHanding() == false) && startTime != 0)
	{
		playerPos2.x = 638;
		playerPos2.y = 110;
		PLAYER2->transform->Position(playerPos2);
		playerPos.x = 638;
		playerPos.y = 255;
		PLAYER->transform->Position(playerPos);
		timeStopper = true;
		if ((startTime + 6) <= nowTime)
		{
			PLAYER->Dontmove(false);
			PLAYER2->Dontmove(false);
			ball->IsBlocking(false);
			startTime = 0;
			playTime = 0;
			timeStopper = false;
			playTime = nowTime + 18.3;
			onemore = false;
			noReplay = false;
		}
	}
	//�÷��̽ð�
	if (playTime != 0)
	{
		if (ball->IsBlocked() == true || goalanddnogoal == true)
		{
			if (playCountTime != 0 && gameSetting == false)
			{
				gameSet = nowTime;
				gameSetting = true;
			}
			if ((gameSet + 3) <= nowTime && gameSetting == true)
			{
				playCountTime = 0;
				gameSet = 0;
				gameSetting = false;
				goalanddnogoal = false;
			}
		}
		else if (ball->IsBlocked() == false && goalanddnogoal == false)
			playCountTime = playTime - nowTime;

		if(playCountTime >= 2.998f && playCountTime <= 3.002f)
			countdown->Play();
		else if (playCountTime >= 1.998f && playCountTime <= 2.002f)
			countdown->Play();
		else if (playCountTime >= 0.998f && playCountTime <= 1.002f)
			countdown->Play();
		if (playCountTime <= 0)
		{
			if (PLAYER->IsHanding() == true && PLAYER->Nomove() == 0)
			{
				p1Shoot = true;
				PLAYER->Stopbreakth();
				PLAYER->IsHand(false);
			}
			if (PLAYER2->IsHanding() == true && PLAYER->Nomove() == 0)
			{
				p2Shoot = true;
				PLAYER2->Stopbreakth();
				PLAYER2->IsHand(false);
			}
			delayTime = nowTime;
			playTime = 0;
			playCountTime = 0;
			endplay->Play();
		}
	}
	//�ʹۿ� ��������
	if (ball->outhanding() != 0)
	{
		{	//p1
			if (playerObjxPos.y >= 480.0f)
			{
				playerPos.y -= 1.0f;
				PLAYER->transform->Position(playerPos);
			}
			if (playerObjxPos.y <= 25.0f)
			{
				playerPos.y += 1.0f;
				PLAYER->transform->Position(playerPos);
			}
			if (playerObjxPos.x <= 55.0f)
			{
				playerPos.x = 55.0f;
				PLAYER->transform->Position(playerPos);
			}
			if (playerObjxPos.x >= 1220.0f)
			{
				playerPos.x = 1220.0f;
				PLAYER->transform->Position(playerPos);
			}
		}
		{	//p2
			if (playerObjxPos2.y >= 480.0f)
			{
				playerPos2.y -= 1.0f;
				PLAYER->transform->Position(playerPos2);
			}
			if (playerObjxPos2.y <= 25.0f)
			{
				playerPos2.y += 1.0f;
				PLAYER->transform->Position(playerPos2);
			}
			if (playerObjxPos2.x <= 55.0f)
			{
				playerPos2.x = 55.0f;
				PLAYER->transform->Position(playerPos2);
			}
			if (playerObjxPos2.x >= 1220.0f)
			{
				playerPos2.x = 1220.0f;
				PLAYER->transform->Position(playerPos2);
			}
		}
	}
	//�浹�˻�
	{
		P1LeftUpColi = Vector2(playerObjxPos.x - 30.0f, playerObjxPos.y + 12.0f);
		P1LeftDownColi = Vector2(playerObjxPos.x - 30.0f, playerObjxPos.y - 12.0f);
		P1RightUpColi = Vector2(playerObjxPos.x + 30.0f, playerObjxPos.y + 12.0f);
		P1RightDownColi = Vector2(playerObjxPos.x + 30.0f, playerObjxPos.y - 12.0f);
		P2LeftUpColi = Vector2(playerObjxPos2.x - 30.0f, playerObjxPos2.y + 12.0f);
		P2LeftDownColi = Vector2(playerObjxPos2.x - 30.0f, playerObjxPos2.y - 12.0f);
		P2RightUpColi = Vector2(playerObjxPos2.x + 30.0f, playerObjxPos2.y + 12.0f);
		P2RightDownColi = Vector2(playerObjxPos2.x + 30.0f, playerObjxPos2.y - 12.0f);
		Vector3 movePos1 = playerPos;
		Vector3 movePos2 = playerPos2;
		if((PLAYER->NoColi() == false && PLAYER2->NoColi() == false) == true)
		{
			if (P1LeftUpColi.x <= P2LeftDownColi.x && P1RightUpColi.x >= P2LeftDownColi.x)
			{	//���ʾƷ��밢���� ���ʿ� �΋H����
				if (P1LeftUpColi.y >= P2LeftDownColi.y && (P1LeftUpColi.y - 12.0f) <= P2LeftDownColi.y)
				{
					movePos1.y -= 1.0f;
					movePos2.y += 1.0f;
					if (PLAYER->IsbreakthColing() == true)
						PLAYER->Stopbreakth();
					if (PLAYER2->IsbreakthColing() == true)
						PLAYER2->Stopbreakth();
				}
			}
			if ((P1RightUpColi.x - 20.0f) <= P2LeftDownColi.x && P1RightUpColi.x >= P2LeftDownColi.x)
			{	//���ʾƷ��밢���� �����ʿ� �΋H����
				if (P1RightUpColi.y >= P2LeftDownColi.y && P1RightDownColi.y <= P2LeftDownColi.y)
				{
					movePos1.x -= 2.0f;
					movePos2.x += 2.0f;
					if (PLAYER->IsbreakthColing() == true)
						PLAYER->Stopbreakth();
					if (PLAYER2->IsbreakthColing() == true)
						PLAYER2->Stopbreakth();
				}
			}
			if ((P1RightUpColi.x - 20.0f) <= P2LeftUpColi.x && P1RightUpColi.x >= P2LeftUpColi.x)
			{	//�������밢���� �����ʿ� �΋H����
				if (P1RightUpColi.y >= P2LeftUpColi.y && P1RightDownColi.y <= P2LeftUpColi.y)
				{
					movePos1.x -= 2.0f;
					movePos2.x += 2.0f;
					if (PLAYER->IsbreakthColing() == true)
						PLAYER->Stopbreakth();
					if (PLAYER2->IsbreakthColing() == true)
						PLAYER2->Stopbreakth();
				}
			}
			if (P1LeftDownColi.x <= P2LeftUpColi.x && P1RightDownColi.x >= P2LeftUpColi.x)
			{	//�������밢���� �Ʒ��ʿ� �΋H����
				if (P1LeftDownColi.y <= P2LeftUpColi.y && (P1LeftDownColi.y + 12.0f) >= P2LeftUpColi.y)
				{
					movePos1.y += 1.0f;
					movePos2.y -= 1.0f;
					if (PLAYER->IsbreakthColing() == true)
						PLAYER->Stopbreakth();
					if (PLAYER2->IsbreakthColing() == true)
						PLAYER2->Stopbreakth();
				}
			}
			if (P1LeftDownColi.x <= P2RightUpColi.x && P1RightDownColi.x >= P2RightUpColi.x)
			{	//���������밢���� �Ʒ��ʿ� �΋H����
				if (P1LeftDownColi.y <= P2RightUpColi.y && (P1LeftDownColi.y + 12.0f) >= P2RightUpColi.y)
				{
					movePos1.y += 1.0f;
					movePos2.y -= 1.0f;
					if (PLAYER->IsbreakthColing() == true)
						PLAYER->Stopbreakth();
					if (PLAYER2->IsbreakthColing() == true)
						PLAYER2->Stopbreakth();
				}
			}
			if ((P1LeftDownColi.x + 20.0f) >= P2RightUpColi.x && P1LeftDownColi.x <= P2RightUpColi.x)
			{	//���������밢���� ���ʿ� �΋H����
				if (P1LeftDownColi.y <= P2RightUpColi.y && P1LeftUpColi.y >= P2RightUpColi.y)
				{
					movePos1.x += 2.0f;
					movePos2.x -= 2.0f;
					if (PLAYER->IsbreakthColing() == true)
						PLAYER->Stopbreakth();
					if (PLAYER2->IsbreakthColing() == true)
						PLAYER2->Stopbreakth();
				}
			}
			if ((P1LeftDownColi.x + 20.0f) >= P2RightDownColi.x && P1LeftDownColi.x <= P2RightDownColi.x)
			{	//�����ʾƷ��밢���� ���ʿ� �΋H����
				if (P1LeftDownColi.y <= P2RightDownColi.y && P1LeftUpColi.y >= P2RightDownColi.y)
				{
					movePos1.x += 2.0f;
					movePos2.x -= 2.0f;
					if (PLAYER->IsbreakthColing() == true)
						PLAYER->Stopbreakth();
					if (PLAYER2->IsbreakthColing() == true)
						PLAYER2->Stopbreakth();
				}
			}
			if (P1LeftUpColi.x <= P2RightDownColi.x && P1RightUpColi.x >= P2RightDownColi.x)
			{	//�����ʾƷ��밢���� ���ʿ� �΋H����
				if (P1LeftUpColi.y >= P2RightDownColi.y && (P1LeftUpColi.y - 12.0f) <= P2RightDownColi.y)
				{
					movePos1.y -= 1.0f;
					movePos2.y += 1.0f;
					if (PLAYER->IsbreakthColing() == true)
						PLAYER->Stopbreakth();
					if (PLAYER2->IsbreakthColing() == true)
						PLAYER2->Stopbreakth();
				}
			}
		}
		if(PLAYER->Fake() == false)
			PLAYER->transform->Position(movePos1);
		if (PLAYER2->Fake() == false)
			PLAYER2->transform->Position(movePos2);
	}


	//���� ������ ����====================================
	if(ball->outhanding() == 1)
	{
		//�÷��̾�1�� �������ϰ��
		if (PLAYER->IsHanding() == true)
		{
			//���ʴ밢��
			if ((playerObjxPos.y < 400) && (playerObjxPos.x < 450))
			{
				ball->BallShootPos(2);
			}
			//�����ʴ밢��
			if ((playerObjxPos.y < 400) && (playerObjxPos.x > 826))
			{
				ball->BallShootPos(2);
			}
			//���ʻ��̵�
			if ((playerObjxPos.y >= 400) && (playerObjxPos.x < 450))
			{
				ball->BallShootPos(1);
			}
			//�����ʻ��̵�
			if ((playerObjxPos.y >= 400) && (playerObjxPos.x > 826))
			{
				ball->BallShootPos(1);
			}
			//���
			if ((playerObjxPos.y < 325) && (playerObjxPos.x <= 826) && (playerObjxPos.x >= 450))
			{
				ball->BallShootPos(3);
			}
		}
		//�÷��̾�2�� �������ϰ��
		else if (PLAYER2->IsHanding() == true)
		{
			//���ʴ밢��
			if ((playerObjxPos2.y < 400) && (playerObjxPos2.x < 450))
			{
				ball->BallShootPos(2);
			}
			//�����ʴ밢��
			if ((playerObjxPos2.y < 400) && (playerObjxPos2.x > 826))
			{
				ball->BallShootPos(2);
			}
			//���ʻ��̵�
			if ((playerObjxPos2.y >= 400) && (playerObjxPos2.x < 450))
			{
				ball->BallShootPos(1);
			}
			//�����ʻ��̵�
			if ((playerObjxPos2.y >= 400) && (playerObjxPos2.x > 826))
			{
				ball->BallShootPos(1);
			}
			//���
			if ((playerObjxPos2.y < 325) && (playerObjxPos2.x <= 826) && (playerObjxPos2.x >= 450))
			{
				ball->BallShootPos(3);
			}
		}
	}
	//��===================================================
	if (PLAYER->IsShooting())
	{
		if ((playerObjxPos.y >= 245) && (playerObjxPos.x >= 450) && (playerObjxPos.x <= 826))
			ball->outhand(5);
		else
			ball->outhand(1);
		ball->Fire(PLAYER->Shoot(), Vector3(1, 0, 0));
		ball->Dunk(PLAYER->Dunkball());
		ball->Update();
		p1Shoot = true;
		PLAYER->IsShoot(false);
	}
	else if (PLAYER2->IsShooting())
	{
		if ((playerObjxPos2.y >= 245) && (playerObjxPos2.x >= 450) && (playerObjxPos2.x <= 826))
			ball->outhand(5);
		else
			ball->outhand(1);
		ball->Fire(PLAYER2->Shoot(), Vector3(1, 0, 0));
		ball->Dunk(PLAYER2->Dunkball());
		ball->Update();
		p2Shoot = true;
		PLAYER2->IsShoot(false);
	}
	//��� ����ġ�� ���� �߷�=================================
	if ((ballPos.x - 10 < GoalInPos.x + 15) &&	//����
		(ballPos.x + 10 > GoalInPos.x - 15) &&	//������
		(ballPos.y > GoalInPos.y - 15) &&	//�Ʒ���
		(ballPos.y < GoalInPos.y + 500) &&	//����
		ball->outhanding() == 1)
	{
		ball->noGoalgra(1);	//1. ��� ����ħ 2.��� ����
	}
	//��� �¾�����===========================================
	if ((ballPos.x - 10 < GoalInPos.x + 15) &&	//����
		(ballPos.x + 10 > GoalInPos.x - 15) &&	//������
		(ballPos.y + 10 > GoalInPos.y - 15) &&	//�Ʒ���
		(ballPos.y - 10 < GoalInPos.y + 15) &&	//����
		(ball->outhanding() == 1 || ball->outhanding() == 5))
	{
		ball->noGoalgra(2); //1. ��� ����ħ 2.��� ����
		//================��Ȯ��===================
		for (int i = 0; i < 100; i++)
		{
			//0 ��
			if (i < 70)
				randomShoot[i] = 0;
			//1 �ȵ�
			else
				randomShoot[i] = 1;
		}
		srand((UINT)time(NULL));
		int ranball = rand() % 100;
		if (randomShoot[ranball] == 0)
		{
			if (noReplay == false)
			{
				if (ballPos.x >= 628.0f && ballPos.x <= 648.0f)
					GoalIn->Play();
				noReplay = true;
			}
			goalanddnogoal = true;
			ball->outhand(4);
			if (p1Shoot == true && onemore == false)
			{
				player1Point += 2;
				delayTime = nowTime;
				if (PLAYER->Dunkball() == 2)
					Dunk->Play();
				onemore = true;
			}
			else if (p2Shoot == true && onemore == false)
			{
				player2Point += 2;
				delayTime = nowTime;
				if (PLAYER2->Dunkball() == 2)
					Dunk->Play();
				onemore = true;
			}
		}
		else if (randomShoot[ranball] == 1)
		{
			if (noReplay == false)
			{
				NoGoal->Play();
				noReplay = true;
			}
			goalanddnogoal = true;
			rimout->Play();
			ball->outhand(2);
			delayTime = nowTime;
		}
		//================��Ȯ��===================//��
	}
	//���̾ƴҶ�===============================================
	if ((ballObjxPos.x - 15 < playerObjxPos.x + 15) &&	//����
		(ballObjxPos.x + 15 > playerObjxPos.x - 15) &&	//������
		(ballObjxPos.y + 15 > playerObjxPos.y - 15) &&	//�Ʒ���
		(ballObjxPos.y - 15 < playerObjxPos.y + 15) &&	//����
		ball->outhanding() == 0)
	{
		if ((D3DXVec3Length(&(ballObjxPos - ballPos)) < 50.0f))
		{
			PLAYER->IsHand(true);
			ball->outhand(3);
			startTime = nowTime;
			PLAYER->Dontmove(true);
			PLAYER2->Dontmove(true);
		}
	}
	else if ((ballObjxPos.x - 15 < playerObjxPos2.x + 15) &&	//����
		(ballObjxPos.x + 15 > playerObjxPos2.x - 15) &&	//������
		(ballObjxPos.y + 15 > playerObjxPos2.y - 15) &&	//�Ʒ���
		(ballObjxPos.y - 15 < playerObjxPos2.y + 15) &&	//����
		ball->outhanding() == 0)
	{
		if ((D3DXVec3Length(&(ballObjxPos - ballPos)) < 50.0f))
		{
			PLAYER2->IsHand(true);
			ball->outhand(3);
			startTime = nowTime;
			PLAYER->Dontmove(true);
			PLAYER2->Dontmove(true);
		}
	}
	//���
	if (PLAYER->IsHanding() == true && PLAYER->Blocking() == true
		&& PLAYER2->Blocked() == true)
	{
		if ((playerObjxPos.x - 50 < playerObjxPos2.x + 30) &&	//����
			(playerObjxPos.x + 50 > playerObjxPos2.x - 30) &&	//������
			(playerObjxPos.y + 30 > playerObjxPos2.y - 12) &&	//�Ʒ���
			(playerObjxPos.y - 30 < playerObjxPos2.y + 12))	//����
		{
			if (noReplay == false)
			{
				Block->Play();
				CvBlock->Play();
				noReplay = true;
			}
			switch (PLAYER2->BlockBallDirection())
			{
			case 1:
				ball->BallBlocked(5); //�߾�
				break;
			case 2:
				ball->BallBlocked(4); //�����ʴ밢���
				break;
			case 3:
				ball->BallBlocked(3); //���ʴ밢���
				break;
			case 4:
				ball->BallBlocked(2); //�����ʺ��
				break;
			case 5:
				ball->BallBlocked(1); //���ʺ��
				break;
			}
			if (p1Shoot == true)
				delayTime = nowTime;
			ball->IsBlocking(true);
		}
	}
	if (PLAYER2->IsHanding() == true && PLAYER2->Blocking() == true
		&& PLAYER->Blocked() == true)
	{
		if ((playerObjxPos2.x - 50 < playerObjxPos.x + 30) &&	//����
			(playerObjxPos2.x + 50 > playerObjxPos.x - 30) &&	//������
			(playerObjxPos2.y + 30 > playerObjxPos.y - 12) &&	//�Ʒ���
			(playerObjxPos2.y - 30 < playerObjxPos.y + 12))	//����
		{
			if (noReplay == false)
			{
				Block->Play();
				CvBlock->Play();
				noReplay = true;
			}
			switch (PLAYER->BlockBallDirection())
			{
			case 1:
				ball->BallBlocked(5); //�߾�
				break;
			case 2:
				ball->BallBlocked(4); //�����ʴ밢���
				break;
			case 3:
				ball->BallBlocked(3); //���ʴ밢���
				break;
			case 4:
				ball->BallBlocked(2); //�����ʺ��
				break;
			case 5:
				ball->BallBlocked(1); //���ʺ��
				break;
			}
			if (p2Shoot == true)
				delayTime = nowTime;
			ball->IsBlocking(true);
		}
	}
	if (ball->IsBlocked() == true && ball->outBall() != 33)
	{
		ball->outhand(6);
	}
}

void PlayScene::Render()
{
	Vector3 vec = Input::Get()->ScreenPosition();
	map->Render();
	scoreboard->Render();

	//����
	{
		if (player1Point < 10)
		{
			scoreNum[player1Point]->Render();
		}
		else
		{
			scoreNum[10]->Render();
			scoreNum[player1Point - 10]->Render();
		}
		if (player2Point < 10)
		{
			scoreNum2[player2Point]->Render();
		}
		else
		{
			scoreNum2[10]->Render();
			scoreNum2[player2Point - 10]->Render();
		}
	}
	
	//�ð�
	if ((int)playCountTime < 10)
	{
		timeNum[(int)playCountTime]->Render();
	}
	else
	{
		timeNum[10]->Render();
		timeNum[(int)playCountTime - 10]->Render();
	}
	
	// 0:������ ���� �ٸ�player���� �� /1: ������ ���� �ٸ�player���� �Ʒ�
	// 2:������ �Ʒ��� �ٸ� player���� �� / 3:������ �Ʒ��� �ٸ� player���� �Ʒ�
	int player1 = 0;	
	int player2 = 0;
	{	//��ġ ���
		if (ballObjxPos.y <= playerObjxPos.y)	//���� �Ʒ�
		{
			if (playerObjxPos2.y >= playerObjxPos.y)
				player1 = 1;
			else if (playerObjxPos2.y < playerObjxPos.y)
				player1 = 0;
		}
		if (ballObjxPos.y <= playerObjxPos2.y)	//���� �Ʒ�
		{
			if (playerObjxPos.y >= playerObjxPos2.y)
				player2 = 1;
			else if (playerObjxPos.y < playerObjxPos2.y)
				player2 = 0;
		}
		if (ballObjxPos.y > playerObjxPos.y)	//���� ��
		{
			if (playerObjxPos2.y >= playerObjxPos.y)
				player1 = 3;
			else if (playerObjxPos2.y < playerObjxPos.y)
				player1 = 2;
		}
		if (ballObjxPos.y > playerObjxPos2.y)	//���� ��
		{
			if (playerObjxPos.y >= playerObjxPos2.y)
				player2 = 3;
			else if (playerObjxPos.y < playerObjxPos2.y)
				player2 = 2;
		}
	}
	//�÷��̾��
	{
		if (player1 == 1 && player2 == 0)
		{
			PLAYER2->Render();
			PLAYER->Render();
		}
		else if (player1 == 0 && player2 == 1)
		{
			PLAYER->Render();
			PLAYER2->Render();
		}
		else if (player1 == 0 && player2 == 3)
		{
			PLAYER->Render();
		}
		else if (player1 == 3 && player2 == 0)
		{
			PLAYER2->Render();
		}
	}
	//���� ����
	if (ball->outhanding() == 4)
	{
		backGoaldae->Render();
		ball->Render();
		frontGoaldae->Render();
	}
	else
	{
		backGoaldae->Render();
		frontGoaldae->Render();
		ball->Render();
	}
	//�÷��̾� ����
	{
		if (player1 == 3 && player2 == 2)
		{
			PLAYER2->Render();
			PLAYER->Render();
		}
		else if (player1 == 2 && player2 == 3)
		{
			PLAYER->Render();
			PLAYER2->Render();
		}
		else if (player1 == 0 && player2 == 3)
		{
			PLAYER2->Render();
		}
		else if (player1 == 3 && player2 == 0)
		{
			PLAYER->Render();
		}
	}
	if (player1Point >= 15)
		win[0]->Render();
	if (player2Point >= 15)
		win[1]->Render();
	
	/*Gui::Get()->RenderText(200, 400, 1, 0, 0, "Test");
	ImGui::Begin("Debug");
	{
		ImGui::Text("screenX : %.2f, screenY : %.2f", vec.x, vec.y);
		ImGui::Text("nowTime : %.2f", nowTime);
		ImGui::Text("startTime : %.2f", startTime);
		ImGui::Text("delayTime : %.2f", delayTime);
		ImGui::Text("playTime : %.2f", playTime);
		ImGui::Text("playCountTime : %.2f", playCountTime);
		ImGui::Text("playerX : %.2f, playerY : %.2f",
			playerPos.x, playerPos.y);
		ImGui::Text("playerxX : %.2f, playerxY : %.2f",
			playerObjxPos.x, playerObjxPos.y);
		ImGui::Text("player2X : %.2f, player2Y : %.2f",
			playerPos2.x, playerPos2.y);
		ImGui::Text("player2xX : %.2f, player2xY : %.2f",
			playerObjxPos2.x, playerObjxPos2.y);
	}
	ImGui::End();*/
}
