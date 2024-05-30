#include "menu.hpp"
#include "N-tree.hpp"
#include "Set_element.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include <string>


std::vector<N_Ary_Tree> Trees;
static size_t N;


void Menu();
void UI();
int create_Tree(size_t N);
int Select_Tree();
int Print_Tree();
int Traversal();
int Max_depth();
int Leaf_count();
int Serialize();
int Get_diameter();
int Find();
int search();
int Insert();
int Erase();
int Check_status();
void Help_Dfs(std::stack<size_t>& result);
void Help_Bfs(std::queue<size_t>& result);



void Menu() {
    std::cout << "MENU" << std::endl;
    std::cout << std::endl;

    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Back to Menu" << std::endl;
    std::cout << "2. Create Tree" << std::endl;
    std::cout << "3. Print Tree" << std::endl;
    std::cout << "4. Check status" << std::endl;
    std::cout << "5. Get Traversal" << std::endl;
    std::cout << "6. Serialize" << std::endl;
    std::cout << "7. find" << std::endl;
    std::cout << "8. Insert (add child to node)" << std::endl;
    std::cout << "9. Erase (remove child from node)" << std::endl;


}



void UI() {
    Menu();
    int wrong_count = 5;
    int status = 1;
    std::string choise;


    while (wrong_count) {
        status = 1;
        std::cin >> choise;

        if (choise == "0"){
				exit(0);
		}
		else if (choise == "1") { // menu
			Menu();
			wrong_count = 5;
		}
		else if (choise == "2") { // create tree
            std::cout << "How many children every node in this Tree should be? Type the N parameter. " << std::endl;
            std::cin >> N; 
			status = create_Tree(N);
			if (status) {
				std::cout << "The operation was aborted\n";
			}
			else {
				std::cout << ">> ";
				std::cin >> choise;
			}
			Menu();
			wrong_count = 5;
		}
		else if (choise == "3") { // print tree
			status = Print_Tree();
			std::cout << ">> ";
			std::cin >> choise;
			if (status) {
				std::cout << "The operation was aborted\n";
			}
			Menu();
			wrong_count = 5;
		}
        else if (choise == "4") { // check state
			status = Check_status();
			std::cout << ">>> ";
			std::cin >> choise;
            if (status) {
                std::cout << "The operation was aborted\n";
            }
			Menu();
            wrong_count = 5;
		}
		else if (choise == "5") { // get traversal
			status = Traversal();
			std::cout << ">>> ";
			std::cin >> choise;
			if (status) {
				std::cout << "The operation was aborted\n";
			}
			Menu();
			wrong_count = 5;
		}
        else if (choise == "6") { // serialize
            status = Serialize();
            std::cout << ">> ";
            std::cin >> choise;
            if (status) {
                std::cout << "The operation was aborted\n";
            }
            Menu();
            wrong_count = 5;
        }
        else if (choise == "7") { // find
            status = Find();
            std::cout << ">> ";
            std::cin >> choise;
            if (status) {
                std::cout << "The operation was aborted\n";
            }
            Menu();
            wrong_count = 5;
        }
		else if (choise == "8") { // insert
			status = Insert();
			std::cout << ">> ";
			std::cin >> choise;
			if (status) {
				std::cout << "The operation was aborted\n";
			}
			Menu();
			wrong_count = 5;
		}
		else if (choise == "9") { // erase
			status = Erase();
			std::cout << ">> ";
			std::cin >> choise;
			if (status) {
				std::cout << "The operation was aborted\n";
			}
			Menu();
			wrong_count = 5;
		}
	}
}



void info(const N_Ary_Tree& tree, size_t index) {
    std::cout << "--------------------------------------------------\n";
    std::cout << "|                                                |\n";
    std::cout << "N-Ary Tree [" << index << "]" << " \n";
    try {
        size_t max_width = tree.Max_width();
        std::cout << "| " << "Max width: " << max_width << "\n";
    } catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error calculating max width: " << e.what() << std::endl;
    }
    try {
        size_t diameter = tree.find_Diameter();
        std::cout << "| " << "Diameter: " << diameter << "\n";
    }
    catch (const TREE_EXCEPTION& err) {
        std::cerr << "Error calculating diameter of this Tree" << err.what() << std::endl;
    }
    try {
        size_t node_count = tree.nodes_count();
        std::cout << "| " << "Node count: " << node_count << "\n";
    } catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error counting nodes: " << e.what() << std::endl;
    }
    try {
        size_t leaf_count = tree.Leaf_count();
        std::cout << "| " << "Leaf count: " << leaf_count << "\n";
    }
    catch(const TREE_EXCEPTION& err) {
        std::cerr << "Error counting Leafs: " << err.what() << "\n";
    }
    std::cout << "|                                                |\n";
    std::cout << "--------------------------------------------------\n";
}



