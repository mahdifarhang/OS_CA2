#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


#include <fcntl.h>
#include <sys/stat.h>

#define PIPENAME "temp"

using namespace std;


vector<string> ls(string path)
{
    DIR *mydir;
    vector<string> files;
    struct dirent *myfile;
    mydir = opendir(&path[0]);
    while ((myfile = readdir(mydir)) != NULL) {
        if (myfile->d_name[0] == '.')
            continue;
        else if (myfile->d_type == DT_DIR) {
            vector <string> recursive_files = ls(path + myfile->d_name + "/");
            files.insert(files.end(), recursive_files.begin(), recursive_files.end());
        } else
            files.push_back(path + myfile->d_name + "\n");
    }
    closedir(mydir);
    return files;
}


string int_to_string(const int& input)
{
    ostringstream my_custom_streamstring;
    my_custom_streamstring << input;
    return my_custom_streamstring.str();
}



int main()
{
	vector<string> paths = ls("databases/");
	int pfd;
	int fd[2];
    int judge,status;
    int l;
	string sensor;
	cin >> sensor;
    sensor += "\n";
	mkfifo(PIPENAME,0666);
	if((judge = fork()) == 0)
	{
		mkfifo(PIPENAME,0666);
		pfd = open(PIPENAME, O_RDONLY);
        dup2(pfd, 0);
        close (pfd);
		execv("judge", (char**) 0);
	}
  pfd = open(PIPENAME, O_WRONLY);
  l = paths.size();
	string path_size = int_to_string(l) + "\n";
	write(pfd, path_size.c_str(), path_size.size());
	for (int i = 0; i < l; i++)
	{
		pipe(fd);
		if (fork() == 0)
		{
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            pfd = open(PIPENAME, O_WRONLY);
            dup2(pfd, 1);
            close (pfd);
			execv("worker", (char**) 0);
		}
		else
		{
			close(fd[0]);
			write(fd[1], paths[i].c_str(), paths[i].size());
			write(fd[1], sensor.c_str(), sensor.size());
		}
	}
}
