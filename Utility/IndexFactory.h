//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_INDEXFACTORY_H
#define FLATLAND_INDEXFACTORY_H

#include <vector>
#include <algorithm>

template<typename I=std::size_t>
class IndexFactory {
    I _next = 0;
    std::vector<I> _free;
public:
    I create();

    void giveBack(I i) {_free.push_back(i);}

    bool exists(I i) {return i < _next && std::find(_free.begin(), _free.end(), i) == _free.end();}
};

template<typename I>
I IndexFactory<I>::create() {
    if (_free.empty())
        return _next++;
    I r = _free.back();
    _free.pop_back();
    return r;
}

#endif //FLATLAND_INDEXFACTORY_H
