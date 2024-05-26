#pragma once

#include "Set_element.hpp"
#include <algorithm>
#include <memory>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
#include "exceptions.hpp"

class N_Ary_Tree;


struct Tree_Node {

    std::pair<std::shared_ptr<Set_Element>, size_t> element_with_Key;

    std::vector<std::shared_ptr<Tree_Node>> children;

    Tree_Node* Parent = nullptr;

    // ----------------------------------------------

    Tree_Node(std::shared_ptr<Set_Element> value, size_t unique_key) {
        element_with_Key = std::make_pair(value, unique_key);
    }

    Tree_Node(std::shared_ptr<Set_Element> elem, std::vector<std::shared_ptr<Tree_Node>> babyes, const size_t unique_key, N_Ary_Tree& tree) : element_with_Key(elem, unique_key) {
        for (const auto& child : babyes) {
            add_child(child, tree);
        }
    }

    Tree_Node(std::shared_ptr<Set_Element> elem, Tree_Node* parent = nullptr) : element_with_Key(elem, 0), Parent(parent) {}

    Tree_Node() = default;

    ~Tree_Node() = default;

    // ---------------------------------------------

    void add_child(const std::shared_ptr<Tree_Node>& child, N_Ary_Tree& tree);

    void remove_child(const std::shared_ptr<Tree_Node>& child, N_Ary_Tree& tree);

    std::shared_ptr<Set_Element> get_data() const;

    std::shared_ptr<Tree_Node> get_child(size_t index) const;

    bool has_child() const;

    bool is_ancestor_of(const std::shared_ptr<Tree_Node>& other_node) const;

    bool is_descendant_of(const std::shared_ptr<Tree_Node>& other_node) const;

    size_t count_children() const;

    void clear_children();

    void Print_Node() const;

    size_t Print_key() const;

    bool is_Root() const;

    bool is_Leaf() const;

};



// ----------------------------------------------------------



class N_Ary_Tree {
public:

    std::shared_ptr<Tree_Node> root;

    std::vector<std::pair<std::shared_ptr<Set_Element>, size_t>> info;

    N_Ary_Tree(std::shared_ptr<Tree_Node> node) : root(node) {}


    // -------------------------------------------------
    // METHODS


    std::shared_ptr<Tree_Node> get_root() const;

    static std::shared_ptr<N_Ary_Tree> Create_Tree(size_t n, std::vector<std::pair<std::shared_ptr<Set_Element>, size_t>>& elements_with_keys);

    void Destroy_Tree();

    void set_data(const std::shared_ptr<Tree_Node>& Node, const std::shared_ptr<Set_Element>& new_data);

    
    // BFS
    size_t Max_width() const;

    size_t find_Diameter() const;

    // DFS

    std::shared_ptr<Set_Element> find_by_key(size_t Key) const;

    size_t find_by_value(const std::shared_ptr<Set_Element>& value) const;

    std::shared_ptr<Tree_Node> find_node_by_key(size_t key) const;

    std::string serialize_dfs() const;

    size_t Leaf_count() const;

    std::shared_ptr<Tree_Node> Leaf_Print() const;

    bool is_Empty() const;

    size_t nodes_count() const;

    void show(const std::shared_ptr<Tree_Node>& node, size_t depth = 0) const; // output the tree in the Terminal
    
    void Print_Tree() const;


    // ------------------------------------------------
    // TRAVERSING

    // DFS

    std::stack<size_t> Preorder_Traversal() const; // ROOT->LEFT->RIGHT

    std::stack<size_t> PostOrder_left_Traversal() const; // LEFT->RIGHT->ROOT

    std::stack<size_t> PostOrder_right_Traversal() const; // RIGHT->LEFT->ROOT

    std::queue<size_t> Level_BFS_Traverse() const;

};


// ----------------------------------------------------


