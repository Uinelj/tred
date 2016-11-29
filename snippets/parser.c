#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  return ret;
}


int main(int argc, char const *argv[]) {
  char sample_line[] = "T1>T2>T3>END";
  printf("%d", tokenize(sample_line));
  tokenize(sample_line);
  return 0;
}
