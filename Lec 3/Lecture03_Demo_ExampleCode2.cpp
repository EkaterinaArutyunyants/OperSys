#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void declare_process(pid_t & ref_pid, int & ref_numofproc)
{

	if(ref_pid>0) //this is executed in the parent process, because the id of the child is returned to the parent by "fork"
	{
	    if(ref_numofproc==1)
	    {
		cout << "There is "<< ref_numofproc << " process at this level, according to parent process "<<getpid()<<" with terminated child process "<<ref_pid<<"\n"<<flush;
	    }else
	    {
		cout << "There are "<< ref_numofproc << " processes at this level, according to parent process "<<getpid()<< " with terminated child process "<<ref_pid<<"\n"<<flush;
	    }
	}else //this is executed in the child process, because "fork" call returns id 0 to the child process
	{
	    ref_numofproc+=1;
	    cout << "There are "<< ref_numofproc << " processes at this level, according to child process "<< getpid() << " with parent "<< getppid() << "\n"<< flush;
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

        if(pid>0){while((wpid=wait(&status))>0);} //if this is the parent process, do not proceed further untill all children have terminated

        declare_process(pid,num_of_processes);
    }	
	
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
