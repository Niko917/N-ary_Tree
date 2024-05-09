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
    children.push_back(child); 
}


void Tree_Node::remove_child(const std::shared_ptr<Tree_Node>& child) {
    auto it = std::find(children.begin(),children.end(), child);
    if (it != children.end()) {
        children.erase(it);
    }
}



std::shared_ptr<Tree_Node> Tree_Node::get_child(size_t index) const {
    if (index >= children.size()) {
        throw ERRORS::Index_Out_Of_Range;
    }
    return children[index];
}



std::shared_ptr<Set_Element> Tree_Node::get_data() const {
    return element;
}



void Tree_Node::set_data(const std::shared_ptr<Set_Element>& new_data) {
    element = new_data;
}



bool Tree_Node::has_child() const {
    return !children.empty();
}



size_t Tree_Node::count_children() const {
    return children.size(); 
}



void Tree_Node::clear_children() {
    children.clear();
}



void Tree_Node::Print_Node(const Tree_Node& node) const {
    if (node.element) {
        node.element->print();
    } 
}



// ----------------------------------------------------------
// TRAVERSING


// Root -> All subtrees from left to right
void Tree_Node::Traverse_KLP() const {
    
    std::stack<const Tree_Node*> stack;
    stack.push(this);  

    while(!stack.empty()) {
        const Tree_Node* curr = stack.top();
        stack.pop();

        curr->Print_Node(*curr);
        
        // reverse iterators
        for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it) {
            stack.push(it->get());
        }
    }
}



// Root -> All subtrees from right to left
void Tree_Node::Traverse_KPL() const {
    std::stack<const Tree_Node*> stack;
    stack.push(this);

    while(!stack.empty()) {
        const Tree_Node* curr = stack.top();
        stack.pop();

        curr->Print_Node(*curr);

        for (const auto& child : curr->children) {
            stack.push(child.get());
        }
    }
}



// All subtrees -> Root
void Tree_Node::Traverse_PLK() const {
    std::stack<const Tree_Node*> stack;
    std::stack<const Tree_Node*> out;
    
    stack.push(this);
    
    while (!stack.empty()) {
        const Tree_Node* curr = stack.top();
        stack.pop();
        out.push(curr);

        for (const auto& child : curr->children) {
            stack.push(child.get());
        }
    }

    while (!out.empty()) {
        const Tree_Node* node = out.top();
        out.pop();
        node->Print_Node(*node);
    }
}


// All subtrees -> Root
void Tree_Node::Traverse_LPK() const {
    std::stack<const Tree_Node*> stack;
    std::stack<const Tree_Node*> out;

    stack.push(this);

    while (!stack.empty()) {
        const Tree_Node* curr = stack.top();
        stack.pop();
        out.push(curr);

        for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it) {
            stack.push(it->get());
        }
    }

    while (!out.empty()) {
        const Tree_Node* node = out.top();
        out.pop();
        node->Print_Node(*node);
    }
}


// -----------------------------------------------------------------------

std::shared_ptr<Tree_Node> Tree_Node::Create_Tree(size_t n, std::vector<std::shared_ptr<Set_Element>>& elements) {
    if (elements.empty()) throw ERRORS::Tree_is_Empty;

    auto root = std::make_shared<Tree_Node>(elements[0]);
    std::queue<std::shared_ptr<Tree_Node>> nodes;
    nodes.push(root);

    int curr_elem = 1; // index of next element

    while (curr_elem < elements.size() && !nodes.empty()) {
        auto parent_node = nodes.front();
        nodes.pop();

        for (int i = 0; i < n && curr_elem < elements.size(); ++i) {
            auto child_node = std::make_shared<Tree_Node>(elements[curr_elem++]);
            parent_node->add_child(child_node);
            nodes.push(child_node);
        }
    }

    return root;
}




// --------------------------------------------------------------------

int main() {
    size_t n = 2;

    std::vector<std::shared_ptr<Set_Element>> elements = {
        std::make_shared<Integer_element>(10),
        std::make_shared<String_element>("Hello!"),
        std::make_shared<Complex_element>(5.2, 3.0)
    };

    auto root = Tree_Node::Create_Tree(n, elements);

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
