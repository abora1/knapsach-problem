#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int items;
int KnapSize;
int totalweight=0;
int profit [10];	// Array for storing profits
int weights[10];	//storing weights
int main(int argc,char *args[])
{

char *token;
char *tok;

FILE *f = fopen(args[1], "r"); 
char line[256];
int i=0;
//file is read and each line is split to store different values.
while(fgets(line,sizeof(line),f)!=NULL) 
{
	i++;
	if(i==1) //1st line stores total items
	{
		items=atoi(line);
	}
	else if(i==2) //2nd line stores weights
	{
		KnapSize=atoi(line);
	}
	else if(i==3) //3rd line stores profits
	{
		int j=1;
		token=strtok(line,",");
		while(token!=NULL)
		{
			profit[j]=atoi(token);
			j++;
			token=strtok(NULL,",");
		}
	}
	else if(i==4) //4th line stores weights
	{
		int j=1;
		tok=strtok(line,",");
		while(tok!=NULL)
		{
		weights[j]=atoi(tok);
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
int v[items+1][KnapSize+1];  //initializing a temporary array to store values.
for(int s=0;s<=KnapSize;s++) //setting the first row as null
{
	v[0][s]=0;
}

for(int x=1;x<=items;x++)
{
v[x][0]=0;		//setting first column as null
	for(int y=1;y<=KnapSize;y++)
	{
		if(weights[x]<=y && (v[x-1][y-weights[x]]+profit[x])>v[x-1][y])
		{
			v[x][y]=v[x-1][y-weights[x]]+profit[x]; //value is achieved if item x is included
		}
		else
		{
			v[x][y]=v[x-1][y];	//value is achieved if item x is not included.
		}
	}

}


int w=KnapSize;
printf("\n************************Items in the knapsack*******************************\n");
printf("PROFIT \t WEIGHT\n");
//for printing the elements and calculating total weights and profit
for(int x=items;x>=0;x--)
{
	if (v[x][w] == v[x - 1][w])	//checks every row value with the previous row value if they are same it continues.
	 {
		continue;	
	  }
 	else  					//otherwise we have found a item which is included in knapsack.
	{
		if(profit[x]!=0)
		{
			printf("%d \t %d\n",profit[x],weights[x]);
		}
		totalweight+=weights[x];  	//total weight is added.
		w -= weights[x];
	}
}


printf("\ntotal weight: %d",totalweight);
printf("\ntotal profit: %d\n",v[items][KnapSize]); //the array index[items][KnapSize] gives the last profit obtained.

return 0;
}


