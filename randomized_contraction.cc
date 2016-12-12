#include <iostream>




int main()
{
    std::ifstream file;
    file.open("/tmp/kargerMinCut.txt");
    std::string no;
    if(file.is_open()) {
        uint64_t i = 0;
        while (std::getline(file, no)) {
            //std::cout << no << std::endl;
            v[i++] = std::stoll(no);
        }
        file.close();
    }
    return 0;
}