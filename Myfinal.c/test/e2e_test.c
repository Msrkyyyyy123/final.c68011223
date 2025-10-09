#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define UNIT_TEST
#include "../book.c"  // ต้องใช้ ../ เพราะว่าอยู่คนละโฟลเดอร์กัน

int main() {
    printf("=== เริ่มการทดสอบ End-to-End ===\n");

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

    // [1] เพิ่มหนังสือ
    printf("\n[Test 1] เพิ่มหนังสือใหม่\n");
    add_book();

    // [2] ค้นหาหนังสือ
    printf("\n[Test 2] ค้นหาหนังสือ\n");
    search_book();

    // [3] อัปเดตราคา
    printf("\n[Test 3] อัปเดตราคาหนังสือ\n");
    update_book();

    // [4] ลบหนังสือ
    printf("\n[Test 4] ลบหนังสือ\n");
    delete_book();

    // [5] แสดงรายการทั้งหมด
    printf("\n[Test 5] แสดงรายการหนังสือทั้งหมด\n");
    show_all_books();

    printf("\n=== ทดสอบเสร็จสิ้น ===\n");
    return 0;
}