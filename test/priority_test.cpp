/*
 * MIT License
 *
 * Copyright (c) 2018 namreeb (legal@namreeb.org) http://github.com/namreeb/useful_containers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "priority.hpp"

#include <iostream>

struct MyClass
{
    int i;

    MyClass() : i(0)
    {
        std::cout << "MyClass()" << std::endl;
    }

    MyClass(int _i) : i(_i)
    {
        std::cout << "MyClass(" << i << ")" << std::endl;
    }

    MyClass(const MyClass &other) : i(other.i)
    {
        std::cout << "MyClass() copy" << std::endl;
    }
};

int main()
{
    constexpr std::size_t count = 10;
    nam::priority<MyClass, std::size_t, count> prio;

    std::cout << "Empty iteration start..." << std::endl;
    for (auto const &i : prio)
        std::cout << "i: " << i.i << std::endl;
    std::cout << "Empty iteration stop.  Should have been empty above." << std::endl;

    for (auto i = 0u; i < count/2; ++i)
        prio.insert(i, static_cast<int>(i));

    std::cout << "priority_test size(): " << prio.size() << " (should be 5) dumping..." << std::endl;

    for (auto const &i : prio)
        std::cout << "i: " << i.i << std::endl;

    std::cout << "filling..." << std::endl;

    for (auto i = count / 2; i < count; ++i)
        prio.emplace(i, static_cast<int>(i));

    prio.emplace(5u, 1234);

    std::cout << "size(): " << prio.size() << " (should be 10)" << std::endl;

    for (auto const &i : prio)
        std::cout << "i: " << i.i << std::endl;

    auto a = prio.begin();
    auto b = prio.end();
    a = b;

    return 0;
}