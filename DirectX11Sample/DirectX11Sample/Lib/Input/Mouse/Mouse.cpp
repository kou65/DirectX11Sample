#include"Mouse.h"



void Mouse::SetPos(
	const int& x,
	const int& y
) {

	SetCursorPos(x, y);
}


void Mouse::GetPos(
	float& x,
	float& y
) {

	POINT p;

	GetCursorPos(&p);

	x = static_cast<float>(p.x);
	y = static_cast<float>(p.y);
}


bool Mouse::IsShow(bool is_show) {

	// 0以上ならば表示0未満なら非表示を返す
	int result = ShowCursor(is_show);

	return true;
}