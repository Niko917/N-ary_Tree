#pragma once

#include "Set_element.hpp"
#include <algorithm>
#include <memory>
#include <stack>
#include <vector>
#include "exceptions.hpp"



class Tree_Node {
public:
    std::shared_ptr<Set_Element> element;
    std::vector<std::shared_ptr<Tree_Node>> children;

    Tree_Node(std::shared_ptr<Set_Element> value) : element(value) {}

    Tree_Node() = default;

    virtual ~Tree_Node() {}

    static std::shared_ptr<Tree_Node> Create_Tree(size_t n, std::vector<std::shared_ptr<Set_Element>>& elements);

    // -------------------------------------------------
    // METHODS

    void add_child(const std::shared_ptr<Tree_Node>& child);

    void remove_child(const std::shared_ptr<Tree_Node>& child);

    std::shared_ptr<Tree_Node> get_child(size_t index) const;

    std::shared_ptr<Set_Element> get_data() const;

    void set_data(const std::shared_ptr<Set_Element>& new_data);

    bool has_child() const;

    size_t count_children() const;

    void clear_children();

    void Print_Node(const Tree_Node& node) const;

    // ------------------------------------------------
    // TRAVERSING

    void Traverse_KLP() const;

    void Traverse_KPL() const;

    void Traverse_PLK() const;

    void Traverse_LPK() const;

};


// ----------------------------------------------------


