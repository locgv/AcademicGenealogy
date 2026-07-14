#include "AcademicGenealogy.h"

int main() {
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
    printf("[SUCCESS] Them dinh vao do thi thanh cong! So dinh hien tai: %d\n", graph.num_vertices);
    
    // 5. Giai phong bo nho an toan
    free_tree(tree.root);
    free_graph(&graph);
    
    printf("\n[SUCCESS] Thu hoi bo nho hoan toan. Kiem thu compile va setup thanh cong!\n");
    return 0;
}
