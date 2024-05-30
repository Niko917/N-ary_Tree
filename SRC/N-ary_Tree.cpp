#include "N-tree.hpp"
#include "Set_element.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <sstream>
#include <stack>
#include <strstream>
#include <unordered_map>
#include <unordered_set>

size_t N_Ary_Tree::N = 0;

//METHODS FOR NODE


void Tree_Node::add_child(const std::shared_ptr<Tree_Node>& child, N_Ary_Tree& tree) {

    if (this->children.size() >= N_Ary_Tree::N) {
        throw TREE_EXCEPTION{ERRORS::Too_many_children};
    }

    if (tree.used_keys.find(child->element_with_Key.second) != tree.used_keys.end()) {
        throw TREE_EXCEPTION{ERRORS::Dublicate_Key};
    }


    tree.used_keys.insert(child->element_with_Key.second);

    child->Parent = this;
    children.push_back(child);
    tree.info.push_back(child->element_with_Key);
}



void Tree_Node::remove_child(const std::shared_ptr<Tree_Node>& child, N_Ary_Tree& tree) {

    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        (*it)->Parent = nullptr;
        children.erase(it);
        tree.used_keys.erase(child->element_with_Key.second);
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
    return element_with_Key.first;
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
    element_with_Key.first->print();
}



size_t Tree_Node::Print_key() const {
    return this->element_with_Key.second;
}



bool Tree_Node::is_Root() const {
    return Parent == nullptr;
}



bool Tree_Node::is_Leaf() const {
    return children.empty();
}



// ----------------------------------------------------------
// TREE IPLEMENTATION


std::shared_ptr<N_Ary_Tree> N_Ary_Tree::Create_Tree(size_t n, std::vector<std::pair<std::shared_ptr<Set_Element>, size_t>>& elements_with_keys) {

    N_Ary_Tree::N = n;

    if (elements_with_keys.empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    auto root_node = std::make_shared<Tree_Node>(elements_with_keys[0].first, elements_with_keys[0].second);

    auto tree = std::make_shared<N_Ary_Tree>(root_node);
    tree->used_keys.insert(elements_with_keys[0].second); // add rott key to used_keys

    std::queue<std::shared_ptr<Tree_Node>> nodes;
    nodes.push(root_node);

    size_t curr_elem = 1; // index of next element

    while (curr_elem < elements_with_keys.size() && !nodes.empty()) {
        auto parent_node = nodes.front();
        nodes.pop();

        for (int i = 0; i < n && curr_elem < elements_with_keys.size(); ++i) {
            auto child_node = std::make_shared<Tree_Node>(elements_with_keys[curr_elem].first, elements_with_keys[curr_elem].second);

            parent_node->add_child(child_node, *tree);
            nodes.push(child_node);
            curr_elem++;
        }
    }

    return tree;
}



void N_Ary_Tree::Destroy_Tree() {
    if (!is_Empty()) {
        std::stack<std::shared_ptr<Tree_Node>> node_stack;
        node_stack.push(this->root);

        while(!node_stack.empty()) {
            auto current = node_stack.top();
            node_stack.pop();

            for (auto& child : current->children) {
                node_stack.push(child);
            }

            current->children.clear();
            current->Parent = nullptr;
        }

        root.reset();
    }
}



std::shared_ptr<Tree_Node> N_Ary_Tree::get_root() const {
    return this->root;
}


void N_Ary_Tree::set_data(const std::shared_ptr<Tree_Node>& Node, const std::shared_ptr<Set_Element>& new_data) {
    Node->element_with_Key.first = new_data;    
}



size_t N_Ary_Tree::Max_width() const {
    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    size_t max_width = 0;

    std::queue<std::shared_ptr<Tree_Node>> q;


    q.push(root);

    while (!q.empty()) {
        size_t level_size = q.size();

        max_width = std::max(max_width, level_size);

        for (size_t i = 0; i < level_size; ++i) {
            auto node = q.front();
            q.pop();

            for (const auto& child : node->children) {
                q.push(child);
            }
        }
    }
    return max_width;
}



size_t N_Ary_Tree::find_Diameter() const {
    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    size_t diameter = 0;

    // first BFS

    std::queue<std::shared_ptr<Tree_Node>> q;

    std::unordered_map<std::shared_ptr<Tree_Node>, size_t> distance;

    q.push(root);

    distance[root] = 0;

    std::shared_ptr<Tree_Node> farthest_node = root;

    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        for (const auto& child : node->children) {
            q.push(child);
            distance[child] = distance[node] + 1;
            if (distance[child] > diameter) {
                diameter = distance[child];
                farthest_node = child;
            }
        }
    }

    // second BFS
    
    q = std::queue<std::shared_ptr<Tree_Node>>();
    q.push(farthest_node);
    distance.clear();
    distance[farthest_node] = 0;

    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        for (const auto& child : node->children) {
            q.push(child);
            distance[child] = distance[node] + 1;
            diameter = std::max(diameter, distance[child]);
        }
    }

    return diameter;
}



size_t N_Ary_Tree::Leaf_count() const {

    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Node_is_a_Leaf};
    
    size_t Leaf_cnt = 0;

    std::stack<std::shared_ptr<Tree_Node>> nodes_stack;

    nodes_stack.push(this->root);

    while (!nodes_stack.empty()) {
        auto curr = nodes_stack.top();
        nodes_stack.pop();

        if (curr->children.empty()) {
            Leaf_cnt++;
        }
        else {
            for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it) {
                nodes_stack.push(*it);
            }
        }
    }
    return Leaf_cnt;
}



