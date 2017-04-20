//TwoPipesTwoChildren
//Anthony Inga
//4/7/2017
//CS 3376

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  int status;
  int childpid;

  char *cat_args[] = {"ls", "-ltr", NULL};
  char *grep_args[] = {"grep", "3340", NULL};
  char *wc_args[] = {"wc", "-l", NULL};

  //create two pipes to send the output of "ls" process to "grep" process and to "wc" process
  int pipe1[2];
  int pipe2[2];
  pipe(pipe1);
  pipe(pipe2);
  int pid_t pid_A, pid_B;

  //first child
  if(!(pid_A = fork()))
  {
    close(pipe1[0]);
    dup2(pipe1[1], 1); //redirect standard output to pipe1
    close(pipe1[1]);
    execvp(*cat_args, cat_args);
    exit(0);
  }

  //second child
  else if(!(pid_B = fork()))
  {
    close(pipe1[1]);
    dup2(pipe1[0], 0); //redirect standard input to pipe1
    close(pipe1[0]);
    close(pipe2[0]);
    dup2(pipe2[1], 1); //edirect standard output to pipe2
    close(pipe2[1]);
    execvp(*grep_args, grep_args);
  }

  //parent
  else
  {
    close(pipe1[1]);
    close(pipe1[0]);
    close(pipe2[1]);
    dup2(pipe2[0], 0); //redirect standard input to pipe2
    close(pipe2[0]);
    execvp(*wc_args, wc_args);
  }

  close(pipe2[1]);
  close(pipe2[0]);
  return(0);
}
