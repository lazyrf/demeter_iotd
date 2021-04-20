#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void daemonize(void)
{
    pid_t pid;
    int fd;

    pid = fork();
    if (pid > 0) {
        // 1. Stop parent process
        exit(EXIT_SUCCESS);
    } else if (pid < 0) {
        perror("[-] fork()");
        exit(EXIT_FAILURE);
    }

    // 2. Create new session
    pid = setsid();
    if (pid == -1) {
        perror("[-] setsid()");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "[+] Daemonize successfully\n");

    // 3. Change the working directory
    // 4. Change the umask

    // 5. Close or redirect the STDIN, STDOUT, STDERR
    close(STDIN_FILENO);
    fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
        perror("[-] open()");
        exit(EXIT_FAILURE);
    }
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    while (1);
}

int main(int argc, char *argv[])
{
    int opt;
    int daemonize_flag;

    daemonize_flag = 0;

    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
            case 'd':
                daemonize_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-d]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
                break;
        }
    }

    printf("[+] %s\n", (daemonize_flag) ? "Run as daemon." : "Run as foreground process.");

    if (daemonize_flag) {
        daemonize();
    }

    exit(EXIT_SUCCESS);
}
