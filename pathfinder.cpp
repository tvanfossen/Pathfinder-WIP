/*
    Author: Tristan VanFossen
    Date: 5-4-2017
*/

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <sys/time.h>


using namespace std;

int findPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize);
void visualize(const int nStartX, const int nStartY, const int* pMap, const int nMapWidth, const int nMapHeight);
void visualize(const int nStartX, const int nStartY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight);
void finVisualize(const int nStartX, const int nStartY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, const int* pOutBuffer, const int nOutBufferSize);
void djikstra(const int nStartX, const int nStartY, const unsigned char* pMap, int* weighted, const int nMapWidth, const int nMapHeight);
bool bufferPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int* weighted, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize, const int minLength, const int bufferPos);

int main()
{

    struct timeval startTV, endTV;

    gettimeofday (&startTV, NULL);

    int nMapWidth = 8;
    int nMapHeight = 3;
    int nStartX = 0;
    int nStartY = 0;
    int nTargetX = 7;
    int nTargetY = 0;
    const int nOutBufferSize = 100;
    int pOutBuffer[nOutBufferSize];
    unsigned char pMap [] = {1, 1, 1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 0, 0, 1, 1,
                             0, 1, 1, 1, 1, 1, 1, 0};

    /* For debugging readout
    unsigned char pMap [] = {0, 1, 2, 3,
                             4, 5, 6, 7,
                             8, 9, 10, 11};
    */

    int length = findPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);

    printf("Minimum path length of: %d\n\n", length);
    printf("Buffer: %d" ,pOutBuffer[0]);
    for (int i = 1;i<length;i++)
    {
        printf(", %d", pOutBuffer[i]);
    }
    printf("\n\n");
    //visualize(nStartX,nStartY,pMap,nMapWidth,nMapHeight);
    //finVisualize(nStartX,nStartY,pMap,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize);

    gettimeofday (&endTV, NULL);
    //printf("Runtime: %lu \n", endTV.tv_sec - startTV.tv_sec);
    return 0;
}

int findPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
    const int grid = nMapWidth*nMapHeight;
    int* weighted = (int*) malloc(sizeof(int)*grid);

    for (int i = 0;i<nOutBufferSize;i++) //Initialize secondary matrix for use in weighting
    {
        pOutBuffer[i] = -1;
    }

    djikstra(nStartX, nStartY, pMap, weighted, nMapWidth, nMapHeight); //calculates a weighted matrix

    //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);//debugging

    //From weighted matrix, find minimum path length to target
    int length = weighted[nTargetX+(nTargetY*nMapWidth)];

    //Knowing the length reduces the size of the area to be searched for a path
    if (length <= nOutBufferSize)
    {
        bufferPath (nStartX, nStartY, nTargetX, nTargetY, pMap, weighted, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize, length, 0);
        return length;
    }
    else return -2;
}

