#include "fork_exec_wait_error_codes.h"

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// start cmd.exe 
//
int main(int argc, char *argv[], char **env)
{

  // *** *** fork the child process *** ***
  //
  // fork - fork (i.e., fission) this process, yielding 
  //    P_NOWAIT - run asynchronously, enable wait on completion
  //    see https://msdn.microsoft.com/en-us/library/wweek9sc.aspx
  // 
  pid_t childProcess_pid = fork();

  if (childProcess_pid == -1) {
    cerr << "fork failed: " << forkErrorCodes[errno] << endl;
    exit(1); 
  }
  
  // *** *** manage child process *** ***
  //
  if (childProcess_pid == 0) {
    //execute the cat command on a text file named output.txt in the same directory
    execle("/bin/cat", "cat", "output.txt", NULL, env);    // try to become the shell; should go no further if successful
    cerr << "exec failed: " << execErrorCodes[errno] << endl;
    exit(2);    
  } 

  // *** manage parent process ****
  //
  cout << "child process " << childProcess_pid << " created" 
       << "\n\n Programmer: Nicholas Bowers\n Class: CSCI 4727 Operating Systems" << endl;
	   
  //code to halt execution of parent process
  int i;
  cin >> i;
	   	   
  //Using SIG_IGN to disable SIGCHILD
  //This is to not allow the child process to Zombie
  if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
  {
	 cerr << "sigaction failed: " << sigactionErrorCodes[errno] << endl;
	 exit(3);
  }
	   
  //create sigaction structure, set flags, handle child process
  struct sigaction s;
  s.sa_flags = SA_NOCLDWAIT;
  if(sigaction(SIGCHLD, &s, 0) == -1)
  {
     cerr << "sigaction failed: " << sigactionErrorCodes[errno] << endl;
	 exit(4);
  }
  
  //message annoucing the parent process is exiting
  cout << "\n\nParent process is exiting... " << endl;
  exit(0);
  
}