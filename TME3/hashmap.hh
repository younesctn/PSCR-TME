#pragma once
#include <vector>
#include <forward_list>
#include <stdexcept>
#include <functional>

namespace pr {

template <typename k, typename v>
class HashMap {
private :
    struct Entry {
        const k Key;
        v value;
    };
    std::vector<std::forward_list<Entry>> Buckets;
    iterator it = buckets.ends;

public:
    HashMap(size_t alloc);

    bool put(const k& Key, const v& value);

    const std::forward_list<Entry>& getBucket(size_t index) const;
};


template <typename k, typename v>
HashMap<k, v>::HashMap(size_t alloc) : Buckets(alloc) {}

template <typename k, typename v>
bool HashMap<k, v>::put(const k& Key, const v& value) {
    size_t n = std::hash<k>()(Key);
    size_t target = n % Buckets.size();

    for (auto &ent : Buckets[target]) {
        if (ent.Key == Key) {
            ent.value = value; // Met à jour la valeur existante.
            return false; // La clé existe déjà, mise à jour de la valeur.
        }
    }

    // La clé n'existe pas, ajoutez une nouvelle entrée avec la valeur spécifiée.
    Buckets[target].push_front({Key, value});
    return true;
}

template <typename k, typename v>
const std::forward_list<typename HashMap<k, v>::Entry>& HashMap<k, v>::getBucket(size_t index) const {
    if (index < Buckets.size()) {
        return Buckets[index];
    }
    throw std::out_of_range("Bucket index out of range");
}



}  // namespace pr
