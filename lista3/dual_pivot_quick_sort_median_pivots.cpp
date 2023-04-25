#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

#undef EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;
unsigned long swapsCounter = 0;


bool smaller(int a, int b) {
    comparisonsCounter++;

    return a < b;
}


bool greater(int a, int b) {
    comparisonsCounter++;

    return a > b;
}

bool smallerEqual(int a, int b) {
    comparisonsCounter++;

    return a <= b;
}

bool equal(int a, int b) {
    comparisonsCounter++;

    return a == b;
}

void swp(int& a, int& b) {
    swapsCounter++;

    int tmp = a;
    a = b;
    b = tmp;
}

void assign(int& a, int& b) {
    swapsCounter++;

    a = b;
}

void insertionSort(std::vector<int>& array, size_t left, size_t right) {
    for(int i=left+1;i<right+1;i++) {
        int key = array[i] ;
        size_t j = i;

        while(j > left && greater(array[j-1], key)) {
            assign(array[j], array[j-1]);
            j--;
        }
        array[j]= key;
    }
}

size_t select_partition(std::vector<int>& array, size_t left, size_t right, int pivot) {
    size_t pivot_index;
    for(pivot_index = left; pivot_index < right; pivot_index++) {
        if(equal(array[pivot_index], pivot)) {
            break;
        }
    }
    swp(array[right], array[pivot_index]);

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

int select(std::vector<int>& array, size_t k, size_t m, size_t left, size_t right) {
    size_t n = right - left + 1;

    if(n + 1 <= m) {
        insertionSort(array, left, right);

        return array[k - 1];
    }

    std::vector<int> medians;
    for(size_t i = left; i <= right; i += m) {
        if(i + m < right) {
            insertionSort(array, i, i + m - 1);
            medians.push_back(array[i + 2]);
        }
        else {
            insertionSort(array, i, right);
            medians.push_back(array[(i + right) / 2]);
        }
    }

    size_t medians_number = medians.size();
    int median = select(medians, medians_number / 2 + 1, m, 0, medians_number - 1);

    size_t pivot_index = select_partition(array, left, right, median);

    if(pivot_index == k-1) {
        return array[pivot_index];
    }
    
    if(k-1 < pivot_index) {
        return select(array, k, m, left, pivot_index - 1);
    }

    return select(array, k, m, pivot_index + 1, right);
}


void dualPivotQuickSortPartition(std::vector<int>& array, size_t left, size_t right, size_t& lp, size_t& rp) {
    if(greater(array[left - 1], array[right - 1])) {
        swp(array[left - 1], array[right - 1]);
    }

    int p = array[left - 1];
    int q = array[right - 1];

    size_t i = left + 1;
    size_t k = right - 1;
    size_t j = i;
    size_t d1 = 0;
    size_t d2 = 0;

    while(j <= k) {
        if(d1 >= d2) {
            if(smaller(array[j - 1], p)) {
                swp(array[i - 1], array[j - 1]);
                i++;
                j++;
                d1++;
            }   
            else {
                if(smaller(array[j - 1], q)) {
                    j++;
                }
                else {
                    swp(array[j - 1], array[k - 1]);
                    k--;
                    d2++;
                }
            }
        }
        else {
            while(greater(array[k - 1], q)) {
                k--;
                d2++;
            }

            if(j <= k) {
                if(smaller(array[k - 1], p)) {
                    int tmp = array[k - 1];
                    array[k - 1] = array[j - 1];
                    array[j - 1] = array[i - 1];
                    array[i - 1] = tmp;
                    i++;
                    d1++;
                }
                else {
                    swp(array[j - 1], array[k - 1]);
                }

                j++;
            }
        } 
    }
    
    array[left - 1] = array[i - 2];
    array[i - 2] = p;
    array[right - 1] = array[k];
    array[k] = q;

    lp = i - 1;
    rp = k + 1;
}

void dualPivotQuickSort(std::vector<int>& array, size_t left, size_t right, size_t m) {
    if(right <= left) {
        return;
    }
    
    size_t lp, rp;

    size_t x = (right - left + 1) / 3;
    if(x != 0) {  
        std::vector<int> array_copy = std::vector<int>(array.begin() + left - 1, array.begin() + right);
        int pivot1 = select(array_copy, x, 5, 0, array_copy.size() - 1);
        int pivot2 = select(array_copy, 2 * x, 5, 0, array_copy.size() - 1);

        size_t pivot1_index;
        for(size_t i = left - 1; i <= right - 1; i++) {
            if(equal(array[i], pivot1)) {
                pivot1_index = i;
                break;
            }
        }

        size_t pivot2_index;
        for(size_t i = left - 1; i <= right - 1; i++) {
            if(equal(array[i], pivot2) && i != pivot1_index) {
                pivot2_index = i;
                break;
            }
        }

        swp(array[left - 1], array[pivot1_index]);
        swp(array[right - 1], array[pivot2_index]);
    }

    dualPivotQuickSortPartition(array, left, right, lp, rp);


#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

#endif  // EXTENSIVE_OUTPUT

    dualPivotQuickSort(array, left, lp - 1, m);
    dualPivotQuickSort(array, lp + 1, rp - 1, m);
    dualPivotQuickSort(array, rp + 1, right, m);
}

bool isSorted(std::vector<int>& array) {
    for(size_t i = 1; i < array.size(); i++) {
        if(array[i - 1] > array[i]) {
            return false;
        } 
    }

    return true;
}


int main(int argc, char** argv) {
    if(argc != 2) {
        return 1;
    }

    int m = std::atoi(argv[1]);

    size_t n;
    std::cin >> n;

    std::vector<int> array;
    array.reserve(n);
    int tmp;
    size_t n_copy = n;
    while(n_copy > 0) {
        std::cin >> tmp;
        array.push_back(tmp);
        n_copy--;
    }

    comparisonsCounter = 0;
    swapsCounter = 0;

    auto start = std::chrono::steady_clock::now();
    dualPivotQuickSort(array, 1, n, m);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::cout << "is sorted: " << isSorted(array) << '\n' <<
        "cmps: " << comparisonsCounter << '\n' <<
        "swps: " << swapsCounter << '\n' <<
        "time: " << elapsed_seconds.count() * 1000 << '\n';

#else

    std::cout << isSorted(array) << '\n' << comparisonsCounter << '\n' << swapsCounter << '\n' << elapsed_seconds.count() * 1000 << '\n';
    
#endif  // EXTENSIVE_OUTPUT

}