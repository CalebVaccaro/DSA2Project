#include "BoxConstruct.h"
#include "BoxRow.h"


void BoxConstruct::CreateRowConstructs()
{
	for (uint i = 0; i < yMax; i++)
	{
		// create BoxRow
		BoxRow* boxRow = new BoxRow();
		constructRows.push_back(boxRow);
		constructRows[i]->CreateRow(xRowIndex, yRowIndex);
		amountOfBoxes = amountOfBoxes + boxRow->numBoxes;
		yRowIndex++;
	}
}
