#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <complex>


class Set_Element {
    
public:
    
    virtual ~Set_Element() = default;
    
    virtual bool is_Equal(const std::shared_ptr<Set_Element>& other) const = 0;

    virtual void print() const = 0;
};


// ----------------------------------------------------------------------------


class Integer_element : public Set_Element {
private:
    int item;

public:
    
    Integer_element(int value) : item(value) {}

    bool is_Equal(const std::shared_ptr<Set_Element>& other) const override {

        auto casted = std::dynamic_pointer_cast<Integer_element>(other);
        // dynamic cast for verification that object 'other' is Integer_element
    
        if (casted) {
            return item == casted->item;
        }

        else {
            return false;
        }
    }

    void print() const override {
        std::cout << this->item;
    }
};


// ----------------------------------------------------------------------------


class Real_element : public Set_Element {
private:
    double item;

public:
    Real_element(double value) : item(value) {}

    bool is_Equal(const std::shared_ptr<Set_Element>& other) const override {
        auto casted = std::dynamic_pointer_cast<Real_element>(other);
        // dynamic cast for verification that object 'other' is Real_element

        if (casted) {
            return item == casted->item;
        }
        else {
            return false;
        }
    }

    void print() const override {
        std::cout << this->item;
    }
};


// ----------------------------------------------------------------------------


class Complex_element : public Set_Element {
private:
    std::complex<double> item;

public:
    Complex_element(double RE, double IM) : item(RE, IM) {}

    bool is_Equal(const std::shared_ptr<Set_Element>& other) const override {
        auto casted = std::dynamic_pointer_cast<Complex_element>(other);

        if (casted) {
            return item == casted->item;
        }
        else {
            return false;
        }
    }

    void print() const override {
        std::cout << "(" << item.real() << item.imag() << ")";
    }
};


// --------------------------------------------------------------------------


class String_element : public Set_Element {
private:
    std::string item;

public:
    String_element(std::string str) : item(str) {}

    bool is_Equal(const std::shared_ptr<Set_Element>& other) const override {
        auto casted = std::dynamic_pointer_cast<String_element>(other);

        if (casted) {
            return item == casted->item;
        }
        else {
            return false;
        }
    }

    void print() const override {
        std::cout << this->item;
    }  
};


// -------------------------------------------------------------------------


class Base_Function {
private:
    virtual~Base_Function() = default;
    virtual std::string Func_name() const = 0;
    virtual void call_function() = 0;

};


template <typename Return_Type, typename... Args>
class Function_element : public Base_Function {
private:
    // general pointer to function
    std::function<Return_Type(Args...)> func;
    std::string Fn_name;

public:
    Function_element(std::function<Return_Type(Args...)> fn, const std::string& name) : func(fn), Fn_name(name) {}
    
    void call_function() override {
        Return_Type result = func();
    }

    std::string Func_name() const override {
        std::cout << this->Fn_name;
    }
};


// ------------------------------------------------------------------------


struct Person_ID {
    std::string series;
    std::string number;

    Person_ID(const std::string& ser, const std::string& num) : series(ser), number(num) {}

    // operator overloading for comparing fields
    bool operator==(const Person_ID& other) const {
        return this->series == other.series && this->number == other.number;
    }
};


class Person {
private:
    Person_ID Id;
    std::string first_Name;
    std::string middle_Name;
    std::string last_Name;
    time_t birth_Date;

public:
    Person(
        const Person_ID& id,
        const std::string& first_Name,
        const std::string& middle_Name,
        const std::string& last_Name,
        time_t birth_Date) :
        Id(id),
        first_Name(first_Name),
        middle_Name(middle_Name),
        last_Name(last_Name),
        birth_Date(birth_Date) {}

    // Getters
    Person_ID Get_ID() const { return Id;}
    std::string Get_First_Name() const {return first_Name;}
    std::string Get_Middle_Name() const {return middle_Name;}
    std::string Get_Last_Name() const {return last_Name;}
    time_t Get_Birth_Date() const {return birth_Date;}
};


class Student_element : public Person, public Set_Element {
private:
    double Avg_mark;

public:

    Student_element (
                const Person_ID& id,
                const std::string& first_Name,
                const std::string& middle_Name,
                const std::string& last_Name,
                time_t birth_Date
                ) : Person (id, first_Name, middle_Name, last_Name, birth_Date) {}

    bool is_Equal(const std::shared_ptr<Set_Element>& other) const override {
        auto casted = std::dynamic_pointer_cast<Student_element>(other);

        if (casted) {
            return this->Get_ID() == casted->Get_ID();
        }
        else {
            return false;
        }
    }


    void print() const override {
        std::cout 
            << "Student: " 
            << Get_First_Name() 
            << " " 
            << Get_Middle_Name() 
            << " " 
            << Get_Last_Name() 
            << ", ID: " 
            << Get_ID().series 
            << Get_ID().number 
            << ", Birth Date: " 
            << Get_Birth_Date()
            << "AVG mark: "
            << this->Avg_mark;
    }

};


// -------------------------------------------------------------


class Teacher_element : public Person, public Set_Element {
private:
    std::string department;

public:
    Teacher_element (
        const Person_ID& id,
        const std::string& f_name,
        const std::string& mid_name,
        const std::string& last_name,
        time_t birth_datenumber,
        std::string depart
        ) : Person (
                id,
                f_name,
                mid_name,
                last_name,
                birth_datenumber
                )
                {}


    bool is_Equal(const std::shared_ptr<Set_Element>& other) const override {
        auto casted = std::dynamic_pointer_cast<Teacher_element>(other);

        if (casted) {
            return this->department == casted->department;
        }
        else {
            return false;
        }
    }


    void print() const override {
        std::cout 
        << "Teacher: "
        << Get_First_Name()
        << " "
        << Get_Middle_Name()
        << " "
        << Get_Last_Name()
        << " ID:"
        << Get_ID().series
        << Get_ID().number
        << " , Birth date:"
        << Get_Birth_Date();
    }

    std::string Get_department() const {
        return this->department;
    }

};
