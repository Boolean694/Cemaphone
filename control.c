#include "control.h"

void crea() {//create
  printf("Creation has initiated\n");
  int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);//creates
  if (semd == -1) {//error handling
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(KEY, 1, 0);
    semctl(semd, 0, GETVAL, 0);
    printf("semctl returned: %d\n", v);
  }
  else {
    union semun us;
    us.val = 1;
    semctl(semd, 0, SETVAL, us);
  }
  //create shared mem and file
  int shmd;
  char * data;
  char input[3];
  shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
  data = shmat(shmd, 0, 0);
  FILE *f = fopen("telephone.txt", w);
  printf("Creation complete\n");
}
void remv() {//remove

}
void view() {//view

}

int main(int argc, char **argv) {
  if(strcmp(argv[1],"-c")) {
    crea();
  }
  else if(strcmp(argv[1],"-r")) {
    remv();
  }
  else if(strcmp(argv[1],"-v")) {
    view();
  }
  else {//no args
    printf("no command line args provided! please provide either -c, -r, -v");
  }
}
