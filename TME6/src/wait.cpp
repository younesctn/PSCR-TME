#include <sys/wait.h>
#include <iostream>
#include <unistd.h>

int wait_till_pid(pid_t pid)
{
    pid_t pid_fils;
    while (true)
    {
        pid_fils = wait(nullptr);
        if (pid_fils == -1 || pid_fils == pid)
        {
            return pid_fils;
        }
    }
}

int wait_till_pid(pid_t pid, int sec)
{
    static bool timeout;
    timeout = false;
    signal(SIGALRM, [](int)
           { std::cout << "received SIGALRM" << std::endl; timeout =
true; });
    signal(SIGCHLD, [](int)
           { std::cout << "received SIGCHLD" << std::endl; });
    alarm(sec);
    sigset_t set;
    sigfillset(&set);
    sigdelset(&set, SIGALRM);
    sigdelset(&set, SIGCHLD);
    while (true)
    {
        std::cout << "waiting..." << std::endl;
        sigsuspend(&set);
        if (timeout)
        {
            std::cout << "Alarm wins" << std::endl;
            return -1;
        }
        else
        {
            pid_t p = wait(nullptr);
            std::cout << "wait answered " << p << std::endl;
            if (p == pid)
            {
                alarm(0);
            }
            if (p == -1 || p == pid)
            {
                return p;
            }
        }
    }
}
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // si on met plus que le timeout il doit mourir
        sleep(5);
    }
    else
    {
        signal(SIGINT, [](int) {});
        pid_t res = wait_till_pid(pid, 3);
        std::cout << "wait gave :" << res << std::endl;
    }
}