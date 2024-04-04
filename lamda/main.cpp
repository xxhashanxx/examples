
#include <functional>
#include <iostream>
/*
[capture list] (parameter list) mutable(optional) exception attribute -> return type {
// function body
}
*/

/// @brief Value capture in lambda ////////////////////////////////////////////////////
void lambda_value_capture()
{
    int value = 1;
    auto copy_value = [value]
    {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // At this moment, stored_value == 1, and value == 100.
    // Because copy_value has copied when its was created.
}

/// @brief  Reference capture //////////////////////////
void lambda_reference_capture()
{
    int value = 1;
    auto copy_value = [&value]
    {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // At this moment, stored_value == 100, value == 100.
    // Because copy_value stores reference
}

// 3. Implicit capture ///////////////////////////////////////////////////////////
/*
• [] empty capture list
• [name1, name2, …] captures a series of variables
• [&] reference capture, let the compiler deduce the reference list by itself
• [=] value capture, let the compiler deduce the value list by itself
*/

/// @brief 4. Expression capture //////////////////////////////////////////////////////////////

#include <memory>  // std::make_unique
#include <utility> // std::move
void lambda_expression_capture()
{
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int
    {
        return x + y + v1 + (*v2);
    };
    std::cout << add(3, 4) << std::endl;
}

/// @brief Generic Lambda /////////////////////////////////////////////////////////
void lambda_generic()
{
    auto generic = [](auto x, auto y)
    {
        return x + y;
    };
    std::cout << generic(1, 2) << std::endl;
    std::cout << generic(1.1, 2.2) << std::endl;
}
//////////////////////////////////////////////////////////////////////
//way 1 with out std::function
using foo1 = void(int); // function pointer
void functional(foo1 f)
{
    f(1);
}

int main1()
{
    auto f = [](int value)
    {
        std::cout << value << std::endl;
    };
    functional(f); // call by function pointer
    f(1);          // call by lambda expression
    return 0;
}
//way 2 with std::function
int foo(int para)
{
    return para;
}
int main()
{
    // std::function wraps a function that take int paremeter and returns int value
    std::function<int(int)> func = foo;
    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int
    {
        return 1 + value + important;
    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
}

////std::bind and std::placeholder////////////////////////////////////////////////////////
int foo2(int a, int b, int c)
{
    ;
}
int main2()
{
    // bind parameter 1, 2 on function foo,
    // and use std::placeholders::_1 as placeholder for the first parameter.
    auto bindFoo = std::bind(foo2, std::placeholders::_1, 1, 2);
    // when call bindFoo, we only need one param left
    bindFoo(1);
}