#include "Tests_Nodes.hpp"
#include "N-tree.hpp"
#include "Set_element.hpp"
#include "exceptions.hpp"
#include <ctime>
#include <iostream>
#include <memory>
#include <assert.h>

/*

void Test_for_Nodes() {

    // ----------------------------------------------
    // Elements for Tests

    std::shared_ptr<Set_Element> Integer = std::make_shared<Integer_element>(5);

    std::shared_ptr<Set_Element> Real = std::make_shared<Real_element>(3.14);

    std::shared_ptr<Set_Element> Complex = std::make_shared<Complex_element>(5.2, 3.0);

    std::shared_ptr<Set_Element> String = std::make_shared<String_element>("Hello, my name is Nikolay!");
    
    
    Person_ID id_1("AB", "123456");
    Person_ID id_2("BS", "124856");

    Student_element Student(id_1, "Nikolay", "Andreevich", "Kolb", std::time(nullptr), 85.5);

    Teacher_element Teacher(id_2, "Dmitriy", "Sergeevich", "Telyakovskiy", std::time(nullptr), "Analysis");

    std::shared_ptr<Set_Element> stud = std::make_shared<Student_element>(Student);

    std::shared_ptr<Set_Element> teacher = std::make_shared<Teacher_element>(Teacher);

    assert(!stud->is_Equal(teacher));
    
    // ----------------------------------------------
    // Methods Tests

    auto Int_Node = std::make_shared<Tree_Node>(Integer, nullptr);
    auto Str_Node = std::make_shared<Tree_Node>(String, nullptr);

    //Int_Node->add_child(Str_Node);
    assert(Int_Node->Parent == nullptr);
    assert(Str_Node->Parent == Int_Node.get());
    assert(Int_Node->get_child(0) == Str_Node);


    // 1. add_child, is_Root, is_Leaf
    auto root = std::make_shared<Tree_Node>();
    assert(root->is_Root());
    assert(root->is_Leaf());

    auto child_1 = std::make_shared<Tree_Node>();

    //root->add_child(child_1);
    assert(root->get_child(0) == child_1);
    assert(child_1->Parent == root.get());
    assert(!root->is_Leaf());
    assert(child_1->is_Root() == false);
    assert(child_1->is_Leaf());

    auto grandchild = std::make_shared<Tree_Node>();
    //child_1->add_child(grandchild);

    assert(!child_1->is_Leaf());
    assert(grandchild->is_Leaf());


    // 2. remove_child
    //root->remove_child(child_1);
    assert(child_1->Parent == nullptr);


    // 3. get_child
    auto child_2 = std::make_shared<Tree_Node>();
    //root->add_child(child_2);
    assert(root->get_child(0) == child_2);

    try {
        root->get_child(4);
        std::cerr << "This line should not be reached if an exception is thrown." << std::endl;
        assert(false);
    }
    catch (const TREE_EXCEPTION& err) {
        std::cerr << "Caught TREE_EXCEPTION with error: " << err.what() << std::endl;
    }

    



    // 4. methods with children
    //std::cout << root->get_data() << "\n"
    //    << root->has_child() << "\n"
    //    << root->count_children() << "\n";
    //assert(true);


    // 5. clear_children 
    Int_Node->clear_children();
    assert(!(Int_Node->has_child()));


    // 6. Print_Node
    // std::cout << "Int_Node element is : ";
    Int_Node->Print_Node();
    // std::cout << std::endl;
   

    std::cout << "Tree Node tests passed! \n";
    
}
*/
