#include <stdio.h>
#include <math.h>
#include <malloc.h>
typedef struct Node{//迷宫节点
	int X;
	int Y;
	int value;
	struct Node* before;
}Node;
typedef struct Cite{//位置队列
	int X;
	int Y;
}Cite; 

//入队 
void putInQuene(int a,int b,Cite quene[625],int*head,int *tail){
	quene[(*tail)].Y = a;
	quene[(*tail)].X = b;
	(*tail)++;
	(*tail) = (*tail)%625;
	if((*tail) == (*head))printf("Quene is full!");
}
//出队 
Cite getOutQuene(Cite quene[625],int*head,int *tail){
	int re = (*head);
	(*head)++;
	(*head) = (*head)%625;
	return quene[re];
}
int findway(int y,int x,Node a[25][25],char operate_bfs[100],int rel_position[3]){
	if(a[y][x].before==NULL)
	{
	return 1;
	}
	if(!(y==rel_position[1]&&x==rel_position[0]))
	{
	 findway(a[y][x].before->Y,a[y][x].before->X,a,operate_bfs, rel_position);
	}

	if(a[y][x].before->X == x&&a[y][x].before->Y == y-1) 
	strcat(operate_bfs,"s");
	else if(a[y][x].before->X == x&&a[y][x].before->Y == y+1) 
	strcat(operate_bfs,"w");
	else if(a[y][x].before->Y == y&&a[y][x].before->X == x-1) 
	strcat(operate_bfs,"d");
    	else if(a[y][x].before->Y == y&&a[y][x].before->X == x+1) 
    	strcat(operate_bfs,"a");
    	return 1;

}
int bfs(int view[25][25],int rel_position[3],int all_things[16],int s[3],char operate_bfs[100])
{
	Node a[25][25];
	for(int i=0;i<25;i++)
		for(int j=0;j<25;j++)
			a[i][j].value=1;
	Cite quene[625];
	int head = 0;//队首
	int tail = 0;//队尾
	int i,j;
		for(i=0;i<s[0];i++){
			for(j=0;j<s[1];j++){
				if(all_things[view[i][j]])
				a[i][j].value=0;
				else
				a[i][j].value=1;				
			    	a[i][j].before = NULL;
			    	a[i][j].Y = i;
			    	a[i][j].X = j;

			}
		}
		printf("//////////////////////////////////////////////////////\n");
		for(i=0;i<s[0];i++){
			for(j=0;j<s[1];j++){
				printf("%d   ",a[i][j].value);				

			}
		printf("\n");	
		}
		putInQuene(rel_position[0],rel_position[1],quene,&head,&tail);
		while(head != tail){

			Cite temp = getOutQuene(quene,&head,&tail);
			i = temp.Y;
			j = temp.X;
			printf("i:%d             j:%d\n",i,j);
			if(view[i][j]==5||view[i][j]==6)
			break;

			
        if(i==rel_position[0]&&j==rel_position[1]){
			if(a[i][j+1].value == 0&&a[i][j+1].before == NULL)//右移 
			    {
			    	a[i][j+1].before = &a[i][j]; 
			    	putInQuene(i,j+1,quene,&head,&tail);
				}
    		if(a[i+1][j].value == 0&&a[i+1][j].before == NULL)//下移 
			    {
			    	a[i+1][j].before = &a[i][j];
			    	putInQuene(i+1,j,quene,&head,&tail);
				}
			if(a[i][j-1].value == 0&&a[i][j-1].before == NULL)//左移 
			    {
			        a[i][j-1].before = &a[i][j]; 
					putInQuene(i,j-1,quene,&head,&tail);	
				}

			if(a[i-1][j].value == 0&&a[i-1][j].before == NULL)//上移 
			    {
			    	a[i-1][j].before = &a[i][j];
			    	putInQuene(i-1,j,quene,&head,&tail);
				}
		if(head==tail)
		return -1;

		}
	    else if(a[i][j].before->Y == i&&a[i][j].before->X == j-1){//右移到达 （不可左移） 
	    printf("右移到达\n");		   
			if(a[i+1][j].value == 0&&a[i+1][j].before == NULL)//下移 
			    {

			    	a[i+1][j].before = &a[i][j];
			    	putInQuene(i+1,j,quene,&head,&tail);
				}
			if(a[i][j+1].value == 0&&a[i][j+1].before == NULL)//右移 
			    {

			    	a[i][j+1].before = &a[i][j]; 
			    	putInQuene(i,j+1,quene,&head,&tail);
				}
			if(a[i-1][j].value == 0&&a[i-1][j].before == NULL)//上移 
			    {
			    	a[i-1][j].before = &a[i][j];
			    	putInQuene(i-1,j,quene,&head,&tail);
				}	

		}		
	    else if(a[i][j].before->X == j&&a[i][j].before->Y == i-1){//下移到达 （不可上移） 
	    printf("下移到达\n");		   
			if(a[i+1][j].value == 0&&a[i+1][j].before == NULL)//下移 
			    {

			    	a[i+1][j].before = &a[i][j];
			    	putInQuene(i+1,j,quene,&head,&tail);
				}
			if(a[i][j-1].value == 0&&a[i][j-1].before == NULL)//左移 
			    {
			        a[i][j-1].before = &a[i][j]; 
				putInQuene(i,j-1,quene,&head,&tail);	
				}
			if(a[i][j+1].value == 0&&a[i][j+1].before == NULL)//右移 
			    {
			    	a[i][j+1].before = &a[i][j]; 
			    	putInQuene(i,j+1,quene,&head,&tail);
				}		

		}

		

    	else if(a[i][j].before->Y == i&&a[i][j].before->X == j+1){//左移到达 （不可右移） 
    	printf("左移到达\n");		  
			if(a[i+1][j].value == 0&&a[i+1][j].before == NULL)//下移 
			    {
			    	a[i+1][j].before = &a[i][j];
			    	putInQuene(i+1,j,quene,&head,&tail);
				}
			if(a[i][j-1].value == 0&&a[i][j-1].before == NULL)//左移 
			    {
			        a[i][j-1].before = &a[i][j]; 
					putInQuene(i,j-1,quene,&head,&tail);	
				}
			if(a[i-1][j].value == 0&&a[i-1][j].before == NULL)//上移 
			    {
			    	a[i-1][j].before = &a[i][j];
			    	putInQuene(i-1,j,quene,&head,&tail);
				}	
    	}    
		else if(a[i][j].before->X == j&&a[i][j].before->Y == i+1){//上移到达 （不可下移） 
			printf("上移到达\n");	
			if(a[i][j-1].value == 0&&a[i][j-1].before == NULL)//左移 
			    {
			        a[i][j-1].before = &a[i][j]; 
					putInQuene(i,j-1,quene,&head,&tail);	
				}
			if(a[i][j+1].value == 0&&a[i][j+1].before == NULL)//右移 
			    {
			    	a[i][j+1].before = &a[i][j]; 
			    	putInQuene(i,j+1,quene,&head,&tail);
				}
			if(a[i-1][j].value == 0&&a[i-1][j].before == NULL)//上移 
			    {
			    	a[i-1][j].before = &a[i][j];
			    	putInQuene(i-1,j,quene,&head,&tail);
				}
		}		

		}
printf("i:%d             j:%d\n",i,j);
	findway(i,j,a,operate_bfs,rel_position);
	return 1;

}


