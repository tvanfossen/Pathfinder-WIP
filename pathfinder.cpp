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
        short* weighted = (short*)malloc(sizeof(short)*grid);
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
            bufferPath(nStartX,nStartY,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize);
        }
        free(weighted);
        return length;
    }
    else return -1;
}

bool bufferPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const short* weighted, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
    int curPosition = nTargetX + nTargetY*nMapWidth;


	if (weighted[curPosition] != -1 && weighted[curPosition] != 0)
    {
        for (int i = weighted[curPosition]-1; i>=0; --i)
        {
            bool temp = false;

            if (curPosition + 1 < nMapWidth*nMapHeight && !temp)
            {
                if(weighted[curPosition + 1] == i)
                {
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+1;
                    temp = true;
                }
            }
            if (curPosition + -1 >=0 && !temp)
            {
                if (weighted[curPosition + -1] == i)
                {
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+-1;
                    temp = true;
                }
            }
            if (curPosition + -1*nMapWidth >= 0 && !temp)
            {
                if (weighted[curPosition + -1*nMapWidth] == i)
                {
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+-1*nMapWidth;
                    temp = true;
                }

            }
            if (curPosition + 1*nMapWidth < nMapWidth*nMapHeight &&  !temp)
            {
                if (weighted[curPosition + 1*nMapWidth] == i)
                {
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+1*nMapWidth;
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


void djikstra(const int nStartX, const int nStartY, const unsigned char* pMap, short* weighted, const int nMapWidth, const int nMapHeight, const int length)
{
    //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

    if (nStartX + nStartY*nMapWidth + 1 < nMapWidth*nMapHeight && nStartX + 1 < nMapWidth)
    { // Checks to ensure the next point accessed is within array bounds
        if (pMap[nStartX + nStartY*nMapWidth + 1] == 1)
        { // Checks to ensure next point checked is a valid path
            if (weighted[nStartX + nStartY*nMapWidth + 1] > weighted[nStartX + nStartY*nMapWidth] + 1 || weighted[nStartX + nStartY*nMapWidth + 1] == -1)
            { //Checks to ensure an -1*nMapWidthdate is necessary to the next weight, if so -1*nMapWidthdates and then recurses
                weighted[nStartX + nStartY*nMapWidth + 1] = weighted[nStartX + nStartY*nMapWidth] + 1;
                if (weighted[nStartX + nStartY*nMapWidth + 1] < length)
                {
                    djikstra(nStartX + 1, nStartY, pMap, weighted, nMapWidth, nMapHeight, length);
                }
            }
        }
    }
    if (nStartX + nStartY*nMapWidth + 1*nMapWidth < nMapWidth*nMapHeight && nStartY + 1 < nMapHeight)
    {
        if (pMap[nStartX + nStartY*(nMapWidth) + 1*nMapWidth] == 1)
        {
            if (weighted[nStartX + nStartY*nMapWidth + 1*nMapWidth] > weighted[nStartX + nStartY*nMapWidth] + 1 || weighted[nStartX + nStartY*nMapWidth + 1*nMapWidth] == -1)
            {
                weighted[nStartX + nStartY*nMapWidth + 1*nMapWidth] = weighted[nStartX + nStartY*nMapWidth] + 1;
                if (weighted[nStartX + nStartY*nMapWidth+1*nMapWidth] < length)
                {
                    djikstra(nStartX, nStartY + 1, pMap, weighted, nMapWidth, nMapHeight, length);
                }
            }
        }
    }
    if (nStartX + nStartY*nMapWidth + -1 >= 0 && nStartX - 1 >= 0)
    {
        if (pMap[nStartX + nStartY*nMapWidth + -1] == 1)
        {
            if (weighted[nStartX + nStartY*nMapWidth + -1] > weighted[nStartX + nStartY*nMapWidth] + 1 || weighted[nStartX + nStartY*nMapWidth + -1] == -1)
            {
                weighted[nStartX + nStartY*nMapWidth + -1] = weighted[nStartX + nStartY*nMapWidth] + 1;
                if (weighted[nStartX + nStartY*nMapWidth + -1] < length)
                {
                   djikstra(nStartX - 1, nStartY, pMap, weighted, nMapWidth, nMapHeight, length);
                }
            }
        }
    }
    if (nStartX + nStartY*nMapWidth + -1*nMapWidth >= 0 && nStartY - 1 >= 0)
    {
        if (pMap[nStartX + nStartY*nMapWidth + -1*nMapWidth] == 1)
        {
            if (weighted[nStartX + nStartY*nMapWidth + -1*nMapWidth] > weighted[nStartX + nStartY*nMapWidth] + 1 || weighted[nStartX + nStartY*nMapWidth + -1*nMapWidth] == -1)
            {
                weighted[nStartX + nStartY*nMapWidth + -1*nMapWidth] = weighted[nStartX + nStartY*nMapWidth] + 1;
                if (weighted[nStartX + nStartY*nMapWidth + -1*nMapWidth] < length)
                {
                    djikstra(nStartX, nStartY - 1, pMap, weighted, nMapWidth, nMapHeight, length);
                }
            }
        }
    }


	return;
}

void visualize(const int nStartX, const int nStartY, const short* pMap, const int nMapWidth, const int nMapHeight)//For weighted graph
{
	//visualization
	for (int i = 0; i<nMapHeight*nMapWidth; i++)
	{
        if (pMap[i] == -1)
        {
            printf("#\t");
        }
        else printf("%d\t", pMap[i]);

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


