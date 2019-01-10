#ifndef _TRANSFORMM_H_
#define _TRANSFORMM_H_

#include "OCRGlobalData.h"
#define ACCURACYSTEP  4//��ȷ����Ϊһλ����λ2^4
#define SHIFTSTEP 10 //��ֵΪ1024
#define SHIFTVAL  1024
//param����Ĭ����Ϊ9
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

//fpArray����16��ֵ��Ӧ8��������꣬ǰ�ĸ���Ϊ�任������꣬���ĸ���Ϊ�任ǰ������
void lwz_transform(unsigned char *srcData, unsigned char *dstData, int width, int widthStep, int height, int nchan, int *fpArray, LRect tranRet);

#endif
