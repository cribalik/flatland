//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_TABLE_H
#define FLATLAND_TABLE_H

#include <vector>

template<typename T, typename Idx = std::size_t>
class Table {
private:
    T undef;
    std::vector<T> _data;
public:
    typedef typename std::vector<T>::iterator iterator;
    Table(const T& undef = T()) : undef(undef) {}
    void insert(Idx i, const T&);
    void erase(Idx i) {};
    void clear() {_data.clear();}
    T& operator[](Idx i) {
        if (i >= _data.size()) insert(i, undef);
        return _data[i];
    }
    iterator begin() {return _data.begin();}
    iterator end() {return _data.end();}
};

template<typename T, typename Idx>
void Table<T, Idx>::insert(Idx i, const T& t) {
    if (i >= _data.size()) {
        _data.resize(i+1,undef);
        _data.back() = t;
    }
    else
        _data[i] = t;
}

#endif //FLATLAND_TABLE_H
