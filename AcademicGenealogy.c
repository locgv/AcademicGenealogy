#include "AcademicGenealogy.h"

// ==========================================
// THIẾT LẬP VÀ QUẢN LÝ CÂY NHIỀU NHÁNH (Cây LCRS)
// ==========================================

// Tạo mới một Node cây học thuật
TreeNode* create_tree_node(Person p) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        perror("Không thể cấp phát bộ nhớ cho Node cây!");
        return NULL;
    }
    newNode->info = p;
    newNode->parent = NULL;
    newNode->first_child = NULL;
    newNode->next_sibling = NULL;
    return newNode;
}

// Khởi tạo cây học thuật trống
void init_academic_tree(AcademicTree* tree) {
    if (tree != NULL) {
        tree->root = NULL;
    }
}

// Thiết lập đỉnh gốc (Tổ sư học thuật)
bool set_tree_root(AcademicTree* tree, Person p) {
    if (tree == NULL || tree->root != NULL) {
        return false; // Cây chưa khởi tạo hoặc đã có gốc
    }
    tree->root = create_tree_node(p);
    return (tree->root != NULL);
}

// Giải phóng bộ nhớ cây học thuật đệ quy
void free_tree(TreeNode* root) {
    if (root == NULL) return;
    
    // Đệ quy giải phóng nhánh con (first_child)
    free_tree(root->first_child);
    
    // Đệ quy giải phóng nhánh anh em (next_sibling)
    free_tree(root->next_sibling);
    
    // Giải phóng chính Node hiện tại
    free(root);
}

// ==========================================
// THIẾT LẬP VÀ QUẢN LÝ ĐỒ THỊ (Directed Graph)
// ==========================================

// Khởi tạo đồ thị trống
void init_graph(Graph* graph) {
    if (graph != NULL) {
        graph->vertices = NULL;
        graph->num_vertices = 0;
    }
}

// Thêm một đỉnh mới vào đồ thị (nếu chưa tồn tại)
void add_vertex(Graph* graph, Person p) {
    if (graph == NULL) return;

    // Kiểm tra trùng lặp đỉnh
    Vertex* curr = graph->vertices;
    while (curr != NULL) {
        if (strcmp(curr->id, p.id) == 0) {
            return; // Đã tồn tại đỉnh này
        }
        curr = curr->next;
    }

    // Tạo đỉnh mới
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    if (newVertex == NULL) {
        perror("Không thể cấp phát bộ nhớ cho đỉnh đồ thị!");
        return;
    }
    
    strncpy(newVertex->id, p.id, sizeof(newVertex->id) - 1);
    newVertex->id[sizeof(newVertex->id) - 1] = '\0';
    newVertex->info = p;
    newVertex->head = NULL;
    
    // Chèn đỉnh mới vào đầu danh sách đỉnh của đồ thị
    newVertex->next = graph->vertices;
    graph->vertices = newVertex;
    graph->num_vertices++;
}

// Giải phóng bộ nhớ đồ thị
void free_graph(Graph* graph) {
    if (graph == NULL) return;
    
    Vertex* currVertex = graph->vertices;
    while (currVertex != NULL) {
        // Giải phóng danh sách kề của đỉnh này
        AdjListNode* currEdge = currVertex->head;
        while (currEdge != NULL) {
            AdjListNode* tempEdge = currEdge;
            currEdge = currEdge->next;
            free(tempEdge);
        }
        
        // Giải phóng chính đỉnh
        Vertex* tempVertex = currVertex;
        currVertex = currVertex->next;
        free(tempVertex);
    }
    
    graph->vertices = NULL;
    graph->num_vertices = 0;
}
// Hàm hỗ trợ tìm kiếm Node theo ID (Dùng nội bộ cho hàm thêm thành viên)
TreeNode* find_node_helper(TreeNode* current, const char* id) {
    if (current == NULL) return NULL;
    
    // Nếu tìm thấy ID trùng khớp
    if (strcmp(current->info.id, id) == 0) return current;
    
    // Tìm tiếp trong nhánh con (học trò)
    TreeNode* found_in_child = find_node_helper(current->first_child, id);
    if (found_in_child != NULL) return found_in_child;
    
    // Tìm tiếp trong nhánh anh em (những học trò cùng cấp)
    return find_node_helper(current->next_sibling, id);
}

