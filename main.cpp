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
    unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                            1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                            1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    /*unsigned char pMap[] = {1, 1, 1, 1,
                            0, 1, 0, 1,
                            1, 1, 0, 1};*/
    int pOutBuffer[70];

    int length = FindPath(0,0,18,6,pMap,19,7,pOutBuffer,70);

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
    int seed = 0;
    srand(0);

    for (int i = 0; i<10000000; i++)
    {
        if (i%100000 == 0)
        {
            printf("%d\n", i);
        }
        //printf("\n%d\n", i);

        for (int j = 0; j<900; j++)
        {
            xMap[j] = rand()%2;
        }


        int length = FindPath(20,25,0,0,xMap,30,30,pOutBuffer,10000);



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
