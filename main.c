#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h> 

typedef struct Queue {
	int val;
	struct Queue *nxt;	
} *Queue;


int top(Queue queue) {
	return queue->val;
}

int bot(Queue queue) {
	Queue cur = queue;
	while(cur->nxt != NULL) {
		cur = cur->nxt;
	}
	return cur->val;
}
Queue dequeue(Queue queue) {
	if(queue == NULL) { 
		return NULL;	
	}
	return queue->nxt;	
}
Queue enqueue(Queue queue, int val) {
	
	Queue cur = queue;
	Queue new = malloc(sizeof(Queue));

	new->val = val;
	new->nxt = NULL;

	while(cur->nxt != NULL) {
		cur = cur->nxt;	
	}

	cur->nxt = new;
	
	return queue;
}
void printqueue(Queue queue) {
	while(queue != NULL) { 
		printf("%d->", queue->val);
		queue = queue->nxt;	
	}
	printf("END\n");
}
int main() {
	Queue test = malloc(sizeof(Queue));
	test->val = 1;
	test = enqueue(test, 2);
	test = enqueue(test, 3);
	test = enqueue(test, 4);
	test = enqueue(test, 5);
	test = enqueue(test, 6);
	printf("TOP:%d\n", top(test));
	printf("BOT:%d\n", bot(test));
	printqueue(test);
	test = dequeue(test);
	printqueue(test);
	test = enqueue(test, 1);
	test = enqueue(test, 2);
	printf("TOP:%d\n", top(test));
	printf("BOT:%d\n", bot(test));
	printqueue(test);
	return 0;
}
