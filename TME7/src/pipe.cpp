#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>

int main(int argc, char **argv) {
    int fd1[2]; // fd1[0] = read, fd1[1] = write
    pid_t pid_fils, pid_fils2;

    // On part du principe qu'il y a que deux commandes
    // pour stocker les arguments
    char** cmd1 = new char*[argc];
    char** cmd2 = new char*[argc];

    // ici on sépare les |
    int i = 1;
    for (; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            i++;
            break;
        } else {
            cmd1[i - 1] = strdup(argv[i]);
        }
    }

    int j = 0;
    for (; i < argc; j++, i++) {
        cmd2[j] = strdup(argv[i]);
    }
    cmd2[j] = nullptr;

    // creation de deux pipes
    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(1);
    }

    if ((pid_fils = fork()) == -1) {
        perror("fork");
        exit(2);
    }

    if (pid_fils == 0) {
        dup2(fd1[1], STDOUT_FILENO); // On redirige la sortie du pipe vers l'entrée standard du fils
        close(fd1[0]);
        close(fd1[1]); 
        if (execv(cmd1[0], cmd1) == -1) {
            perror("execv");
            exit(3);
        }
    }

    if ((pid_fils2 = fork()) == -1) {
        perror("fork");
        exit(2);
    }

    if (pid_fils2 == 0) {
        dup2(fd1[0], STDIN_FILENO); // On redirige l'entrée du pipe vers la sortie standard du père
        close(fd1[0]);
        close(fd1[1]);
        if (execv(cmd2[0], cmd2) == -1) {
            perror("execv");
            exit(3);
        }
    }

    close(fd1[0]);
    close(fd1[1]);

    wait(NULL);

    // Free allocated memory
    for (int i = 0; cmd1[i] != nullptr; i++) {
        free(cmd1[i]);
    }
    delete[] cmd1;

    for (int i = 0; cmd2[i] != nullptr; i++) {
        free(cmd2[i]);
    }
    delete[] cmd2;

    return 0;
}
