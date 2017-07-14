#include <stdio.h>
#include <stdlib.h>
#include "pathfinder.h"
#include <time.h>

int main()
{
	int pOutBuffer[900];
	unsigned char xMap[10000];
	int length;
	//time_t t;
	//srand((unsigned) time(&t));

	xMap[0] = 1;

    for (int j = 0; j<100000; j++)
    {
        for (int i = 1; i<10000; i++)
        {
            xMap[i] = rand()%2;
        }


        length = FindPath(10, 10, 20, 20, xMap, 30, 30, pOutBuffer, 900);

        if (length>=0)
        {
            finVisualize(0,0,xMap,30,30, pOutBuffer, 2500);
            printf("\n\nMinimum path length of: %d\n\n", length);
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
