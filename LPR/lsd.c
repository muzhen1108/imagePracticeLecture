/////////////////////////////////////////////////////////////////////////
//
//	File:		lsd.c
//
//	Author:		
//
//	Purpose :	lsd line detect
//
//	Date:		Mar. 28, 2014
//
/////////////////////////////////////////////////////////////////////////


#include "lsd.h"
#include "MemProcess.h"

extern int res[14000];

int exRegSize[1024] = {131702,65851,43900,32925,26340,21950,18814,16462,14633,13170,11972,10975,10130,9407,8780,8231,7747,7316,6931,6585,
	6271,5986,5726,5487,5268,5065,4877,4703,4541,4390,4248,4115,3990,3873,3762,3658,3559,3465,3376,3292,
	3212,3135,3062,2993,2926,2863,2802,2743,2687,2634,2582,2532,2484,2438,2394,2351,2310,2270,2232,2195,
	2159,2124,2090,2057,2026,1995,1965,1936,1908,1881,1854,1829,1804,1779,1756,1732,1710,1688,1667,1646,
	1625,1606,1586,1567,1549,1531,1513,1496,1479,1463,1447,1431,1416,1401,1386,1371,1357,1343,1330,1317,
	1303,1291,1278,1266,1254,1242,1230,1219,1208,1197,1186,1175,1165,1155,1145,1135,1125,1116,1106,1097,
	1088,1079,1070,1062,1053,1045,1037,1028,1020,1013,1005,997,990,982,975,968,961,954,947,940,
	934,927,920,914,908,902,895,889,883,878,872,866,860,855,849,844,838,833,828,823,
	818,812,807,803,798,793,788,783,779,774,770,765,761,756,752,748,744,739,735,731,
	727,723,719,715,711,708,704,700,696,693,689,685,682,678,675,671,668,665,661,658,
	655,651,648,645,642,639,636,633,630,627,624,621,618,615,612,609,606,604,601,598,
	595,593,590,587,585,582,580,577,575,572,570,567,565,562,560,558,555,553,551,548,
	546,544,541,539,537,535,533,531,528,526,524,522,520,518,516,514,512,510,508,506,
	504,502,500,498,496,495,493,491,489,487,485,484,482,480,478,477,475,473,472,470,
	468,467,465,463,462,460,458,457,455,454,452,451,449,447,446,444,443,441,440,439,
	437,436,434,433,431,430,428,427,426,424,423,422,420,419,418,416,415,414,412,411,
	410,409,407,406,405,403,402,401,400,399,397,396,395,394,393,391,390,389,388,387,
	386,385,383,382,381,380,379,378,377,376,375,374,373,372,370,369,368,367,366,365,
	364,363,362,361,360,359,358,357,356,355,354,354,353,352,351,350,349,348,347,346,
	345,344,343,342,342,341,340,339,338,337,336,335,335,334,333,332,331,330,330,329,
	328,327,326,325,325,324,323,322,322,321,320,319,318,318,317,316,315,315,314,313,
	312,312,311,310,309,309,308,307,306,306,305,304,304,303,302,302,301,300,300,299,
	298,297,297,296,295,295,294,293,293,292,292,291,290,290,289,288,288,287,286,286,
	285,285,284,283,283,282,282,281,280,280,279,279,278,277,277,276,276,275,274,274,
	273,273,272,272,271,270,270,269,269,268,268,267,267,266,266,265,264,264,263,263,
	262,262,261,261,260,260,259,259,258,258,257,257,256,256,255,255,254,254,253,253,
	252,252,251,251,250,250,249,249,248,248,248,247,247,246,246,245,245,244,244,243,
	243,242,242,242,241,241,240,240,239,239,239,238,238,237,237,236,236,236,235,235,
	234,234,233,233,233,232,232,231,231,231,230,230,229,229,229,228,228,227,227,227,
	226,226,225,225,225,224,224,223,223,223,222,222,222,221,221,220,220,220,219,219,
	219,218,218,218,217,217,216,216,216,215,215,215,214,214,214,213,213,213,212,212,
	212,211,211,211,210,210,210,209,209,209,208,208,208,207,207,207,206,206,206,205,
	205,205,204,204,204,203,203,203,202,202,202,201,201,201,201,200,200,200,199,199,
	199,198,198,198,198,197,197,197,196,196,196,195,195,195,195,194,194,194,193,193,
	193,193,192,192,192,191,191,191,191,190,190,190,190,189,189,189,188,188,188,188,
	187,187,187,187,186,186,186,186,185,185,185,184,184,184,184,183,183,183,183,182,
	182,182,182,181,181,181,181,180,180,180,180,179,179,179,179,178,178,178,178,177,
	177,177,177,177,176,176,176,176,175,175,175,175,174,174,174,174,173,173,173,173,
	173,172,172,172,172,171,171,171,171,171,170,170,170,170,169,169,169,169,169,168,
	168,168,168,167,167,167,167,167,166,166,166,166,166,165,165,165,165,165,164,164,
	164,164,164,163,163,163,163,162,162,162,162,162,161,161,161,161,161,161,160,160,
	160,160,160,159,159,159,159,159,158,158,158,158,158,157,157,157,157,157,156,156,
	156,156,156,156,155,155,155,155,155,154,154,154,154,154,154,153,153,153,153,153,
	152,152,152,152,152,152,151,151,151,151,151,151,150,150,150,150,150,150,149,149,
	149,149,149,148,148,148,148,148,148,147,147,147,147,147,147,146,146,146,146,146,
	146,146,145,145,145,145,145,145,144,144,144,144,144,144,143,143,143,143,143,143,
	142,142,142,142,142,142,142,141,141,141,141,141,141,141,140,140,140,140,140,140,
	139,139,139,139,139,139,139,138,138,138,138,138,138,138,137,137,137,137,137,137,
	137,136,136,136,136,136,136,136,135,135,135,135,135,135,135,134,134,134,134,134,
	134,134,133,133,133,133,133,133,133,133,132,132,132,132,132,132,132,131,131,131,
	131,131,131,131,131,130,130,130,130,130,130,130,130,129,129,129,129,129,129,129,
	128,128,128,128,};
	
