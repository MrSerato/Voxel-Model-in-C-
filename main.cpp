#include <iostream>
#include "Voxelmodel.h";

int main(int argc, char* argv[]) {
	VoxelModel myModel;
	myModel = allocateModel(16, 24, 18);
	clearModel(myModel);
	addSphere(myModel, 10, 15, 8, 6);
	addSphere(myModel, 15, 24, 0, 10);
	subSphere(myModel, 5, 6, 7, 8);

	char *filename = "newModel.STL";
	writeSTL(myModel, filename);
}