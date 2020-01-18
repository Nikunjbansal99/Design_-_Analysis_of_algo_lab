#include <stdio.h> 
#include <stdlib.h> 
#define MAX_TREE_HT 100 

struct QueueNode 
{ 
	char data; 
	unsigned freq; 
	struct QueueNode *left, *right; 
}; 

struct Queue 
{ 
	int front, rear; 
	int capacity; 
	struct QueueNode **array; 
}; 

struct QueueNode* newNode(char data, unsigned freq) 
{ 
	struct QueueNode* temp = 
	(struct QueueNode*) malloc(sizeof(struct QueueNode)); 
	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 
	return temp; 
} 

struct Queue* createQueue(int capacity) 
{ 
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
	queue->front = queue->rear = -1; 
	queue->capacity = capacity; 
	queue->array = 
	(struct QueueNode**) malloc(queue->capacity * sizeof(struct QueueNode*)); 
	return queue; 
} 
 
int isSizeOne(struct Queue* queue) 
{ 
	return queue->front == queue->rear && queue->front != -1; 
} 

int isEmpty(struct Queue* queue) 
{ 
	return queue->front == -1; 
} 

int isFull(struct Queue* queue) 
{ 
	return queue->rear == queue->capacity - 1; 
} 

void enQueue(struct Queue* queue, struct QueueNode* item) 
{ 
	if (isFull(queue)) 
		return; 
	queue->array[++queue->rear] = item; 
	if (queue->front == -1) 
		++queue->front; 
} 

struct QueueNode* deQueue(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return NULL; 
	struct QueueNode* temp = queue->array[queue->front]; 
	if (queue->front == queue->rear) 
		queue->front = queue->rear = -1; 
	else
		++queue->front; 
	return temp; 
} 

struct QueueNode* getFront(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return NULL; 
	return queue->array[queue->front]; 
} 


struct QueueNode* EXTRACT-MIN(struct Queue* firstQueue, struct Queue* secondQueue) 
{ 
	if (isEmpty(firstQueue)) 
		return deQueue(secondQueue); 

	if (isEmpty(secondQueue)) 
		return deQueue(firstQueue); 

	if (getFront(firstQueue)->freq < getFront(secondQueue)->freq) 
		return deQueue(firstQueue); 

	return deQueue(secondQueue); 
} 

int isLeaf(struct QueueNode* root) 
{ 
	return !(root->left) && !(root->right) ; 
} 

void printArr(int arr[], int n) 
{ 
	int i; 
	for (i = 0; i < n; ++i) 
		printf("%d", arr[i]); 
	printf("\n"); 
} 

struct QueueNode* buildHuffmanTree(char data[], int freq[], int size) 
{ 
	struct QueueNode *left, *right, *top; 

	
	struct Queue* firstQueue = createQueue(size); 
	struct Queue* secondQueue = createQueue(size); 

	for (int i = 0; i < size; ++i) 
		enQueue(firstQueue, newNode(data[i], freq[i])); 

	while (!(isEmpty(firstQueue) && isSizeOne(secondQueue))) 
	{ 
		left = EXTRACT-MIN(firstQueue, secondQueue); 
		right = EXTRACT-MIN(firstQueue, secondQueue); 

		top = newNode('$' , left->freq + right->freq); 
		top->left = left; 
		top->right = right; 
		enQueue(secondQueue, top); 
	} 

	return deQueue(secondQueue); 
} 


void printCodes(struct QueueNode* root, int arr[], int top) 
{ 
	if (root->left) 
	{ 
		arr[top] = 0; 
		printCodes(root->left, arr, top + 1); 
	} 

	if (root->right) 
	{ 
		arr[top] = 1; 
		printCodes(root->right, arr, top + 1); 
	} 
	
	if (isLeaf(root)) 
	{ 
		printf("%c: ", root->data); 
		printArr(arr, top); 
	} 
} 

void HuffmanCodes(char data[], int freq[], int size) 
{ 
struct QueueNode* root = buildHuffmanTree(data, freq, size); 

int arr[MAX_TREE_HT], top = 0; 
printCodes(root, arr, top); 
} 
 
int main() 
{ 
	char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'}; 
	int freq[] = {5, 9, 12, 13, 16, 45}; 
	int size = sizeof(arr)/sizeof(arr[0]); 
	HuffmanCodes(arr, freq, size); 
	return 0; 
} 
