// #include <stdio.h>



// void show_menu() {
//     printf("=== Book Management Menu ===\n");
//     printf("1. Show all books\n");
//     printf("2. Add a book\n");
//     printf("3. Search a book\n");
//     printf("4. Update a book\n");
//     printf("5. Delete a book\n");
//     printf("0. Exit program\n");

// }

// int main() {
//     int choice;

//     do {
//         show_menu(); // แสดงเมนูทุกครั้ง
//         scanf("%d", &choice); // รับค่าจากผู้ใช้

//         switch(choice) {
//             case 1:
//                 printf("คุณเลือก: แสดงรายการหนังสือ\n");
//                 break;
//             case 2:
//                 printf("คุณเลือก: เพิ่มหนังสือ\n");
//                 break;
//             case 3:
//                 printf("คุณเลือก: ค้นหาหนังสือ\n");
//                 break;
//             case 4:
//                 printf("คุณเลือก: อัปเดตราคา\n");
//                 break;
//             case 5:
//                 printf("คุณเลือก: ลบหนังสือ\n");
//                 break;
//             case 0:
//                 printf("👋 ออกจากโปรแกรมแล้ว\n");
//                 break;
//             default:
//                 printf("❌ เลือกเมนูไม่ถูกต้อง กรุณาเลือกใหม่\n");
//         }

//     } while(choice != 0);

//     return 0;
// }
