#pragma once

#include <exception>


enum class ERRORS {
    Index_Out_Of_Range,
    Tree_is_Empty,
    Node_is_a_Leaf,
    Memory_allocation_error,
    Null_pointer_error
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
                return "this Sequence is empty!";

            case ERRORS::Memory_allocation_error:
                return "Memory_allocation_error!";

            default:
                return "Unknown error";
        }
    }
};


