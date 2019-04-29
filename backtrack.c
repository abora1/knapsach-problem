#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void BackTracking(int k,int cp,int cw);
int Bound(int cp,int cw,int k);
int promising(int x,int cw1,int cp1);
int items;
int capacity;
//use structure to store the profit and weight of a item.
struct data{   
int profit;
int weights;
};
struct data s[10];
int final_profit;
bool include[20],bestset[20]; //temporary arrays used to store the solutions arrray items
int final_wt;
int main(int argc,char *args[])
{
char *token;
char *tok;

FILE *f = fopen(args[1], "r"); 
char line[256];
int i=0;
//File Reader same as dynamic.c
while(fgets(line,sizeof(line),f)!=NULL)
{
	i++;
	if(i==1)
	{
		items=atoi(line);
	}
	else if(i==2)
	{
		capacity=atoi(line);
	}
	else if(i==3)
	{
		int j=1;
		token=strtok(line,",");
		while(token!=NULL)
		{
			s[j].profit=atoi(token);
			j++;
			token=strtok(NULL,",");
		}
	}
	else if(i==4)
	{
		int j=1;
		tok=strtok(line,",");
		while(tok!=NULL)
		{
		s[j].weights=atoi(tok);
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
BackTracking(0,0,0);   //calling the backtracking function with starting profit,weight and item as 0.
printf("\ntotal profit is :%d",final_profit);
printf("\ntotal weight is :%d",final_wt);
printf("\n***********************************************************\n");
printf("items in knapsack are:\n");
printf("PROFIT \t WEIGHTS\n");
int q=0;
while(q<=items)
{
	if(bestset[q])
	{
		printf("%d \t %d",s[q].profit,s[q].weights);
		printf("\n");	
	}
q++;
}
return 0;
}

void BackTracking(int k,int cp,int cw)
{
if(cw <= capacity && (cp>final_profit)) //checks if the value is not crossing the capacity and is greater than current profit.
{
	final_profit=cp;
	  final_wt=cw;
	int i=0;
	while(i<=items)
	{
	bestset[i]=include[i];   //include those values in the bestset i.e solution.
	i++;
	}
}

float x=promising(k,cw,cp);  //check if traversing item k will result in a better profit or not
if((x>0) && (k+1<=items))  //if there are more items and item is promising.
	{
		include[k+1]=true;
		BackTracking(k+1,cp+s[k+1].profit,cw+s[k+1].weights); //calling the backtracking taking the next item in the solution
		include[k+1]=false;
		BackTracking(k+1,cp,cw); //calling backtracking with excluding the next element.
	}
}
int Bound(int cp,int cw,int k)//Bound calculation
{
 int ub,c,i;
 ub=cp;
 c=cw;
 i=k;
 while(i <= items && c<=capacity) //if the current weight is less than capacity then keep on adding weights
 {
	if(c+s[i].weights<=c)
	{
  	c=c+s[i].weights;
	ub=ub+s[i].profit;
	}
  else{
	float z=0;	//if the current weight increases beyond capacity then use fractional knapsack to compute bound.
	z=(capacity-c);
	c=capacity;
	ub=ub+((s[i].profit/s[i].weights)*z);
	
}
  i++;
 }
 return ub;
}
int promising(int x,int cw1,int cp1)//checks if the item is promising or not i.e travesing the item further can lead to better solution or not.
{
if(cw1>=capacity)
{
return 0;
}
else
{
	int b=Bound(cp1,cw1,x); //checks the bound with that item and if bound>=final_profit then item k is promising.
	if(b>=final_profit)
	{
		return 1;
	}
	
}
return 0;
}