//
//功能:通过移位方法求绝对值
//输入 整数值
//返回:返回绝对值
static int abs_M(int n)
{
	return (n^(n >> 31)) - (n >> 31);
}

//
//功能:查表法求角度
//输入 x   y    x值  y值
//返回:点(x,y)的角度

short myangle[65] =
{
	0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 10,11,11,12,13,14,15,16,17,17,18,19,20,
	21,21,22,23,24,24,25,26,27,27,28,29,29,30,31,31,32,33,33,34,35,35,36,36,
	37,37,38,39,39,40,40,41,41,42,42,43,43,44,44,45,45
};

short Atan2_M(int x, int y)
{

	int nx = 0, ny = 0, cb = 0;

	nx = (x < 0);
	ny = (y < 0);
	if (y == 0) 
	{
		if (x > 0) 
		{
			x = 0;
		}
		else 
		{
			x = 180;
		}
		return x; 
	}
	if (x < 0)
	{
		x = -x;
	}
	if (y < 0)
	{
		y = -y;
	}
	if (x < y)
	{
		x = 90 - myangle[(x << 6) / y];//余切值*64
	}
	else
	{
		x = myangle[(y << 6) / x];//正切值*64
	}
	if (nx)
	{
		x = 180-x;
	}
	if (ny)
	{
		x = -x;
	}
	if (x < 0) 
	{
		x = x+360;
	}
	return x;
}



//功能:高斯滤波
//输入:
//corrupted 源图像
//width height源图像宽高
//rapeP  缩放比率
//输入输出:
//smooth 高斯滤波后的图像

