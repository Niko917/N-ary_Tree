#pragma once

#include "Set_element.hpp"
#include <algorithm>
#include <memory>
#include <vector>
#include "exceptions.hpp"


template <typename T>
class Tree_Node {
public:
    std::shared_ptr<T> element;
    std::vector<std::shared_ptr<Tree_Node>> children;

    Tree_Node(std::shared_ptr<T> value) : element(value) {}

    Tree_Node() : element(nullptr) {}

    virtual ~Tree_Node() {}

    // -------------------------------------------------
    // METHODS

    void add_child(const std::shared_ptr<Tree_Node<T>>& child);

    void remove_child(const std::shared_ptr<Tree_Node<T>>& child);

    std::shared_ptr<Tree_Node<T>> get_child(size_t index) const;

    std::shared_ptr<T> get_data() const;

    void set_data(const std::shared_ptr<T>& new_data);

    bool has_child() const;

    size_t count_children() const;

    void clear_children();

    void Print_Node(const Tree_Node<T>& node) const;

    // ------------------------------------------------
    // TRAVERSING

    void Traverse_KLP(const Tree_Node<T>& root) const;

    void Traverse_KPL(const Tree_Node<T>& root) const;

    void Traverse_PLK(const Tree_Node<T>& root) const;

    void Traverse_LPK(const Tree_Node<T>& root) const;

};


// ----------------------------------------------------

template <typename T>
void Tree_Node<T>::add_child(const std::shared_ptr<Tree_Node<T>>& child) {
    children.push_back(child); 
}


template <typename T>
void Tree_Node<T>::remove_child(const std::shared_ptr<Tree_Node<T>>& child) {
    auto it = std::find(children.begin(),children.end(), child);
    if (it != children.end()) {
        children.erase(it);
    }
}


template <typename T>
std::shared_ptr<Tree_Node<T>> Tree_Node<T>::get_child(size_t index) const {
    if (index >= children.size()) {
        throw ERRORS::Index_Out_Of_Range;
    }
    return children[index];
}


template <typename T>
std::shared_ptr<T> Tree_Node<T>::get_data() const {
    return element;
}


template <typename T>
void Tree_Node<T>::set_data(const std::shared_ptr<T>& new_data) {
    element = new_data;
}


template <typename T>
bool Tree_Node<T>::has_child() const {
    return !children.empty();
}


template <typename T>
size_t Tree_Node<T>::count_children() const {
    return children.size(); 
}


template <typename T>
void Tree_Node<T>::clear_children() {
    children.clear();
}


template <typename T>
void Tree_Node<T>::Print_Node(const Tree_Node<T>& node) const {
    if (node.element) {
        std::cout << *(node.element) << " ";
    } 
}



// ----------------------------------------------------------
// TRAVERSING



