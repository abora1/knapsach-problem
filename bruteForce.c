#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main(int argc,char *args[])
{
int size=0;
int capacity=0;
int profit [size];
int weight [size];
char *token;
char *tok;
int max_profit;
int max_weight;
FILE *f = fopen(args[1], "r"); 
char line[256];
int s=0;
while(fgets(line,sizeof(line),f)!=NULL)
{
	s++;
	if(s==1)
	{
		size=atoi(line);
	}
	else if(s==2)
	{
		capacity=atoi(line);
	}
	else if(s==3)
	{
		int j=0;
		token=strtok(line,",");
		while(token!=NULL)
		{
			profit[j]=atoi(token);
			j++;
			token=strtok(NULL,",");
		}
	}
	else if(s==4)
	{
		int j=0;
		tok=strtok(line,",");
		while(tok!=NULL)
		{
		weight[j]=atoi(tok);
		j++;
		tok=strtok(NULL,",");
		}
	}
	else
	{
		continue;
	}
}
fclose(f);
int i=0,j,isSelected=1,maxWt,maxProfit;
	int iter=pow(2.0,size);
	int result=0;
	for(i=0;i<iter;i++) {
		isSelected=1;
		maxProfit=0;
		maxWt=0;
		int temp1=i;
		for(j=0;j<size;j++){
			if(temp1%2==1){
				maxWt+=weight[j];
				maxProfit+= profit[j];
			}temp1=temp1/2;
		}
		if( maxWt <= capacity && maxProfit>result)
		{
			max_profit=maxProfit;
			max_weight=maxWt;
			result=i;
		} 
}
printf("result is%d\n",max_profit);
printf("weight is%d\n",max_weight);
for(int q=0;q<size;q++)
{
	if(result%2==1)
	{
		printf("%d \t %d\n",profit[q],weight[q]);
	}result=result/2;
}
return 0;
}