bool bufferPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int* weighted, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize , const int minLength, const int bufferPos)
{
    int right, left, up, down;
    bool flag = false;
    right = (nStartX+1) + nStartY*nMapWidth;
    left = (nStartX-1) + nStartY*nMapWidth;
    up = nStartX + (nStartY-1)*nMapWidth;
    down = nStartX + (nStartY+1)*nMapWidth;


    /*printf("%d", pOutBuffer[0]); // debug
    for (int i = 1; i<12; i++)
    {
        printf(", %d", pOutBuffer[i]);
    }
    printf("\n\n");*/

    if (nStartX == nTargetX&&nStartY==nTargetY) //end case for the recursion, if it hits the endpoint, falls back on itself until origin
    {
        return true;
    }
    else if (bufferPos == 0)
    {
        for (int k = 0; k<5;k++)//Iterates through each of the possible adjacencies
        {
            //For each of the below cases: checks the next in the adjacent vertex to the max allowed length and that it was not previously stored(prevent early backtracking) and that it is within range of the matrix
            if (!flag && nStartX+1<nMapWidth && k == 0)
            {
                if (weighted[right]<=minLength&&weighted[right]!=-1)
                {
                    pOutBuffer[bufferPos] = right; // sets the buffer to the next position, will be overwritten if different path exists
                    flag = bufferPath(nStartX+1,nStartY,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize,minLength,bufferPos+1);
                }
            }
            else if (!flag && nStartX-1>=0 && k == 1)
            {
                if (weighted[left]<=minLength&&weighted[left]!=-1)
                {
                    pOutBuffer[bufferPos] = left;
                    flag = bufferPath(nStartX-1,nStartY,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize,minLength,bufferPos+1);
                }
            }
            else if (!flag && nStartY-1>=0 && k == 2)
            {
                if (weighted[up]<=minLength&&weighted[up]!=-1)
                {
                    pOutBuffer[bufferPos] = up;
                    flag = bufferPath(nStartX,nStartY-1,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize,minLength,bufferPos+1);
                }
            }
            else if (!flag && nStartY+1<nMapHeight && k == 3)
            {
                if (weighted[down]<=minLength&&weighted[down]!=-1)
                {
                    pOutBuffer[bufferPos] = down;
                    flag = bufferPath(nStartX,nStartY+1,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize,minLength,bufferPos+1);
                }
            }
            else if (k == 5)
            {
                pOutBuffer[bufferPos] = -1;
            }
        }
    }
    else
    {
        for (int k = 0; k<5;k++)//Iterates through each of the possible adjacencies
        {
            //For each of the below cases: checks the next in the adjacent vertex to the max allowed length and that it was not previously stored(prevent early backtracking) and that it is within range of the matrix
            if (!flag && nStartX+1<nMapWidth && k == 0)
            {
                if (weighted[right]<=minLength&&weighted[right]>weighted[pOutBuffer[bufferPos-1]])
                {
                    pOutBuffer[bufferPos] = right; // sets the buffer to the next position, will be overwritten if different path exists
                    flag = bufferPath(nStartX+1,nStartY,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize,minLength,bufferPos+1);
                }
            }
            else if (!flag && nStartX-1>=0 && k == 1)
            {
                if (weighted[left]<=minLength&&weighted[left]>weighted[pOutBuffer[bufferPos-1]])
                {
                    pOutBuffer[bufferPos] = left;
                    flag = bufferPath(nStartX-1,nStartY,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize,minLength,bufferPos+1);
                }
            }
            else if (!flag && nStartY-1>=0 && k == 2)
            {
                if (weighted[up]<=minLength&&weighted[up]>weighted[pOutBuffer[bufferPos-1]])
                {
                    pOutBuffer[bufferPos] = up;
                    flag = bufferPath(nStartX,nStartY-1,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize,minLength,bufferPos+1);
                }
            }
            else if (!flag && nStartY+1<nMapHeight && k == 3)
            {
                if (weighted[down]<=minLength&&weighted[down]>weighted[pOutBuffer[bufferPos-1]])
                {
                    pOutBuffer[bufferPos] = down;
                    flag = bufferPath(nStartX,nStartY+1,nTargetX,nTargetY,pMap,weighted,nMapWidth,nMapHeight,pOutBuffer,nOutBufferSize,minLength,bufferPos+1);
                }
            }
            else if (k == 5)
            {
                pOutBuffer[bufferPos] = -1;
            }
        }
    }

    return false;
}

