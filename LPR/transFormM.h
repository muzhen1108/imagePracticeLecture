#ifndef _TRANSFORMM_H_
#define _TRANSFORMM_H_

#include "OCRGlobalData.h"
#define ACCURACYSTEP  4//精确度数为一位，移位2^4
#define SHIFTSTEP 10 //数值为1024
#define SHIFTVAL  1024
//param长度默认设为9
void lwz_squareToQuadrilateral(
    int x0, int y0, 
    int x1, int y1, 
    int x2, int y2, 
    int x3, int y3, 
    int *param);

void lwz_buildAdjoint(int * param);

void lwz_quadrilateralToSquare(
    int x0, int y0, 
    int x1, int y1, 
    int x2, int y2, 
    int x3, int y3, 
    int *param);

void lwz_times(int *param, int *paramOther);

void lwz_quadrilateralToQuadrilateral(
    int x0, int y0, 
    int x1, int y1,
    int x2, int y2, 
    int x3, int y3, 
    int x0p, int y0p, 
    int x1p, int y1p, 
    int x2p, int y2p,
    int x3p, int y3p, 
    int *param);

void lwz_transformPoints(unsigned short *points, const int pointSize, int *param, LRect tranRet, int xHighbd, int yHighbd);

//fpArray保存16个值对应8个点的坐标，前四个点为变换后的坐标，后四个点为变换前的坐标
void lwz_transform(unsigned char *srcData, unsigned char *dstData, int width, int widthStep, int height, int nchan, int *fpArray, LRect tranRet);

#endif
