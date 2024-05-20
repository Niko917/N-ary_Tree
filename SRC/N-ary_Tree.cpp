#include "N-tree.hpp"
#include "Set_element.hpp"
#include "exceptions.hpp"
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ostream>
#include <queue>
#include <stack>


//METHODS


void Tree_Node::add_child(const std::shared_ptr<Tree_Node>& child) {
    child->Parent = this;
    children.push_back(child); 
}


void Tree_Node::remove_child(const std::shared_ptr<Tree_Node>& child) {
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        (*it)->Parent = nullptr;
        children.erase(it);
    }
}



std::shared_ptr<Tree_Node> Tree_Node::get_child(size_t index) const {
    if (index >= children.size()) {
        throw TREE_EXCEPTION{ERRORS::Index_Out_Of_Range};
    }
    if (children.empty()) {
        throw TREE_EXCEPTION{ERRORS::Node_is_a_Leaf};
    }
    return children[index];
}



std::shared_ptr<Set_Element> Tree_Node::get_data() const {
    return element;
}



bool Tree_Node::has_child() const {
    return !children.empty();
}



size_t Tree_Node::count_children() const {
    return children.size(); 
}



void Tree_Node::clear_children() {
    for (auto& child : children) {
        child->Parent = nullptr;
    }
    children.clear();
}



void Tree_Node::Print_Node() const {
    element->print();
}


bool Tree_Node::is_Root() const {
    return Parent == nullptr;
}


bool Tree_Node::is_Leaf() const {
    return children.empty();
}


// ----------------------------------------------------------
// TREE IPLEMENTATION


std::shared_ptr<N_Ary_Tree> N_Ary_Tree::Create_Tree(size_t n, std::vector<std::shared_ptr<Set_Element>>& elements) {
    if (elements.empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    auto root_node = std::make_shared<Tree_Node>(elements[0]);

    auto tree = std::make_shared<N_Ary_Tree>(root_node);

    std::queue<std::shared_ptr<Tree_Node>> nodes;
    nodes.push(root_node);

    size_t curr_elem = 1; // index of next element

    while (curr_elem < elements.size() && !nodes.empty()) {
        auto parent_node = nodes.front();
        nodes.pop();

        for (int i = 0; i < n && curr_elem < elements.size(); ++i) {
            auto child_node = std::make_shared<Tree_Node>(elements[curr_elem++]);
            parent_node->add_child(child_node);
            nodes.push(child_node);
        }
    }

    return tree;
}


// ----------------------------------------------------------
// TRAVERSING


// Root -> All subtrees from left to right
void N_Ary_Tree::Traverse_KLP() const {
    
    std::stack<Tree_Node*> stack;
    stack.push(root.get());

    while(!stack.empty()) {
        Tree_Node* curr = stack.top();
        stack.pop();

        curr->Print_Node();
        
        // reverse iterators
        for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it) {
            stack.push(it->get());
        }
    }
}



// Root -> All subtrees from right to left
void N_Ary_Tree::Traverse_KPL() const {
    std::stack<Tree_Node*> stack;
    stack.push(root.get());

    while(!stack.empty()) {
        Tree_Node* curr = stack.top();
        stack.pop();

        curr->Print_Node();

        for (auto& child : curr->children) {
            stack.push(child.get());
        }
    }
}



// All subtrees -> Root
void N_Ary_Tree::Traverse_PLK() const {

    std::stack<Tree_Node*> stack;
    std::stack<Tree_Node*> out;
    
    stack.push(root.get());
    
    while (!stack.empty()) {
        Tree_Node* curr = stack.top();
        stack.pop();
        out.push(curr);

        for (auto& child : curr->children) {
            stack.push(child.get());
        }
    }

    while (!out.empty()) {
        Tree_Node* node = out.top();
        out.pop();
        node->Print_Node();
    }
}



// All subtrees -> Root
void N_Ary_Tree::Traverse_LPK() const {

    std::stack<Tree_Node*> stack;
    std::stack<Tree_Node*> out;

    stack.push(root.get());

    while (!stack.empty()) {
        Tree_Node* curr = stack.top();
        stack.pop();
        out.push(curr);

        for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it) {
            stack.push(it->get());
        }
    }

    while (!out.empty()) {
        Tree_Node* node = out.top();
        out.pop();
        node->Print_Node();
    }
}


// --------------------------------------------------------------------


/*
int main() {
    size_t n = 45;

    std::vector<std::shared_ptr<Set_Element>> elements = {
        std::make_shared<Integer_element>(10),
        std::make_shared<String_element>("Hello!"),
        std::make_shared<Complex_element>(5.2, 3.0)
    };

    auto root = N_Ary_Tree::Create_Tree(n, elements);

    std::cout << "KLP Traverse: ";
    root->Traverse_KLP();
    std::cout << '\n';

    std::cout << "PLK Traverse: ";
    root->Traverse_PLK();
    std::cout << '\n';

    std::cout << "KPL Traverse: ";
    root->Traverse_KPL();
    std::cout << '\n';

    return 0;
}
*/