void GaussianFilter(UChar *corrupted, UChar *smooth, short width, short height, struct M_double *pRate)
{

// 	short templates[25] =
// 	{1, 4, 7, 4, 1,
// 	4, 16, 26, 16, 4,
// 	7, 26, 41, 26, 7,
// 	4, 16, 26, 16, 4,
// 	1, 4, 7, 4, 1 };	//高斯滤波模板
	int i = 0, j = 0, m = 0, n = 0, sum = 0, index = 0, kernel_sum = 0, a = 0, b = 0;
	short gaussian_width = width * pRate->x/pRate->y, gaussian_height = height * pRate->x/pRate->y;
	int gaussian_wTmp = 0;
	int widthTmp = 0;
	int mwidthTmp = 0;
	short width2 = width * 2;
	short width3 = width * 3;
	short width4 = width * 4;
	short width5 = width * 5;
	int aWidth;
	int tmp;
	//check param
	if (pRate->y == 0 || pRate->x == 0)
	{
		printf("\nerror: gausifilter ratep=0\n");
		return;
	}
	//gaussian filter
    
	for (j = 2; j < gaussian_height - 3; j++)
	{
		gaussian_wTmp = j * gaussian_width;
		for (i = 2; i < gaussian_width - 3; i++)
		{
			sum = 0;
			index = 0;
			kernel_sum = 0;
			a = j + (j >> 2) + 3;//a = j + (j >> 2) + 3，针对的是0.8倍缩放情况
			b = i + (i >> 2) + 3;//b = i + (i >> 2) + 3，针对的是0.8倍缩放情况
			aWidth = a * width;
			tmp = aWidth - width5 + b;
			sum += corrupted[tmp - 5];
			sum += (corrupted[tmp - 4] << 2);
			sum += (corrupted[tmp - 3] << 2);
			sum += (corrupted[tmp - 3] << 1);
			sum += corrupted[tmp - 3];
			sum += (corrupted[tmp - 2] << 2);
			sum += corrupted[tmp - 1];

			tmp = aWidth - width4 + b;
			sum += (corrupted[tmp - 5] << 2);
			sum += (corrupted[tmp - 4] << 4);
			sum += (corrupted[tmp - 3] << 4);
			sum += (corrupted[tmp - 3] << 3);
			sum += (corrupted[tmp - 3] << 1);
			sum += (corrupted[tmp - 2] << 4);
			sum += (corrupted[tmp - 1] << 2);

			tmp = aWidth - width3 + b;
			sum += (corrupted[tmp - 5] << 2);
			sum += (corrupted[tmp - 5] << 1);
			sum += corrupted[tmp - 5];
			sum += (corrupted[tmp - 4] << 4);
			sum += (corrupted[tmp - 4] << 3);
			sum += (corrupted[tmp - 4] << 1);
			sum += (corrupted[tmp - 3] << 5);
			sum += (corrupted[tmp - 3] << 3);
			sum += corrupted[tmp - 3];
			sum += (corrupted[tmp - 2] << 4);
			sum += (corrupted[tmp - 2] << 3);
			sum += (corrupted[tmp - 2] << 1);
			sum += (corrupted[tmp - 1] << 2);
			sum += (corrupted[tmp - 1] << 1);
			sum += corrupted[tmp - 1];

			tmp = aWidth - width2 + b;
			sum += (corrupted[tmp - 5] << 2);
			sum += (corrupted[tmp - 4] << 4);
			sum += (corrupted[tmp - 3] << 4);
			sum += (corrupted[tmp - 3] << 3);
			sum += (corrupted[tmp - 3] << 1);
			sum += (corrupted[tmp - 2] << 4);
			sum += (corrupted[tmp - 1] << 2);

			tmp = aWidth - width + b;
			sum += corrupted[tmp - 5];
			sum += (corrupted[tmp - 4] << 2);
			sum += (corrupted[tmp - 3] << 2);
			sum += (corrupted[tmp - 3] << 1);
			sum += corrupted[tmp - 3];
			sum += (corrupted[tmp - 2] << 2);
			sum += corrupted[tmp - 1];

			sum = (sum * 60)>>14;

			if (sum > 255)
			{
				sum = 255;
			}
			smooth[gaussian_wTmp + i] = sum;
		}//for i
	}//for j//*/

}
//功能:得到图像每个点的梯度和方向
//输入:
//in 输入的灰度图像
//width height 图像宽高
//threshold sqrt(dx^2+dy^2)阀值
//list_p返回点集  梯度从大到小
//modgrad 梯度值
//n_bins 扩展到的范围
//返回每个点的角度
void GetAngleAndGradient(UChar *pIn,short width,short height,struct coorlist **ppList,struct coorlist *list,int *pModgrad,short *pAngles,short n_bins)
{
	Int  x, y, tmp, adr, i, width_4;
	int com1 = 0 , com2 = 0 , gx = 0 , gy = 0 , norm = 0 , norm2 = 0;
	//
	int list_count = 0;
	//int binNum[1024] = {0};
	int *binNum;
	struct coorlist **range_l_s = NULL; // array of pointers to start of bin list 
	struct coorlist **range_l_e = NULL; // array of pointers to end of bin list 
	struct coorlist *start = NULL;
	struct coorlist *end = NULL;
	int max_grad = 0;//最大梯度

	int normNum = 0;
	int thresholdBin = 0;
	int thresholdNorm = 0;
	// calloc
	binNum = (int *)malloc(sizeof(int) * 1024);
	memset(binNum, 0, sizeof(int) * 1024);
	range_l_s = (struct coorlist **) scalloc( n_bins, sizeof(struct coorlist *) );
	range_l_e = (struct coorlist **) scalloc( n_bins, sizeof(struct coorlist *) );
	for (i = 0; i < n_bins; i++) 
	{
		range_l_s[i] = range_l_e[i] = NULL;
	}

    width_4 = width/4*4;//4位对齐
    //compute gradient on the remaining pixels
	for (y = 4; y < height - 5; y++)
    {
        tmp = y * width; 
		for (x = 4; x < width_4 - 4; x++)
        {
			adr = tmp + x;		
			com1 = pIn[adr + width + 1] - pIn[adr];
			com2 = pIn[adr + 1]   - pIn[adr + width];

			gx = com1 + com2; 
			gy = com1 - com2; 
			norm2 = gx * gx + gy * gy;
			norm =  (norm2 >> 2);
			norm = (norm > 6998)?6998:norm;
            norm = (norm < 0)?0:norm;

			pModgrad[adr] = norm;  

			if (norm > 5)
			{
				pAngles[adr] = Atan2_M(gx, -gy);
				if (norm > max_grad ) max_grad = norm;
			}
		}//for y
	}//for x
	//compute histogram of gradient values 
	max_grad++;
	for (y = 4; y < height - 5; y++)
	{
		tmp = y * width;
        for (x = 4; x < width_4 - 4; x++)
		{
			norm = pModgrad[tmp + x];


			i = (norm * res[max_grad + 7000] >> 13);
            i = (i > 1023)?1023:i;
            i = (i < 0)?0:i;
			//i = ((norm << 10) / max_grad);

            binNum[i]++;

			if( range_l_e[i] == NULL )
				range_l_s[i] = range_l_e[i] = list + list_count++;
			else
			{
				range_l_e[i]->next = list + list_count;
				range_l_e[i] = list + list_count++;
			}
			range_l_e[i]->x = x;
			range_l_e[i]->y = y;
			range_l_e[i]->next = NULL;
		}
	}

	//获取阀值
	normNum = 0;
	for (i = n_bins - 1; i > 0; i--)
	{
		normNum += binNum[i];
		if (normNum > MAXLISTCOUNT)
		{
			thresholdBin = i;
			break;
		}
	}
	thresholdNorm = (i + 1) * max_grad/n_bins;

	for (y = 4; y < height - 5; y++)
	{
		tmp = y * width;

        for (x = 4; x < width_4 - 4; x++)
        {
            norm = pModgrad[tmp + x];
            if (norm < thresholdNorm)
            {
                pAngles[tmp + x] = NOTDEF;
            }
        }
	}

		//按梯度大小连接
        for (i = n_bins - 1; i > 0 && range_l_s[i]==NULL; i--);
        start = range_l_s[i];
        end = range_l_e[i];
		if (start != NULL )
		{
			while (i > 0)
			{
				--i;
				if (range_l_s[i] != NULL )
				{
					end->next = range_l_s[i];
					end = range_l_e[i];
				}
			}
		}
		*ppList = start;
		//free
		sfree((void *) range_l_s );
		sfree((void *) range_l_e );
		sfree(binNum);
}


