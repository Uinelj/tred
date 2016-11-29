#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

/*Faire une fonction qui prend un thread ou une fonction de travail classique, qui execute sa callback et qui le kill pas mais le fait boucler sur un sem_wait.*/

/*A réfléchir : une struct avec un thread et sa mutex associée ?*/

typedef struct Tred {
  pthread_t thread;
  sem_t mutex;
  void *cb;
} *Tred;

void *work(void *arg) {
  printf("working\n");
  sleep(2);
  printf("done\n");
}

Tred new_tred(void *cb) {
  pthread_t thread;
  sem_t mutex;
  Tred new = malloc(sizeof(Tred));
  new->thread = pthread_create(&thread, NULL, cb, NULL);
  sem_init(&mutex, 0, 0);
  new->mutex = mutex;
  new->cb = cb;

  return new;
}

void tred_work(Tred tred) {

  pthread_join(tred->thread, NULL);
}
int main(int argc, char const *argv[]) {
  Tred test = new_tred(&work);
  tred_work(test);
  work(NULL);
  return 0;
}
