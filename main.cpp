#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

using namespace std;

int findPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize);
int pathAvailable(const unsigned char* pMap, const int nTargetX, const int nTargetY, const int nStartX, const int nStartY, const int nMapWidth, const int nMapHeight, int pathLength);
int main()
{
    int nMapWidth = 4;
    int nMapHeight = 3;
    int nStartX = 0;
    int nStartY = 0;
    int nTargetX = 1;
    int nTargetY = 2;
    int nOutBufferSize = 12;
    int pOutBuffer[nOutBufferSize];
    unsigned char pMap [] = {1, 1, 1, 1,
                             0, 1, 0, 1,
                             0, 1, 1, 1};



    printf("%d\n\n",findPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize));

    return 0;
}

int findPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{

    /*for (int i=0;i<(nMapHeight*nMapWidth);i++) //For visualization
    {
        printf("%u", *(pMap+i));
        if (i%nMapWidth==nMapWidth-1)
        {
            printf("\n");
        }
    }*/


    if (*(pMap + ((nMapHeight+1)*(nStartY+1))) == 1 && nStartY < nMapHeight && *(pOutBuffer+nOutBufferSize) != ((nMapHeight+1)*nStartY+1) + (1*(nStartX+1))) //Checks for available position down 1
    {
        printf("check\n");
        *(pOutBuffer+(nOutBufferSize-1)) = (nMapHeight+1)*(nStartY+1) + (1*(nStartX+1));
        return 1+ findPath(nStartX, nStartY+1, nTargetY, nTargetX, pMap, nMapWidth,nMapHeight, pOutBuffer,nOutBufferSize-1);

    }
    else if (*(pMap + (1*(nStartX+1))) == 1 && nStartX < nMapWidth && *(pOutBuffer+nOutBufferSize) != (1*(nStartX+1))+((nMapHeight+1)*nStartY+1))
    {
        printf("check2\n");
        *(pOutBuffer+(nOutBufferSize-1)) = (1*(nStartX+1)+((nMapHeight+1)*(nStartY+1)));
        return 1+ findPath(nStartX+1, nStartY, nTargetY, nTargetX, pMap, nMapWidth,nMapHeight, pOutBuffer,nOutBufferSize-1);
    }
    else if (*(pMap + ((nMapHeight+1)*(nStartY-1))) == 1 && nStartY > 0 && *(pOutBuffer+nOutBufferSize) != ((nMapHeight+1)*(nStartY-1)) + (1*(nStartX+1)))
    {
        printf("check3\n");
        *(pOutBuffer+(nOutBufferSize-1)) = (nMapHeight+1)*(nStartY-1)+ (1*(nStartX+1));
        return 1 + findPath(nStartX, nStartY-1, nTargetY, nTargetX, pMap, nMapWidth,nMapHeight, pOutBuffer,nOutBufferSize-1);
    }
    else if (*(pMap + (1*(nStartX-1))) == 1 && nStartX > 0 && *(pOutBuffer + nOutBufferSize) != (1*(nStartX-1)) + (nMapHeight+1)*(nStartY+1))
    {
        printf("check4\n");
        *(pOutBuffer+(nOutBufferSize-1)) = (1*(nStartX-1)) + ((nMapHeight+1)+(nStartY+1));
        return 1 + findPath(nStartX-1, nStartY, nTargetY, nTargetX, pMap, nMapWidth,nMapHeight, pOutBuffer,nOutBufferSize-1);
    }
    else return 0;
}






