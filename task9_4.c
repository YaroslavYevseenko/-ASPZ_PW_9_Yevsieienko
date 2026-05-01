#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int result;

    printf("=== whoami ===\n");
    result = system("whoami");

    if (result == -1) {
        perror("whoami");
    }

    printf("\n=== id ===\n");
    result = system("id");

    if (result == -1) {
        perror("id");
    }

    return 0;
}
