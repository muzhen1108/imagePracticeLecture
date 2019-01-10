#ifndef _LSD_H
#define _LSD_H

#include "GlobalData.h"
#include "OCRGlobalData.h"

#ifndef FALSE
#define FALSE	0
#endif /* !FALSE */
#ifndef TRUE
#define TRUE	1
#endif

//MARCO DEFINE
#define ANGLE_THRESHOLD	25
#define NOTDEF			-1024//Label for pixels not used in yet
#define NOTUSED			0  //Label for pixels already used in detection
//#define MAX_LINE_NUM	500
#define USED			1
#define REGRESIZE       17
#define MAXLISTCOUNT    8000


typedef struct coorlist
{
	short x, y;
	struct coorlist *next;
}coorlist;//point set

typedef struct M_line
{
	short x1, y1, x2, y2;//直线的两个点坐标
	short x, y;//直线斜率用整数表示
}M_line;
typedef struct M_double//可用作double型
{
	 short x;  //除数
	 short y;  //被除数
}M_double;
typedef struct M_point {short x,y;}M_point;//点

#if defined (__cplusplus)
extern "C" {
#endif
	//查表法求角度  
    short Atan2_M(int x,int y);
    //查表法求正切值
    unsigned int  tan_M(int x);
	//得到角度和梯度
	void GetAngleAndGradient(UChar *pIn,short width,short height,struct coorlist **ppList,struct coorlist *list,int *pModgrad,short *pAngles,short n_bins);
	//lsd得到直线
	void GetLines(UChar *data,short width,short height,short *lines,short *lines_num, LRect *rect);
	//高斯滤波函数
	void GaussianFilter(UChar *corrupted,UChar* smooth,short width,short height,struct M_double *rateP);

#if defined (__cplusplus)
}
#endif
#endif
