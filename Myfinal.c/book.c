#include <stdio.h>
#include <stdlib.h>

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

void  search_book() {
    printf("hello");
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
                printf("คุณเลือก: ลบหนังสือ\n");
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