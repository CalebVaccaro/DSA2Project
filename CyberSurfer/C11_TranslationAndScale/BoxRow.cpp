#include "BoxRow.h"
#include "MyMesh.h"

void BoxRow::CreateRow(int vecX, int vecY, int vecZ)
{ 
	int count = 11;
	for (uint i = 0; i < count; i++)
	{
		// Create Mesh
		MyMesh* rowMesh = new MyMesh();
		rowMeshes.push_back(rowMesh);
		rowMesh->GenerateCuboid(C_WHITE, C_BLACK);	// white is 1.0f,1.0f,1.0f
		numBoxes++;
	}
}
