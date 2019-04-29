
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//to store number of characters
int size=0;

//to store total bits
int tolat_bits=0;

// Structure for the node
struct Node
{
    char chars;
    int freq;
    struct Node *left, *right;
};

//array of nodes
struct Node* nodes[50];

//inputs
struct Entry
{
	char character;
	int frequency;
};

int code[100];
struct Entry input[20];

//funstion to read file
void readFile(char* file)
{

	char buffer[1024];

	//Open file
	FILE *f = fopen(file, "r");
	int line =1;

	//Taking inputs from the csv file
	while(fgets(buffer,1024,f)!=NULL)
	{

		if(line==1)
		{
			int temp=0;
			char *token=strtok(buffer,", ");//converting a line into tokens
			while(token!=NULL)
			{
				char *tempr=token;
				//storing input characters
				strcpy(&input[temp].character, tempr);
				temp++;
				token=strtok(NULL,", ");
			}

		}
		else if(line==2)
		{

			int temp=0;
			char *token=strtok(buffer,", ");//converting a line into tokens
				while(token!=NULL)
				{

					int c=atoi(token);
					//storing input frequency foe respective character
					input[temp].frequency=c;
					temp++;
					token=strtok(NULL,", ");
				}

				//total no of characters
				size=temp;
		}

		line++;
	}
	//close the file
	fclose(f);
}


//This function takes an array of nodes and sorts them in ascending order
void sort(struct Node* nodes[50] )
{

	for (int i = 0; i < size; ++i)
	    {
	        for (int j = i + 1; j < size; ++j)
	        {
	        	//comparing consecutive nodes frequency
	            if (nodes[i]->freq > nodes[j]->freq)
	            {
	            	//if previous mode frequency is greater than the freq of next one
	            	//then swap those nodes in the array
	            	struct Node** a= &nodes[i];
					struct Node** b= &nodes[j];

					struct Node* t = *a;
					*a = *b;
					*b = t;
	            }
	        }
	    }
}

void decode(struct Node *lastNode,int code[], int pos)
{

	//if the node has another child left node then consider the edge as 0
	if(lastNode->left!=NULL)
	{
		code[pos] = 0;
		decode(lastNode->left,code,pos+1);

	}

	//if the node has another child right node then con; sider the edge as 1
	if(lastNode->right!=NULL)
	{
		code[pos] = 1;
		decode(lastNode->right,code,pos+1);

	}

	//if the node does not have any left or right child node then print the code for it
	if((lastNode->left==NULL)&& (lastNode->right==NULL))
	{
		 printf("code for %c : ", lastNode->chars);

		 for (int i = 0; i < pos; ++i)
		 {
			 printf("%d", code[i]);

		 }

	    //finding total bits
	    tolat_bits=tolat_bits+(pos*(lastNode->freq));
	    printf("\n");
	}
}

//This function removes two nodes with min frequency
//Creates an intermediate node with frequency equal to addition of two min frequencies
//and inserts this new node into the array of nodes untill only one node is left
void operations(struct Node* nodes[50])
{

	while(size!=1)
	{
		//1st min
		struct Node *leftnode= nodes[0];
		nodes[0]= nodes[size - 1];
		size--;
		sort(nodes);

		//2nd min
		struct Node *rightnode= nodes[0];
		nodes[0]= nodes[size - 1];
		size--;
		sort(nodes);

		//creating new node
		struct Node *newnode=(struct Node*)malloc(sizeof(struct Node));;
		newnode->chars='*';
		newnode->freq=leftnode->freq + rightnode->freq;
		newnode->left=leftnode;
		newnode->right=rightnode;
		size++;
		//adding the new node into the array of nodes
		nodes[size - 1]=newnode;
		sort(nodes);

	}

	//storing the last node
	struct Node *lastNode= nodes[0];

	//Calling function to decode and print
	decode(lastNode,code,0);

}


//This function takes giver characters as nodes
//and stores these nodes in an array of nodes
void Huffman(struct Entry arr[])
{

	//adding new nodes to array of nodes
	for (int i = 0; i < size; ++i)
	{
		//allocating space
		struct Node* initialNode= (struct Node*)malloc(sizeof(struct Node));

		initialNode->chars = arr[i].character;
		initialNode->freq = arr[i].frequency;
		initialNode->left = NULL;
		initialNode->right = NULL;

		nodes[i]=initialNode;

	}

	//Calling function to arrange all the nodes in the array in ascending order with their respective frequencies
	sort(nodes);

    //Calling this function to find intermediate nodes by adding frequencies of two min freq nodes
	operations(nodes);
}


void main(int argc, char* args[])
{
	//read the input file
	readFile(args[1]);

	//Function for Huffman coding
	Huffman(input);

	//print total Number of bits
    printf("Total Bits: %d\n",tolat_bits);

}
