#include <iostream>
#include <vector>
#include <fstream>

using std::vector;

typedef vector<uint64_t> vect;

uint64_t merge_count(vect& v1, vect& v2,
                     vect& merged)
{
    merged.clear();
    if(v1.size() == 0) {
        merged.push_back(*v2.begin());
        return 0;
    } else if(v2.size() == 0) {
        merged.push_back(*v1.begin());
        return 0;
    }

    uint64_t inversions {0};
    auto v1it = v1.begin();
    auto v2it = v2.begin();
    while (v1it != v1.end() && v2it != v2.end()) {
        if (*v1it < *v2it) {
            merged.push_back(*v1it);
            ++v1it;
        } else {
            merged.push_back(*v2it);
            ++v2it;
            inversions += std::distance(v1it, v1.end());
        }
    }
    
    for(; v1it != v1.end(); ++v1it) {
        merged.push_back(*v1it);
    }

    for(; v2it != v2.end(); ++v2it) {
        merged.push_back(*v2it);
    }
    return inversions;
}

uint64_t inversion(vect& v, vect& s)
{
    auto vit = v.begin();
    std::advance(vit, (v.size()/2));
    vect v1 (v.begin(), vit);
    vect v2 (vit, v.end());
    vect v1s = v1, v2s = v2;
    
    /*std::cout << "size is " << v1.size()
              << " " << v2.size()
              << std::endl;*/

    uint64_t left_inv{0}, right_inv{0};  

    if(v.size() > 2) {
        left_inv += inversion(v1, v1s);
        right_inv += inversion(v2, v2s);
    }

    auto split_inv = merge_count(v1s, v2s, s);

    return left_inv + right_inv + split_inv;
}

int main()
{
    vect v1{1, 3, 2, 4}, v1s;
    
    vect v2{1, 3, 5, 2, 4, 6}, v2s;

    vect v3, v3s;
    
    std::cout << "Inv :"
              << inversion(v1, v1s)
              << std::endl;
    std::cout << "Inv :"
              << inversion(v2, v2s)
              << std::endl;

    std::ifstream file;
    file.open("/tmp/IntegerArray.txt");
    std::string no;
    if(file.is_open()) {
        while (std::getline(file, no)) {
            //std::cout << no << std::endl;
            v3.push_back(std::stoll(no));
        }
        file.close();
    }

    std::cout << "Inversions of "
              << v3.size() << " no: "
              << inversion(v3, v3s)
              << std::endl;
    
    return 0;
}
