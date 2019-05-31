#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10

typedef struct {
  char type;
  int amount;
  char unit;
} item;

item buffer[SIZE];  // queue to transfer package from productor to user
int first = 0;
int last = 0;
sem_t mutex;

void produce(item *i) {
  while ((first + 1) % SIZE == last) {

  }
  memcpy(&buffer[first], i, sizeof(item));
  first = (first + 1) % SIZE;
  printf("Done producing; Log value:--- first: %d last: %d\n", first, last);
}

item *consume() {
  item *i = malloc(sizeof(item));
  while (first == last) {

  }
  memcpy(i, &buffer[last], sizeof(item));
  last = (last + 1) % SIZE;
  printf("Done selling; Log value --- first: %d last: %d\n",first,last);

  return i;
}

item* addItem(char type, int amount, char unit){
  item *i = malloc(sizeof(item));
  i->type = type;
  i->amount = amount;
  i->unit = unit;

  return i;
}

void *produce_thread (void *param){
  sem_wait(&mutex);
  produce(addItem('3','1','2'));
  produce(addItem('4','0','7'));
  produce(addItem('7','3','2'));
  sem_post(&mutex);
}

void *use_thread (void *param){
  sem_wait(&mutex);
  consume();
  consume();
  sem_post(&mutex);
}

int main(){
  sem_init(&mutex, 0, 1);
  pthread_t fac_tid, user_tid;

  pthread_create(&fac_tid, NULL, produce_thread, NULL);
  pthread_create(&user_tid, NULL, use_thread, NULL);

  pthread_join(fac_tid, NULL);
  pthread_join(user_tid, NULL);

  sem_destroy(&mutex);

  return 0;
}