//*****************************************************************************************//
//**                                                                                     **//
//**                             CreateGeometry                                          **//
//**                                                                                     **//
//*****************************************************************************************//

#ifndef Class_CreateGeometry_Header
#define Class_CreateGeometry_Header

#include "../CoordTf/CoordTf.h"

namespace CreateGeometry {

	struct ver {
		CoordTf::VECTOR3 Pos;    //位置
		CoordTf::VECTOR3 normal; //法線
		CoordTf::VECTOR2 tex;    //テクスチャ座標
	};

	ver* createCube(int numArr, CoordTf::VECTOR3* PosArr, CoordTf::VECTOR3* sizeArr, bool Reverse);
	unsigned int* createCubeIndex(int numArr, bool Reverse);

	ver* createSphere(int xMax, int yMax, int numArr,
		CoordTf::VECTOR3* PosArr, CoordTf::VECTOR3* sizeArr, bool Reverse);

	unsigned int* createSphereIndex(int xMax, int yMax, int numArr, bool Reverse);
}

#endif
