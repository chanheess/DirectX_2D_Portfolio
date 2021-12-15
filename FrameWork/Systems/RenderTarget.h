#pragma once
//ī�޶� �Կ��� ������ -> ȭ�� ��� 
//ī�޶� �Կ��� ������ -> �̹��� ���� 
//�̴ϸ� ���鶧 
class RenderTarget
{
public:
	RenderTarget(UINT wdith = 0, UINT height = 0);
	~RenderTarget();

	void Set(D3DXCOLOR clear = 0xFF000000);

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	void SaveRtvTexture(wstring saveFile);

	ID3D11RenderTargetView* GetRTV(){ return rtv; }
private:
	UINT wdith, height;
	ID3D11ShaderResourceView* srv; //���̴��� �����͸� �ѱ�
	ID3D11Texture2D* rtvTexture; //�̹��� ������ �������� 
	ID3D11RenderTargetView* rtv; //������ �Կ��� ����
};

