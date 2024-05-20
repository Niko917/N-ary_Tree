#pragma once

#include "Set_element.hpp"
#include <algorithm>
#include <memory>
#include <stack>
#include <vector>
#include "exceptions.hpp"

struct Tree_Node {

    std::shared_ptr<Set_Element> element;

    std::vector<std::shared_ptr<Tree_Node>> children;

    Tree_Node* Parent = nullptr; 

    // ----------------------------------------------

    Tree_Node(std::shared_ptr<Set_Element> value, Tree_Node* parent = nullptr) : element(value), Parent(parent) {}

    Tree_Node() = default;

    // ---------------------------------------------

    void add_child(const std::shared_ptr<Tree_Node>& child);

    void remove_child(const std::shared_ptr<Tree_Node>& child);

    std::shared_ptr<Set_Element> get_data() const;

    std::shared_ptr<Tree_Node> get_child(size_t index) const;

    bool has_child() const;

    size_t count_children() const;

    void clear_children();

    void Print_Node() const;

    bool is_Root() const;

    bool is_Leaf() const;

};


class N_Ary_Tree {
public:

    std::shared_ptr<Tree_Node> root;

    N_Ary_Tree(std::shared_ptr<Tree_Node> root_node) : root(root_node) {}


    // -------------------------------------------------
    // METHODS


    static std::shared_ptr<N_Ary_Tree> Create_Tree(size_t n, std::vector<std::shared_ptr<Set_Element>>& elements);

    void set_data(const std::shared_ptr<Set_Element>& new_data);

    void Max_width() const;

    void find_Diameter() const;

    void Leaf_count() const;

    void Leaf_Print() const;

    void Min_distance() const;

    void Get_level(size_t level) const;

    bool is_Empty() const;

    size_t size() const;

    void Print_Node(Tree_Node& node) const;

    void serialize(); // Преобразование дерева в строку или другой сериализуемый формат.

    void deserialize(const std::string& data); // Создание дерева из сериализованных данных.

    // ------------------------------------------------
    // TRAVERSING

    void Traverse_KLP() const;

    void Traverse_KPL() const;

    void Traverse_PLK() const;

    void Traverse_LPK() const;

};


// ----------------------------------------------------