//功能:判断点(x,y)是否可以加入
//(x,y) 点坐标
//pAngles 图像每个点度数
//angle 已经扩展区域的平均角度
//width图像宽
static int Isaligned( short x, short y, short *pAngles,short angle,short width)
{
	short a;
	short b;
	a = pAngles[ x + y * width];
	if( a == NOTDEF ) return FALSE;
    b = a - angle;
    return(b > 335 || b < -335 || (b < 25 && b > -25));//度数差在阀值范围内
}
//功能:从某一点开始扩展找角度相似的点
//输入:
//(x,y)起点
//pAngles图像每个点的角度
//width height 宽高
//输入输出:
//pReg 相似的点集
//pRegSize  相似点的个数
//pRegAngle 相似点的平均度数  一开始时为(x,y)的度数
//pUsed   点是否用过了
void RegionGrow(short x, short y,short *pAngles, struct M_point *pReg,
	short *pRegSize,short *pRegAngle, UChar *pUsed,short width,short height,int sign)
{
	int tmp;
	int sumAngles = 0;
	short xx = 0, yy = 0, i = 0;
	short tolerate_x = 1, tolerate_y = 1;//判断是否为相似点的相邻范围
	short aRegSize = 1;
	short aRegAngle;
	// first point of the region 
	*pRegSize = 1;
	pReg[0].x = x;
	pReg[0].y = y;
	sumAngles = *pRegAngle = pAngles[x + y * width]; 
	aRegAngle = *pRegAngle;
	//
	if (sign == 1)
	{
		if (tabs(aRegAngle - 180) < 25 || (aRegAngle < 25 || aRegAngle > 335)) 
		{
			tolerate_y = 2;
		}
		else if (tabs(aRegAngle - 90) < 25 || tabs(aRegAngle - 270) < 25)
		{
			tolerate_x = 2;
		}
	}

	pUsed[x + y * width] = USED;
	// try neighbors as new region points 
	for (i = 0; i < aRegSize; i++)
	{
		for (yy = pReg[i].y - tolerate_y; yy <= pReg[i].y + tolerate_y; yy++)
		{
			tmp = yy*width;
			for (xx = pReg[i].x - tolerate_x; xx <= pReg[i].x + tolerate_x; xx++)
			{
				if (xx >= 0 && yy >= 0 && xx < width&& yy < height &&
					pUsed[xx+tmp] != USED &&
					Isaligned(xx, yy, pAngles, aRegAngle, width) 
					)
				{
					/* add point */
					pUsed[xx + tmp] = USED;
					pReg[aRegSize].x = xx;
					pReg[aRegSize].y = yy;
					++aRegSize;

					/* update region's angle */
					if (tabs(aRegAngle - pAngles[xx + tmp]) > 335)//在0度两侧
					{
						if (aRegAngle > pAngles[xx + tmp])
						{
							sumAngles = sumAngles + 360 + pAngles[xx + tmp];
						}
						else
						{
							sumAngles = sumAngles - 360 + pAngles[xx + tmp];
						}
					}
					else
					{
						sumAngles += pAngles[xx + tmp];
					}

					aRegSize = (aRegSize > 1023)?1023:aRegSize;
                    aRegSize = (aRegSize < 0)?0:aRegSize;
					aRegAngle = (sumAngles * exRegSize[aRegSize - 1]) >> REGRESIZE;
					if (aRegAngle > 360)
					{
						aRegAngle -= 360;
						sumAngles = (aRegAngle) * (aRegSize);
					}
				}
			}//for yy
		}//for xx
	}//for i
	*pRegSize = aRegSize;
	*pRegAngle = aRegAngle;
}
//功能:通过离散的点求直线
//输入:
//pReg  角度相似的连续的点
//pModgrad 图像梯度
//reg_size 点的个数
//width图像宽
//输入输出:
//pLine  返回直线信息

