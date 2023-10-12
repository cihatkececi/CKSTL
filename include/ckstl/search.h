#pragma once

namespace ck {

template<class It, class Val>
It find(It first, It last, const Val& value) {
    for (; first != last; first++) {
        if (*first == value) {
            break;
        }
    }
    return first;
}

template<class It, class Pred>
It find_if(It first, It last, const Pred& pred) {
    for (; first != last; first++) {
        if (pred(*first)) {
            break;
        }
    }
    return first;
}

}
