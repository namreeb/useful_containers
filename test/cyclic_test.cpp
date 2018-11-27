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

#include "cyclic.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <array>

struct MyStruct
{
    int a;
    int b;
    std::string str;
};

class Store
{
private:
    nam::cyclic<MyStruct, 5> members;
    std::vector<MyStruct> vec;

public:
    void Add(int a, int b, std::string &&c)
    {
        members.push_back({ a, b, c });
        vec.push_back({ a, b, c });
    }

    void DumpAll() const
    {
        auto begin = vec.begin();
        auto b2 = members.begin();

        auto end = vec.end();
        auto e2 = members.end();

        for (auto const &m : vec)
            std::cout << m.a << " " << m.b << " " << m.str << std::endl;
    }
};

int main()
{
    nam::cyclic<MyStruct, 5> cyc;

    std::cout << "cyclic_test" << std::endl;
    
    std::cout << "size() should be 0: " << cyc.size() << std::endl;
    std::cout << "empty() should be true: " << (cyc.empty() ? "true" : "false") << std::endl;

    const MyStruct x { 1, 2, "hithere" };

    cyc.push_back(x);
    cyc.push_back(x);
    cyc.push_back(x);

    std::cout << "size() should be 3: " << cyc.size() << std::endl;

    cyc.push_back(x);
    cyc.push_back(x);
    cyc.push_back(x);

    std::cout << "size() should be 5: " << cyc.size() << std::endl;

    auto a = cyc.begin();
    auto b = cyc.end();
    a = b;

    Store myStore;
    myStore.Add(1, 2, "asdf");
    myStore.DumpAll();

    // just to make sure it compiles
    for (auto const &i : cyc)
        std::cout << "i: " << i.str << std::endl;

    constexpr std::size_t intsize = 10;
    nam::cyclic<int, intsize> cycint;

    for (auto i = 0u; i < intsize*10; ++i)
        cycint.push_back(static_cast<int>(i));

    for (auto const &i : cycint)
        std::cout << "i: " << i << std::endl;

    return 0;
}