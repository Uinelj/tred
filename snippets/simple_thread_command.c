#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include "../main.c"

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
  int i=0;
  pthread_t work_thread[NBTHREADS];

  for(i; i<NBTHREADS; i++) {
    printf("Creating thread %d\n", i);
    if(pthread_create(&work_thread[i], NULL, work, NULL)) {
      fprintf(stderr, "Error creating thread\n");
      return 1;
    }
  }

  sem_init(&ready, 0, 0);

  Queue thread_queue = malloc(sizeof(Queue));
  thread_queue->val = work_thread[0];

  for(i=1; i<NBTHREADS; i++) {
    thread_queue = enqueue(thread_queue, work_thread[i]);

  }

  sem_post(&ready);
  while(!empty(thread_queue)) {
    printf("Thread queue :\n");
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
  //while(1){}
  return 0;
}
