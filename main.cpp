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
    int pOutBuffer[1000000];
	unsigned char xMap[10000];
	int length;


	for (int i = 0; i<10000; i++)
    {
        pOutBuffer[i] = -1;
    }

    for (int j = 0; j<1000000; j++)
    {
        int x;
        if (j%10000 == 0)
        {
            x = j%101;
            srand(x);
        }
       // printf("%d : %d\n", j, x);
	
        for (int i = 0; i<1000000; i++)
        {
            xMap[i] = rand()%2;
        }
        //visualize(0,0,xMap,10,10);

        length = FindPath(0, 0, 15, 15, xMap, 1000, 1000, pOutBuffer, 1000000);


        printf("\nGrids processed: %d", j);
        if (length>=0)
        {
            //printf("Grids Processed: %d\n", j);
            printf("\n\nMinimum path length of: %d\n\n", length);
            printf("Buffer: %d", pOutBuffer[0]);
            for (int i = 1; i<length; i++)
            {
                printf(", %d", pOutBuffer[i]);
            }
            printf("\n\n");
        }
        
    }
}
