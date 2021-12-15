#pragma once
#include "Components/Component.h"
//���� 
class Particle : public Component
{
public:
	Particle(
		float		spawnTime,
		UINT		totalNum,
		float		minSpeed,
		float		maxSpeed,
		float		minAccel,
		float		maxAccel,
		float		minLiveTime,
		float		maxLiveTime,
		Vector2		minPos,
		Vector2		maxPos,
		Vector2		minDir,
		Vector2		maxDir,
		vector<D3DXCOLOR> color
	);
	~Particle();

	void Update();
	void Render();

private:
	void EmitParticle(); //���� 1���� �����ϰڴ�.
	void UpdateParticle(); //���ڵ��� �̵��ϰڴ�.
	void KillParticle();	//ȭ�鿡 ��½�Ű�� �ʰڴ�.
private:

	UINT totalNum; //�����ڼ� 
	UINT currentNum;

	Vector2 minPos;
	Vector2 maxPos;

	Vector2 minDir;
	Vector2 maxDir;

	float minSpeed;
	float maxSpeed;

	float minAccel;
	float maxAccel;

	float minLiveTime;
	float maxLiveTime;

	vector<D3DXCOLOR> color;

	/*D3DXCOLOR minColor;
	D3DXCOLOR maxColor;*/

	float spawnTime;
	float spawn;
private:
	struct Instancing
	{
		Vector2 Coord;
		D3DXCOLOR Color;

		bool bAlive;
		Vector2 LiveTime;
		Vector2 Direction;
		Vector2 SpeedAndAccel;
	}* instance;
private:
	VertexTexture * vertices;
	UINT* indices;
	
	class Shader* shader;
	class VBuffer* vBuffer;
	class VBuffer* instacing;
	class IBuffer* iBuffer;
	class Texture* texture;
};

