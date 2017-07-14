/*
Author: Tristan VanFossen
Date: 5-4-2017
*/

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include "pathfinder.h"

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
    if (nOutBufferSize != 0)
    {
        const int grid = nMapWidth*nMapHeight;
        int* weighted = (int*)malloc(sizeof(int)*grid);

        djikstra(nStartX, nStartY, pMap, weighted, nMapWidth, nMapHeight); //calculates a weighted matrix
                                                                           //From weighted matrix, find minimum path length to target
        int length = weighted[nTargetX + (nTargetY*nMapWidth)];

        //Knowing the length reduces the size of the area to be searched for a path
        if (length <= nOutBufferSize)
        {
            bool temp = bufferPath(nStartX, nStartY, nTargetX, nTargetY, pMap, weighted, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize, length, 0);
            if (temp)
            {
                return length;
            }
            else return -1;
        }
        else return -1;
    }
    else if (nStartX == nTargetX && nStartY == nTargetY)
    {
        return 0;
    }
    else return -1;
}

bool bufferPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int* weighted, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize, const int minLength, const int bufferPos)
{
    int curPosition = nTargetX + nTargetY*nMapWidth;
    int totalLength = weighted[curPosition];

    int right = 1;
    int left = -1;
    int up = -1*nMapWidth;
    int down = 1*nMapWidth;

	if (totalLength != -1)
    {
        for (int i = totalLength-1; i>=0; i--)
        {
            bool temp = false;

            if (curPosition + right < nMapWidth*nMapHeight && !temp)
            {
                if(weighted[curPosition + right] == i)
                {
                    //printf("%d : %d \n", weighted[curPosition+right], i);
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+right;
                    temp = true;
                }
            }
            if (curPosition + left >=0 && !temp)
            {
                if (weighted[curPosition + left] == i)
                {
                    //printf("%d : %d \n", weighted[curPosition+left], i);
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+left;
                    temp = true;
                }
            }
            if (curPosition + up >= 0 && !temp)
            {
                if (weighted[curPosition + up] == i)
                {
                    //printf("%d : %d \n", weighted[curPosition+up], i);
                    pOutBuffer[i] = curPosition;
                    curPosition = curPosition+up;
                    temp = true;
                }

            }
            if (curPosition + down < nMapWidth*nMapHeight && !temp)
            {
                if (weighted[curPosition + down] == i)
                {
                    //printf("%d : %d \n", weighted[curPosition+down],  i);
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

void djikstra(const int nStartX, const int nStartY, const unsigned char* pMap, int* weighted, const int nMapWidth, const int nMapHeight)
{
	int current, right, left, down, up;

	for (int i = 0; i<nMapWidth*nMapHeight; i++)
	{
		weighted[i] = -1; //init matrix to "infinite" length
	}
	weighted[nStartX + nStartY*nMapWidth] = 0; // Always a length of 0 to start pos

	for (int i = 0; i < nMapHeight; i++) //Djikstra's Algorithm -> weighted matrix
	{                                    // Running from start of array
		for (int j = 0; j < nMapWidth; j++)
		{

			current = (i*nMapWidth) + j;
			right = (i*nMapWidth) + (j + 1);
			left = (i*nMapWidth) + (j - 1);
			down = ((i + 1)*nMapWidth) + j;
			up = ((i - 1)*nMapWidth) + j;


			//printf("current: %d\ti: %d\tj: %d\n\n", current, i, j); //debugging

			if (pMap[right] == 1 && pMap[current] != 0 && weighted[current] != -1 && j + 1<nMapWidth)
			{
				//  printf("\t Right open\n"); //for debugging
				if (weighted[right] == -1)
				{
					weighted[right] = weighted[current] + 1;
				}
				else if (weighted[right] != -1)
				{
					if (weighted[right] >= weighted[current] + 1)
					{
						weighted[right] = weighted[current] + 1;
					}
				}
			}
			if (pMap[left] == 1 && pMap[current] != 0 && weighted[current] != -1 && j - 1 >= 0)
			{
				//printf("\t Left open\n");//debugging
				if (weighted[left] == -1)
				{
					weighted[left] = weighted[current] + 1;
				}
				else if (weighted[left] != -1)
				{
					if (weighted[left] > weighted[current] + 1)
					{
						weighted[left] = weighted[current] + 1;
					}
				}
			}
			if (pMap[down] == 1 && pMap[current] != 0 && weighted[current] != -1 && i + 1<nMapHeight)
			{
				//printf("\t Down open\n");//debugging
				if (weighted[down] == -1)
				{
					weighted[down] = weighted[current] + 1;
				}
				else if (weighted[down] != -1)
				{
					if (weighted[down] > weighted[current] + 1)
					{
						weighted[down] = weighted[current] + 1;
					}
				}
			}
			if (pMap[up] == 1 && pMap[current] != 0 && weighted[current] != -1 && i - 1 >= 0)
			{
				//printf("\t Up open\n");//debugging
				if (weighted[up] == -1)
				{
					weighted[up] = weighted[current] + 1;
				}
				else if (weighted[up] != -1)
				{
					if (weighted[up] > weighted[current] + 1)
					{
						weighted[up] = weighted[current] + 1;
					}
				}
			}
		}
	}

	for (int i = nMapHeight - 1; i >= 0; i--) //Djikstra's Algorithm -> weighted matrix
	{                                       // Running second time to catch any missed positions
		for (int j = nMapWidth - 1; j >= 0; j--)
		{
			current = (i*nMapWidth) + j;
			right = (i*nMapWidth) + (j + 1);
			left = (i*nMapWidth) + (j - 1);
			down = ((i + 1)*nMapWidth) + j;
			up = ((i - 1)*nMapWidth) + j;

			//visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

			//printf("current: %d\ti: %d\tj: %d\n\n", current, i, j); //debugging

			if (pMap[right] == 1 && pMap[current] != 0 && weighted[current] != -1 && j + 1<nMapWidth)
			{
				//  printf("\t Right open\n"); //for debugging
				if (weighted[right] == -1)
				{
					weighted[right] = weighted[current] + 1;
				}
				else if (weighted[right] != -1)
				{
					if (weighted[right] >= weighted[current] + 1)
					{
						weighted[right] = weighted[current] + 1;
					}
				}
			}
			if (pMap[left] == 1 && pMap[current] != 0 && weighted[current] != -1 && j - 1 >= 0)
			{
				//printf("\t Left open\n");//debugging
				if (weighted[left] == -1)
				{
					weighted[left] = weighted[current] + 1;
				}
				else if (weighted[left] != -1)
				{
					if (weighted[left] > weighted[current] + 1)
					{
						weighted[left] = weighted[current] + 1;
					}
				}
			}
			if (pMap[down] == 1 && pMap[current] != 0 && weighted[current] != -1 && i + 1<nMapHeight)
			{
				//printf("\t Down open\n");//debugging
				if (weighted[down] == -1)
				{
					weighted[down] = weighted[current] + 1;
				}
				else if (weighted[down] != -1)
				{
					if (weighted[down] > weighted[current] + 1)
					{
						weighted[down] = weighted[current] + 1;
					}
				}
			}
			if (pMap[up] == 1 && pMap[current] != 0 && weighted[current] != -1 && i - 1 >= 0)
			{
				//printf("\t Up open\n");//debugging
				if (weighted[up] == -1)
				{
					weighted[up] = weighted[current] + 1;
				}
				else if (weighted[up] != -1)
				{
					if (weighted[up] > weighted[current] + 1)
					{
						weighted[up] = weighted[current] + 1;
					}
				}
			}
		}
	}
	for (int i = 0; i <nMapHeight; i++) //Djikstra's Algorithm -> weighted matrix
	{                                       // Running sthird time to catch missed positions (Top right corner
		for (int j = nMapWidth - 1; j >= 0; j--)
		{
			current = (i*nMapWidth) + j;
			right = (i*nMapWidth) + (j + 1);
			left = (i*nMapWidth) + (j - 1);
			down = ((i + 1)*nMapWidth) + j;
			up = ((i - 1)*nMapWidth) + j;

			//visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

			//printf("current: %d\ti: %d\tj: %d\n\n", current, i, j); //debugging

			if (pMap[right] == 1 && pMap[current] != 0 && weighted[current] != -1 && j + 1<nMapWidth)
			{
				//  printf("\t Right open\n"); //for debugging
				if (weighted[right] == -1)
				{
					weighted[right] = weighted[current] + 1;
				}
				else if (weighted[right] != -1)
				{
					if (weighted[right] >= weighted[current] + 1)
					{
						weighted[right] = weighted[current] + 1;
					}
				}
			}
			if (pMap[left] == 1 && pMap[current] != 0 && weighted[current] != -1 && j - 1 >= 0)
			{
				//printf("\t Left open\n");//debugging
				if (weighted[left] == -1)
				{
					weighted[left] = weighted[current] + 1;
				}
				else if (weighted[left] != -1)
				{
					if (weighted[left] > weighted[current] + 1)
					{
						weighted[left] = weighted[current] + 1;
					}
				}
			}
			if (pMap[down] == 1 && pMap[current] != 0 && weighted[current] != -1 && i + 1<nMapHeight)
			{
				//printf("\t Down open\n");//debugging
				if (weighted[down] == -1)
				{
					weighted[down] = weighted[current] + 1;
				}
				else if (weighted[down] != -1)
				{
					if (weighted[down] > weighted[current] + 1)
					{
						weighted[down] = weighted[current] + 1;
					}
				}
			}
			if (pMap[up] == 1 && pMap[current] != 0 && weighted[current] != -1 && i - 1 >= 0)
			{
				//printf("\t Up open\n");//debugging
				if (weighted[up] == -1)
				{
					weighted[up] = weighted[current] + 1;
				}
				else if (weighted[up] != -1)
				{
					if (weighted[up] > weighted[current] + 1)
					{
						weighted[up] = weighted[current] + 1;
					}
				}
			}
		}
	}

	for (int i = nMapHeight - 1; i >= 0; i--) //Djikstra's Algorithm -> weighted matrix
	{                                       // Running second time to catch any missed positions
		for (int j = 0; j <nMapWidth; j++)
		{
			current = (i*nMapWidth) + j;
			right = (i*nMapWidth) + (j + 1);
			left = (i*nMapWidth) + (j - 1);
			down = ((i + 1)*nMapWidth) + j;
			up = ((i - 1)*nMapWidth) + j;

			//visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

			//printf("current: %d\ti: %d\tj: %d\n\n", current, i, j); //debugging

			if (pMap[right] == 1 && pMap[current] != 0 && weighted[current] != -1 && j + 1<nMapWidth)
			{
				//  printf("\t Right open\n"); //for debugging
				if (weighted[right] == -1)
				{
					weighted[right] = weighted[current] + 1;
				}
				else if (weighted[right] != -1)
				{
					if (weighted[right] >= weighted[current] + 1)
					{
						weighted[right] = weighted[current] + 1;
					}
				}
			}
			if (pMap[left] == 1 && pMap[current] != 0 && weighted[current] != -1 && j - 1 >= 0)
			{
				//printf("\t Left open\n");//debugging
				if (weighted[left] == -1)
				{
					weighted[left] = weighted[current] + 1;
				}
				else if (weighted[left] != -1)
				{
					if (weighted[left] > weighted[current] + 1)
					{
						weighted[left] = weighted[current] + 1;
					}
				}
			}
			if (pMap[down] == 1 && pMap[current] != 0 && weighted[current] != -1 && i + 1<nMapHeight)
			{
				//printf("\t Down open\n");//debugging
				if (weighted[down] == -1)
				{
					weighted[down] = weighted[current] + 1;
				}
				else if (weighted[down] != -1)
				{
					if (weighted[down] > weighted[current] + 1)
					{
						weighted[down] = weighted[current] + 1;
					}
				}
			}
			if (pMap[up] == 1 && pMap[current] != 0 && weighted[current] != -1 && i - 1 >= 0)
			{
				//printf("\t Up open\n");//debugging
				if (weighted[up] == -1)
				{
					weighted[up] = weighted[current] + 1;
				}
				else if (weighted[up] != -1)
				{
					if (weighted[up] > weighted[current] + 1)
					{
						weighted[up] = weighted[current] + 1;
					}
				}
			}
		}
	}

   //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);


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

void finVisualize(const int nStartX, const int nStartY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, const int* pOutBuffer, const int nOutBufferSize)//For reg graph
{
	bool flag;
	//visualization
	for (int i = 0; i<nMapHeight*nMapWidth; i++)
	{
		flag = false;
		for (int j = 0; j<nOutBufferSize; j++)
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


