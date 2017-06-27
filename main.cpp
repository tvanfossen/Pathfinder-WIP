#include <stdio.h>
#include <stdlib.h>
#include "pathfinder.h"
#include <time.h>

int main()
{
	int pOutBuffer[100000];
	unsigned char xMap[100000];
	int length;
	time_t t;
	srand((unsigned) time(&t));

	xMap[0] = 1;

    for (int j = 0; j<100000; j++)
    {
        for (int i = 1; i<100000; i++)
        {
            xMap[i] = rand()%2;
        }

        length = FindPath(0, 0, 10, 15, xMap, 100, 100, pOutBuffer, 10000);

        if (length>0)
        {
            printf("Minimum path length of: %d\n\n", length);
            printf("Buffer: %d", pOutBuffer[0]);
            for (int i = 1; i<length; i++)
            {
                printf(", %d", pOutBuffer[i]);
            }
            printf("\n\n");
        }
    }

    printf("completed");

	//int length = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);


	/*printf("Minimum path length of: %d\n\n", length);
	printf("Buffer: %d", pOutBuffer[0]);
	for (int i = 1; i<length; i++)
	{
		printf(", %d", pOutBuffer[i]);
	}
	printf("\n\n");
	*/

	//visualize(nStartX,nStartY,pMap,nMapWidth,nMapHeight);
	//finVisualize(nStartX,nStartY,pMap,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize);

	//printf("Runtime: %lu \n", endTV.tv_sec - startTV.tv_sec);

	while (true)
	{

	}

	return 0;
}
