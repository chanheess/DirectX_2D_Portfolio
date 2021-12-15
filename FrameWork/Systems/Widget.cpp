#include "stdafx.h"
#include "Widget.h"

//ImGui -> window â�� ���鶧 
//���� �̸��̸� 

Widget::Widget()
{
	title = "##";
	windowFlags = ImGuiWindowFlags_NoCollapse;
	bVisible = true;
}


Widget::~Widget()
{
}

void Widget::Begin()
{
	ImGui::Begin(title.c_str(), &bVisible, windowFlags);
}

void Widget::End()
{
	ImGui::End();
}
