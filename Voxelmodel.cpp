#include <stdio.h>
#include <cstdint>
#include <math.h>
#include <iostream>

/*
Anthony Clementi
Intro to Systems Programming
February 2017

This program expands on the 4x4x4 voxel implementation from the previous 2 assignemnts
by creating an arbitrarily large model using dynmically allocated memory.
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Voxelmodel.h";


VoxelModel allocateModel(int nx, int ny, int nz)
{
	VoxelModel model;
	int bytes = nx*ny*nz/8;
	bytes++;
	model.bitmap = new uint8_t[bytes];
	model.x = nx;
	model.y = ny;
	model.z = nz;
	return model;
}

void clearModel(VoxelModel &model)
{
	int bytes = model.x*model.y*model.z / 8;
	bytes++;

	for (int i = 0; i < bytes; i++)
	{
		model.bitmap[i] = 0;
	}
}

void fillModel(VoxelModel &model)
{
	int bytes = model.x*model.y*model.z / 8;

	for (int i = 0; i < bytes; i++)
	{
		model.bitmap[i] = 0xFF;
	}
}

void deleteModel(VoxelModel &model)
{
	delete[] model.bitmap;
	model.bitmap = NULL;
	model.x = 0;
	model.y = 0;
	model.z = 0;
}

int getIndex(const VoxelModel& model, int x, int y, int z)
{
	int index = 0;
	index = ((model.z * model.y * x) + (model.z*y) + z);
	return index;
}

void getXYZ(const VoxelModel& model, int index, int& x, int& y, int& z)
{
	x = index / (model.y*model.z);
	y = index / (model.z)%model.y;
	z = index %model.z;
}

int getByteNumber(int index)
{
	return index / 8;
}

uint8_t getBitNumber(int index)
{
	return index % 8;
}

bool getBit(VoxelModel &model, int x, int y, int z)
{
	int index = getIndex(model, x, y, z);
	int byte = getByteNumber(index);
	int bit = getBitNumber(index);
	int tempbit = 1;
	int searchFor = model.bitmap[byte];
	bit = (searchFor >> bit) & tempbit;
	return bit;
}

void setBit(VoxelModel &model, int x, int y, int z)
{
	int index = getIndex(model, x, y, z);
	int byte = getByteNumber(index);
	int bit = getBitNumber(index);
	int copy = 1;
	copy <<= bit;
	model.bitmap[byte] |= copy;
}

void toggleBit(VoxelModel &model, int x, int y, int z)
{
	int index = getIndex(model, x, y, z);
	int byte = getByteNumber(index);
	int bit = getBitNumber(index);
	int copy = 1;
	copy <<= bit;
	model.bitmap[byte] ^= copy;
}

void clearBit(VoxelModel &model, int x, int y, int z)
{
	int index = getIndex(model, x, y, z);
	int byte = getByteNumber(index);
	int bit = getBitNumber(index);
	int copy = 1;
	copy <<= bit;
	model.bitmap[byte] &= ~copy;
}

void addSphere(VoxelModel &model, int cx, int cy, int cz, float rad)
{
	/*
	Recall that a point (x, y, z) 
	is inside a sphere if (x - cx)^2 + (y - cy)^2 + (z - cz)^2 < radius^2.
	*/
	for (int x = 0; x < model.x; x++)
	{
		for (int y = 0; y < model.y; y++)
		{
			for (int z = 0; z < model.z; z++)
			{
				if (pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2) < pow(rad, 2))
				{
					setBit(model, x, y, z);
				}
			}
		}
	}
}

void subSphere(VoxelModel &model, int cx, int cy, int cz, float rad)
{
	for (int x = 0; x < model.x; x++)
	{
		for (int y = 0; y < model.y; y++)
		{
			for (int z = 0; z < model.z; z++)
			{
				if (pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2) < pow(rad, 2))
				{
					clearBit(model, x, y, z);
				}
			}
		}
	}
}


void toggleSphere(VoxelModel &model, int cx, int cy, int cz, float rad)
{
	for (int x = 0; x < model.x; x++)
	{
		for (int y = 0; y < model.y; y++)
		{
			for (int z = 0; z < model.z; z++)
			{
				if (pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2) < pow(rad, 2))
				{
					toggleBit(model, x, y, z);
				}
			}
		}
	}
}

