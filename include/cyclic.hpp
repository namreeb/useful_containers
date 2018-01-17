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

#ifndef __CYCLIC_HPP_
#define __CYCLIC_HPP_

#include <array>
#include <memory>

namespace nam
{
template <typename T, std::size_t N> class cyclic;

template <typename CyclicEntryT, std::size_t N>
class CyclicIterator : public std::iterator<std::input_iterator_tag, CyclicEntryT>
{
private:
    friend class nam::cyclic<CyclicEntryT, N>;

    nam::cyclic<CyclicEntryT, N> * _me;
    std::size_t _idx;

    CyclicIterator(nam::cyclic<CyclicEntryT, N> *container, std::size_t idx) noexcept : _me(container), _idx(idx) {}

public:
    using BaseIteratorT = std::iterator<std::input_iterator_tag, CyclicEntryT>;
    using reference = typename BaseIteratorT::reference;

    reference operator*() const
    {
        return _me->operator[](_idx);
    }

    bool operator == (CyclicIterator<CyclicEntryT, N> const &other) const noexcept
    {
        return _me == other._me && _idx == other._idx;
    }

    bool operator != (CyclicIterator<CyclicEntryT, N> const &other) const noexcept
    {
        return !(*this == other);
    }

    CyclicIterator& operator++()
    {
        ++_idx;
        return *this;
    }
};

template <typename T, std::size_t N>
class cyclic
{
private:
    bool _filled;
    std::size_t _curr;
    std::array<T, N> _raw;

public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = CyclicIterator<T, N>;
    using const_iterator = CyclicIterator<T const, N>;

    cyclic() : _filled(false), _curr(0u) {}

    void push_back(const_reference val)
    {
        _raw[_curr] = val;

        if (_curr == _raw.size() - 1)
        {
            _filled = true;
            _curr = 0;
        }
        else
            ++_curr;
    }

    void clear()
    {
        _filled = false;
        _curr = 0;
    }

    std::size_t size() const { return _filled ? N : _curr; }
    bool empty() const { return !_filled && !_curr; }

    reference operator[](std::size_t n)
    {
        return _raw[_filled ? (_curr + n) % N : n];
    }

    iterator begin() noexcept
    {
        return iterator(this, 0);
    }

    iterator end() noexcept
    {
        return iterator(this, N);
    }
};
}
#endif /* !__CYCLIC_HPP_ */