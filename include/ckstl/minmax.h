#pragma once

#include "functional.h"


namespace ck {

// min_element
template<class ForwardIt, class Compare>
constexpr ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp) {
    if (first == last)
        return last;

    ForwardIt min = first;
    ++first;

    while (first != last) {
        if (comp(*first, *min))
            min = first;

        ++first;
    }

    return min;
}

template<class ExecutionPolicy, class ForwardIt, class Compare>
ForwardIt min_element(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Compare comp) {
    return min_element(first, last, comp);
}

template<class ForwardIt>
constexpr ForwardIt min_element(ForwardIt first, ForwardIt last) {
    return min_element(first, last, Less<typename ForwardIt::value_type>{});
}

template<class ExecutionPolicy, class ForwardIt>
ForwardIt min_element(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last) {
    return min_element(first, last);
}


// min
template<class T, class Compare>
constexpr const T& min(const T& a, const T& b, Compare comp) {
    return comp(a, b) ? a : b;
}

template<class T>
constexpr const T& min(const T& a, const T& b) {
    return min(a, b, Less<T>{});
}

template<class T, class Compare>
constexpr T min(std::initializer_list<T> ilist, Compare comp) {
    return min_element(ilist.begin(), ilist.end(), comp);
}

template<class T>
constexpr T min(std::initializer_list<T> ilist) {
    return min_element(ilist.begin(), ilist.end(), Less<T>{});
}

// max_element
template<class ForwardIt, class Compare>
constexpr ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp) {
    if (first == last)
        return last;

    ForwardIt min = first;
    ++first;

    while (first != last) {
        if (!comp(*first, *min))
            min = first;

        ++first;
    }

    return min;
}

template<class ExecutionPolicy, class ForwardIt, class Compare>
ForwardIt max_element(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Compare comp) {
    return max_element(first, last, comp);
}

template<class ForwardIt>
constexpr ForwardIt max_element(ForwardIt first, ForwardIt last) {
    return max_element(first, last, Less<typename ForwardIt::value_type>{});
}

template<class ExecutionPolicy, class ForwardIt>
ForwardIt max_element(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last) {
    return max_element(first, last);
}


// max
template<class T, class Compare>
constexpr const T& max(const T& a, const T& b, Compare comp) {
    return comp(a, b) ? b : a;
}

template<class T>
constexpr const T& max(const T& a, const T& b) {
    return max(a, b, Less<T>{});
}

template<class T, class Compare>
constexpr T max(std::initializer_list<T> ilist, Compare comp) {
    return max_element(ilist.begin(), ilist.end(), comp);
}

template<class T>
constexpr T max(std::initializer_list<T> ilist) {
    return max_element(ilist.begin(), ilist.end(), Less<T>{});
}

}