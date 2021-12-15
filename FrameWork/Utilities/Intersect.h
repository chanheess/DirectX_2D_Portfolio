#pragma once
class Intersect
{
public:
	//�簢�� - ��
	static bool IsConstantsPoint(D3DXMATRIX W, D3DXVECTOR3 vec);
	static bool IsConstantsPoint(struct BBox box, D3DXMATRIX W, D3DXVECTOR3 vec);
	static bool IsConstantsPoint(class GameObject* obj, D3DXVECTOR3 point);
	static bool IsConstantsPoint(vector<D3DXVECTOR3> verticse, D3DXVECTOR3 vec);

	
	//�� - ��
	static bool IsConstantsPointCircle(D3DXMATRIX world,
		D3DXVECTOR3 vec);
	//Axis-Aligned-Bound-Box
	//�簢�� -�簢�� (AABB)
	static bool IsConstantsRect(class BBox* temp, D3DXMATRIX comp1, D3DXMATRIX comp2);
	//�簢�� - ��
	static bool IsConstantsRectCircle(D3DXMATRIX box,
		D3DXMATRIX Sphere);
	//�� - �� 
	static bool IsConstantsSphere(
		D3DXMATRIX world1, D3DXMATRIX world2);
	//������Ʈ - ������Ʈ
	static bool IsConstantsObject(
		class GameObject* obj1, class GameObject* obj2
	);
};

