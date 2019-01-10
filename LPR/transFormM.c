//#include <malloc.h>
#include <stdio.h>
#include "transFormM.h"
#include "GlobalData.h"

extern int res[14000];

void lwz_transformPoints(unsigned short *points, int pointSize, int *param, LRect tranRet, int xHighbd, int yHighbd) 
{
    int i,x,y,x1,y1;
    int denominator;
	int findDeno;
    int a11,a12,a13,a21,a22,a23,a31,a32,a33;

	denominator = 998;
	denominator = denominator;

    a11 = param[0] << ACCURACYSTEP;
    a21 = param[1] << ACCURACYSTEP;
    a31 = param[2] << ACCURACYSTEP;
    a12 = param[3] << ACCURACYSTEP;
    a22 = param[4] << ACCURACYSTEP;
    a32 = param[5] << ACCURACYSTEP;
    a13 = param[6];
    a23 = param[7];
    a33 = param[8] << SHIFTSTEP;

    for (i = 0; i < pointSize; i += 2) 
    {
        x = points[i];
        y = points[i + 1];
#if 1
		denominator = (a13 * x + a23 * y + a33) >> (SHIFTSTEP + 4);
		denominator = (denominator > 6999)?6999:denominator;
		denominator = (denominator < -6999)?-6999:denominator;
		denominator = denominator + 7000;
		findDeno = res[denominator];
		x1 = ((a11 * x + a21 * y + a31) >> 11) * findDeno >> 16;
        y1 = ((a12 * x + a22 * y + a32) >> 11) * findDeno >> 16;

        x1 = (x1 < 0)? 0:x1;
        x1 = (x1 > xHighbd)? xHighbd:x1;
        y1 = (y1 < 0)? 0:y1;
        y1 = (y1 > yHighbd)? yHighbd:y1;	

        points[i] = x1;
        points[i + 1] = y1;  

#else
		denominator = (a13 * x + a23 * y + a33) >> SHIFTSTEP;
		denominator = denominator + ((denominator >> 31) << 1) + 1;
		points[i] = (a11 * x + a21 * y + a31) / denominator;
		points[i + 1] = (a12 * x + a22 * y + a32) / denominator;  
#endif
    }
}

void lwz_squareToQuadrilateral(int x0, int y0, int x1, int y1, int x2,
    int y2, int x3, int y3, int *param)
{
    int dx3;
    int dy3;
    int dx1;
    int dx2;
    int dy1;
    int dy2;
    int a13;
    int a23;
    int denominator;

    dx3 = x0 - x1 + x2 - x3;
    dy3 = y0 - y1 + y2 - y3;

    if (dx3 == 0 && dy3 == 0) 
    {
        param[0] = x1 - x0;
        param[1] = x2 - x1;
        param[2] = x0;
        param[3] = y1 - y0;
        param[4] = y2 - y1;
        param[5] = y0;
        param[6] = 0;
        param[7] = 0;
        param[8] = 1;
    } 
    else 
    {
        dx1 = x1 - x2;
        dx2 = x3 - x2;
        dy1 = y1 - y2;
        dy2 = y3 - y2;
        denominator = dx1 * dy2 - dx2 * dy1;
        a13 = ((dx3 * dy2 - dx2 * dy3) << SHIFTSTEP) / (denominator + 1);//denominator
        a23 = ((dx1 * dy3 - dx3 * dy1) << SHIFTSTEP) / (denominator + 1);//denominator

        param[0] = x1 - x0 + (a13 * x1 >> SHIFTSTEP);
        param[1] = x3 - x0 + (a23 * x3 >> SHIFTSTEP);
        param[2] = x0;
        param[3] = y1 - y0 + (a13 * y1 >> SHIFTSTEP);
        param[4] = y3 - y0 + (a23 * y3 >> SHIFTSTEP);
        param[5] = y0;
        param[6] = a13;
        param[7] = a23;
        param[8] = 1;   
    }
}

void lwz_buildAdjoint(int * param)
{
    int a11,a12,a13,a21,a22,a23,a31,a32,a33;

    a11 = param[0];
    a21 = param[1];
    a31 = param[2];
    a12 = param[3];
    a22 = param[4];
    a32 = param[5];
    a13 = param[6];
    a23 = param[7];
    a33 = param[8];

    param[0] = a22 * a33 - (a23 * a32 >> SHIFTSTEP);
    param[1] = (a23 * a31 >> SHIFTSTEP) - a21 * a33;
    param[2] = a21 * a32 - a22 * a31;
    param[3] = (a13 * a32 >> SHIFTSTEP) - a12 * a33;
    param[4] = a11 * a33 - (a13 * a31 >> SHIFTSTEP);
    param[5] = a12 * a31 - a11 * a32;
    param[6] = a12 * a23 - a13 * a22;
    param[7] = a13 * a21 - a11 * a23;
    param[8] = a11 * a22 - a12 * a21;   
}

