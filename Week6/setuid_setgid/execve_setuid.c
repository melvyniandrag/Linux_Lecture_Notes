#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void)
{
    int current_uid = getuid();
    printf("My UID is: %d. My GID is: %d\n", current_uid, getgid());
    char* const argv[1] = { "usr/bin/id" };
    execve("/usr/bin/id", argv, NULL);
    if (setuid(0))
    {
        perror("setuid");
        return 1;
    }
    printf("My UID is: %d. My GID is: %d\n", getuid(), getgid());


    //system("apt-get update");
    execve("/usr/bin/id", argv, NULL);

    //Time to drop back to regular user privileges
    setuid(current_uid);
    printf("My UID is: %d. My GID is: %d\n", getuid(), getgid());
    execve("/usr/bin/id", argv, NULL);
    return 0;
}
