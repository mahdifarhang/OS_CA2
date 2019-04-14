#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>



using namespace std;



int main()
{
	vector<string> paths;
	int fd[2];





	for (int i = 0; i < paths.size(); i++)
	{
		pipe(fd);
		if (fork() == 0)
		{
            dup2(fd[0],0);
            close(fd[0]);
            close(fd[1]);
            pfd = open("ttt.txt", O_WRONLY);
            dup2(pfd,1);
            close (pfd);
			execv("worker.out", (char**) 0);
		}
		else
		{
			close(fd[0]);
			write(fd[1],paths[i].c_str(),paths[i].size()+1);
			write(fd[1],,);
		}
	}
}

        if(fork()==0){
            dup2(fd[0],0);
            close(fd[0]);
            close(fd[1]);
            pfd = open(PIPENAME, O_WRONLY);
            dup2(pfd,1);
            close (pfd);
            execv("worker",(char **)0);
        }else{
            workers[i] = fd[1];
            close(fd[0]);
        }