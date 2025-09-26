#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("books.csv", "r");
    char line[200];

    if (file == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}


