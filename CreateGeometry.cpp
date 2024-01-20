//*****************************************************************************************//
//**                                                                                     **//
//**                             CreateGeometry                                          **//
//**                                                                                     **//
//*****************************************************************************************//

#include "CreateGeometry.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace {

	const int numBaseVer = 24;
	const int numBaseIndex = 36;
	const int numTriangle = numBaseIndex / 3;

	const CreateGeometry::ver baseVer[numBaseVer] =
	{
		{ {-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f} ,{0.0f,0.0f}},
		{ {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f} ,{1.0f,0.0f}},
		{ {-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f} ,{0.0f,1.0f}},
		{ {1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f},{1.0f,1.0f} },

		{ {1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f},{0.0f,0.0f} },
		{ {-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} ,{1.0f,0.0f}},
		{ {1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f} ,{0.0f,1.0f}},
		{ {-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f} ,{1.0f,1.0f}},

		{ {-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} ,{0.0f,0.0f}},
		{ {-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} ,{1.0f,0.0f}},
		{ {-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} ,{0.0f,1.0f}},
		{ {-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} ,{1.0f,1.0f}},

		{ {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f} ,{0.0f,0.0f}},
		{ {1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f} ,{1.0f,0.0f}},
		{ {1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} ,{0.0f,1.0f}},
		{ {1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} ,{1.0f,1.0f}},

		{ {1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{0.0f,0.0f}},
		{ {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{1.0f,0.0f}},
		{ {1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{0.0f,1.0f}},
		{ {-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{1.0f,1.0f}},

		{ {-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,0.0f}},
		{ {1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,0.0f}},
		{ {-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,1.0f}},
		{ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,1.0f}},
	};

	const unsigned baseIndex[] =
	{
		0,1,2,
		2,1,3,

		4,5,6,
		6,5,7,

		8,9,10,
		10,9,11,

		12,13,14,
		14,13,15,

		16,17,18,
		18,17,19,

		20,21,22,
		22,21,23
	};
}

CreateGeometry::ver* CreateGeometry::createCube(int numArr, CoordTf::VECTOR3* PosArr,
	CoordTf::VECTOR3* sizeArr, bool Reverse) {

	ver* V = new ver[numArr * numBaseVer];
	for (int i = 0; i < numArr; i++) {
		ver* v = &V[i * numBaseVer];
		for (int j = 0; j < numBaseVer; j++) {
			if (Reverse) {
				v[j].normal.as(-baseVer[j].normal.x, -baseVer[j].normal.y, -baseVer[j].normal.z);
				v[j].tex.as(1.0f - baseVer[j].tex.x, baseVer[j].tex.y);
			}
			else {
				v[j].normal = baseVer[j].normal;
				v[j].tex = baseVer[j].tex;
			}
			v[j].Pos.x = baseVer[j].Pos.x * sizeArr[i].x + PosArr[i].x;
			v[j].Pos.y = baseVer[j].Pos.y * sizeArr[i].y + PosArr[i].y;
			v[j].Pos.z = baseVer[j].Pos.z * sizeArr[i].z + PosArr[i].z;
		}
	}
	return V;
}

unsigned int* CreateGeometry::createCubeIndex(int numArr, bool Reverse) {
	unsigned int* Ind = new unsigned int[numArr * numBaseIndex];
	for (int i = 0; i < numArr; i++) {
		unsigned int* ind = &Ind[i * numBaseIndex];
		for (int j = 0; j < numBaseIndex; j += 3) {
			if (Reverse) {
				ind[j] = baseIndex[j + 1] + i * numBaseVer;
				ind[j + 1] = baseIndex[j] + i * numBaseVer;
			}
			else {
				ind[j] = baseIndex[j] + i * numBaseVer;
				ind[j + 1] = baseIndex[j + 1] + i * numBaseVer;
			}
			ind[j + 2] = baseIndex[j + 2] + i * numBaseVer;
		}
	}
	return Ind;
}

static float ConvertAnglesToRadians(float angle) {
	return angle * (float)M_PI / 180.0f;
}

CreateGeometry::ver* CreateGeometry::createSphere(int xMax, int yMax, int numArr,
	CoordTf::VECTOR3* PosArr, CoordTf::VECTOR3* sizeArr, bool Reverse) {

	const int numVer = (xMax + 1) * (yMax + 1);
	ver* V = new ver[numVer * numArr];

	int Vcnt = 0;
	for (int n = 0; n < numArr; n++) {
		for (int y = 0; y <= yMax; y++) {
			for (int x = 0; x <= xMax; x++) {
				float theta = ConvertAnglesToRadians(180.0f * y / yMax);
				float phi = ConvertAnglesToRadians(360.0f * x / xMax);

				float nx = (float)sin(theta) * (float)cos(phi);
				float ny = (float)cos(theta);
				float nz = (float)sin(theta) * (float)sin(phi);

				float vx = nx * sizeArr[n].x + PosArr[n].x;
				float vy = ny * sizeArr[n].y + PosArr[n].y;
				float vz = nz * sizeArr[n].z + PosArr[n].z;

				int index = (xMax + 1) * y + x + Vcnt;

				V[index].Pos.as(vx, vy, vz);
				if (Reverse) {
					V[index].normal.as(-nx, -ny, -nz);
					V[index].tex.as(1.0f - ((float)x / (float)xMax), (float)y / (float)yMax);
				}
				else {
					V[index].normal.as(nx, ny, nz);
					V[index].tex.as((float)x / (float)xMax, (float)y / (float)yMax);
				}
			}
		}
		Vcnt += numVer;
	}
	return V;
}

unsigned int* CreateGeometry::createSphereIndex(int xMax, int yMax, int numArr, bool Reverse) {

	const int numVer = (xMax + 1) * (yMax + 1);
	const int numIndex = xMax * yMax * 6;
	unsigned int* Ind = new unsigned int[numIndex * numArr];
	int Icnt = 0;
	int Vcnt = 0;
	for (int n = 0; n < numArr; n++) {
		for (int y = 0; y < yMax; y++) {
			for (int x = 0; x < xMax; x++) {
				if (Reverse) {
					Ind[Icnt++] = (xMax + 1) * y + x + 1 + Vcnt;
					Ind[Icnt++] = (xMax + 1) * y + x + Vcnt;
					Ind[Icnt++] = (xMax + 1) * (y + 1) + x + Vcnt;

					Ind[Icnt++] = (xMax + 1) * (y + 1) + x + 1 + Vcnt;
					Ind[Icnt++] = (xMax + 1) * y + x + 1 + Vcnt;
					Ind[Icnt++] = (xMax + 1) * (y + 1) + x + Vcnt;
				}
				else {
					Ind[Icnt++] = (xMax + 1) * y + x + Vcnt;
					Ind[Icnt++] = (xMax + 1) * y + x + 1 + Vcnt;
					Ind[Icnt++] = (xMax + 1) * (y + 1) + x + Vcnt;

					Ind[Icnt++] = (xMax + 1) * y + x + 1 + Vcnt;
					Ind[Icnt++] = (xMax + 1) * (y + 1) + x + 1 + Vcnt;
					Ind[Icnt++] = (xMax + 1) * (y + 1) + x + Vcnt;
				}
			}
		}
		Vcnt += numVer;
	}
	return Ind;
}