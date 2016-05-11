//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_CONTIGUOUSMAP_H
#define FLATLAND_CONTIGUOUSMAP_H

#include <vector>
#include <limits>
#include "Table.h"

/*
 * ContiguousMap, A map from ids to data
 * consists of a lookup table of ids + contiguous array of data
        < Restriction: Only 1 data point per id!!! for multiple data points, see ContiguousMultiMap >

data:  [ d3 d1 d6 d2 d7  ]
id2 :  [  -  1  3  0  -  -  -  2  4  -  - ... ]
Insertion/Deletion: Constant
Lookup: Constant
Iteration without ids: Contiguous
Iteration with ids: contiguous
        Memory: #used entities + #total entities
*/
#include <limits>

namespace fl {

    template<typename T, typename I=std::size_t>
    class ContiguousMap {
        Table<std::size_t, I> _pos;
        std::vector<std::pair<I, T>> _data;
    public:

        typedef typename std::vector<std::pair<I, T>>::iterator iterator;
        typedef typename std::vector<std::pair<I, T>>::const_iterator const_iterator;

        ContiguousMap() : _pos(std::numeric_limits<std::size_t>::max()) {}

        void insert(I i, const T& t) {
            _pos.insert(i, _data.size());
            _data.push_back({i, t});
        }

        void erase(I i) {
            using std::swap;
            /* Swap the data with the lastmost data and pop
             * Update the index table */
            if (_data.empty() || _pos[i] == std::numeric_limits<std::size_t>::max()) return;
            _pos[_data.back().first] = _pos[i];
            _pos.erase(i);
            /* Move data to back and pop it */
            swap(_data[i], _data.back());
            _data.pop_back();
        }

        std::size_t size() const {return _data.size();}

        iterator begin() {return _data.begin();}
        iterator end() {return _data.end();}
        const_iterator begin() const {return _data.begin();}
        const_iterator end() const {return _data.end();}

        T& operator[](I i) {return _data[_pos[i]].second;}
        const T& operator[](I i) const {return _data[_pos[i]].second;}
    };

}

#endif //FLATLAND_CONTIGUOUSMAP_H
