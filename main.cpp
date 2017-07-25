#include <stdio.h>
#include <stdlib.h>
#include "pathfinder.h"
#include <time.h>

void directInput();
void randomInput();

int main()
{
    randomInput();

    printf("completed");


	while (true)
	{

	}

	return 0;
}

void directInput()
{
    /*unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                            1, 1, 1, 1, 1, 0, 0, 1, 1, 1,
                            1, 0, 0, 0, 1, 1, 1, 1, 0, 1,
                            1, 0, 0, 1, 0, 0, 1, 1, 1, 1,
                            1, 0, 0, 1, 0, 0, 1, 0, 0, 0,
                            1, 1, 1, 1, 0, 1, 1, 0, 0, 0};*/
    unsigned char pMap[] = {1, 1, 1, 1,
                            0, 1, 0, 1,
                            1, 1, 0, 1};
    int pOutBuffer[70];

    int length = FindPath(0,0,0,2,pMap,4,3,pOutBuffer,12);

    printf("Length: %d\n", length);
    printf("pOutBuffer: %d", pOutBuffer[0]);
    for (int i = 1; i<length;i++)
    {
        printf(", %d", pOutBuffer[i]);
    }
    printf("\n\n");

}

void randomInput()
{
    int pOutBuffer[10000];
    unsigned char xMap[100000];
    srand(0);

    for (int i = 0; i<99999; i++)
    {
        for (int j = 0; j<900; j++)
        {
            xMap[j] = rand()%2;
        }

        int length = FindPath(0,0,15,15,xMap,30,30,pOutBuffer,500);



        if (length>0)
        {
            printf("\n\n");
            finVisualize(0,0,xMap,30,30,pOutBuffer,length);
            printf("Grids Processed: %d\n", i);
            printf("\nLength: %d\n", length);
            printf("Path Buffer: %d", pOutBuffer[0]);
            for (int j = 1; j<length; j++)
            {
                printf(", %d", pOutBuffer[j]);
            }
            printf("\n\n");
        }
    }
}