int Check_status() {
	if (Trees.size() == 0) {
		std::cout << "\n";
		std::cout << "There are no trees\n";
	}
	else {
		for (int i = 0; i < Trees.size(); ++i) {
			info(Trees[i], i);
		}
	}

	return 0;
}




void Aborted() {
    std::cout << "Enter 'abort' to get out from Menu and finish the program" << std::endl;
}



bool is_valid_elem(std::string element) {
	size_t position;
	try {
		int elem = std::stoi(element, &position);

		if (position != element.length()) {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}



bool is_valid_index(const std::string& ind, size_t size) {
	size_t position;

	try {
		int index = std::stoi(ind, &position);

		if (position != ind.length()) {
			return false;
		}
		if (index < 0 || index >= size) {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}



std::vector<std::pair<std::shared_ptr<Integer_element>, size_t>> Fill_Tree(size_t N) {
    std::vector<std::pair<std::shared_ptr<Integer_element>, size_t>> elements_with_keys;
    std::cout << "Enter the root element value:" << std::endl;
    
    int root_value;
    std::cin >> root_value;

    std::shared_ptr<Integer_element> root_element = std::make_shared<Integer_element>(root_value);
    std::cout << "Enter unique key for root: ";

    size_t root_key;
    std::cin >> root_key;

    elements_with_keys.push_back(std::make_pair(root_element, root_key));

    for (size_t i = 0; i < N; ++i) {

        std::cout << "Enter element value for child node " << i + 1 << ": ";
        int value;
        std::cin >> value;
        std::shared_ptr<Integer_element> element = std::make_shared<Integer_element>(value);

        std::cout << "Enter unique key for node " << i + 1 << ": ";
        size_t key;
        std::cin >> key;

        elements_with_keys.push_back(std::make_pair(element, key));
    }
    return elements_with_keys;
}



int create_Tree(size_t N) {
    std::vector<std::pair<std::shared_ptr<Integer_element>, size_t>> elements_with_keys = Fill_Tree(N);
    if (elements_with_keys.empty()) {
        std::cerr << "No elements provided to create the tree" << std::endl;
        return 1;
    }

    try {
        std::vector<std::pair<std::shared_ptr<Set_Element>, size_t>> elements_with_keys_set_element;
        for (const auto& pair : elements_with_keys) {
            elements_with_keys_set_element.push_back(std::make_pair(std::static_pointer_cast<Set_Element>(pair.first), pair.second));
        }
        auto tree = N_Ary_Tree::Create_Tree(N, elements_with_keys_set_element);
        Trees.push_back(*tree);
        return 0;
    } 
    
    catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error creating tree: " << e.what() << std::endl;
        return 1;
    }
}



int Select_Tree() {

    Check_status();

    if (Trees.size() == 0) {
        std::cerr << "No trees available to select." << std::endl;
        return -1;
    }

    int w_count = 5;
    std::string index;

    std::cout << "Input the index of tree" << std::endl;
    while (w_count) {
        std::cout << ">> ";
        std::cin >> index;
        if (index == "abort") {
            return -1; 
        }
        if (is_valid_index(index, Trees.size())) { 
            int ind = std::stoi(index);
            return ind; 
        } 
        else {
            std::cerr << "Invalid index: " << index << " is not found. Please try again." << std::endl;
            w_count--;
        }
    }

    if (!w_count) {
        std::cerr << "Too many invalid attempts. Operation aborted." << std::endl;
        return -1; 
    }

    return -1;
}



int Print_Tree() {
    size_t choosen_Tree = Select_Tree();

    if (choosen_Tree >= 0 && choosen_Tree < Trees.size()) {
        Trees[choosen_Tree].Print_Tree();
    }
    else {
        std::cerr << "No Tree selected..." << std::endl;
    }
    return 0;
}



int Traversal() {
    size_t choosen_Tree = Select_Tree();
    if (choosen_Tree < 0) {
        return -1;
    }

    std::stack<size_t> result_Dfs;
    std::queue<size_t> result_Bfs;

    std::cout << "Choose traversal type (1 - Preorder, 2 - PostOrder_left, 3 - PostOrder_right, 4 - Level_BFS_Traverse): ";
        int traversal_type;
        std::cin >> traversal_type;
        switch (traversal_type) {

            case 1:
                Trees[choosen_Tree].Print_Tree();
                result_Dfs = Trees[choosen_Tree].Preorder_Traversal();
                std::cout << "\n" << "Preorder Traversal: ";
                Help_Dfs(result_Dfs);
                break;

            case 2:
                Trees[choosen_Tree].Print_Tree();
                result_Dfs = Trees[choosen_Tree].PostOrder_left_Traversal();
                std::cout << "\n" << "PostOrder_left Traversal: ";
                Help_Dfs(result_Dfs);
                break;

            case 3:
                Trees[choosen_Tree].Print_Tree();
                result_Dfs = Trees[choosen_Tree].PostOrder_right_Traversal();
                std::cout << "\n" << "PostOrder_right Traversal: ";
                Help_Dfs(result_Dfs);
                break;

            case 4:
                Trees[choosen_Tree].Print_Tree();
                result_Bfs = Trees[choosen_Tree].Level_BFS_Traverse();
                std::cout << "\n" << "Level_Bfs Traversal: ";
                Help_Bfs(result_Bfs);
                break;

            default:
                std::cerr << "Invalid traversal type" << std::endl;
                return 1;
    }
    return 0;
}


void Help_Dfs(std::stack<size_t>& result) {
    while (!result.empty()) {
        std::cout << result.top() << " -> ";
        result.pop();
    }
    std::cout << std::endl;
}



void Help_Bfs(std::queue<size_t>& result) {
    while (!result.empty()) {
        std::cout << result.front() << " -> ";
        result.pop();
    }
    std::cout << std::endl;
}



int Max_depth() {
    size_t choosen_Tree = Select_Tree();
    if (choosen_Tree < 0) {
        return -1;
    }
    try {
        size_t depth = Trees[choosen_Tree].find_Diameter();
        std::cout << "Max depth of the tree is: " << depth << std::endl;
        return 0;
    } catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error calculating max depth: " << e.what() << std::endl;
        return 1;
    }
}



int Leaf_count() {
    size_t choosen_Tree = Select_Tree();
    if (choosen_Tree < 0) {
        return -1;
    }
    try {
        size_t count = Trees[choosen_Tree].Leaf_count();
        std::cout << "Leaf count of the tree is: " << count << std::endl;
        return 0;
    } catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error counting leafs: " << e.what() << std::endl;
        return 1;
    }
}



int Serialize() {
    size_t choosen_Tree = Select_Tree();
        
    try {
        std::string serialized = Trees[choosen_Tree].serialize_dfs();
        std::cout << "Serialized tree: " << serialized << std::endl;
        return 0;
    } catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error serializing tree: " << e.what() << std::endl;
        return 1;
    }
}



