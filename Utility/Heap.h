//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_HEAP_H
#define FLATLAND_HEAP_H

#include <algorithm>

/* A heap that allows a bit more functionality than std::priority_queue,
 * like removing certain elements */
template<typename T>
class Heap {
    std::vector<T> _c;
public:

    bool empty() const {
        return _c.empty();
    }

    void push(const T& t) {
        _c.push_back(t);
        std::push_heap(_c.begin(), _c.end());
    }

    const T& top() const {return _c.front();}

    void pop() {
        std::pop_heap(_c.begin(), _c.end());
        _c.pop_back();
    }

    template<typename Pred>
    void remove_if(Pred p) {
        _c.resize( std::remove_if(_c.begin(), _c.end(), p) - _c.begin() );
        std::make_heap(_c.begin(), _c.end());
    }

};

#endif //FLATLAND_HEAP_H
