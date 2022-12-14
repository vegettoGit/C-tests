#include "MoveTests.h"

#include <iostream>
#include <vector>

// Note: All the below comments apply to observations being made when using the VS2019 compiler

MoveTest1::MoveTest1()
{
   m_name.reserve(32);
   m_singleChar = new char();

   std::cout << "default constructor" << std::endl;
}

MoveTest1::MoveTest1(const char* name)
{
    m_name.assign(name);
    m_singleChar = new char();
    
    std::cout << m_name.c_str() << " constructor" << std::endl;
}

MoveTest1::~MoveTest1()
{
    delete m_singleChar;
    
    std::cout << m_name.c_str() << " destructor" << std::endl;
}

MoveTest1::MoveTest1(const MoveTest1& other)
{
    m_name        = other.m_name;
    m_singleChar  = new char();
    *m_singleChar = *(other.m_singleChar);
    
    std::cout << m_name.c_str() << " copy constructor" << std::endl;
}

MoveTest1::MoveTest1(MoveTest1&& other)
{
    m_name             = std::move(other.m_name);
    m_singleChar       = other.m_singleChar;
    other.m_singleChar = nullptr;

    std::cout << m_name.c_str() << " move constructor" << std::endl;
}

MoveTest1& MoveTest1::operator = (const MoveTest1& other)
{
    if (this != &other)
    {
       m_name = other.m_name;
       *m_singleChar = *(other.m_singleChar);
    }

    std::cout << m_name.c_str() << " copy assignment" << std::endl;

    return *this;
}

MoveTest1& MoveTest1::operator = (MoveTest1&& other)
{
    if (this != &other)
    {
        m_name = std::move(other.m_name);
        std::swap(m_singleChar, other.m_singleChar);
    }

    std::cout << m_name.c_str() << " move assignment" << std::endl;

    return *this;
}

const char* MoveTest1::getName() const
{
    return m_name.c_str();
}

void MoveTest1::printName() const
{
    std::cout << m_name.c_str() << " is my name" << std::endl;
}

void helperFunction(MoveTest1 parameter)
{
    std::cout << parameter.getName() << " helper Function" << std::endl;
}

void main()
{
    MoveTest1 a("a");

    MoveTest1 b(a);                 // Copy constructor

    MoveTest1 c(MoveTest1("c"));    // Optimised to just one constructor, so no move here

    helperFunction(c);              // Copy constructor

    helperFunction(MoveTest1("d")); // Optimised to just one constructor, so no move here

    MoveTest1 e("e");

    helperFunction(std::move(e));  // Move constructor
    // e destructor called here!
    
    // e.printName(); // Danger!

    std::vector<MoveTest1> container(3);
    container[0] = MoveTest1("1st container element"); // Creates temporary, move assigns to existing vector memory, destroys temporary
    container[1] = MoveTest1("2nd container element"); // Creates temporary, move assigns to existing vector memory, destroys temporary
    container[2] = MoveTest1("3rd container element"); // Creates temporary, move assigns to existing vector memory, destroys temporary

    return;
}