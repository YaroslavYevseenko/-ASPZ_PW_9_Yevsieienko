#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    FILE *fp;
    char line[512];
    char username[128];
    char current_user[128];
    int uid;
    int found = 0;

    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    if (getlogin_r(current_user, sizeof(current_user)) != 0) {
        strcpy(current_user, "");
    }

    printf("Current user: %s\n\n", current_user);
    printf("Regular users found:\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token;
        char copy[512];

        strcpy(copy, line);

        token = strtok(copy, ":");
        if (token == NULL) {
            continue;
        }

        strcpy(username, token);

        strtok(NULL, ":");

        token = strtok(NULL, ":");
        if (token == NULL) {
            continue;
        }

        uid = atoi(token);

        if (uid >= 1000 && strcmp(username, current_user) != 0) {
            printf("User: %s, UID: %d\n", username, uid);
            found = 1;
        }
    }

    if (!found) {
        printf("No other regular users found.\n");
    }

    pclose(fp);
    return 0;
}
