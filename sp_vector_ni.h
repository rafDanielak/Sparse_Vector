#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class sparse_vector
{
    struct vect_elem {
        size_t  idx;
        T       value;
    };

    size_t n_elem = 0;
    std::vector<vect_elem> elements;

public:
    // creates n_elements vector with all elements of value T()
    explicit sparse_vector(size_t n_elements = 10u) : n_elem(n_elements) {}

    // returns number of elments in the vector
    size_t size() const
    {
        return n_elem;
    }

    // returns number of non-default values in the vector
    size_t nd_count() const
    {
        return elements.size();
    }

    // sets all non-default values to T() (size() is not changed)
    void clear()
    {
        elements.clear();
    }

    // returns const reference to element in the vector or T()
    // if element with given idx has default value
    // invalid idx results in invalid_argument exception
    T operator[](int idx) const
    {
        
        if (idx < 0 || (size_t)idx >= n_elem)
            throw std::invalid_argument("invalid index.");
        auto it = std::lower_bound(elements.cbegin(), elements.cend(), idx, [](const vect_elem& vec, int id){return vec.idx < (size_t)id;});
        if (it == elements.cend() || it->idx != (size_t)idx)
            return T();
        else
            return it->value;
    }

    // returns const reference to element in the vector
    // if element with given idx has default value new element is inserted
    // invalid idx results in invalid_argument exception
    T& operator[](int idx)
    {
        if (idx < 0 || (size_t)idx >= n_elem)
            throw std::invalid_argument("invalid index.");
        auto it = std::lower_bound(elements.begin(), elements.end(), idx, [](const vect_elem& vec, int id){return vec.idx < (size_t)id;});
        if (it == elements.end())
        {
            elements.push_back({(size_t)idx, T()});
            return elements.back().value;
        }
        if (it->idx == (size_t)idx)
        {
            return it->value;
        }
        it = elements.insert(it, {(size_t)idx, T()});
        return it->value;
    }

    class const_iterator
    {
        const sparse_vector& vec;
        size_t pos = 0;
        typename std::vector<vect_elem>::const_iterator element;
        const_iterator(const sparse_vector& vector, size_t position) : vec(vector), pos(position)
        {
            if (position == 0)
                element = vec.elements.cbegin();
            else
                element = vec.elements.cend();
        }
        friend sparse_vector;
    public:
        const_iterator& operator++()
        {
            if (element != vec.elements.cend() && element->idx == pos)
                ++element;
            ++pos;
            return *this;
        }
        T operator*() const
        {
            if (element != vec.elements.cend() && element->idx == pos)
                return element->value;
            else
                return T();
        }
        bool operator!=(const const_iterator& other)
        {
            return &vec != &other.vec || pos != other.pos; 
        }
    };

    const_iterator cbegin() const
    {
        return const_iterator(*this, 0);
    }
    const_iterator cend() const
    {
        return const_iterator(*this, size());
    }

    const_iterator begin() const
    {
        return cbegin();
    }
    const_iterator end() const
    {
        return cend();
    }

    friend std::ostream& operator<<(std::ostream& os, const sparse_vector& vec)
    {
        os << '[';
        for (auto val : vec)
            os << val << ' ';
        return os << ']';
    }
};