void djikstra(const int nStartX, const int nStartY, const unsigned char* pMap, int* weighted, const int nMapWidth, const int nMapHeight)
{
    int current, right, left, down, up;

    for (int i = 0; i<nMapWidth*nMapHeight;i++)
    {
        weighted[i] = -1; //init matrix to "infinite" length
    }
    weighted[nStartX+nStartY*nMapWidth] = 0; // Always a length of 0 to start pos

    for (int i = 0; i < nMapHeight; i++) //Djikstra's Algorithm -> weighted matrix
    {                                    // Running from start of array
        for (int j = 0; j < nMapWidth; j++)
        {

            current = (i*nMapWidth)+j;
            right = (i*nMapWidth)+(j+1);
            left = (i*nMapWidth)+(j-1);
            down = ((i+1)*nMapWidth)+j;
            up = ((i-1)*nMapWidth)+j;

            //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

            //printf("current: %d\ti: %d\tj: %d\n\n", current, i, j); //debugging

            if (pMap[right] == 1 && pMap[current] != 0 && weighted[current] != -1 && j+1<nMapWidth)
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
            if (pMap[left] == 1 && pMap[current] != 0 &&weighted[current] != -1 && j-1>=0)
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
            if (pMap[down] == 1 && pMap[current] != 0  && weighted[current] != -1 && i+1<nMapHeight)
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
            if (pMap[up] == 1 && pMap[current] != 0 && weighted[current] != -1 && i-1>=0)
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

    for (int i = nMapHeight-1; i >= 0; i--) //Djikstra's Algorithm -> weighted matrix
    {                                       // Running second time to catch any missed positions
        for (int j = nMapWidth-1; j >= 0; j--)
        {
            current = (i*nMapWidth)+j;
            right = (i*nMapWidth)+(j+1);
            left = (i*nMapWidth)+(j-1);
            down = ((i+1)*nMapWidth)+j;
            up = ((i-1)*nMapWidth)+j;

            //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

            //printf("current: %d\ti: %d\tj: %d\n\n", current, i, j); //debugging

            if (pMap[right] == 1 && pMap[current] != 0 && weighted[current] != -1 && j+1<nMapWidth)
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
            if (pMap[left] == 1 && pMap[current] != 0 &&weighted[current] != -1 && j-1>=0)
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
            if (pMap[down] == 1 && pMap[current] != 0  && weighted[current] != -1 && i+1<nMapHeight)
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
            if (pMap[up] == 1 && pMap[current] != 0 && weighted[current] != -1 && i-1>=0)
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
        for (int j = nMapWidth-1; j >= 0; j--)
        {
            current = (i*nMapWidth)+j;
            right = (i*nMapWidth)+(j+1);
            left = (i*nMapWidth)+(j-1);
            down = ((i+1)*nMapWidth)+j;
            up = ((i-1)*nMapWidth)+j;

            //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

            //printf("current: %d\ti: %d\tj: %d\n\n", current, i, j); //debugging

            if (pMap[right] == 1 && pMap[current] != 0 && weighted[current] != -1 && j+1<nMapWidth)
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
            if (pMap[left] == 1 && pMap[current] != 0 &&weighted[current] != -1 && j-1>=0)
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
            if (pMap[down] == 1 && pMap[current] != 0  && weighted[current] != -1 && i+1<nMapHeight)
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
            if (pMap[up] == 1 && pMap[current] != 0 && weighted[current] != -1 && i-1>=0)
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

    for (int i = nMapHeight-1; i >= 0; i--) //Djikstra's Algorithm -> weighted matrix
    {                                       // Running second time to catch any missed positions
        for (int j = 0; j <nMapWidth; j++)
        {
            current = (i*nMapWidth)+j;
            right = (i*nMapWidth)+(j+1);
            left = (i*nMapWidth)+(j-1);
            down = ((i+1)*nMapWidth)+j;
            up = ((i-1)*nMapWidth)+j;

            //visualize(nStartX, nStartY, weighted, nMapWidth, nMapHeight);

            //printf("current: %d\ti: %d\tj: %d\n\n", current, i, j); //debugging

            if (pMap[right] == 1 && pMap[current] != 0 && weighted[current] != -1 && j+1<nMapWidth)
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
            if (pMap[left] == 1 && pMap[current] != 0 &&weighted[current] != -1 && j-1>=0)
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
            if (pMap[down] == 1 && pMap[current] != 0  && weighted[current] != -1 && i+1<nMapHeight)
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
            if (pMap[up] == 1 && pMap[current] != 0 && weighted[current] != -1 && i-1>=0)
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


    return;
}

void visualize(const int nStartX, const int nStartY, const int* pMap, const int nMapWidth, const int nMapHeight)//For weighted graph
{
    //visualization
    for (int i = 0;i<nMapHeight*nMapWidth;i++)
    {

        printf("%d\t", pMap[i]);

        if (i%nMapWidth == nMapWidth-1)
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
    for (int i = 0;i<nMapHeight*nMapWidth;i++)
    {

        printf("%d", pMap[i]);

        if (i%nMapWidth == nMapWidth-1)
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
    for (int i = 0;i<nMapHeight*nMapWidth;i++)
    {
        flag = false;
        for (int j = 0;j<nOutBufferSize; j++)
        {
            if (pOutBuffer[j] == i) flag = true;
        }
        if (flag)
        {
            printf("*");
        }
        else printf("%d", pMap[i]);

        if (i%nMapWidth == nMapWidth-1)
        {
            printf("\n");
        }
    }
    printf("\n\n");

    return;
}

