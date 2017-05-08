#include <stdio.h>
#include <stdlib.h>
#include "pathfinder.h"

int main()
{
	int nMapWidth = 16;
	int nMapHeight = 5;
	int nStartX = 6;
	int nStartY = 2;
	int nTargetX = 15;
	int nTargetY = 1;
	unsigned char pMap[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer[7];

	/* For debugging readout
	unsigned char pMap [] = {0, 1, 2, 3,
							 4, 5, 6, 7,
							 8, 9, 10, 11};
	*/

	int length = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);

	
	printf("Minimum path length of: %d\n\n", length);
	printf("Buffer: %d", pOutBuffer[0]);
	for (int i = 1; i<length; i++)
	{
		printf(", %d", pOutBuffer[i]);
	}
	printf("\n\n");
	//visualize(nStartX,nStartY,pMap,nMapWidth,nMapHeight);
	//finVisualize(nStartX,nStartY,pMap,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize);

	//printf("Runtime: %lu \n", endTV.tv_sec - startTV.tv_sec);

	while (true)
	{

	}

	return 0;
}
