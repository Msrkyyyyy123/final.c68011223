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
    char line[1000];

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
    char line[1000];
    int found = 0;

    printf("กรอกชื่อหนังสือที่ต้องการค้นหา: ");
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


void update_book() {
    FILE *file = fopen("books.csv", "r");
    if (file == NULL) {
        printf("ไม่สามารถเปิดไฟล์ books.csv ได้\n");
        return;
    }

    const int MAX = 1000;
    char titles[MAX][100], authors[MAX][100], publishers[MAX][100], prices[MAX][20];
    char line[1000];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%99[^,],%99[^,],%99[^,],%19[^\r\n]",
                   titles[count], authors[count], publishers[count], prices[count]) == 4) {
            count++;
            if (count >= MAX) break;
        }
    }
    fclose(file);

    if (count == 0) {
        printf("ไฟล์ว่างหรือไม่มีข้อมูลใน books.csv\n");
        return;
    }

    while (1) {
        char keyword[100];
        printf("กรอกชื่อหนังสือที่ต้องการเปลี่ยนราคาหรือคีย์เวิร์ดที่จะค้นหา (พิมพ์ 0 เพื่อยกเลิก): ");
        scanf(" %[^\n]", keyword);

        if (strcmp(keyword, "0") == 0) {
            printf("ยกเลิกการเปลี่ยนราคา\n");
            return;
        }

        int matches[MAX];
        int matchCount = 0;
        for (int i = 0; i < count; i++) {
            if (strstr(titles[i], keyword) != NULL || strstr(authors[i], keyword) != NULL) {
                matches[matchCount++] = i;
            }
        }

        if (matchCount == 0) {
            printf("ไม่พบหนังสือที่ตรงกับ \"%s\" กรุณาลองใหม่\n", keyword);
            continue;
        }

        printf("พบ %d รายการ:\n", matchCount);
        for (int j = 0; j < matchCount; j++) {
            int idx = matches[j];
            printf("%d. %s | %s | %s | %s\n",
                   j + 1, titles[idx], authors[idx], publishers[idx], prices[idx]);
        }

        int sel;
        printf("เลือกหมายเลขหนังสือที่จะเปลี่ยนราคา (1-%d) หรือ 0 เพื่อยกเลิก: ", matchCount);
        if (scanf("%d", &sel) != 1 || sel < 0 || sel > matchCount) {
            printf("ตัวเลือกไม่ถูกต้อง กรุณาลองใหม่\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (sel == 0) {
            printf("ยกเลิกการเปลี่ยนราคา\n");
            return;
        }

        int idx = matches[sel - 1];
        printf("คุณต้องการเปลี่ยนราคาหนังสือ \"%s\" (จากราคา: %s) เป็นราคาเท่าไหร่: ", 
               titles[idx], prices[idx]);

        char newPrice[20];
        scanf(" %[^\n]", newPrice);
        strcpy(prices[idx], newPrice); 

        file = fopen("books.csv", "w");
        if (file == NULL) {
            printf("ไม่สามารถเขียนไฟล์ books.csv ได้\n");
            return;
        }
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s,%s,%s,%s\n", titles[i], authors[i], publishers[i], prices[i]);
        }
        fclose(file);

        printf("เปลี่ยนราคาหนังสือ \"%s\" เรียบร้อย!\n", titles[idx]);
        
        return;
    }
}


void delete_book() {
    FILE *file = fopen("books.csv", "r");
    if (file == NULL) {
        printf("ไม่สามารถเปิดไฟล์ books.csv ได้\n");
        return;
    }

    const int MAX = 1000;
    char titles[MAX][100], authors[MAX][100], publishers[MAX][100], prices[MAX][20];
    char line[512];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%99[^,],%99[^,],%99[^,],%19[^\r\n]",
                   titles[count], authors[count], publishers[count], prices[count]) == 4) {
            count++;
            if (count >= MAX) break;
        }
    }
    fclose(file);

    if (count == 0) {
        printf("ไฟล์ว่างหรือไม่มีข้อมูลใน books.csv\n");
        return;
    }

    while (1) {
        char keyword[100];
        printf("กรอกชื่อหนังสือที่ต้องการลบหรือคีย์เวิร์ดที่จะค้นหา (พิมพ์ 0 เพื่อยกเลิก): ");
        scanf(" %[^\n]", keyword);

        if (strcmp(keyword, "0") == 0) {
            printf("ยกเลิกการลบ\n");
            return;
        }

        int matches[MAX];
        int matchCount = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(titles[i], "BookTitle") == 0) continue; 
            if (strstr(titles[i], keyword) != NULL || strstr(authors[i], keyword) != NULL) {
                matches[matchCount++] = i;
            }
        }

        if (matchCount == 0) {
            printf("ไม่พบหนังสือที่ตรงกับ \"%s\" กรุณาลองใหม่\n", keyword);
            continue; 
        }

        printf("พบ %d รายการ:\n", matchCount);
        for (int j = 0; j < matchCount; j++) {
            int idx = matches[j];
            printf("%d. %s | %s | %s | %s\n",
                   j + 1, titles[idx], authors[idx], publishers[idx], prices[idx]);
        }

        int sel;
        printf("เลือกหมายเลขหนังสือที่จะลบ (1-%d) หรือ 0 เพื่อยกเลิก: ", matchCount);
        if (scanf("%d", &sel) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("ตัวเลือกไม่ถูกต้อง กรุณาลองใหม่\n");
            continue;
        }

        int ch; while ((ch = getchar()) != '\n' && ch != EOF);

        if (sel == 0) {
            printf("ยกเลิกการลบ\n");
            return;
        }
        if (sel < 1 || sel > matchCount) {
            printf("เลือกนอกช่วงที่กำหนด กรุณาลองใหม่\n");
            continue;
        }

        int deleteIdx = matches[sel - 1];

        int confirm;
        printf("คุณต้องการลบหนังสือ \"%s\" (ผู้แต่ง: %s) ใช่หรือไม่? 1=ใช่  2=ไม่: ",
               titles[deleteIdx], authors[deleteIdx]);
        if (scanf("%d", &confirm) != 1) {
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("ตัวเลือกไม่ถูกต้อง\n");
            continue;
        }
        while ((ch = getchar()) != '\n' && ch != EOF);

        if (confirm != 1) {
            printf("ยกเลิกการลบ\n");
            return;
        }

        FILE *temp = fopen("temp.csv", "w");
        if (temp == NULL) {
            printf("ไม่สามารถสร้างไฟล์ temp.csv ได้\n");
            return;
        }

        for (int i = 0; i < count; i++) {
            if (i == deleteIdx) continue; 
            fprintf(temp, "%s,%s,%s,%s\n", titles[i], authors[i], publishers[i], prices[i]);
        }
        fclose(temp);

        remove("books.csv");
        rename("temp.csv", "books.csv");

        printf("ลบหนังสือ \"%s\" เรียบร้อย!\n", titles[deleteIdx]);
        return;
    } 
}

#ifndef UNIT_TEST
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
                update_book();
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
#endif