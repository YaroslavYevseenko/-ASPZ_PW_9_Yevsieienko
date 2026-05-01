#include <stdio.h>
#include <stdlib.h>

int test_read(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }

    fclose(file);
    return 1;
}

int test_write(const char *filename) {
    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        return 0;
    }

    fprintf(file, "Test write\n");
    fclose(file);
    return 1;
}

void check_access(const char *description, const char *filename) {
    printf("\n%s\n", description);
    printf("Read:  %s\n", test_read(filename) ? "yes" : "no");
    printf("Write: %s\n", test_write(filename) ? "yes" : "no");
}

int main(void) {
    const char *filename = "temp_test_file.txt";
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    fprintf(file, "Temporary file created by regular user\n");
    fclose(file);

    printf("Temporary file created: %s\n", filename);

    system("ls -l temp_test_file.txt");

    check_access("Initial access", filename);

    system("sudo chown root:root temp_test_file.txt");
    system("sudo chmod 600 temp_test_file.txt");
    system("ls -l temp_test_file.txt");
    check_access("Owner root, permissions 600", filename);

    system("sudo chmod 644 temp_test_file.txt");
    system("ls -l temp_test_file.txt");
    check_access("Owner root, permissions 644", filename);

    system("sudo chmod 666 temp_test_file.txt");
    system("ls -l temp_test_file.txt");
    check_access("Owner root, permissions 666", filename);

    system("sudo chmod 400 temp_test_file.txt");
    system("ls -l temp_test_file.txt");
    check_access("Owner root, permissions 400", filename);

    system("sudo chmod 000 temp_test_file.txt");
    system("ls -l temp_test_file.txt");
    check_access("Owner root, permissions 000", filename);

    system("sudo rm temp_test_file.txt");

    return 0;
}