void LineFit(struct M_point *pReg, short reg_size, int *pModgrad, short angle, struct M_line *pLine, short width)
{
	struct M_double b = {0};
	short left = 1000, right = 0, up = 1000, down = 0;//要处理点的四个方向初值
	int i = 0;
	//
	struct M_point p_left = {0}, p_right = {0}, p_down = {0}, p_up = {0};//pReg区域的四个点
	//
	for (i = 0; i < reg_size; i++)//得到四个点
	{
		if (pReg[i].x < left)//最左边点
		{
			p_left.x = pReg[i].x;
			p_left.y = pReg[i].y;
			left = pReg[i].x;
		}
		if (pReg[i].x > right)//最右边点
		{
			p_right.x = pReg[i].x;
			p_right.y = pReg[i].y;
			right = pReg[i].x;
		}
		if (pReg[i].y < up)//最上边点
		{
			p_up.x = pReg[i].x;
			p_up.y = pReg[i].y;
			up = pReg[i].y;
		}
		if (pReg[i].y > down)//最下边点
		{
			p_down.x = pReg[i].x;
			p_down.y = pReg[i].y;
			down = pReg[i].y;
		}
	}	
	if (tabs(right - left) > tabs(down - up))//横线
	{

		pLine->x1 = p_left.x;
		pLine->y1 = p_left.y;
		pLine->x2 = p_right.x;
		pLine->y2 = p_right.y;
	}
	else//竖线
	{
		pLine->x1 = p_up.x;
		pLine->y1 = p_up.y;
		pLine->x2 = p_down.x;
		pLine->y2 = p_down.y;
	}
	pLine->x = pLine->x2-pLine->x1;
	pLine->y = pLine->y2-pLine->y1;
}

