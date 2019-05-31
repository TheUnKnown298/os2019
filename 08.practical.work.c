#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define BUFFER_SIZE 10

typedef struct {
    char type; // 0=fried chicken, 1=French fries
    int amount; // pieces or weight
    char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0 ;

void produce(item *i) {
    while ((first + 1) % BUFFER_SIZE == last) {
        // do nothing -- no free buffer item
    }
    memcpy(&buffer[first], i, sizeof(item));
    first = (first + 1) % BUFFER_SIZE;
    printf("first = %d    last = %d\n", first, last);
}

item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last) {
        // do nothing -- nothing to consume
    }
    memcpy(i, &buffer[last], sizeof(item));
    last = (last + 1) % BUFFER_SIZE;
    printf("first = %d    last = %d\n", first, last);
    return i;
}

item *initItem(char type, int amount, char unit) {
	item *i = malloc(sizeof(item));
	i->amount=amount;
	i->type=type;
	i->unit=unit;
	return i;
}

void *produceThread(void* param) {
	item *i1=initItem('2',7,'4');
    item *i2=initItem('5',1,'3');
    item *i3=initItem('6',4,'6');
    produce(i1);
    produce(i2);
    produce(i3);
	pthread_exit(NULL);
}

void *consumeThread(void* param) {
	consume();
	consume();
	pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    printf("Thread for produce function\n");
    pthread_create(&tid,NULL,produceThread,NULL);
    pthread_join(tid,NULL);
    printf("Thread for consume function\n");
    pthread_create(&tid,NULL,consumeThread,NULL);
    pthread_exit(NULL);
}