#ifndef __LEVEL_H__
#define __LEVEL_H__

#define LEVEL_ROW              9
#define LEVEL_COLUMN       9

int level1[LEVEL_ROW][LEVEL_COLUMN]={
	{1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,3,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,3,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0,1}
};
int level2[LEVEL_ROW][LEVEL_COLUMN]={
	{1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,3,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,3,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0,1}
};
int level3[LEVEL_ROW][LEVEL_COLUMN]={
	{1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,3,0,1,0,1},
	{0,0,0,0,2,0,0,0,0},
	{1,0,1,0,3,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0,1}
};
int level4[LEVEL_ROW][LEVEL_COLUMN]={
	{1,0,1,0,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,3,0,1,0,1,0,1},
	{0,0,2,0,0,0,0,0,0},
	{1,0,1,0,1,2,3,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,3,2,1,0,1,0,1},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0,1}
};

int level5[LEVEL_ROW][LEVEL_COLUMN]= {
			{1,0,1,0,1,0,1,0,1},
			{0,0,0,0,0,0,0,0,0},
			{1,0,3,0,1,0,1,0,1},
			{0,0,0,0,2,0,0,0,2},
			{1,0,1,0,1,0,1,0,3},
			{0,0,0,0,0,0,0,2,2},
			{1,0,1,2,3,0,1,0,1},
			{0,0,0,0,0,0,0,0,0},
			{1,0,1,0,1,0,1,0,1}
};
int level6[LEVEL_ROW][LEVEL_COLUMN]={
			{1,0,1,0,1,0,1,0,1},
			{0,0,0,0,0,0,0,0,0},
			{1,0,1,0,3,2,1,0,1},
			{0,0,2,0,0,0,0,0,0},
			{1,0,3,0,1,0,3,0,1},
			{0,0,0,0,0,0,2,0,0},
			{1,0,1,2,3,0,1,0,1},
			{0,0,0,0,0,0,0,0,0},
			{1,0,1,0,1,0,1,0,1}
};
int level7[LEVEL_ROW][LEVEL_COLUMN]={
			{1,0,1,0,1,0,1,0,1},
			{0,0,0,0,0,0,0,0,0},
			{1,0,3,0,1,2,3,0,1},
			{0,0,2,0,0,0,0,0,0},
			{1,0,1,0,3,0,1,0,1},
			{0,0,0,0,0,0,2,0,0},
			{1,2,3,2,1,0,3,0,1},
			{0,0,2,0,0,0,0,0,0},
			{1,0,1,0,1,0,1,0,1}
};
int level8[LEVEL_ROW][LEVEL_COLUMN]={
			{1,0,1,0,1,0,1,0,1},
			{0,0,0,0,0,0,0,0,0},
			{1,0,3,2,1,0,1,0,3},
			{2,0,0,0,0,0,0,0,2},
			{3,0,1,0,1,0,1,0,3},
			{0,0,0,0,0,0,0,0,0},
			{1,0,1,0,1,0,3,0,1},
			{0,2,0,0,0,0,0,0,0},
			{1,2,3,0,1,0,1,0,1}
};
int level9[LEVEL_ROW][LEVEL_COLUMN]={
			{1,0,1,0,1,0,1,0,1},
			{0,0,0,0,2,0,0,0,0},
			{3,0,3,0,1,0,1,0,1},
			{0,0,0,0,0,0,2,0,0},
			{1,2,3,0,1,0,3,0,1},
			{0,0,0,0,0,0,0,0,0},
			{1,0,1,2,3,2,1,0,1},
			{0,0,0,0,2,0,0,0,2},
			{1,0,1,0,1,0,1,0,3}
};
int level10[LEVEL_ROW][LEVEL_COLUMN]={
			{1,0,1,0,1,0,3,0,1},
			{0,0,2,0,0,0,0,0,0},
			{1,0,3,2,1,0,1,0,1},
			{0,0,2,0,0,0,0,0,0},
			{1,0,1,0,3,2,1,2,3},
			{0,0,0,0,0,0,0,0,0},
			{1,2,3,0,1,0,1,0,1},
			{0,0,2,0,0,0,0,0,0},
			{1,0,1,0,1,0,3,0,1}
};
int level11[LEVEL_ROW][LEVEL_COLUMN]={
			{1,0,1,0,3,0,1,0,1},
			{2,0,0,0,2,0,0,0,0},
			{3,0,1,0,1,0,1,0,3},
			{0,0,0,0,2,0,0,0,0},
			{1,0,1,0,3,2,1,0,1},
			{0,0,0,0,2,0,0,0,2},
			{3,2,1,0,1,0,1,2,3},
			{0,0,0,0,2,0,0,0,0},
			{1,0,1,0,3,0,1,0,1}
};
int level12[LEVEL_ROW][LEVEL_COLUMN]={
			{1,0,1,0,1,0,1,0,1},
			{0,0,0,0,0,0,0,0,0},
			{3,0,1,0,1,2,3,0,1},
			{0,0,0,0,0,0,0,0,0},
			{1,0,3,2,1,0,1,0,1},
			{0,0,2,0,2,0,0,0,0},
			{1,0,1,0,3,0,1,0,1},
			{0,0,0,0,0,0,2,0,0},
			{3,0,1,0,1,2,3,0,1}
};

#endif