void lwz_quadrilateralToSquare(int x0, int y0, int x1, int y1, int x2,
    int y2, int x3, int y3, int *param)
{
    lwz_squareToQuadrilateral(x0, y0, x1, y1, x2, y2, x3, y3, param);   
    lwz_buildAdjoint(param);
}

void lwz_times(int *param, int *paramOther)
{
    int a11,a12,a13,a21,a22,a23,a31,a32,a33;
    int o_a11,o_a12,o_a13,o_a21,o_a22,o_a23,o_a31,o_a32,o_a33;

    a11 = paramOther[0];
    a21 = paramOther[1];
    a31 = paramOther[2];
    a12 = paramOther[3];
    a22 = paramOther[4];
    a32 = paramOther[5];
    a13 = paramOther[6];
    a23 = paramOther[7];
    a33 = paramOther[8];

    o_a11 = param[0];
    o_a21 = param[1];
    o_a31 = param[2];
    o_a12 = param[3];
    o_a22 = param[4];
    o_a32 = param[5];
    o_a13 = param[6];
    o_a23 = param[7];
    o_a33 = param[8];

    param[0] = a11 * o_a11 + a21 * o_a12 + (a31 * o_a13 >> SHIFTSTEP);
    param[1] = a11 * o_a21 + a21 * o_a22 + (a31 * o_a23 >> SHIFTSTEP);
    param[2] = a11 * o_a31 + a21 * o_a32 + a31 * o_a33;
    param[3] = a12 * o_a11 + a22 * o_a12 + (a32 * o_a13 >> SHIFTSTEP);
    param[4] = a12 * o_a21 + a22 * o_a22 + (a32 * o_a23 >> SHIFTSTEP);
    param[5] = a12 * o_a31 + a22 * o_a32 + a32 * o_a33;
	param[6] = a13 * o_a11 + a23 * o_a12 + a33 * o_a13;
	param[7] = a13 * o_a21 + a23 * o_a22 + a33 * o_a23;
	param[8] = (a13 * o_a31 >> SHIFTSTEP) + (a23 * o_a32 >> SHIFTSTEP) + a33 * o_a33; 
   
}

void lwz_quadrilateralToQuadrilateral(int x0, int y0, int x1, int y1,
    int x2, int y2, int x3, int y3, int x0p, int y0p, int x1p, int y1p, int x2p, int y2p,
    int x3p, int y3p, int *param)
{
    int paramOther[9] = {0};
    lwz_quadrilateralToSquare(x0, y0, x1, y1, x2, y2, x3, y3, param);
    lwz_squareToQuadrilateral(x0p, y0p, x1p, y1p, x2p, y2p, x3p, y3p, paramOther);
    lwz_times(param, paramOther);
}

