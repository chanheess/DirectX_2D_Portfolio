#pragma once
class String
{
public:
	//str ���ڿ����� comp��� �Ǿ��ִ� ����(��)�� rep�� ����
	//str�̶�� ���ڿ����� comp�̶�� ����(��)�� rep���� �ٲ���
	static void Replace(IN OUT wstring* str, wstring comp, wstring rep);

	static string ToString(wstring str);
	static wstring ToWString(string str);

	//wstring�� �����ڵ�
	//string�� ��Ƽ����Ʈ
};

