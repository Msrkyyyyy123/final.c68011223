#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> 
#define UNIT_TEST
#include "../book.c"


// ประกาศฟังก์ชันจากไฟล์หลัก
void add_book();
void search_book();


int main() {
    printf("=== เริ่มการทดสอบ ===\n");

    // เตรียมไฟล์ใหม่ ห้ามเป็น w เพราะมันจะหายหมด
FILE *f = fopen("books.csv", "r");
if (f == NULL) {
    f = fopen("books.csv", "w");
    if (f == NULL) {
        printf("สร้างไฟล์ books.csv ไม่ได้\n");
        return 1;
    }
}
fclose(f);


    printf("\n[Test 1] ทดสอบฟังก์ชัน add_book()\n");
    printf("กรอกชื่อหนังสือว่า : mark \n");
    add_book();


    f = fopen("books.csv", "r");
    char line[200];
    int found = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "mark") != NULL) {
            found = 1;
            break;
        }
    }
    fclose(f);

    if (found)
        printf("ทดสอบ add_book() ผ่าน!!!!!!!!!!!!!!!!!\n");
    else
        printf("ทดสอบ add_book() ล้มเหลว!\n");

    printf("\n[Test 2] ทดสอบฟังก์ชัน search_book()\n");
    search_book();
    printf("(ตรวจสอบด้วยตาได้ว่าควรแสดง mark)\n");

    printf("\n=== ทดสอบเสร็จสิ้น ===\n");
    return 0;
}
