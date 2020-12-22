#ifndef INPUT_DESC_INFO_H_
#define INPUT_DESC_INFO_H_



#include<d3d11.h>



/**
* @brief インプットレイアウト情報
*/
struct InputDescInfo {

	const D3D11_INPUT_ELEMENT_DESC *p_desc;
	int array_size;
};

#endif
