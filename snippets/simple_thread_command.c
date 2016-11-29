#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#include "../main.c"
#include "parser.c"

#define NBTHREADS 3

sem_t ready;
pthread_t cur_work;
void *work(void *arg) {
  printf("\t\e[34m%d\033[0m Is it my turn ? It's %d turn\n", pthread_self(), cur_work);
    while(cur_work != pthread_self()){}
    printf("\t\e[34m%d\033[0m waiting for sem\n", pthread_self());
    sem_wait(&ready);
    printf("\t\e[34m%d\033[0m sem ready. Is it my turn ? It's %d turn\n", pthread_self(), cur_work);
    if(cur_work == pthread_self()) {
      printf("\t\e[34m%d\033[0m It's my turn. Working.\n", pthread_self());
      sleep(1);
      printf("\t\e[34m%d\033[0m My work is done. Unlocking mutex\n\n", pthread_self());
      sem_post(&ready);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {

  int i;
  Node threadset = load("./tredfile.txt");
  int thread_number = threadset->val;

  Queue thread_queue = malloc(sizeof(Queue));
  pthread_t first_thread;
  sem_init(&ready, 0, 0);

  for(i=0; i<thread_number; i++) {
    printf("Creating thread %d\n", i);
    pthread_t tmp;
    if(pthread_create(&tmp, NULL, work, NULL)) {
      fprintf(stderr, "Error creating thread\n");
      return 1;
    }
    thread_queue = enqueue(thread_queue, tmp);
  }
  thread_queue = dequeue(thread_queue);

  sem_post(&ready);

  while(!empty(thread_queue)) {
    printf("\nThread queue :\n");
    printqueue(thread_queue);

    cur_work = top(thread_queue);
    printf("Next thread to work : %d\n\n", top(thread_queue));
    if(pthread_join(top(thread_queue), NULL)) {
      fprintf(stderr, "Error joining thread\n");
      return 2;
    }
    //sem_post(&ready);
    printf("Dequeueing thread\n");
    thread_queue = dequeue(thread_queue);

  }

  return 0;
}
