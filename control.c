#include "control.h"

void crea() {//create
  printf("Creation initiated\n");
  int semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);//creates
  if (semid == -1) {//error handling
    printf("error %d: %s\n", errno, strerror(errno));
    semid = semget(KEY, 1, 0);
    printf("semctl returned: %d\n", semctl(semid, 0, GETVAL, 0));
  }
  else {
    union semun us;
    us.val = 1;
    semctl(semid, 0, SETVAL, us);
  }
  //create shared mem and file
  char * data;
  char input[3];
  int shmid = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
  data = shmat(shmid, 0, 0);
  file = fopen("telephone.txt", "w+");
  int fildes = open(file,O_CREAT | O_TRUNC | O_RDWR, 0644);
  printf("Creation complete\n");
}
void remv() {//remove
  printf("Current story:\n");
  //reading story
  int fildes = open(file,O_RDONLY);
  char buf[SEG_SIZE];
  read(fildes,buf,SEG_SIZE);
  printf("%s\n",buf);
  close(fildes);

  printf("Removal initiated\n");
  int semid = semget(KEY,1,0);
  semctl(semid,IPC_RMID,0);//sema removed
  //rem shared mem
  int shmid = shmget(KEY,1,0);
  shmctl(shmid,IPC_RMID,0);
  printf("Removal complete\n");
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
