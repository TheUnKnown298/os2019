# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define SIZE 2

typedef struct {
  char type;
  int amount;
  char unit;
} item;

item buffer[SIZE]; // queue to transfer package from productor to user
int first = 0;
int last = 0;

void produce(item *i) {
  while ((first + 1) % SIZE == last) {

  }
  memcpy(&buffer[first], i, sizeof(item));
  first = (first + 1) % SIZE;
  printf("Done producing value:--- first: %d last: %d\n", first, last);
}

item *consume() {
  item *i = malloc(sizeof(item));
  while (first == last) {

  }
  memcpy(i, &buffer[last], sizeof(item));
  last = (last + 1) % SIZE;
  printf("Done --- first: %d last: %d\n",first,last);

  return i;
}

item* addItem(char type, int amount, char unit){
  item *i = malloc(sizeof(item));
  i->type = type;
  i->amount = amount;
  i->unit = unit;

  return i;
}

void *threadFunction (void *param){
  produce(addItem('3','1','2'));
  produce(addItem('4','0','7'));
  produce(addItem('7','3','2'));
}

void *use_thread (void *param){
  consume();
  consume();
}

int main(){
  pthread_t fac_tid;
  pthread_t user_tid;

  pthread_create(&fac_tid, NULL, threadFunction, NULL);
  pthread_create(&user_tid, NULL, use_thread, NULL);

  pthread_join(fac_tid, NULL);
  pthread_join(user_tid, NULL);

  return 0;
}