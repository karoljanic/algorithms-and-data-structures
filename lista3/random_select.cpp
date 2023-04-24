#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>

#undef EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;
unsigned long swapsCounter = 0;

size_t get_rand_int(size_t min_val, size_t max_val) {
    static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);

    std::uniform_int_distribution<size_t> dis(min_val, max_val);

    return(dis(gen));
}


bool smallerEqual(int a, int b) {
    comparisonsCounter++;

    return a <= b;
}

void swp(int& a, int& b) {
    swapsCounter++;

    int tmp = a;
    a = b;
    b = tmp;
}

size_t random_select_partition(std::vector<int>& array, size_t left, size_t right) {
    swp(array[right], array[get_rand_int(left, right)]);

    int pivot = array[right];  
    int i = left - 1;
 
    for (int j = left; j <= right - 1; j++) {
        if (smallerEqual(array[j], pivot)) {
            i++;
            swp(array[i], array[j]);
        }
    }
    swp(array[i + 1], array[right]);

    return i + 1;
}

int random_select(std::vector<int>& array, size_t k, size_t left, size_t right) {
    if(left == right) {
        return array[left];
    }

    size_t pivot_index = random_select_partition(array, left, right);

#ifdef EXTENSIVE_OUTPUT

    std::cout << "middle: ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

#endif  // EXTENSIVE_OUTPUT

    if(pivot_index == k-1) {
        return array[pivot_index];
    }
    
    if(k-1 < pivot_index) {
        return random_select(array, k, left, pivot_index - 1);
    }

    return random_select(array, k, pivot_index + 1, right);
}


int main(int argc, char** argv) {
    if(argc != 2) {
        return 1;
    }

    size_t k = std::stoi(argv[1]);

    size_t n;
    std::cin >> n;

    std::vector<int> array;
    array.reserve(n);
    int tmp;
    size_t m = n;
    while(m > 0) {
        std::cin >> tmp;
        array.push_back(tmp);
        m--;
    }

    comparisonsCounter = 0;
    swapsCounter = 0;

#ifdef EXTENSIVE_OUTPUT

    std::cout << "before: ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';
    
#endif  // EXTENSIVE_OUTPUT
    
    auto start = std::chrono::steady_clock::now();
    int result = random_select(array, k, 0, n-1);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

#ifdef EXTENSIVE_OUTPUT

    std::cout << "after:  ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::sort(array.begin(), array.end(), std::less<int>());

    std::cout << "sorted: ";
    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::cout << "\nk-th smallest element = " << result << '\n' <<
        "is correct: " << (array[k - 1] == result) << '\n' <<
        "cmps: " << comparisonsCounter << '\n' <<
        "swps: " << swapsCounter << '\n' <<
        "time: " << elapsed_seconds.count() * 1000 << '\n';
#else

    std::sort(array.begin(), array.end(), std::less<int>());
    std::cout << (array[k - 1] == result) << " " << comparisonsCounter << " " << swapsCounter << " " << elapsed_seconds.count() * 1000 << '\n';

#endif  // EXTENSIVE_OUTPUT 

}