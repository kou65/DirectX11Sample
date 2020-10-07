#ifndef SURFACE_2D_H_
#define SURFACE_2D_H_

#include<d3d11.h>
#include"Surface2DCustomVertex.h"


/**
* @class Surface2D
* @brief ïΩñ É|ÉäÉSÉì
*/
class Surface2D {
public:

	/**
	* @brief çÏê¨
	*/
	void Create();

private:

	static const int LIST = 3;
	static const int DESC_SIZE = 2;

private:

	D3D11_INPUT_ELEMENT_DESC m_desc[DESC_SIZE];

	Sur2DCustomVertex m_cv1[LIST];
	Sur2DCustomVertex m_cv2[LIST];
};


#endif
