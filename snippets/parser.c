#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct node {
  int val;
  struct node *nxt;
} *Node;


void print_node(Node node) {
  while(node != NULL) {
    printf("%d->", node->val);
    node = node->nxt;
  }
  printf("END");
}

/*
  Returns a linked list of the number of threads to spawn for each line.
*/
Node load(char *path) {

  Node threadset = malloc(sizeof(Node));
  threadset->val = 0;
  threadset->nxt = NULL;

  Node cur = threadset;

    FILE *tredfile;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    tredfile = fopen(path, "r");

    if(tredfile != NULL) {
      while ((read = getline(&line, &len, tredfile)) != -1) {
        cur->val = tokenize(line);
        cur->nxt = malloc(sizeof(Node));

        cur = cur->nxt;
        //printf("%s", line);
        //printf("%d\n", tokenize(line));
      }
    }
    return threadset;
}

/*Shoud tokenize properly and return future thread identifiers.
  Currently returns the number of threads.
  I'm aware that there's no error handling.
*/
int tokenize(char *str){

  int ret=0;
  char *tokens;
  tokens = strtok(str, "T>END");

  while(tokens != NULL) {
    ret++;
    tokens = strtok(NULL, "T>END");
  }

  return ret-1; //strips newline
}


int main(int argc, char const *argv[]) {
  char sample_line[] = "T1>T2>T3>END";
  //printf("%d", tokenize(sample_line));
  //tokenize(sample_line);
  Node threadset = load("./tredfile.txt");

  print_node(threadset);
  return 0;
}
