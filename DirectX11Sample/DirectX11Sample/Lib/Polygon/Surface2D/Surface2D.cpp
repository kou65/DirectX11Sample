#include"Surface2D.h"



void Surface2D::Create() {


	// 1番目
	{
		// 左
		// x
		m_cv1[0].pos[0] = 0.f;
		// y
		m_cv1[0].pos[1] = 0.f;
		// z
		m_cv1[0].pos[2] = 0.f;

		// 右下
		m_cv1[1].pos[0] = 1.f;
		m_cv1[1].pos[1] = 1.f;
		m_cv1[1].pos[2] = 0.f;

		// 左下
		m_cv1[2].pos[0] = 0.f;
		m_cv1[2].pos[1] = 1.f;
		m_cv1[2].pos[2] = 0.f;
	}

}