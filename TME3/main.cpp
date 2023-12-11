#include <iostream>
#include <vector>
#include <string>

namespace pr {
    template<typename Iterator>
    size_t count(Iterator begin, Iterator end) {
        size_t cpt = 0;
        while (begin != end) {
            ++begin;
            ++cpt;
        }
        return cpt;
    }

    template<typename Iterator, typename T>
    size_t count_if_equal(Iterator begin, Iterator end, const T &val) {
        size_t cpt = 0;
        while (begin != end) {
            if (*begin == val)  
                ++cpt;
            ++begin;
        }
        return cpt;
    }
}

int main() {
    std::vector<std::string> VectString;  
    VectString.push_back("un");
    VectString.push_back("deux");
    VectString.push_back("trois");
    VectString.push_back("un");

    std::cout <<pr::count(VectString.begin(),VectString.end()) << std::endl;
    std::cout <<pr::count_if_equal(VectString.begin(),VectString.end(),"un") << std::endl;
    return 0;
}