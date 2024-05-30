#pragma once

#include <exception>


enum class ERRORS {
    Index_Out_Of_Range,
    Tree_is_Empty,
    Node_is_a_Leaf,
    Memory_allocation_error,
    Null_pointer_error,
    Node_not_found,
    Dublicate_Key,
    Key_not_found,
    Too_many_children,
    Removed_parent
};



struct TREE_EXCEPTION : public std::exception {
    ERRORS error;

    TREE_EXCEPTION(ERRORS err) : error(err) {}

    const char* what() const throw() {
        switch (error) {
            case ERRORS::Index_Out_Of_Range:
                return "Index is out of range!";

            case ERRORS::Null_pointer_error:
                return "nullptr error!";

            case ERRORS::Tree_is_Empty:
                return "this Tree is empty!";

            case ERRORS::Memory_allocation_error:
                return "Memory_allocation_error!";

            case ERRORS::Node_not_found:
                return "This Node wasn't found!";

            case ERRORS::Dublicate_Key:
                return "This Key isn't unique!";

            case ERRORS::Key_not_found:
                return "This Key not found!";

            case ERRORS::Too_many_children:
                return "Too many children! (>= N)";

            case ERRORS::Removed_parent:
                return "Parent of this node was removed";

            default:
                return "Unknown error";
        }
    }
};


