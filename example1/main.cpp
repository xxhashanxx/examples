#include "foo.h"
#include <iostream>
#include <functional>
void foo(char *);
void foo(int);


//Fold expression
template <typename... T>
auto sum(T... t)
{
    return (t + ...);
}
int main()
{
    //extern C example
    [out = std::ref(std::cout << "Result from C code: " << add(1, 2))]()
    {
        out.get() << ".\n";
    }();

//////////////////////////////////////////////////////////////////////////////////////////////////////////
    //nullptr example
    std::cout << std::is_same<decltype(NULL), decltype(NULL)>::value << std::endl;
    if (std::is_same<decltype(NULL), decltype(0)>::value)
        std::cout << "NULL == 0" << std::endl;
    if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
        std::cout << "NULL == (void *)0" << std::endl;
    if (std::is_same<decltype(NULL), std::nullptr_t>::value)
        std::cout << "NULL == nullptr" << std::endl;
    foo(0); // will call foo(int)
    // foo(NULL); // doesn't compile
    foo(nullptr); // will call foo(char*)

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//decltype example
    auto x = 1;
    auto y = 2;
    decltype(x + y) z;
    if (std::is_same<decltype(x), int>::value)
        std::cout << "type x == int" << std::endl;
    if (std::is_same<decltype(x), float>::value)
        std::cout << "type x == float" << std::endl;
    if (std::is_same<decltype(x), decltype(z)>::value)
        std::cout << "type z == type x" << std::endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;

    return 0;
}
template <typename R, typename T, typename U>
R add(T x, U y)
{
    return x + y;
}
template <typename T, typename U>
auto add2(T x, U y) -> decltype(x + y)
{
    return x + y;
}
template <typename T, typename U>
auto add3(T x, U y)
{
    return x + y;
}

void foo(char *)
{
    std::cout << "foo(char*) is called" << std::endl;
}
void foo(int i)
{
    std::cout << "foo(int) is called" << std::endl;
}


///////////////////////////////////////////////////////////////
//return decltype(auto)
std::string lookup1(){
    std::cout << "lookup1" << std::endl;
    return "lookup1";
}
std::string& lookup2(){
    std::cout << "lookup2" << std::endl;
    std::string *a = new std::string("lookup2");
    return *a;
}
std::string look_up_a_string_1()
{
    return lookup1();
}
std::string &look_up_a_string_2()
{
    return lookup2();
}

decltype(auto) look_up_a_string_1c11()
{
    return lookup1();
}
decltype(auto) look_up_a_string_2C11()
{
    return lookup2();
}

/////////////////////////////////////////////////
template <typename T, int BufSize>
class buffer_t
{
public:
    T &alloc();
    void free(T &item);

private:
    T data[BufSize];
};

class example
{
    public:
        buffer_t<int, 100> buf;// 100 as template parameter
};


///////////////////////////////////////////////////////////////////
//Delegate constructor
#include <iostream>
class Base
{
public:
    int value1;
    int value2;
    Base()
    {
        value1 = 1;
    }
    Base(int value) : Base()
    { // delegate Base() constructor
        value2 = value;
    }
};