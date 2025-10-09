HOW TO COMPLY IN  book.c 

    PS C:\Users\uSEr\OneDrive\Documents\Myfinal.c>      chcp 65001   
    PS C:\Users\uSEr\OneDrive\Documents\Myfinal.c>      ./book    

    why [chcp 65001] ? ... เพราะว่าไฟล์ของผมเป็นภาษา "UTF-8" แต่ PowerShell เป็นภาษา "CP874" 
    ซึ่งทั้งสองอย่างคนละภาษากันเลยไม่รู้เรื่อง จึงต้องสั่งมันว่า "chcp 65001" เหมือนเป็นตัวเชื่อมกัน  
   
HOW TO COMPLY IN unit_test.c 

    PS C:\Users\uSEr\OneDrive\Documents\Myfinal.c> 
    
        >> gcc test/unit_test.c -o test/unit_test
        >> .\test\unit_test.exe

HOW TO COMPLY IN e2e_test.c

    PS C:\Users\uSEr\OneDrive\Documents\Myfinal.c> 
        
        >> gcc test/e2e_test.c -o test/e2e_test  
        >> .\test\e2e_test.exe 

---------โจทย์ที่ผมได้รับ------------

    < ระบบจัดการข้อมูลหนังสือการเรียนการสอน >
    
    ฟีเจอร์หลัก:
    
    1. บันทึกข้อมูลหนังสือการเรียนการสอนลงในไฟล์ CSV (ชื่อหนังสือ, ผู้แต่ง, สำนักพิมพ์, ราคา)
    2. อ่านข้อมูลหนังสือการเรียนการสอนจากไฟล์ CSV 
    3. เพิ่มข้อมูลหนังสือใหม่ (add) ✅
    4. ค้นหาข้อมูลหนังสือ (search) โดยค้นหาจากชื่อหนังสือหรือผู้แต่ง 
    5. อัพเดทข้อมูลหนังสือ (update) เช่น เปลี่ยนแปลงราคา
    6. ลบข้อมูลหนังสือ (delete) ตามชื่อหนังสือ
    7. แสดงเมนูให้ผู้ใช้เลือกดำเนินการต่างๆ (display_menu) 
    
    ไฟล์ CSV จะประกอบด้วย 4 คอลัมน์: BookTitle, Author, Publisher, Price และมีข้อมูลไม่น้อยกว่า 15 รายการ