// Thêm thành viên vào đúng người hướng dẫn
bool add_tree_member(AcademicTree* tree, const char* advisor_id, Person new_member) {
    // 1. Kiểm tra dữ liệu đầu vào (Rất quan trọng!)
    if (tree == NULL || tree->root == NULL) {
        printf("[LỖI] Cây chưa được khởi tạo hoặc chưa có Giảng viên gốc!\n");
        return false;
    }
    if (advisor_id == NULL) {
        printf("[LỖI] Mã ID người hướng dẫn không hợp lệ!\n");
        return false;
    }

    // 2. Tìm Node của người hướng dẫn (Thầy/Cô) trong cây
    TreeNode* advisor_node = find_node_helper(tree->root, advisor_id);
    if (advisor_node == NULL) {
        printf("[LỖI] Không tìm thấy người hướng dẫn có ID: %s trong hệ thống!\n", advisor_id);
        return false;
    }

    // 3. Tạo Node mới cho sinh viên bằng hàm có sẵn
    TreeNode* new_node = create_tree_node(new_member);
    if (new_node == NULL) {
        return false; // Hết bộ nhớ
    }
    
    // Liên kết ngược để sinh viên nhận diện Thầy của mình
    new_node->parent = advisor_node; 

    // 4. Đảm bảo cây được liên kết đúng cấu trúc LCRS
    if (advisor_node->first_child == NULL) {
        // Trường hợp Thầy chưa có học trò nào -> Sinh viên này là "con đầu lòng"
        advisor_node->first_child = new_node;
    } else {
        // Trường hợp Thầy đã có học trò -> Tìm "em út" hiện tại để nối thêm vào
        TreeNode* current_child = advisor_node->first_child;
        while (current_child->next_sibling != NULL) {
            current_child = current_child->next_sibling; // Duyệt tới cuối danh sách
        }
        // Gắn sinh viên mới vào làm "em út"
        current_child->next_sibling = new_node;
    }

    printf("[THÀNH CÔNG] Đã thêm %s vào dưới sự hướng dẫn của %s.\n", new_member.name, advisor_node->info.name);
    return true;
}

//=========================================
// CHỨC NĂNG TÌM KIẾM
//=========================================
// 1. Hàm tìm kiếm theo mã số (ID)
TreeNode* find_member_by_id(TreeNode* root, const char* id) {
    if (root == NULL) return NULL;
    
    // Kiểm tra ID ở node hiện tại
    if (strcmp(root->info.id, id) == 0) {
        return root;
    }
    
    // Tìm trong nhánh con
    TreeNode* res = find_member_by_id(root->first_child, id);
    if (res) return res;

    // Tìm trong nhánh anh em
    return find_member_by_id(root->next_sibling, id);
}

// 2. Hàm tìm kiếm theo tên (Name)
TreeNode* find_member_by_name(TreeNode* root, const char* name) {
    if (root == NULL) return NULL;

    // Kiểm tra tên ở node hiện tại
    if (strstr(root->info.name, name) != NULL) {
        return root;
    }

    // Tìm trong nhánh con
    TreeNode* res = find_member_by_name(root->first_child, name);
    if (res) return res;

    // Tìm trong nhánh anh em
    return find_member_by_name(root->next_sibling, name);
}

//=========================================
// CHỨC NĂNG CẬP NHẬT DỮ LIỆU
//=========================================
// 1. Hàm cập nhật năm tốt nghiệp
bool update_graduation_year(TreeNode* root, const char* id, int new_year) {
    // Sử dụng hàm tìm kiếm để xác định Node cần cập nhật dựa theo ID
    TreeNode* member = find_member_by_id(root, id);
    
    // Kiểm tra trường hợp không tìm thấy người cần cập nhật
    if (member == NULL) {
        printf("[LỖI] Không tìm thấy thành viên có ID: %s để cập nhật năm tốt nghiệp.\n", id);
        return false;
    }

    // Nếu tìm thấy, tiến hành cập nhật năm tốt nghiệp
    member->info.graduation_year = new_year;
    printf("[THÀNH CÔNG] Đã cập nhật năm tốt nghiệp cho %s thành %d.\n", member->info.name, member->info.graduation_year);
    return true;
}

// 2. Hàm cập nhật đề tài nghiên cứu
bool update_research_topic(TreeNode* root, const char* id, const char* new_topic) {
    // Sử dụng hàm tìm kiếm để xác định Node cần cập nhật dựa theo ID
    TreeNode* member = find_member_by_id(root, id);
    
    // Kiểm tra trường hợp không tìm thấy người cần cập nhật
    if (member == NULL) {
        printf("[LỖI] Không tìm thấy thành viên có ID: %s để cập nhật đề tài nghiên cứu.\n", id);
        return false;
    }

    // Nếu tìm thấy, tiến hành cập nhật đề tài nghiên cứu
    strncpy(member->info.research_topic, new_topic, sizeof(member->info.research_topic) - 1);
    member->info.research_topic[sizeof(member->info.research_topic) - 1] = '\0'; // Đảm bảo kết thúc chuỗi
    printf("[THÀNH CÔNG] Đã cập nhật đề tài nghiên cứu cho %s thành \"%s\".\n", member->info.name, member->info.research_topic);
    return true;
}
