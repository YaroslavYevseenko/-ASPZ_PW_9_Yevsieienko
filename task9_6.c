#include <stdio.h>
#include <stdlib.h>

void show_permissions(const char *path) {
    char command[256];

    printf("\n=== ls -l %s ===\n", path);
    snprintf(command, sizeof(command), "ls -l %s | head -10", path);
    system(command);
}

void test_access(const char *path) {
    char command[512];

    printf("\n=== Access test for %s ===\n", path);

    snprintf(command, sizeof(command), "test -r %s && echo 'Read: yes' || echo 'Read: no'", path);
    system(command);

    snprintf(command, sizeof(command), "test -w %s && echo 'Write: yes' || echo 'Write: no'", path);
    system(command);

    snprintf(command, sizeof(command), "test -x %s && echo 'Execute: yes' || echo 'Execute: no'", path);
    system(command);
}

int main(void) {
    const char *home = getenv("HOME");

    if (home == NULL) {
        printf("HOME not found\n");
        return 1;
    }

    show_permissions(home);
    show_permissions("/usr/bin");
    show_permissions("/etc");

    test_access(home);
    test_access("/usr/bin/ls");
    test_access("/etc/passwd");
    test_access("/etc/shadow");

    printf("\n=== Trying to read files ===\n");
    system("head -3 /etc/passwd");
    system("head -3 /etc/shadow");

    printf("\n=== Trying to write files ===\n");
    system("echo 'test' >> /etc/passwd");
    system("echo 'test' >> /usr/bin/ls");

    printf("\n=== Trying to execute files ===\n");
    system("/usr/bin/ls > /dev/null && echo '/usr/bin/ls executed' || echo 'cannot execute /usr/bin/ls'");
    system("/etc/passwd > /dev/null 2>&1 && echo '/etc/passwd executed' || echo 'cannot execute /etc/passwd'");

    return 0;
}
