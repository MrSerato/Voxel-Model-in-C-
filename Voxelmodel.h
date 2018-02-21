#pragma once
#include <cstdint>
#include <cstdio>

struct VoxelModel
{
	int x, y, z;
	uint8_t *bitmap;
};

VoxelModel allocateModel(int nx, int ny, int nz);
void clearModel(VoxelModel& model);
void fillModel(VoxelModel& model);
void deleteModel(VoxelModel& model);
	
void getXYZ(const VoxelModel& model, int index, int& x, int& y, int& z);
int getIndex(const VoxelModel& model, int x, int y, int z);
int getByteNumber(int index);
uint8_t getBitNumber(int index);

bool getBit(VoxelModel &model, int x, int y, int z);
void setBit(VoxelModel &model, int x, int y, int z);
void clearBit(VoxelModel &model, int x, int y, int z);
void toggleBit(VoxelModel &model, int x, int y, int z);
void writeSTL(VoxelModel model, const char* filename);

void addSphere(VoxelModel &model, int cx, int cy, int cz, float rad);
void subSphere(VoxelModel &model, int cx, int cy, int cz, float rad);
void toggleSphere(VoxelModel &model, int cx, int cy, int cz, float rad);