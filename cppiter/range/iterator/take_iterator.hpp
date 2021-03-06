#pragma once

#include "iterator_facade.hpp"

namespace cppiter::range::iter {

template<typename BaseIter, typename Category>
class take_iterator;

template<typename BaseIter>
class take_iterator<BaseIter, std::forward_iterator_tag> :
    public iterator_facade<take_iterator<BaseIter, std::forward_iterator_tag>> {
    using BaseType = iterator_facade<take_iterator<BaseIter, std::forward_iterator_tag>>;

    friend class derived_access;

public:
    take_iterator(BaseIter iter, detail::difference_t<BaseType> index) :
        iter{ iter }, index{ index }
    {}

private:
    bool equal(const take_iterator& other) const {
        return iter == other.iter || index == other.index;
    }

    void increment() {
        ++index;
        ++iter;
    }

    typename BaseType::reference dereference() const {
        return *iter;
    }

    BaseIter iter;
    detail::difference_t<BaseType> index;
};

template<typename BaseIter>
class take_iterator<BaseIter, std::bidirectional_iterator_tag> :
    public iterator_facade<take_iterator<BaseIter, std::bidirectional_iterator_tag>> {
    using BaseType = iterator_facade<
        take_iterator<BaseIter, std::bidirectional_iterator_tag>>;

    friend class derived_access;

public:
    take_iterator(BaseIter iter, detail::difference_t<BaseType> index) :
        iter{ iter }, index{ index }
    {}

private:
    bool equal(const take_iterator& other) const {
        return iter == other.iter || index == other.index;
    }

    void increment() {
        ++index;
        ++iter;
    }


    void decrement() {
        --index;
        --iter;
    }

    typename BaseType::reference dereference() const {
        return *iter;
    }

    BaseIter iter;
    detail::difference_t<BaseType> index;
};

template<typename BaseIter>
class take_iterator<BaseIter, std::random_access_iterator_tag> :
    public iterator_facade<take_iterator<BaseIter, std::random_access_iterator_tag>> {
    using BaseType = iterator_facade<
        take_iterator<BaseIter, std::random_access_iterator_tag>>;

    friend class derived_access;

public:
    take_iterator(BaseIter iter) : iter{ iter }
    {}

private:
    bool equal(const take_iterator& other) const {
        return iter == other.iter;
    }

    void increment() {
        ++iter;
    }


    void decrement() {
        --iter;
    }

    typename BaseType::reference dereference() const {
        return *iter;
    }

    void advance(typename BaseType::difference_type n) {
        iter += n;
    }

    typename BaseType::difference_type distance_to(const take_iterator& other) const {
        return iter - other.iter;
    }

    BaseIter iter;
};

}
