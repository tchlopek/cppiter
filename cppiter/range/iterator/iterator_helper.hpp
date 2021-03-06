#pragma once

#include <iterator>

namespace cppiter::range::iter::detail {

template<typename IteratorWrapper>
struct inner_iterator;

template<template<typename...> class IteratorWrapper, typename InnerIterator, typename... Ts>
struct inner_iterator<IteratorWrapper<InnerIterator, Ts...>> {
    using type = InnerIterator;
};

template<typename IteratorWrapper>
using inner_iterator_t = typename inner_iterator<IteratorWrapper>::type;

/* ========================================================================= */

template<typename ExternalTraits, typename DefaultTraits>
using conditional_iterator_traits_t = std::iterator_traits<
    typename std::conditional_t<
        std::is_same_v<ExternalTraits, void>,
        DefaultTraits,
        ExternalTraits>>;

/* ========================================================================= */

template<typename C> constexpr std::size_t iterator_category_rank;
template<> constexpr std::size_t iterator_category_rank<std::input_iterator_tag> = 0;
template<> constexpr std::size_t iterator_category_rank<std::output_iterator_tag> = 1;
template<> constexpr std::size_t iterator_category_rank<std::forward_iterator_tag> = 2;
template<> constexpr std::size_t iterator_category_rank<std::bidirectional_iterator_tag> = 3;
template<> constexpr std::size_t iterator_category_rank<std::random_access_iterator_tag> = 4;

template<typename C1, typename C2>
struct max_iterator_category {
    using type = std::conditional_t<
        (iterator_category_rank<C1> > iterator_category_rank<C2>),
        C1,
        C2>;
};

template<typename C1, typename C2>
using max_iterator_category_t = typename max_iterator_category<C1, C2>::type;

template<typename C1, typename C2>
struct min_iterator_category {
    using type = std::conditional_t<
        (iterator_category_rank<C1> < iterator_category_rank<C2>),
        C1,
        C2>;
};

template<typename C1, typename C2>
using min_iterator_category_t = typename min_iterator_category<C1, C2>::type;

/* ========================================================================= */

template<typename T>
struct add_ref_const;

template<typename T>
struct add_ref_const<T&> {
    using type = const T&;
};

template<typename T>
struct add_ref_const<const T&> {
    using type = const T&;
};

template<typename T>
struct add_ref_const<T*> {
    using type = const T*;
};

template<typename T>
struct add_ref_const<const T*> {
    using type = const T*;
};

template<typename T>
using add_ref_const_t = typename add_ref_const<T>::type;

/* ========================================================================= */

template<typename Iterator>
using value_t = typename std::iterator_traits<Iterator>::value_type;

template<typename Iterator>
using reference_t = typename std::iterator_traits<Iterator>::reference;

template<typename Iterator>
using iterator_category_t = typename std::iterator_traits<Iterator>::iterator_category;

template<typename Iterator>
using pointer_t = typename std::iterator_traits<Iterator>::pointer;

template<typename Iterator>
using difference_t = typename std::iterator_traits<Iterator>::difference_type;

}
