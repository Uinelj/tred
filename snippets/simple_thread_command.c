#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

sem_t ready;

void *work(void *arg) {
  sem_wait(&ready);
  printf("working...\n");
  sleep(1);
  printf("task done.\n");
  sem_post(&ready);
  return NULL;
}
int main(int argc, char const *argv[]) {

  pthread_t work_thread;
  pthread_t work_thread2;

  sem_init(&ready, 0, 0);
  printf("Creating thread 1\n");
  if(pthread_create(&work_thread, NULL, work, NULL)) {
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }

  printf("Creating thread 2\n");
  if(pthread_create(&work_thread2, NULL, work, NULL)) {
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }

  sleep(4);
  sem_post(&ready); //launching thread 1

  if(pthread_join(work_thread, NULL)) {
    fprintf(stderr, "Error joining thread\n");
    return 2;
  }
  printf("Thread 1 done\n");

  if(pthread_join(work_thread2, NULL)) {
    fprintf(stderr, "Error joining thread\n");
    return 2;
  }
  printf("Thread 2 done\n");

  return 0;
}
