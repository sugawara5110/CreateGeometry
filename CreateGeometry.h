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
		CoordTf::VECTOR3 Pos;    //�ʒu
		CoordTf::VECTOR3 normal; //�@��
		CoordTf::VECTOR2 tex;    //�e�N�X�`�����W
	};

	ver* createCube(int numArr, CoordTf::VECTOR3* PosArr, CoordTf::VECTOR3* sizeArr, bool Reverse);
	unsigned int* createCubeIndex(int numArr, bool Reverse);

	ver* createSphere(int xMax, int yMax, int numArr,
		CoordTf::VECTOR3* PosArr, CoordTf::VECTOR3* sizeArr, bool Reverse);

	unsigned int* createSphereIndex(int xMax, int yMax, int numArr, bool Reverse);
}

#endif
