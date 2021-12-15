#pragma once
//1���� ����ڴ�.(�̱���)

struct D2DDesc
{
	wstring AppName; //Ÿ��Ʋ
	HWND Handle;	 //â��ȣ
	float Width;	 //â�ʺ�
	float Height;	 //â����
	bool bFullScreen;//��üȭ�� 
	bool bVsync;	 //��������ȭ
};
class D2D
{
public:
	static D2D* Get();
	static void Delete();

	void SetGpuInfo();
	//Device, DeviceContext, SwapChain 
	void CreateDeviceAndSwapChain();
	//BackBuffer
	void CreateBackBuffer();
	//viewport(âũ��)
	void CreateViewport();
	//�ĸ���� ������� 
	void Clear(
		D3DXCOLOR color = 0xFF808080,
		ID3D11RenderTargetView* rtv = NULL);
	//�ĸ� ���� ���� -> ������� 
	void Present();

	static void SetDesc(D2DDesc& val);
	static void GetDesc(D2DDesc* val);
	static ID3D11Device* GetDevice() { return device; };
	static ID3D11DeviceContext* GetDC() { return deviceContext; }
	IDXGISwapChain* GetSwapChain() { return swapChain; }

private:
	D2D();
	~D2D();

	static D2D* instance;
private:
	static D2DDesc desc;
	static ID3D11Device * device; //��ġ ������ �ʿ��� ����
	static ID3D11DeviceContext* deviceContext; //�������� �ʿ��� ���� 

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* RTV; //������� 

	UINT numerator;
	UINT denominator;

	UINT gpuMemorySize;
	wstring gpuDescription;

};

#define D2DCLASS() D2D::Get()
#define DEVICE() D2DCLASS()->GetDeivce()
#define DEVICECONTEXT() D2DCLASS()->GetDC()