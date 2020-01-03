#include "control.h"

int main() {
  int semid = semget(KEY,1,0);
  int shmid = shmget(KEY,1,0);
  struct sembuf sbs;
  sbs.sem_num = 0;
  sbs.sem_op = -1;
  //input
  char *lastln = shmat(shmid,0,0);
  char *newln;
  printf("Last line added: %s\n", lastln);
  printf("Enter new text to be added:\n");
  fgets(newln,SEG_SIZE,stdin);
  int fildes = open(file,O_RDWR|O_APPEND,0644);
  write(fildes,newln,sizeof(newln)/sizeof(char));
  close(fildes);
  strcpy(lastln,newln);

  sbs.sem_op = 1;
  semop(semid,&sbs,1);
  shmdt(shmid);
  return 0;
}