//功能:lsd算法检测直线
//输入:
//pData输入的灰度图像
//width height 宽高
//输入输出
//pLines  检测到的直线 1（1,2,3，4)  2(5,6,7,8) .....每四个点分别为直线的两点坐标 
//pLinesNum 直线的个数
//pRect 所有检测到的直线的矩形范围
void GetLines(UChar *pData,short width,short height,short *pLines,short *pLinesNum,LRect *pRect)
{
	int i = 0, j = 0;
	short n_bin = 1024;//
	struct coorlist *pListStart = NULL;
	struct coorlist *list_p = NULL;
	struct coorlist *list = NULL;
	struct M_point *pLinePoints = NULL;//记录可能组成直线的点
	short linePoints_size = 0;//可能组成直线点的数量
	int *modgrad = NULL;
	short *anglesP = NULL, reg_angle = 0;
	int allpoint_num = width * height;
	short reg_size = 0;//
	//int min_reg_size = 20;//相似角度点的个数 阀值
	int ls_count = 0;
	int tmp;
	UChar *used = NULL;
	struct M_point *reg = NULL;
	struct M_line line = {0};

	//
	//
	pRect->x1 = width;
	pRect->x2 = 0;
	pRect->y1 = height;
	pRect->y2 = 0;
	//calloc
	used = (UChar *) scalloc( allpoint_num,sizeof(UChar));
	for (i = 0; i < allpoint_num; i++)
	{
		used[i] = NOTUSED;
	}
//	memset(used, NOTUSED, sizeof(UChar) * allpoint_num);
	reg = (struct M_point *) scalloc( allpoint_num, sizeof(struct M_point) );
	modgrad = (int *) scalloc( allpoint_num, sizeof(int));
	anglesP = (short *) scalloc( allpoint_num, sizeof(short));
	list = (struct coorlist *) scalloc( allpoint_num, sizeof(struct coorlist));
	//pLinePoints = (struct M_point *) scalloc( allpoint_num, sizeof(struct M_point));
	//得到每个点的角度和梯度
	for (i = 0; i < allpoint_num; ++i)
	{
		anglesP[i] = NOTDEF;
	}
	GetAngleAndGradient( pData, width, height, &list_p, list, modgrad, anglesP, n_bin);
	//
	//根据梯度从大到小找相似的角度  根据点集得到直线
	pListStart = list_p;

	for (i = 0; i < allpoint_num; i++)
	{
		used[i] = NOTUSED;
	}

	ls_count = 0;
	list_p = pListStart;
	for (; list_p != NULL; list_p = list_p->next )
	{
		if (used[ list_p->x + list_p->y * width] == NOTUSED &&
			anglesP[ list_p->x + list_p->y * width ] != NOTDEF )
		{
			//找相似的角  扩张
			RegionGrow(list_p->x, list_p->y, anglesP, reg, &reg_size,&reg_angle, used, width,height,1);

			//从得到的点求得直线
			LineFit(reg, reg_size, modgrad,reg_angle, &line, width);
			//过滤
			if ((tabs(line.x2 - line.x1)</*tmax(width/10,30)*/10) && (tabs(line.y2 - line.y1)</*tmax(height/10,30)*/10))
			{
				continue;
			}
			if (ls_count >= MAX_LINE_NUM) 
			{
				continue;
			}
			//add line
			if (line.x1 > line.x2)
			{
				tmp = ls_count << 2;
				pLines[tmp] = line.x2;
				pLines[tmp + 1] = line.y2;
				pLines[tmp + 2] = line.x1;
				pLines[tmp + 3] = line.y1;
			}
			else
			{
				tmp = ls_count << 2;
				pLines[tmp] = line.x1;
				pLines[tmp + 1] = line.y1;
				pLines[tmp + 2] = line.x2;
				pLines[tmp + 3] = line.y2;
			}

			++ls_count;
			//
		}
	}
	*pLinesNum = ls_count;
	//free
	sfree(list);
	sfree(used);
	sfree(modgrad);
	sfree(reg);
	sfree(anglesP);
	sfree(pLinePoints);
}

