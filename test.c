#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[256];

    fp = popen("ls -l", "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    fgets(buffer, sizeof(buffer), fp);
    pclose(fp);

    fp = popen("wc", "w");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    fprintf(fp, buffer);


    pclose(fp);

    return 0;
}