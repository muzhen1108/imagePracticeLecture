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
	short x1, y1, x2, y2;//ֱ�ߵ�����������
	short x, y;//ֱ��б����������ʾ
}M_line;
typedef struct M_double//������double��
{
	 short x;  //����
	 short y;  //������
}M_double;
typedef struct M_point {short x,y;}M_point;//��

#if defined (__cplusplus)
extern "C" {
#endif
	//�����Ƕ�  
    short Atan2_M(int x,int y);
    //���������ֵ
    unsigned int  tan_M(int x);
	//�õ��ǶȺ��ݶ�
	void GetAngleAndGradient(UChar *pIn,short width,short height,struct coorlist **ppList,struct coorlist *list,int *pModgrad,short *pAngles,short n_bins);
	//lsd�õ�ֱ��
	void GetLines(UChar *data,short width,short height,short *lines,short *lines_num, LRect *rect);
	//��˹�˲�����
	void GaussianFilter(UChar *corrupted,UChar* smooth,short width,short height,struct M_double *rateP);

#if defined (__cplusplus)
}
#endif
#endif
