#pragma once
class Texture
{
private:
	friend class Textures;
public:
	Texture(wstring fileName);
	~Texture();

	void Render();
	void Insfactor();

	ID3D11ShaderResourceView* GetSRV() { return SRV; }
	wstring GetFile() { return file; }
private:
	wstring file;
	char str[64];

	ID3D11ShaderResourceView * SRV;
	static ID3D11SamplerState* WrapSampler;
};

class Textures
{
private:
	friend class Texture;

private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);
private:
	struct TextureDesc
	{
		//RefrenceCount;
		UINT RefCount = 0;
		ID3D11ShaderResourceView* SRV = NULL; //�̹���
	};
	static map<wstring, TextureDesc> TextureMap;
};

//Create -> ����
//new , Bengin , Create -> count +1
//delete ,end , Release -> count -1



