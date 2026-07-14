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
