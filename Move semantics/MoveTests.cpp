#include "MoveTests.h"

#include <iostream>


MoveTest1::MoveTest1(const char* name)
{
	m_name.assign(name);
	m_movableData = new char();
    
	std::cout << m_name.c_str() << " constructor" << std::endl;
}

MoveTest1::~MoveTest1()
{
	delete m_movableData;
    
	std::cout << m_name.c_str() << " destructor" << std::endl;
}

MoveTest1::MoveTest1(const MoveTest1& other)
{
	m_name              = other.m_name;
	m_movableData       = new char();
	*m_movableData      = *(other.m_movableData);
    
	std::cout << m_name.c_str() << " copy constructor" << std::endl;
}

MoveTest1::MoveTest1(MoveTest1&& other)
{
    m_name              = other.m_name;
	m_movableData       = other.m_movableData;
	other.m_movableData = nullptr;

    std::cout << m_name.c_str() << " move constructor" << std::endl;
}

MoveTest1 & MoveTest1::operator= (const MoveTest1&)
{
    std::cout << m_name.c_str() << " copy assignment" << std::endl;

    return *this;
}

MoveTest1& MoveTest1::operator = (MoveTest1&& other)
{
    if (this != &other)
    {
        m_name              = other.m_name;
		m_movableData       = other.m_movableData;
		other.m_movableData = nullptr;
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

    return;
}