void lwz_transform(unsigned char *srcData, unsigned char *dstData, int width, int widthStep, int height, int nchan, int *fpArray, LRect tranRet)
{
	long long thre;
    int tmp,tmp1,xt;
	int srcWTmp,srcRWTmp;
    int param[9] = {0};
    int pointsNum = 0;
	int widthTmp = 0;
	int widthTmp1 = 0;
	int tranRetWidth = 0;
	int xTmp = 0;
    unsigned short factor_x0,factor_x1,factor_y0,factor_y1;
    unsigned short i,j,x,y,x1,y1,xHighbd,yHighbd;
    unsigned short doubleAccuracy = 2 * ACCURACYSTEP;
    unsigned short *ponits;
    unsigned char data1,data2,data3,data4;

    ponits = (unsigned short *)malloc(width * height * 2 * sizeof(unsigned short));
    tranRetWidth = abs(tranRet.x1 - tranRet.x2);
    tranRetWidth = (tranRetWidth/4)*4;
    tranRet.x2 = tranRet.x1 + tranRetWidth;

    for (i = tranRet.y1; i < tranRet.y2; ++i)
    {
        for (j = tranRet.x1; j < tranRet.x2; ++j)
        {
            ponits[pointsNum++] = j;
            ponits[pointsNum++] = i;
        }
    }

    lwz_quadrilateralToQuadrilateral(fpArray[0], fpArray[1],
        fpArray[2], fpArray[3],
        fpArray[4], fpArray[5],
        fpArray[6], fpArray[7],
        fpArray[8], fpArray[9], // top left
        fpArray[10], fpArray[11], // top right
        fpArray[12], fpArray[13],// bottom left
        fpArray[14], fpArray[15],
        param);

    xHighbd = ((width - 1) << ACCURACYSTEP) - 16;
    yHighbd = ((height - 1) << ACCURACYSTEP) - 16;

    lwz_transformPoints(ponits, pointsNum, param, tranRet, xHighbd,yHighbd);

	memset(dstData,0,sizeof(unsigned char)*widthStep*height);
	//printf("4\n");
    if (1 == nchan)
    {
        pointsNum = 0;
        for (i = tranRet.y1; i < tranRet.y2; ++i)
        {
            srcWTmp = i * widthStep;
            tmp1 = i * width;

#ifndef _dsp_

            for (j = tranRet.x1; j < tranRet.x2; j += 4)
            {
                //1
                _memd8(&thre) = _memd8(&ponits[pointsNum]);
                pointsNum += 4;	

                x = ((thre << 48) >> 48);
                y = ((thre << 32) >> 48);
                x1 = ((thre << 16) >> 48);
                y1 = (thre >> 48);
                
                factor_x0 = ((x >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - x;
                factor_x1 = x - ((x >> ACCURACYSTEP) << ACCURACYSTEP);
                factor_y0 = ((y >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - y;
                factor_y1 = y - ((y >> ACCURACYSTEP) << ACCURACYSTEP);

                x = (x >> ACCURACYSTEP);
                y = (y >> ACCURACYSTEP);

                widthTmp = y * widthStep;
                widthTmp1 = widthTmp + widthStep;

                data1 = (
                    factor_x0 * (factor_y0 * srcData[widthTmp + x] + 
                    factor_y1 * srcData[widthTmp1 + x]) + 
                    factor_x1 * (factor_y0 * srcData[widthTmp + x + 1] + 
                    factor_y1 * srcData[widthTmp1 + x + 1]) )>> doubleAccuracy;

                factor_x0 = ((x1 >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - x1;
                factor_x1 = x1 - ((x1 >> ACCURACYSTEP) << ACCURACYSTEP);
                factor_y0 = ((y1 >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - y1;
                factor_y1 = y1 - ((y1 >> ACCURACYSTEP) << ACCURACYSTEP);

                x1 = (x1 >> ACCURACYSTEP);
                y1 = (y1 >> ACCURACYSTEP);

                widthTmp = y1 * widthStep;
                widthTmp1 = widthTmp + widthStep;
                //2
                data2 = (
                    factor_x0 * (factor_y0 * srcData[widthTmp + x1] + 
                    factor_y1 * srcData[widthTmp1 + x1]) + 
                    factor_x1 * (factor_y0 * srcData[widthTmp + x1 + 1] + 
                    factor_y1 * srcData[widthTmp1 + x1 + 1]) )>> doubleAccuracy;
                //3
                _memd8(&thre) = _memd8(&ponits[pointsNum]);
                pointsNum += 4;	

                x = ((thre << 48) >> 48);
                y = ((thre << 32) >> 48);
                x1 = ((thre << 16) >> 48);
                y1 = (thre >> 48);

                factor_x0 = ((x >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - x;
                factor_x1 = x - ((x >> ACCURACYSTEP) << ACCURACYSTEP);
                factor_y0 = ((y >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - y;
                factor_y1 = y - ((y >> ACCURACYSTEP) << ACCURACYSTEP);

                x = (x >> ACCURACYSTEP);
                y = (y >> ACCURACYSTEP);

                widthTmp = y * widthStep;
                widthTmp1 = widthTmp + widthStep;

                data3 = (
                    factor_x0 * (factor_y0 * srcData[widthTmp + x] + 
                    factor_y1 * srcData[widthTmp1 + x]) + 
                    factor_x1 * (factor_y0 * srcData[widthTmp + x + 1] + 
                    factor_y1 * srcData[widthTmp1 + x + 1]) )>> doubleAccuracy;

                factor_x0 = ((x1 >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - x1;
                factor_x1 = x1 - ((x1 >> ACCURACYSTEP) << ACCURACYSTEP);
                factor_y0 = ((y1 >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - y1;
                factor_y1 = y1 - ((y1 >> ACCURACYSTEP) << ACCURACYSTEP);

                x1 = (x1 >> ACCURACYSTEP);
                y1 = (y1 >> ACCURACYSTEP);

                widthTmp = y1 * widthStep;
                widthTmp1 = widthTmp + widthStep;
                //4
                data4 = (
                    factor_x0 * (factor_y0 * srcData[widthTmp + x1] + 
                    factor_y1 * srcData[widthTmp1 + x1]) + 
                    factor_x1 * (factor_y0 * srcData[widthTmp + x1 + 1] + 
                    factor_y1 * srcData[widthTmp1 + x1 + 1]) )>> doubleAccuracy;

                dstData[srcWTmp + j] = data1;
                dstData[srcWTmp + j+1] = data2;
                dstData[srcWTmp + j+2] = data3;
                dstData[srcWTmp + j+3] = data4;
                //xt = (int)data1 | ((int)data2 << 8) | ((int)data3 << 16) | ((int)data4 << 24);
                //_mem4(&dstData[srcWTmp + j]) = _mem4(&xt);

            }
#else
            for (j = tranRet.x1; j < tranRet.x2; ++j)
            {
                x = ponits[pointsNum++];
                y = ponits[pointsNum++];

                factor_x0 = ((x >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - x;
                factor_x1 = x - ((x >> ACCURACYSTEP) << ACCURACYSTEP);
                factor_y0 = ((y >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - y;
                factor_y1 = y - ((y >> ACCURACYSTEP) << ACCURACYSTEP);

                x = (x >> ACCURACYSTEP);
                y = (y >> ACCURACYSTEP);

                widthTmp = y * widthStep;
                widthTmp1 = widthTmp + widthStep;

                dstData[srcWTmp + j] = (
                    factor_x0 * (factor_y0 * srcData[widthTmp + x] + 
                    factor_y1 * srcData[widthTmp1 + x]) + 
                    factor_x1 * (factor_y0 * srcData[widthTmp + x + 1] + 
                    factor_y1 * srcData[widthTmp1 + x + 1]) )>> doubleAccuracy;

            }
#endif
        }
    }
    if (3 == nchan)
    {
        pointsNum = 0;
        for (i = tranRet.y1; i < tranRet.y2; ++i)
        {
            srcWTmp = i * widthStep;
            tmp1 = i * width;

            for (j = tranRet.x1; j < tranRet.x2; ++j)
            {
                x = ponits[pointsNum++];
                y = ponits[pointsNum++];	

                factor_x0 = ((x >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - x;
                factor_x1 = x - ((x >> ACCURACYSTEP) << ACCURACYSTEP);
                factor_y0 = ((y >> ACCURACYSTEP) + 1 << ACCURACYSTEP) - y;
                factor_y1 = y - ((y >> ACCURACYSTEP) << ACCURACYSTEP);

                x = (x >> ACCURACYSTEP);
                y = (y >> ACCURACYSTEP);
                
                srcRWTmp = srcWTmp + 3 * j;
                xTmp = 3 * x;
                widthTmp = y * widthStep + xTmp;
                widthTmp1 = widthTmp + widthStep;
                //
                dstData[srcRWTmp] = (
                    factor_x0 *  (factor_y0 * srcData[widthTmp] + 
                    factor_y1 * srcData[widthTmp1] ) + 
                    factor_x1 * (factor_y0 * srcData[widthTmp + 3] + 
                    factor_y1 * srcData[widthTmp1 + 3]) ) >> doubleAccuracy;

                dstData[srcRWTmp + 1] = (
                    factor_x0 * (factor_y0 * srcData[widthTmp + 1] + 
                    factor_y1 * srcData[widthTmp1 + 1]) + 
                    factor_x1 * (factor_y0 * srcData[widthTmp + 4] + 
                    factor_y1 * srcData[widthTmp1 + 4])) >> doubleAccuracy;

                dstData[srcRWTmp + 2] = (
                    factor_x0 * (factor_y0 * srcData[widthTmp + 2] + 
                    factor_y1 * srcData[widthTmp1 + 2]) + 
                    factor_x1 * (factor_y0 * srcData[widthTmp + 5] + 
                    factor_y1 * srcData[widthTmp1 + 5])) >> doubleAccuracy;
                //*/
            }
        }
    }
    //printf("5\n");
    free(ponits);
    ponits = NULL;
}
