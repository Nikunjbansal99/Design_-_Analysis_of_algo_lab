#include<stdio.h> 

int max(int a, int b) 
{
	return (a > b)? a : b; 
} 

int knapSack(int W, int wt[], int val[], int n) 
{ 
	if (n == 0 || W == 0) 
		return 0; 
	if (wt[n-1] > W) 
		return knapSack(W, wt, val, n-1); 
	else 
		return max( val[n-1] + knapSack(W-wt[n-1], wt, val, n-1),knapSack(W, wt, val, n-1)); 
} 

int main() 
{
	int n,W;
	printf("Enter the no. of PRODUCTS: ");
	scanf("%d",&n);
	int val[n],wt[n];
	for(k=0;k<=n;k++)
	{
		printf("PRODUCT %d VALUE: ",k);
		scanf("%d",&val[k]);
	}
	for(k=0;k<=n;k++)
	{
		printf("PRODUCT %d WEIGHT: ",k);
		scanf("%d",&wt[k]);
	}
	printf("Enter Basket WEIGHT: ");
	scanf("%d",&W);

	printf("%d", knapSack(W, wt, val, n)); 
	return 0; 
} 
