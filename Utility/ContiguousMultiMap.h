
#ifndef FLATLAND_CONTIGUOUSMULTIMAP_H
#define FLATLAND_CONTIGUOUSMULTIMAP_H

#include "Table.h"
#include <algorithm>
#include "Core.h"

/*
Sorted array of data + lookup table of (ids, #datas for that id)
id :  [  -  0,1  1,1  -  -  2,2  -  4,1  -  -  - ... ]
data:  [ d1 d2 d5 d5 d7  ]

Insertion/Deletion: Linear in #total entities
Lookup: Constant
Iteration: Contiguous
Memory: #used entities + 2*#total entities
*/


namespace fl {

    template<typename T, typename I=std::size_t>
    class ContiguousMultiMap {

    public:

        struct Data {I index; T data;};

    private:

        struct Entry {std::size_t loc = 0; std::size_t num = 0;};
        
        Table<Entry, std::size_t> _pos;
        std::vector<Data> _data;

    public:

        typedef typename std::vector<Data>::iterator iterator;
        typedef typename std::vector<Data>::const_iterator const_iterator;
        
        void insert(I i, const T& t) {
            /* TODO: if Table had a way to tell that an entry does not exist,
             * we could check the table first, instead of searching through */
            auto pos = std::lower_bound(_data.begin(), _data.end(), i, [](const Data& d, I i) {
                return d.index < i;
            });
            if (pos == _data.end()) {
                /* Update loc in table entry */
                _pos[i].loc = _data.size();
                _data.push_back(Data{i, t});
            }
            else 
                _data.insert(pos, Data{i,t});

            /* Update num in table entry */
            ++_pos[i].num;

            /* Update location of following entries */
            for (auto it = _pos.begin()+i+1 ; it != _pos.end(); ++it)
                ++it->loc;
        }

        std::size_t size() const {return _data.size();}

        void erase(I i) {
            auto p = this->operator[](i);
            _data.erase(p.first, p.second);
            _pos[i].num = 0;
            for (auto it = _pos.begin() + i + 1; it != _pos.end(); ++it)
                it->loc -= p.second - p.first;
        }

        void erase(iterator pos) {
            auto i = pos->index;
            _data.erase(pos);
            --_pos[i].num;
            for (auto it = _pos.begin() + i + 1; it != _pos.end(); ++it)
                --it->loc;
        }

        std::pair<iterator, iterator> operator[] (I i) {
            const Entry& p = _pos[i];
            iterator ptr = _data.begin() + p.loc;
            return {ptr, ptr + p.num};
        }

        iterator begin() {return _data.begin();}
        iterator end() {return _data.end();}
        const_iterator begin() const {return _data.begin();}
        const_iterator end() const {return _data.end();}

    };

}

#endif /* FLATLAND_CONTIGUOUSMULTIMAP_H */
