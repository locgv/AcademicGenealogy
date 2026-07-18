#include <windows.h>
#include "AcademicGenealogy.h"

int main() {
    SetConsoleOutputCP(65001); 
    printf("=== KIEM THU CAU TRUC DU LIEU ACADEMIC GENEALOGY (PHAN 1) ===\n\n");
    
    // 1. Khoi tao Cay hoc thuat
    AcademicTree tree;
    init_academic_tree(&tree);
    
    // 2. Khoi tao Do thi
    Graph graph;
    init_graph(&graph);
    
    // 3. Khai bao thong tin "To su hoc thuat" (Goc cay)
    Person founder = {
        "GV001",
        "Giao su. Nguyen Van A",
        1985,
        "Cấu trúc dữ liệu và giải thuật tiên tiến",
        "Giang vien",
        "GS.TS"
    };
    
    // 4. Set goc cay va them vao do thi
    if (set_tree_root(&tree, founder)) {
        printf("[SUCCESS] Khoi tao goc cay thanh cong!\n");
        printf(" -> Ten: %s\n", tree.root->info.name);
        printf(" -> Hoc vi: %s\n", tree.root->info.academic_degree);
    } else {
        printf("[ERROR] Khong the set goc cay!\n");
    }
    
    add_vertex(&graph, founder);
    printf("\n--- TEST PHAN 2: THEM SINH VIEN ---\n");
    
    // Tạo thông tin
    // Thế hệ 1 -> Sinh viên 1 (Học trò trực tiếp của GV001)
    Person student1 = {
        "SV001",
        "Do Lam Minh Ngoc",
        2028,
        "Cấu hình định tuyến OSPF trên mạng Cisco", 
        "Sinh vien",
        "Cu nhan"
    };
    
    // Thêm vào làm học trò của Giao su. Nguyen Van A (ID: GV001)
    add_tree_member(&tree, "GV001", student1);
    add_vertex(&graph, student1);

    // Thế hệ 1 -> Giảng viên 2 (Sau này trở thành giảng viên hướng dẫn tiếp)
    Person student2 = {
        "GV002",
        "Tran Dinh Thach",
        2010,
        "An ninh mang", 
        "Giang vien",
        "Thac si"
    };

    // Thêm vào làm học trò của Giao su. Nguyen Van A (ID: GV001)
    add_tree_member(&tree, "GV001", student2); // Cùng thầy với Do Lam Minh Ngoc 
    add_vertex(&graph, student2);

    // Thế hệ 2 -> Sinh viên 3 (Học trò của GV002)
    Person student3 = {
        "SV003",
        "Nguyen Quang Sang",
        2024,
        "Phát triển ứng dụng di động",
        "Sinh vien",
        "Cu nhan"
    };

    // Thêm vào làm học trò của Tran Dinh Thach (ID: GV002)
    add_tree_member(&tree, "GV002", student3);
    add_vertex(&graph, student3);

    // In ra thử để kiểm tra xem cây đã liên kết đúng first_child chưa
    if (tree.root != NULL && tree.root->first_child != NULL) {
        printf(" -> Kiem tra lien ket: Hoc tro dau tien cua thay %s la %s\n", 
                tree.root->info.name, 
                tree.root->first_child->info.name);
    }

    printf("[SUCCESS] Them dinh vao do thi thanh cong! So dinh hien tai: %d\n", graph.num_vertices);
    
    printf("\n--- TEST PHAN 3: TIM KIEM VA CAP NHAT ---\n");

    // 1. Tìm kiếm theo mã số (Thành công & Không tìm thấy người cần cập nhật)
    printf("[SEARCH] Tim kiem theo ma so (ID): SV003\n");
    TreeNode* found_member = find_member_by_id(tree.root, "SV003"); // ID đúng để test trường hợp tìm thấy
    if (found_member) {
        printf(" -> Ket qua: Tim thay thanh vien: %s\n", found_member->info.name);
    } else {
        printf(" -> Ket qua: Khong tim thay thanh vien!\n");
    }

    // 2. Tìm kiếm theo họ tên - Tìm kiếm tương đối (Thành công & Không tìm thấy người cần cập nhật)
    printf("[SEARCH] Tim kiem theo ho ten: Dinh Thach\n");
    TreeNode* found_member_by_name = find_member_by_name(tree.root, "Dinh Thach");
    if (found_member_by_name) {
        printf(" -> Ket qua: Tim thay thanh vien: %s\n", found_member_by_name->info.name);
        printf(" -> Ma so tuong ung la %s\n", found_member_by_name->info.id);
    } else {
        printf(" -> Ket qua: Khong tim thay thanh vien!\n");
    }

    // 3. Cập nhật năm tốt nghiệp (Thành công & Không tìm thấy người cần cập nhật)
    printf("[UPDATE] Cap nhat nam tot nghiep cho SV001 (2028 -> 2029):\n");
    update_graduation_year(tree.root, "SV001", 2029);

    // 4. Cập nhật đề tài nghiên cứu (Thành công & Không tìm thấy người cần cập nhật)
    printf("[UPDATE] Cap nhat de tai nghien cuu cho SV003:\n");
    update_research_topic(tree.root, "SV003", "Nghiên cứu và phát triển ứng dụng AI trên di động");

    // 5. Kiểm tra trường hợp không tìm thấy để cập nhật
    printf("[UPDATE ERROR] Thu nghiem cap nhat cho ID khong ton tai: SV999\n");
    update_graduation_year(tree.root, "SV999", 2030);

    // === KẾT THÚC CODE TEST ===
    // 6. Giải phóng bộ nhớ an toàn
    free_tree(tree.root);
    free_graph(&graph);
    
    printf("\n[SUCCESS] Thu hoi bo nho hoan toan. Kiem thu compile va setup thanh cong!\n");
    return 0;
}
