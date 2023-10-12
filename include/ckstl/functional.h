#pragma once

namespace ck {

template<class T>
class Less {
public:
    constexpr bool operator()(const T& lhs, const T& rhs) {
        return lhs < rhs;
    }
};

template<class T>
class Greater {
public:
    constexpr bool operator()(const T& lhs, const T& rhs) {
        return lhs > rhs;
    }
};

}