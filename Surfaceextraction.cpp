//
//  surfaceExtraction.cpp
//  Homework3
//
//  Created by Ben Jones on 1/6/17.
//  Copyright © 2017 Ben Jones. All rights reserved.
//


#define _CRT_SECURE_NO_WARNINGS
#include "Surfaceextraction.hpp"
#include "Voxelmodel.h"
#include <cstdio>
#include <iostream>

inline void fillPlane(int a1, int a2, int b1, int b2, int c, int cInd, Triangle& t1, Triangle& t2) {
	t1.v1[cInd] = c;
	t2.v1[cInd] = c;
	t1.v2[cInd] = c;
	t2.v2[cInd] = c;
	t1.v3[cInd] = c;
	t2.v3[cInd] = c;
	int aInd = (cInd + 1) % 3;
	int bInd = (cInd + 2) % 3;

	t1.v1[aInd] = a1;
	t1.v2[aInd] = a2;
	t1.v3[aInd] = a2;

	t2.v1[aInd] = a1;
	t2.v2[aInd] = a2;
	t2.v3[aInd] = a1;

	t1.v1[bInd] = b1;
	t1.v2[bInd] = b1;
	t1.v3[bInd] = b2;

	t2.v1[bInd] = b1;
	t2.v2[bInd] = b2;
	t2.v3[bInd] = b2;

}

void extractFace(int x, int y, int z, FaceType face, Triangle& t1, Triangle& t2) {
	for (int i = 0; i < 3; i++) {
		t1.normal[i] = 0;
		t2.normal[i] = 0;
	}
	switch (face) {
	case NX:
		t1.normal[0] = -1;
		t2.normal[0] = -1;
		fillPlane(y + 1, y, z, z + 1, x, 0, t1, t2);
		break;
	case NY:
		t1.normal[1] = -1;
		t2.normal[1] = -1;
		fillPlane(z + 1, z, x, x + 1, y, 1, t1, t2);
		break;
	case NZ:
		t1.normal[2] = -1;
		t2.normal[2] = -1;
		fillPlane(x + 1, x, y, y + 1, z, 2, t1, t2);
		break;
	case PX:
		t1.normal[0] = 1;
		t2.normal[0] = 1;
		fillPlane(y, y + 1, z, z + 1, x + 1, 0, t1, t2);
		break;
	case PY:
		t1.normal[1] = 1;
		t2.normal[1] = 1;
		fillPlane(z, z + 1, x, x + 1, y + 1, 1, t1, t2);
		break;
	case PZ:
		t1.normal[2] = 1;
		t2.normal[2] = 1;
		fillPlane(x, x + 1, y, y + 1, z + 1, 2, t1, t2);
		break;
	}
}

void writeSTL(VoxelModel model, const char* filename)
{
	FILE *the_file;
	the_file = fopen(filename, "wb+");

	char header[80];
	char filler = '0';
	for (int i = 0; i < 80; i++)
	{
		header[i] = filler;
	}

	uint32_t numTriangles = 0;
	fwrite(&header, sizeof(header), 1, the_file);
	fwrite(&numTriangles, sizeof(numTriangles), 1, the_file);

	uint16_t zero = 0;

	//loops to write triangles in the directions

	for (int x = 0; x < model.x; x++)
	{
		for (int y = 0; y < model.y; y++)
		{
			for (int z = 0; z < model.z; z++)
			{
				if (getBit(model, x, y, z) == true)
				{
					if (x == 0 || getBit(model, x - 1, y, z) == false)
					{
						Triangle t1;
						Triangle t2;
						numTriangles += 2;
						extractFace(x, y, z, NX, t1, t2);
						fwrite(&t1, sizeof(t1), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
						fwrite(&t2, sizeof(t2), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
					}
					if (x == model.x-1 || getBit(model, x + 1, y, z) == false)
					{
						Triangle t1;
						Triangle t2;
						numTriangles += 2;
						extractFace(x, y, z, PX, t1, t2);
						fwrite(&t1, sizeof(t1), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
						fwrite(&t2, sizeof(t2), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
					}
					if (y == 0 || getBit(model, x, y - 1, z) == false)
					{
						Triangle t1;
						Triangle t2;
						numTriangles += 2;
						extractFace(x, y, z, NY, t1, t2);
						fwrite(&t1, sizeof(t1), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
						fwrite(&t2, sizeof(t2), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
					}
					if (y == model.y-1 || getBit(model, x, y + 1, z) == false)
					{
						Triangle t1;
						Triangle t2;
						numTriangles += 2;
						extractFace(x, y, z, PY, t1, t2);
						fwrite(&t1, sizeof(t1), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
						fwrite(&t2, sizeof(t2), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
					}
					if (z == 0 || getBit(model, x, y, z - 1) == false)
					{
						Triangle t1;
						Triangle t2;
						numTriangles += 2;
						extractFace(x, y, z, NZ, t1, t2);
						fwrite(&t1, sizeof(t1), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
						fwrite(&t2, sizeof(t2), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
					}
					if (z == model.z-1 || getBit(model, x, y, z + 1) == false)
					{
						Triangle t1;
						Triangle t2;
						numTriangles += 2;
						extractFace(x, y, z, PZ, t1, t2);
						fwrite(&t1, sizeof(t1), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
						fwrite(&t2, sizeof(t2), 1, the_file);
						fwrite(&zero, sizeof(zero), 1, the_file);
					}
				}
			}
		}
	}
	fseek(the_file, 80, SEEK_SET);
	fwrite(&numTriangles, sizeof(numTriangles), 1, the_file);
	fclose(the_file);
}
