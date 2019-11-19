#pragma once
#include "Definitions.h"
#include "MyMesh.h"
#include <vector>
using namespace std;

class BoxRow {
public:
	std::vector<MyMesh*> rowMeshes;
	int numBoxes = 0;

	// Create a Row of Mesh Objects
	void CreateRow(int vecX, int vecY, int vecZ = 1);
private:
};