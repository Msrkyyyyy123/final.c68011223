#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_menu() {
    printf("\n=== เมนูจัดการหนังสือ ===\n");
    printf("1. แสดงรายการหนังสือ\n");
    printf("2. เพิ่มหนังสือ\n");
    printf("3. ค้นหาหนังสือ\n");
    printf("4. อัปเดตราคา\n");
    printf("5. ลบหนังสือ\n");
    printf("0. ออกโปรแกรม\n");
    printf("กรุณาเลือกเมนู: ");
}

void show_all_books() {
    FILE *file = fopen("books.csv", "r");  
    char line[200];

    if (file == NULL) {
        printf("ไม่พบไฟล์ books.csv\n");
        return;
    }

    printf("\n=== รายการหนังสือทั้งหมด ===\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  
    }

    fclose(file);
}

void add_book() {

    FILE *file = fopen("books.csv", "a"); 
    if (file == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    char booktitle[100], author[100], publisher[100], price[10];

    printf("กรอกชื่อหนังสือ: ");
    scanf(" %[^\n]", booktitle);  

    printf("กรอกชื่อผู้แต่ง: ");
    scanf(" %[^\n]", author);

    printf("กรอกสำนักพิมพ์: ");
    scanf(" %[^\n]", publisher);

    printf("กรอกราคา: ");
    scanf(" %[^\n]", price);

    fprintf(file, "%s,%s,%s,%s\n", booktitle, author, publisher, price);

    fclose(file);
    printf("เพิ่มหนังสือใหม่เรียบร้อย!\n");
}

void search_book() {
    FILE *file = fopen("books.csv", "r");
    if (file == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    char keyword[100];
    char line[200];
    int found = 0;

    printf("กรอกชื่อหนังสือหรือผู้แต่งที่ต้องการค้นหา: ");
    scanf(" %[^\n]", keyword);  

    printf("\n=== ผลการค้นหา \"%s\" ===\n", keyword);

    while (fgets(line, sizeof(line), file)) {
        char title[100], author[100], publisher[100], price[20];

        if (sscanf(line, "%99[^,],%99[^,],%99[^,],%19[^\n]",
                   title, author, publisher, price) == 4) {
            
            if (strstr(title, keyword) != NULL || strstr(author, keyword) != NULL) {
                printf("ชื่อหนังสือ: %s | ผู้แต่ง: %s | สำนักพิมพ์: %s | ราคา: %s\n",
                       title, author, publisher, price);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("ไม่พบหนังสือหรือผู้แต่งที่ค้นหา\n");
    }

    fclose(file);
}

void delete_book() {
    FILE *file = fopen("books.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (file == NULL || temp == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    char booktitle[100];
    char line[200];
    int found = 0;

    printf("กรอกชื่อหนังสือที่ต้องการลบ: ");
    scanf(" %[^\n]", booktitle);

    while (fgets(line, sizeof(line), file)) {
        char title[100], author[100], publisher[100], price[20];

        if (sscanf(line, "%99[^,],%99[^,],%99[^,],%19[^\n]", title, author, publisher, price) == 4) {
            if (strcmp(title, booktitle) != 0) {
                fprintf(temp, "%s,%s,%s,%s\n", title, author, publisher, price);
            } else {
                found = 1; 
            }
        }
    }

    fclose(file);
    fclose(temp);

    remove("books.csv");           
    rename("temp.csv", "books.csv"); 

    if (found)
        printf("ลบหนังสือ \"%s\" เรียบร้อย!\n", booktitle);
    else
        printf("ไม่พบหนังสือ \"%s\" ในระบบ\n", booktitle);
}

int main() {
    int choice;

    do {
        show_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                show_all_books();  
                break;
            case 2:
                add_book();
                break;
            case 3:
                search_book();
                break;
            case 4:
                printf("คุณเลือก: อัปเดตราคา\n");
                break;
            case 5:
                delete_book();
                break;
            case 0:
                printf("ออกจากโปรแกรมแล้ว\n");
                break;
            default:
                printf("เลือกเมนูไม่ถูกต้อง กรุณาเลือกใหม่\n");
        }

    } while(choice != 0);

    return 0;
}