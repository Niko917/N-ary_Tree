#include "N-tree.hpp"
#include "Set_element.hpp"
#include "exceptions.hpp"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

void Test_constructors() {
    std::vector<std::pair<std::shared_ptr<Set_Element>, size_t>> elements_with_keys = {
        {std::make_shared<Integer_element>(1), 1},
        {std::make_shared<Integer_element>(2), 2},
        {std::make_shared<Integer_element>(3), 3},
        {std::make_shared<Integer_element>(4), 4},
        {std::make_shared<Integer_element>(5), 5},
        {std::make_shared<Integer_element>(6), 6},
        {std::make_shared<Integer_element>(7), 7}
    };

    auto tree = N_Ary_Tree::Create_Tree(3, elements_with_keys);

    tree->Destroy_Tree();
    assert(tree->is_Empty());
    assert(tree->root == nullptr);
}

void Test_methods() {
    std::vector<std::pair<std::shared_ptr<Set_Element>, size_t>> elements_with_keys = {
        {std::make_shared<Real_element>(1.1), 1}, // root
        {std::make_shared<Real_element>(2.2), 2},
        {std::make_shared<Real_element>(3.3), 3},
        {std::make_shared<Complex_element>(5.2, 3.0), 4}
    };


    auto tree = N_Ary_Tree::Create_Tree(4, elements_with_keys);


    assert(tree != nullptr);
    assert(tree->root != nullptr);
    assert(tree->root->element_with_Key.second == 1);


    // 1. Set_data
    std::cout << "root of the tree: ";
    tree->root->Print_Node();
    std::cout << std::endl;


    assert(tree->root->has_child());


    try {
        auto node = tree->root->get_child(0);
        auto new_data = std::make_shared<Real_element>(10.0);

        tree->set_data(node, new_data);
        assert(node->get_data()->is_Equal(new_data));
    } catch (const TREE_EXCEPTION& err) {
        std::cerr << err.what() << std::endl;
    }


    // 2. Max_width
    try {
        size_t max_width = tree->Max_width();
        std::cout << "Max_width: " << max_width << std::endl;
        assert(max_width > 0);
    } catch (const TREE_EXCEPTION& err) {
        std::cerr << err.what() << std::endl;
    }


    // 3. find_Diameter
    try {
        size_t diameter = tree->find_Diameter();
        std::cout << "Diameter: " << diameter << std::endl;
        assert(diameter > 0);
    } catch (const TREE_EXCEPTION& err) {
        std::cerr << err.what() << std::endl;
    }


    // 4. Leaf_count
    try {
        size_t leaf_count = tree->Leaf_count();
        std::cout << "Leaf count: " << leaf_count << std::endl;
        assert(leaf_count > 0);
    } catch (const TREE_EXCEPTION& err) {
        std::cerr << err.what() << std::endl;
    }


    // 5. nodes_count
    try {
        size_t node_count = tree->nodes_count();
        std::cout << "Node count: " << node_count << std::endl;
        assert(node_count == elements_with_keys.size());
    } catch (const TREE_EXCEPTION& err) {
        std::cerr << err.what() << std::endl;
    }


    // 6. find_by_key
    try {
        std::cout << "Found by key (1): ";
        tree->find_by_key(1)->print();
        std::cout << std::endl;
    } catch (const TREE_EXCEPTION& err) {
        std::cerr << err.what() << std::endl;
    }


    // 7. find by value
    try {
        auto value_to_find = std::make_shared<Real_element>(1.1);
        std::cout << "Found by value (1.1): ";
        auto result = tree->find_by_value(value_to_find);
        std::cout << result << std::endl;
    } catch (const TREE_EXCEPTION& err) {
        std::cerr << err.what() << std::endl;
    }


    // 8. serialize
    try {
        std::string result = tree->serialize_dfs();
        std::cout << "Serialized string: " << result << std::endl;
        assert(!result.empty());
    } catch (const TREE_EXCEPTION& err) {
        std::cerr << err.what() << std::endl;
    }


    // 9. Print Tree
    std::cout << "Printing the tree:" << std::endl;
    tree->Print_Tree();


    // Traversing
    auto preorder = tree->Preorder_Traversal();
    std::cout << "Preorder Traversal (root -> left -> right): ";
    while (!preorder.empty()) {
        std::cout << preorder.top() << " ";
        preorder.pop();
    }
    std::cout << std::endl;


    
    auto Post_left = tree->PostOrder_left_Traversal();
    std::cout << "PostOrder left Traversal (left -> right -> root): ";
    while (!Post_left.empty()) {
        std::cout << Post_left.top() << " ";
        Post_left.pop();
    }
    std::cout << std::endl;


    auto Post_right = tree->PostOrder_right_Traversal();
    std::cout << "PostOrder right Traversal (right -> left -> root): ";
    while (!Post_right.empty()) {
        std::cout << Post_right.top() << " ";
        Post_right.pop();
    }
    std::cout << std::endl;


    auto level_BFS_traversal = tree->Level_BFS_Traverse();
    std::cout << "Level_BFS Traverse: ";
    while (!level_BFS_traversal.empty()) {
        std::cout << level_BFS_traversal.front() << " ";
        level_BFS_traversal.pop();
    }
    std::cout << std::endl;


    // ---------------------------------------------------

    auto child_1 = std::make_shared<Tree_Node>(std::make_shared<Complex_element>(3.4, 2.5), 5);
    auto child_2 = std::make_shared<Tree_Node>(std::make_shared<String_element>("Hi!"), 6);
    auto child_3 = std::make_shared<Tree_Node>(std::make_shared<Real_element>(2.5), 7);


    auto leaf_1 = tree->find_node_by_key(2);
    auto leaf_2 = tree->find_node_by_key(3);
    auto leaf_3 = tree->find_node_by_key(4);


    leaf_1->add_child(child_1, *tree);
    assert(leaf_1->get_child(0) == child_1);

    leaf_2->add_child(child_2, *tree);
    assert(leaf_2->get_child(0) == child_2);

    leaf_3->add_child(child_3, *tree);
    assert(leaf_3->get_child(0) == child_3);

    std::cout << "Nodes count: " <<tree->nodes_count() << std::endl;
    std::cout << "Node with key (2) has child (y/n): " << tree->find_node_by_key(2)->has_child() << std::endl;
    std::cout << "Diameter: " << tree->find_Diameter() << std::endl;

    std::cout << "Printing the tree: " << std::endl;
    tree->Print_Tree();
    std::cout << std::endl;


    auto child_1_1 = std::make_shared<Tree_Node>(std::make_shared<Complex_element>(1.0, 3.14), 8);
    leaf_1->add_child(child_1_1, *tree);

    std::cout << "Printing the tree: " << std::endl;
    tree->Print_Tree();

}

void Tests_for_Tree() {
    Test_constructors();
    Test_methods();
}
