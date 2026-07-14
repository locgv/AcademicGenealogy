# Đồ án: Mạng lưới Gia phả Học thuật (Academic Genealogy)

Dự án này quản lý "Gia phả học thuật" trong trường đại học: Giảng viên hướng dẫn luận văn cho sinh viên, sinh viên sau đó tốt nghiệp trở thành giảng viên và tiếp tục hướng dẫn các thế hệ tiếp theo.

Đây là bộ khung mã nguồn nền tảng được thiết kế bằng **ngôn ngữ C** cho nhóm nhỏ phụ trách **Phần 1, 2, 3**.

---

## Cấu trúc thư mục mã nguồn

*   `AcademicGenealogy.h`: Tệp tiêu đề định nghĩa toàn bộ struct dữ liệu ([Person](#1-struct-person), [TreeNode](#2-cay-nhieu-nhanh-lcrs), [Graph](#3-do-thi-co-huong)) và các nguyên mẫu hàm (API) cho cả nhóm.
*   `AcademicGenealogy.c`: Triển khai các hàm khởi tạo cấu trúc dữ liệu cơ bản và thu hồi bộ nhớ (tránh rò rỉ bộ nhớ).
*   `main.c`: Chương trình kiểm thử luồng khởi tạo và biên dịch.
*   `compile.bat`: File kịch bản tự động biên dịch và chạy trên Windows (chỉ cần kích đúp chuột để chạy).

---

## Chi tiết Thiết kế Cấu trúc Dữ liệu

### 1. Struct `Person`
Lưu thông tin cá nhân của mỗi thành viên trong mạng lưới:
*   `id`: Mã số định danh (MSSV hoặc mã giảng viên).
*   `name`: Họ và tên đầy đủ.
*   `graduation_year`: Năm tốt nghiệp.
*   `research_topic`: Đề tài nghiên cứu khoa học / luận văn.
*   `role`: Vai trò (`"Giang vien"` hoặc `"Sinh vien"`).
*   `academic_degree`: Học vị (`"Cu nhan"`, `"Thac si"`, `"Tien si"`...).

### 2. Cây nhiều nhánh (LCRS - Left Child Right Sibling)
Vì ngôn ngữ C không có thư viện lưu danh sách động như `std::vector` của C++, chúng ta sử dụng cấu trúc **Con trái nhất - Anh em kề phải (LCRS)**.
*   `first_child`: Con trỏ trỏ tới người học trò/sinh viên đầu tiên.
*   `next_sibling`: Con trỏ trỏ tới người học trò tiếp theo của cùng một thầy.

**Mô hình trực quan:**
```
       [Thầy A]
          │ (first_child)
       [Sinh viên B] ──(next_sibling)──> [Sinh viên C] ──(next_sibling)──> [Sinh viên D]
```

### 3. Đồ thị có hướng (Directed Graph)
Biểu diễn bằng **Danh sách kề sử dụng Danh sách liên kết đơn**:
*   `vertices`: Con trỏ đầu danh sách liên kết quản lý tất cả các đỉnh đồ thị.
*   `head` (trong Vertex): Con trỏ đầu danh sách liên kết các học trò nhận hướng dẫn từ giảng viên này.

---

## Phân công công việc (Team Phần 1, 2, 3)

### 1. Phần 1 - Đã hoàn tất
*   Thiết kế cấu trúc dữ liệu (`Person`, `TreeNode`, `Graph`, `AdjListNode`, `Vertex`).
*   Triển khai các hàm khởi tạo (`init_academic_tree`, `init_graph`).
*   Triển khai các hàm giải phóng bộ nhớ đệ quy an toàn (`free_tree`, `free_graph`).

### 2. Phần 2
Mở tệp `AcademicGenealogy.c` và triển khai chi tiết hàm:
```c
bool add_tree_member(AcademicTree* tree, const char* advisor_id, Person new_member);
```
*   *Gợi ý*: Bạn làm phần này cần duyệt cây để tìm Node của người hướng dẫn (`advisor_id`), sau đó chèn `new_member` vào danh sách con của Node đó (nếu là con đầu tiên thì trỏ vào `first_child`, nếu đã có con thì duyệt tới cuối danh sách `next_sibling` rồi chèn vào cuối).

### 3. Phần 3
Mở tệp `AcademicGenealogy.c` và triển khai chi tiết hai hàm tìm kiếm:
```c
TreeNode* find_member_by_id(TreeNode* root, const char* id);
TreeNode* find_member_by_name(TreeNode* root, const char* name);
```
*   *Gợi ý*: Sử dụng thuật toán duyệt đệ quy (DFS) trên cây LCRS để tìm kiếm theo thuộc tính thích hợp.

---

## Hướng dẫn Biên dịch & Chạy

### Cách 1: Sử dụng file `compile.bat` (Khuyên dùng)
Chỉ cần kích đúp chuột vào tệp `compile.bat` trong thư mục `C:\AcademicGenealogy`. Cửa sổ dòng lệnh sẽ tự động biên dịch mã nguồn và chạy tệp thực thi.

### Cách 2: Chạy dòng lệnh thủ công bằng GCC
Mở Command Prompt (CMD) hoặc PowerShell trong thư mục này và gõ lệnh sau:
```bash
gcc -Wall -o main.exe AcademicGenealogy.c main.c
.\main.exe
```

---
