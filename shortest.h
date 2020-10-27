#include <stdio.h>
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>
void show(cJSON*root,int s[2],int view[25][25],int abs_position[3],int * if_15)//position[0]为x坐标position[1]为y坐标
{
	int i=0;
	int j=0;
	cJSON *arrayItem = cJSON_GetObjectItem(root,"view"); //获取这个对象成员
	cJSON *x = cJSON_GetObjectItem(root,"x");
	cJSON *y = cJSON_GetObjectItem(root,"y");
	abs_position[0]=x->valueint;
	abs_position[1]=y->valueint;
	for(i=0;i<cJSON_GetArraySize(arrayItem);i++)
	{
		cJSON *object = cJSON_GetArrayItem(arrayItem,i);
		for(j=0;j<cJSON_GetArraySize(object);j++)
		{
			cJSON *item = cJSON_GetArrayItem(object,j);
			view[i][j]=item->valueint;
			printf("%d    ",view[i][j]);	
		}
		printf("\n");
	
	}
	s[0]=i;
	s[1]=j;
	printf("s[0]:%d          s[1]:%d\n",i,j);
	if(i==15)
	(*if_15)=24;
	

}
void relative_position(int abs_position[3],int rel_position[3],int if_15)//rel_position值为数组中坐标 从0开始
{
	if(abs_position[0]<5&&abs_position[1]<5)
		{
			rel_position[0]=abs_position[0];
			rel_position[1]=abs_position[1];
		}
	if(abs_position[0]<5&&abs_position[1]>=5)
		{
			rel_position[0]=abs_position[0];
			rel_position[1]=4;
		}
	if(abs_position[0]>= 5&&abs_position[1]<5)
		{
			rel_position[1]=abs_position[1];
			rel_position[0]=4;
		}
	if(abs_position[0]>=5&&abs_position[1]>=5)
		{
			rel_position[0]=4;
			rel_position[1]=4;
		}
	if(if_15)
		{
			if(abs_position[0]<=7&&abs_position[1]<=7)
				{
					rel_position[0]=abs_position[0];
					rel_position[1]=abs_position[1];
				}
			if(abs_position[0]<=7&&abs_position[1]>7)
				{
					rel_position[0]=abs_position[0];
					rel_position[1]=7;
				}
			if(abs_position[0]> 7&&abs_position[1]<=7)
				{
					rel_position[1]=abs_position[1];
					rel_position[0]=7;
				}
			if(abs_position[0]>7&&abs_position[1]>7)
				{
					rel_position[0]=7;
					rel_position[1]=7;
				}
		}		

	
}
int if_positive(int x,int all_things[16])
{
	if(all_things[x]>0)
		return 1;
	else
		return 0;
}
char* get_operate(int view[25][25],int square[2],int rel_position[3],int all_things[16],int *if_15,int *if_speed)//suqure[0]为行数，suare[1]为列数，获得if_15,if_speed,
{
printf("15:%d           speed:%d\n",*if_15,*if_speed);

	if(*if_speed)
	{
		if(if_positive(view[rel_position[0]][rel_position[1]+1],all_things)&&if_positive(view[rel_position[0]][rel_position[1]+2],all_things))
		{
		if(view[rel_position[0]][rel_position[1]+1]==3||view[rel_position[0]][rel_position[1]+2]==3)
			*if_15=24;
		if(view[rel_position[0]][rel_position[1]+1]==2||view[rel_position[0]][rel_position[1]+2]==2)
			*if_speed=24;
			printf("d\n");
			return "d";
		}
		if(if_positive(view[rel_position[0]+1][rel_position[1]],all_things)||if_positive(view[rel_position[0]+2][rel_position[1]],all_things))
		{
			if(view[rel_position[0]+1][rel_position[1]]==3||view[rel_position[0]+2][rel_position[1]]==3)
			*if_15=24;
			if(view[rel_position[0]+1][rel_position[1]]==2||view[rel_position[0]+2][rel_position[1]]==2)
			*if_speed=24;
			printf("s\n");			
			return "s";
		}
		if(if_positive(view[rel_position[0]][rel_position[1]-1],all_things)||if_positive(view[rel_position[0]][rel_position[1]-2],all_things))
		{
		if(view[rel_position[0]][rel_position[1]-1]==3||view[rel_position[0]][rel_position[1]-2]==3)
			*if_15=24;
		if(view[rel_position[0]][rel_position[1]-1]==2||view[rel_position[0]][rel_position[1]-1]==2)
			*if_speed=24;
			printf("a\n");
			return "a";
			}
		if(if_positive(view[rel_position[0]-1][rel_position[1]],all_things)||if_positive(view[rel_position[0]-2][rel_position[1]],all_things))
			{
			if(view[rel_position[0]-1][rel_position[1]]==3||view[rel_position[0]-2][rel_position[1]]==3)
				*if_15=24;
			if(view[rel_position[0]-1][rel_position[1]]==2||view[rel_position[0]-2][rel_position[1]]==2)
				*if_speed=24;
				printf("w\n");
				return "w";
			}
	//////////////////////////////////////////////
			if(*if_15)
		*if_15--;
	if(*if_speed)
		*if_speed--;	
	}
	else{
		if(if_positive(view[rel_position[0]][rel_position[1]+1],all_things))
		{
		if(view[rel_position[0]][rel_position[1]+1]==3)
			*if_15=24;
		if(view[rel_position[0]][rel_position[1]+1]==2)
			*if_speed=24;
			printf("d\n");
			return "d";
		}
		if(if_positive(view[rel_position[0]+1][rel_position[1]],all_things))
		{
			if(view[rel_position[0]+1][rel_position[1]]==3)
			*if_15=24;
			if(view[rel_position[0]+1][rel_position[1]]==2)
			*if_speed=24;
			printf("s");
			return "s";
		}
		if(if_positive(view[rel_position[0]][rel_position[1]-1],all_things))
		{
		if(view[rel_position[0]][rel_position[1]-1]==3)
			*if_15=24;
		if(view[rel_position[0]][rel_position[1]-1]==2)
			*if_speed=24;
			printf("a\n");
			return "a";
			}
		if(if_positive(view[rel_position[0]-1][rel_position[1]],all_things))
			{
			if(view[rel_position[0]-1][rel_position[1]]==3)
				*if_15=24;
			if(view[rel_position[0]-1][rel_position[1]]==2)
				*if_speed=24;
				printf("w\n");
				return "w";
			}
	/////////////////////////////////////////////////////
		if(*if_15)
		*if_15--;
	if(*if_speed)
		*if_speed--;	
	}	
	return "d";
}
	
