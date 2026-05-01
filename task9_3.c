#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    FILE *file;

    file = fopen("user_file.txt", "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    fprintf(file, "File created by regular user\n");
    fclose(file);

    printf("File created by regular user.\n");

    system("sudo cp user_file.txt ~/root_copy.txt");
    system("sudo chown root:root ~/root_copy.txt");
    system("sudo chmod 644 ~/root_copy.txt");

    printf("File copied by root to home directory.\n");

    file = fopen("root_copy.txt", "a");
    if (file == NULL) {
        perror("Trying to modify file");
    } else {
        fprintf(file, "Trying to modify this file\n");
        fclose(file);
        printf("File modified successfully.\n");
    }

    if (remove("root_copy.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("Trying to delete file");
    }

    return 0;
}
