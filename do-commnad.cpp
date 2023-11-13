#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/times.h>
#include <sys/wait.h>
using namespace std;

void do_command(char **argv)
{
    struct tms tmsstart, tmsend;
    clock_t start, end;

    start = times(&tmsstart);

    pid_t pid = fork();

    if (pid = -1)
    {
        cerr << "Error: fork failed" << endl;
        exit(1);
    }
    else if (pid == 0)
    {
        int result = execvp(argv[0], argv);

        if (result == -1)
        {
            cerr << "Error: command not found" << endl;
            exit(errno);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        tmsend = times(&tmsend);

        double duration = (double)(tmsend - tmsstart) / sysconf(_SC_CLK_TCK);
    }

    end = times(&tmsend);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Error: command not found" << endl;
        exit(1);
    }

    char **new_argv = new char *[argc];

    for (int i = 1; i < argc; i++)
    {
        new_argv[i - 1] = argv[i];
    }
    new_argv[argc - 1] = nullptr;

    do_command(new_argv);

    delete[] new_argv;
    return 0;
}