int Get_diameter() {
    size_t choosen_Tree = Select_Tree();
    
    try {
        size_t diameter = Trees[choosen_Tree].find_Diameter();
        std::cout << "Diameter of the tree is: " << diameter << std::endl;
        return 0;
    } catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error calculating diameter: " << e.what() << std::endl;
        return 1;
    }
}



int Find() {
    size_t choosen_Tree = Select_Tree();

    Trees[choosen_Tree].Print_Tree();
    std::cout << std::endl;
    
    std::cout << "Enter key to find: ";
    size_t key;
    std::cin >> key;
    try {
        std::shared_ptr<Set_Element> found = Trees[choosen_Tree].find_by_key(key);
        std::shared_ptr<Integer_element> casted_found = std::static_pointer_cast<Integer_element>(found);
        std::cout << "Found element: ";
        casted_found->print();
        std::cout << std::endl;
        return 0;
    } catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error finding element: " << e.what() << std::endl;
        return 1;
    }
}



int Insert() {
    size_t choosen_Tree = Select_Tree();

    

    std::cout << "Enter parent node key: ";
    size_t parent_key;
    std::cin >> parent_key;


    std::shared_ptr<Tree_Node> parent_node = Trees[choosen_Tree].find_node_by_key(parent_key);


    if (!parent_node) {
        std::cerr << "Parent node with key " << parent_key << " not found" << std::endl;
        return 1;
    }

    std::cout << "Enter new child value: ";
    int child_value;
    std::cin >> child_value;

    
    std::shared_ptr<Set_Element> child_data = std::make_shared<Integer_element>(child_value);

    
    std::shared_ptr<Tree_Node> new_child_node = std::make_shared<Tree_Node>(child_data, parent_key + 1); 

    try {
        
        parent_node->add_child(new_child_node, Trees[choosen_Tree]);
        return 0;
    } catch (const TREE_EXCEPTION& e) {
        std::cerr << "Error inserting child: " << e.what() << std::endl;
        return 1;
    }
}



int Erase() {
    size_t choosen_Tree = Select_Tree();

    std::cout << "Enter node key to erase: ";
    size_t node_key;
    std::cin >> node_key;

    
    std::shared_ptr<Tree_Node> node = Trees[choosen_Tree].find_node_by_key(node_key);
    if (!node) {
        std::cerr << "Node with key " << node_key << " not found" << std::endl;
        return 1;
    }

    
    if (node->is_Root()) {
        std::cerr << "Cannot erase root node directly" << std::endl;
        return 1;
    }

    
    Tree_Node* parent_node = node->Parent;

    try {
        
        parent_node->remove_child(node, Trees[choosen_Tree]);

        
        node->clear_children();

        
        node.reset();

        return 0;
    } 
    catch (const TREE_EXCEPTION& err) {
        std::cerr << "Error erasing node: " << err.what() << std::endl;
        return 1;
    }
}