bool N_Ary_Tree::is_Empty() const {
    return (this->root == nullptr);
}



size_t N_Ary_Tree::nodes_count() const {

    if (is_Empty()) TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    size_t nodes_cnt = 0;

    std::stack<std::shared_ptr<Tree_Node>> node_stack;

    node_stack.push(this->root);


    while(!node_stack.empty()) {
        auto current  = node_stack.top();
        node_stack.pop();

        nodes_cnt++;

        for (const auto& child : current->children) {
            node_stack.push(child);
        }
    }
    return nodes_cnt;
}



std::shared_ptr<Set_Element> N_Ary_Tree::find_by_key(size_t given_key) const {

    if (is_Empty()) TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    std::stack<std::shared_ptr<Tree_Node>> nodes_stack;

    nodes_stack.push(this->root);

    while (!nodes_stack.empty()) {
        auto current = nodes_stack.top();
        nodes_stack.pop();

        if (current->element_with_Key.second == given_key) {
            return current->element_with_Key.first;
        }
        
        for (auto& child : current->children) {
                nodes_stack.push(child);
        }
    }
    throw TREE_EXCEPTION{ERRORS::Key_not_found};
}




size_t N_Ary_Tree::find_by_value(const std::shared_ptr<Set_Element>& value) const {
    
    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};


    std::stack<std::shared_ptr<Tree_Node>> nodes_stack;

    nodes_stack.push(this->root);

    while (!nodes_stack.empty()) {
        auto current = nodes_stack.top();

        nodes_stack.pop();

        if ((current->element_with_Key.first->is_Equal(value))) {
            return current->element_with_Key.second;
        }

        for (auto& child : current->children) {
            nodes_stack.push(child);
        }
    }
}



std::shared_ptr<Tree_Node> N_Ary_Tree::find_node_by_key(size_t key) const {
    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    std::stack<std::shared_ptr<Tree_Node>> nodes_stack;

    nodes_stack.push(this->root);

    while (!nodes_stack.empty()) {
        auto curr = nodes_stack.top();
        nodes_stack.pop();

        if (curr->element_with_Key.second == key) {
            return curr;
        }

        for (auto& child : curr->children) {
            nodes_stack.push(child);
        }
    }


}



//from left to right
std::string N_Ary_Tree::serialize_dfs() const {
    std::ostringstream oss;
    std::stack<std::shared_ptr<Tree_Node>> nodes_stack;

    nodes_stack.push(root);

    while (!nodes_stack.empty()) {

        auto current = nodes_stack.top();
        nodes_stack.pop();

        if (current) {
            oss << "{" << current->Print_key() << "}";

            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                nodes_stack.push(*it);
            }
        }
    }
    return oss.str();
}



void N_Ary_Tree::show(const std::shared_ptr<Tree_Node>& node, size_t depth) const {
    if (!node) return;

    for (size_t i = 0; i < depth; ++i) {
        std::cout << "|     "; // five backspaces for each level
    }

    std::cout << "+ --- " << node->element_with_Key.second << std::endl;

    for (const auto& child : node->children) {
        show(child, depth + 1);
    }
}


void N_Ary_Tree::Print_Tree() const {
    show(this->root, 0);
}


// ----------------------------------------------------------
// TRAVERSING


std::stack<size_t> N_Ary_Tree::Preorder_Traversal() const {
    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    std::stack<std::shared_ptr<Tree_Node>> stack;
    std::vector<size_t> nodes;
    stack.push(this->root);

    while (!stack.empty()) {
        auto curr = stack.top();
        stack.pop();
        nodes.push_back(curr->element_with_Key.second);

        for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it) {
            stack.push(*it);
        }
    }


    std::stack<size_t> out;
    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
        out.push(*it);
    }

    return out;
}




std::stack<size_t> N_Ary_Tree::PostOrder_left_Traversal() const {

    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    std::stack<std::shared_ptr<Tree_Node>> stack;
    std::stack<size_t> out;
    
    stack.push(this->root);
    
    while (!stack.empty()) {
        auto curr = stack.top();
        stack.pop();

        out.push(curr->element_with_Key.second);

        for (auto it = curr->children.begin(); it != curr->children.end(); ++it) {
            stack.push(*it);
        }
    }

    return out;
}



std::stack<size_t> N_Ary_Tree::PostOrder_right_Traversal() const {

    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    std::stack<std::shared_ptr<Tree_Node>> stack_nodes;
    std::stack<size_t> out;

    stack_nodes.push(this->root);

    while (!stack_nodes.empty()) {
        auto curr = stack_nodes.top();
        stack_nodes.pop();

        out.push(curr->element_with_Key.second);

        for (auto it = curr->children.rbegin(); it != curr->children.rend(); ++it) {
            stack_nodes.push(*it);
        }
    }

    return out;
}



std::queue<size_t> N_Ary_Tree::Level_BFS_Traverse() const {

    if (is_Empty()) throw TREE_EXCEPTION{ERRORS::Tree_is_Empty};

    std::queue<std::shared_ptr<Tree_Node>> q;
    std::queue<size_t> out;

    q.push(this->root);

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        out.push(curr->element_with_Key.second);

        for (const auto& child : curr->children) {
            q.push(child);
        }
    }
    return out;
}



// --------------------------------------------------------------------

