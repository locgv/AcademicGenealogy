#ifndef ACADEMIC_GENEALOGY_H
#define ACADEMIC_GENEALOGY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 1. THÀNH PHẦN DỮ LIỆU CÁ NHÂN (Person)
typedef struct Person {
    char id[50];               // Mã số định danh duy nhất (MSSV hoặc Mã giảng viên)
    char name[100];            // Họ và tên đầy đủ
    int graduation_year;       // Năm tốt nghiệp
    char research_topic[200];  // Đề tài nghiên cứu khoa học / luận văn
    
    // Thuộc tính gợi ý bổ sung cho logic nghiệp vụ (tránh lấn sân các phần sau)
    char role[20];             // Vai trò: "Giảng viên" (Lecturer) hoặc "Sinh viên" (Student)
    char academic_degree[30];  // Học vị: "Cử nhân", "Thạc sĩ", "Tiến sĩ", "PGS", "GS"
} Person;

// 2. CẤU TRÚC CÂY NHIỀU NHÁNH (Multi-way Tree)
// Biểu diễn theo phương pháp: Con trái nhất - Anh em kề phải (Left Child - Right Sibling)
typedef struct TreeNode {
    Person info;
    struct TreeNode* parent;          // Con trỏ trỏ ngược về Thầy/Cô hướng dẫn trực tiếp (NULL nếu là gốc cây)
    struct TreeNode* first_child;     // Con trỏ trỏ tới người học trò/sinh viên đầu tiên
    struct TreeNode* next_sibling;    // Con trỏ trỏ tới người học trò/sinh viên tiếp theo có cùng người hướng dẫn
} TreeNode;

typedef struct AcademicTree {
    TreeNode* root; // "Tổ sư học thuật" - Gốc của cây gia phả học thuật
} AcademicTree;

// --- Khai báo các hàm quản lý cây ---
// Tạo mới một Node cây
TreeNode* create_tree_node(Person p);
// Khởi tạo cây học thuật
void init_academic_tree(AcademicTree* tree);
// Thiết lập Node gốc cho cây
bool set_tree_root(AcademicTree* tree, Person p);
// Thêm học trò mới dưới sự hướng dẫn của advisor_id (Ngọc code chính - Phần 2)
bool add_tree_member(AcademicTree* tree, const char* advisor_id, Person new_member);
// Tìm kiếm thành viên theo ID (Tuyền code chính - Phần 3)
TreeNode* find_member_by_id(TreeNode* root, const char* id);
// Tìm kiếm thành viên theo Họ tên (Tuyền code chính - Phần 3)
TreeNode* find_member_by_name(TreeNode* root, const char* name);
// Giải phóng bộ nhớ cây học thuật
void free_tree(TreeNode* root);


// 3. CẤU TRÚC ĐỒ THỊ CÓ HƯỚNG (Directed Graph)
// Sử dụng danh sách kề được biểu diễn bằng danh sách liên kết đơn

// Node biểu diễn một cung (cạnh có hướng) trong danh sách kề
typedef struct AdjListNode {
    char dest_id[50];               // ID của học trò được hướng dẫn
    struct AdjListNode* next;       // Con trỏ tới cung tiếp theo
} AdjListNode;

// Đỉnh của đồ thị (Vertex) chứa thông tin cá nhân và danh sách cung đi ra
typedef struct Vertex {
    char id[50];                    // ID định danh đỉnh
    Person info;                    // Thông tin cá nhân của đỉnh này
    AdjListNode* head;              // Con trỏ trỏ tới danh sách học trò được hướng dẫn trực tiếp
    struct Vertex* next;            // Con trỏ tới đỉnh tiếp theo trong danh sách các đỉnh của đồ thị
} Vertex;

typedef struct Graph {
    Vertex* vertices;               // Danh sách liên kết đơn quản lý toàn bộ các đỉnh trong đồ thị
    int num_vertices;               // Số lượng đỉnh hiện tại
} Graph;

// --- Khai báo các hàm quản lý đồ thị ---
// Khởi tạo đồ thị
void init_graph(Graph* graph);
// Thêm đỉnh mới vào đồ thị
void add_vertex(Graph* graph, Person p);
// Thêm cạnh có hướng từ thầy (from_id) sang trò (to_id)
bool add_edge(Graph* graph, const char* from_id, const char* to_id);
// Xóa cạnh có hướng (dùng để rollback khi chạy thử nghiệm chu trình)
void remove_edge(Graph* graph, const char* from_id, const char* to_id);
// Kiểm tra đồ thị có chứa chu trình hay không (DFS tô màu)
bool has_cycle(const Graph* graph);
// Kiểm tra việc thêm mối quan hệ mới có an toàn hay không (không tạo vòng lặp logic)
bool is_safe_to_add_relationship(Graph* graph, const char* advisor_id, const char* student_id);
// Giải phóng bộ nhớ đồ thị
void free_graph(Graph* graph);
// Cập nhật năm tốt nghiệp cho một thành viên theo ID
bool update_graduation_year(TreeNode* root, const char* id, int new_year);
// Cập nhật đề tài nghiên cứu cho một thành viên theo ID
bool update_research_topic(TreeNode* root, const char* id, const char* new_topic);

#endif // ACADEMIC_GENEALOGY_H
