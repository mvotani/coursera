#include <iostream>
#include <vector>
#include <fstream>

static uint64_t comparisons = 0;

void myswap(uint64_t* a, uint64_t* b)
{
   uint64_t temp = *a;
   *a = *b;
   *b = temp;
}

void partition(uint64_t* v, const size_t s, uint64_t& i)
{
   uint64_t* pivot = &v[0];
   uint64_t j = 1;
   i = 0;

   for (; j < s; ++j) {
        if (v[j] < *pivot) {
            ++i;
            myswap(&v[i], &v[j]);
        }
   }
   myswap(&v[i], pivot);
}

void myqsort(uint64_t* v, const size_t s)
{
   if (s <=1)
        return;
   comparisons += s - 1;

   /*
   uint64_t temp = v[s - 1];
   v[s - 1] = v[0];
   v[0] = temp;
   */
   
   uint64_t* middle;
   if (s%2) {
        middle = &v[s/2];
   } else {
        middle = &v[(s/2) - 1];
   }
   uint64_t** arr = new uint64_t*[3];
   arr[0] = &v[0];
   arr[1] = middle;
   arr[2] = &v[s-1];
   if (*arr[1] < *arr[0]) {
        uint64_t* temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
   }
   if (*arr[2] < *arr[1]) {
        uint64_t* temp = arr[2];
        arr[2] = arr[1];
        arr[1] = temp;
   }
   if (*arr[1] < *arr[0]) {
        uint64_t* temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
   }
   if (*arr[2] < *arr[1]) {
        uint64_t* temp = arr[2];
        arr[2] = arr[1];
        arr[1] = temp;
   }
   myswap(&v[0], arr[1]);
   delete[] arr;
   uint64_t i = 0;
   partition(v, s, i);

   myqsort(v, i);
   myqsort(&v[i+1], s - i - 1);
}

int main()
{
    size_t s = 10000;
    uint64_t* v = new uint64_t[s];
    /*v[0] = 3;
    v[1] = 2;
    v[2] = 1;
    v[3] = 5;
    v[4] = 4;
    v[5] = 8;
    v[6] = 6;
    v[7] = 7;*/
    std::ifstream file;
    file.open("/tmp/QuickSort.txt");
    std::string no;
    if(file.is_open()) {
        uint64_t i = 0;
        while (std::getline(file, no)) {
            //std::cout << no << std::endl;
            v[i++] = std::stoll(no);
        }
        file.close();
    }

    myqsort(v, s);

    std::cout << "Output:" << std::endl;
    uint64_t check = v[0];
    std::cout << check << std::endl;
    for (size_t temp = 1; temp < s; ++temp) {
        if ((check + 1) != v[temp])
            return -1;
        check = v[temp];
        std::cout << v[temp] << std::endl;
    }
    std::cout << "Comparisons: " << comparisons << std::endl;

    delete[] v;
    return 0;
}
