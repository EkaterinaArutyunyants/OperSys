#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void declare_process(pid_t & ref_pid, int & ref_numofproc)
{
	ref_numofproc*=2;

	if(ref_pid>0) //this is executed in the parent process, because the id of the child is returned to the parent by "fork"
	{
	cout << "There are "<< ref_numofproc << " processes at this level, according to process "<< getpid() << "\n" << flush;
	}else //this is executed in the child process, because "fork" call returns id 0 to the child process
	{
	
	cout << "There are "<< ref_numofproc << " processes at this level, according to process "<< getpid() << " and its parent "<< getppid() << "\n"<< flush;
	}
}

int main()
{
	int num_of_processes = 1;	
    int num_of_fork_levels = 2;
    int status = 0; //used by "wait" call to check child statuses
    pid_t pid, wpid; //used to store return values from system calls "fork" and "wait"


	while(num_of_fork_levels>0)
    {
        num_of_fork_levels--; //reduce the number of fork levels by 1
        
        pid = fork();
        if(-1==pid) //no child was created
        {
        perror("fork");
        exit(EXIT_FAILURE);
        }
        
        declare_process(pid,num_of_processes);
    }

	while((wpid=wait(&status))>0);	
	
    if(pid==0) //this is a child process
	{
		char str1[] = "/usr/bin/ps";
                char str2[] = "-f";
		char str3[] = "--forest";
		char * ls_args[] = { str1, str2, str3, NULL};
	   
		//execute the program
		  execv(   ls_args[0],     ls_args);
	}
	
    

    return 0;
}
