/*
Author: Tristan VanFossen
Date: 7-21-2017
*/

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include "pathfinder.h"

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
    if (nOutBufferSize != 0)
    {
        int length = -1;
        const int grid = nMapWidth*nMapHeight;
        int* weighted = (int*)malloc(sizeof(int)*grid);
        for (int i = 0; i<nMapWidth*nMapHeight; i++)
        {
            weighted[i] = -1; //init matrix to "infinite" length
        }
        weighted[nStartX + nStartY*nMapWidth] = 0; // Always a length of 0 to start pos

        djikstra(nStartX, nStartY, pMap, weighted, nMapWidth, nMapHeight, nOutBufferSize); //calculates a weighted matrix

        //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

        length = weighted[nTargetX + (nTargetY*nMapWidth)];

        if (length >= 0 && length <= nOutBufferSize);
        {
            bool temp = bufferPath(nStartX,nStartY,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize);
        }

        return length;
    }
    else return -1;
}

bool bufferPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int* weighted, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
    int curPosition = nTargetX + nTargetY*nMapWidth;
    int totalLength = weighted[curPosition];

    int right = 1;
    int left = -1;
    int up = -1*nMapWidth;
    int down = 1*nMapWidth;


	if (totalLength != -1 && totalLength != 0)
    {
        for (int i = totalLength-1; i>=0; i--)
        {
            bool temp = false;

            if (curPosition + right < nMapWidth*nMapHeight && !temp)
            {
                if(weighted[curPosition + right] == i)
                {
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+right;
                    temp = true;
                }
            }
            if (curPosition + left >=0 && !temp)
            {
                if (weighted[curPosition + left] == i)
                {
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+left;
                    temp = true;
                }
            }
            if (curPosition + up >= 0 && !temp)
            {
                if (weighted[curPosition + up] == i)
                {
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+up;
                    temp = true;
                }

            }
            if (curPosition + down < nMapWidth*nMapHeight &&  !temp)
            {
                if (weighted[curPosition + down] == i)
                {
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+down;
                    temp = true;
                }
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}


void djikstra(const int nStartX, const int nStartY, const unsigned char* pMap, int* weighted, const int nMapWidth, const int nMapHeight, const int length)
{
    int curPosition = nStartX + nStartY*nMapWidth;
	int right = 1;
    int left = -1;
    int up = -1*nMapWidth;
    int down = 1*nMapWidth;

    //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

    if (curPosition + right < nMapWidth*nMapHeight && nStartX + 1 < nMapWidth)
    { // Checks to ensure the next point accessed is within array bounds
        if (pMap[curPosition + right] == 1)
        { // Checks to ensure next point checked is a valid path
            if (weighted[curPosition + right] > weighted[curPosition] + 1 || weighted[curPosition + right] == -1)
            { //Checks to ensure an update is necessary to the next weight, if so updates and then recurses
                weighted[curPosition + right] = weighted[curPosition] + 1;
                if (weighted[curPosition + right] < length)
                {
                    djikstra(nStartX + 1, nStartY, pMap, weighted, nMapWidth, nMapHeight, length);
                }
            }
        }
    }
    if (curPosition + down < nMapWidth*nMapHeight && nStartY + 1 < nMapHeight)
    {
        if (pMap[curPosition + down] == 1)
        {
            if (weighted[curPosition + down] > weighted[curPosition] + 1 || weighted[curPosition + down] == -1)
            {
                weighted[curPosition + down] = weighted[curPosition] + 1;
                if (weighted[curPosition+down] < length)
                {
                    djikstra(nStartX, nStartY + 1, pMap, weighted, nMapWidth, nMapHeight, length);
                }
            }
        }
    }
    if (curPosition + left >= 0 && nStartX - 1 >= 0)
    {
        if (pMap[curPosition + left] == 1)
        {
            if (weighted[curPosition + left] > weighted[curPosition] + 1 || weighted[curPosition + left] == -1)
            {
                weighted[curPosition + left] = weighted[curPosition] + 1;
                if (weighted[curPosition + left] < length)
                {
                   djikstra(nStartX - 1, nStartY, pMap, weighted, nMapWidth, nMapHeight, length);
                }
            }
        }
    }
    if (curPosition + up >= 0 && nStartY - 1 >= 0)
    {
        if (pMap[curPosition + up] == 1)
        {
            if (weighted[curPosition + up] > weighted[curPosition] + 1 || weighted[curPosition + up] == -1)
            {
                weighted[curPosition + up] = weighted[curPosition] + 1;
                if (weighted[curPosition + up] < length)
                {
                    djikstra(nStartX, nStartY - 1, pMap, weighted, nMapWidth, nMapHeight, length);
                }
            }
        }
    }


	return;
}

void visualize(const int nStartX, const int nStartY, const int* pMap, const int nMapWidth, const int nMapHeight)//For weighted graph
{
	//visualization
	for (int i = 0; i<nMapHeight*nMapWidth; i++)
	{

		printf("%d\t", pMap[i]);

		if (i%nMapWidth == nMapWidth - 1)
		{
			printf("\n");
		}
	}
	printf("\n\n");

	return;
}

void visualize(const int nStartX, const int nStartY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight)//For reg graph
{
	//visualization
	for (int i = 0; i<nMapHeight*nMapWidth; i++)
	{

		printf("%d", pMap[i]);

		if (i%nMapWidth == nMapWidth - 1)
		{
			printf("\n");
		}
	}
	printf("\n\n");

	return;
}

void finVisualize(const int nStartX, const int nStartY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, const int* pOutBuffer, const int length)//For reg graph
{
	bool flag;
	//visualization
	for (int i = 0; i<nMapHeight*nMapWidth; i++)
	{
		flag = false;
		for (int j = 0; j<length; j++)
		{
			if (pOutBuffer[j] == i) flag = true;
		}
		if (flag)
		{
			printf("*");
		}
		else printf("%d", pMap[i]);

		if (i%nMapWidth == nMapWidth - 1)
		{
			printf("\n");
		}
	}
	printf("\n\n");

	return;
}


