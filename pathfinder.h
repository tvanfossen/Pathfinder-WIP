#ifndef PATHFINDER_H_INCLUDED
#define PATHFINDER_H_INCLUDED

int FindPath(const int nStartX, const int nStartY,const int nTargetX, const int nTargetY,const unsigned char* pMap, const int nMapWidth, const int nMapHeight,int* pOutBuffer, const int nOutBufferSize);
void visualize(const int nStartX, const int nStartY, const int* pMap, const int nMapWidth, const int nMapHeight);
void visualize(const int nStartX, const int nStartY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight);
void finVisualize(const int nStartX, const int nStartY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, const int* pOutBuffer, const int nOutBufferSize);
void djikstra(const int nStartX, const int nStartY, const unsigned char* pMap, int* weighted, const int nMapWidth, const int nMapHeight, const int length);
bool bufferPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int* weighted, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize);


#endif // PATHFINDER_H_INCLUDED
