#pragma once
class Path
{
public:
	static bool ExistFile(string path); //���� ���� ����
	static bool ExistFile(wstring path); //���� ���� ����
	static bool ExistDirectory(wstring path); //���� ���� ���� 

	static wstring GetDirectoryName(string path);

	static wstring GetExtension(wstring path);

	static wstring GetFileName(wstring path);

	static wstring GetFileNameWithoutExtension(wstring);

	static void CreateFolder(wstring path);
	static void CreateFolders(wstring path);

	//--------------------------------------------------------
	const static wstring ImageFilter;
	const static wstring XmlFilter;
	const static wstring ShaderFilter;
	const static wstring SoundFilter;

	static void OpenFileDialog(
		wstring file,
		const wstring filter,
		wstring folder,
		function<void(wstring)> func,
		HWND hwnd = NULL);
};


