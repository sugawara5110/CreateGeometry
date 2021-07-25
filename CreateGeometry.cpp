//*****************************************************************************************//
//**                                                                                     **//
//**                             CreateGeometry                                          **//
//**                                                                                     **//
//*****************************************************************************************//

#include "CreateGeometry.h"
#define _USE_MATH_DEFINES
#include <math.h>

static const int numBaseVer = 24;
static const int numBaseIndex = 36;

static const CreateGeometry::ver baseVer[numBaseVer] =
{
	{ {-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f} ,{0.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f},{0.0f,1.0f} },

	{ {-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f},{0.0f,0.0f} },
	{ {1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} ,{0.0f,0.0f}},
	{ {-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} ,{1.0f,0.0f}},
	{ {-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} ,{0.0f,1.0f}},

	{ {1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} ,{1.0f,1.0f}},
	{ {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,1.0f}},
};

static const unsigned baseIndex[] =
{
	3,1,0,
	2,1,3,

	6,4,5,
	7,4,6,

	11,9,8,
	10,9,11,

	14,12,13,
	15,12,14,

	19,17,16,
	18,17,19,

	22,20,21,
	23,20,22
};

CreateGeometry::ver* CreateGeometry::createCube(int numArr, CoordTf::VECTOR3* PosArr,
	CoordTf::VECTOR3* sizeArr, bool Reverse) {

	ver* V = new ver[numArr * numBaseVer];
	for (int i = 0; i < numArr; i++) {
		ver* v = &V[i * numBaseVer];
		for (int j = 0; j < numBaseVer; j++) {
			if (!Reverse) {
				v[j].normal = baseVer[j].normal;
				v[j].tex = baseVer[j].tex;
				v[j].Pos.x = baseVer[j].Pos.x * sizeArr[i].x + PosArr[i].x;
				v[j].Pos.y = baseVer[j].Pos.y * sizeArr[i].y + PosArr[i].y;
				v[j].Pos.z = baseVer[j].Pos.z * sizeArr[i].z + PosArr[i].z;
			}
			else {
				v[j].normal.as(-baseVer[j].normal.x, -baseVer[j].normal.y, -baseVer[j].normal.z);
				v[j].tex.as(1.0f - baseVer[j].tex.x, baseVer[j].tex.y);
				v[j].Pos.x = baseVer[j].Pos.x * sizeArr[i].x + PosArr[i].x;
				v[j].Pos.y = baseVer[j].Pos.z * sizeArr[i].z + PosArr[i].z;
				v[j].Pos.z = baseVer[j].Pos.y * sizeArr[i].y + PosArr[i].y;
			}
		}
	}
	return V;
}

unsigned int* CreateGeometry::createCubeIndex(int numArr) {
	unsigned int* Ind = new unsigned int[numArr * numBaseIndex];
	for (int i = 0; i < numArr; i++) {
		unsigned int* ind = &Ind[i * numBaseIndex];
		for (int j = 0; j < numBaseIndex; j++) {
			ind[j] = baseIndex[j] + i * numBaseVer;
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

				float nx = sin(theta) * cos(phi);
				float ny = cos(theta);
				float nz = sin(theta) * sin(phi);

				float vx = nx * sizeArr[n].x + PosArr[n].x;
				float vy = ny * sizeArr[n].y + PosArr[n].y;
				float vz = nz * sizeArr[n].z + PosArr[n].z;

				int index = (xMax + 1) * y + x + Vcnt;
				if (!Reverse) {
					V[index].Pos.as(vx, vy, vz);
					V[index].normal.as(nx, ny, nz);
					V[index].tex.as((float)x / (float)xMax, (float)y / (float)yMax);
				}
				else {
					V[index].Pos.as(vx, vz, vy);
					V[index].normal.as(-nx, -ny, -nz);
					V[index].tex.as(1.0f - ((float)x / (float)xMax), (float)y / (float)yMax);
				}
			}
		}
		Vcnt += numVer;
	}
	return V;
}

unsigned int* CreateGeometry::createSphereIndex(int xMax, int yMax, int numArr) {

	const int numVer = (xMax + 1) * (yMax + 1);
	const int numIndex = xMax * yMax * 6;
	unsigned int* Ind = new unsigned int[numIndex * numArr];
	int Icnt = 0;
	int Vcnt = 0;
	for (int n = 0; n < numArr; n++) {
		for (int y = 0; y < yMax; y++) {
			for (int x = 0; x < xMax; x++) {
				Ind[Icnt++] = (xMax + 1) * y + x + Vcnt;
				Ind[Icnt++] = (xMax + 1) * y + x + 1 + Vcnt;
				Ind[Icnt++] = (xMax + 1) * (y + 1) + x + Vcnt;

				Ind[Icnt++] = (xMax + 1) * y + x + 1 + Vcnt;
				Ind[Icnt++] = (xMax + 1) * (y + 1) + x + 1 + Vcnt;
				Ind[Icnt++] = (xMax + 1) * (y + 1) + x + Vcnt;
			}
		}
		Vcnt += numVer;
	}
	return Ind;
}