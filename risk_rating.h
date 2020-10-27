void risk_rating(int view[25][25],int square[3])
{
for(int i=0;i<square[0];i++)
{
int count=0;
	for(int j=0;j<square[1];j++)
	{
	if(view[i][j]==5||view[i][j]==6||view[i][j]==3)
	{
	if(view[i][j+1]==1)
		count++;
	if(view[i][j-1]==1)
		count++;
	if(view[i+1][j]==1)
		count++;
	if(view[i-1][j]==1)
		count++;
	if(count>2)
	view[i][j]=1;
	count=0;	
	}
	}
	}
	}
