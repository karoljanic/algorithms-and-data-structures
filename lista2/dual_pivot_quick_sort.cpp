#include <iostream>
#include <iomanip>
#include <vector>

#undef EXTENSIVE_OUTPUT

unsigned long comparisonsCounter = 0;
unsigned long swapsCounter = 0;


bool cmp1(int a, int b) {
    comparisonsCounter++;

    return a > b;
}


bool cmp2(int a, int b) {
    comparisonsCounter++;

    return a < b;
}


void swap(int& a, int& b) {
    swapsCounter++;

    int tmp = a;
    a = b;
    b = tmp;
}


void dualPivotQuickSortPartition(std::vector<int>& array, size_t left, size_t right, size_t& lp, size_t& rp) {
    if(cmp1(array[left - 1], array[right - 1])) {
        swap(array[left - 1], array[right - 1]);
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
            if(cmp2(array[j - 1], p)) {
                swap(array[i - 1], array[j - 1]);
                i++;
                j++;
                d1++;
            }   
            else {
                if(cmp2(array[j - 1], q)) {
                    j++;
                }
                else {
                    swap(array[j - 1], array[k - 1]);
                    k--;
                    d2++;
                }
            }
        }
        else {
            while(cmp1(array[k - 1], q)) {
                k--;
                d2++;
            }

            if(j <= k) {
                if(cmp2(array[k - 1], p)) {
                    int tmp = array[k - 1];
                    array[k - 1] = array[j - 1];
                    array[j - 1] = array[i - 1];
                    array[i - 1] = tmp;
                    i++;
                    d1++;
                }
                else {
                    swap(array[j - 1], array[k - 1]);
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

void dualPivotQuickSort(std::vector<int>& array, size_t left, size_t right) {
    if(right <= left) {
        return;
    }

    size_t lp, rp;
    dualPivotQuickSortPartition(array, left, right, lp, rp);

#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

#endif  // EXTENSIVE_OUTPUT

    dualPivotQuickSort(array, left, lp - 1);
    dualPivotQuickSort(array, lp + 1, rp - 1);
    dualPivotQuickSort(array, rp + 1, right);
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

    dualPivotQuickSort(array, 1, n);

#ifdef EXTENSIVE_OUTPUT

    for(const int& element : array) {
        std::cout << std::setw(2) << element << ' ';
    }
    std::cout << '\n';

    std::cout << "is sorted: " << isSorted(array) << '\n' <<
        "cmps: " << comparisonsCounter << '\n' <<
        "swps: " << swapsCounter << '\n';

#else

    std::cout << isSorted(array) << '\n' << comparisonsCounter << '\n' << swapsCounter << '\n';
    
#endif  // EXTENSIVE_OUTPUT

}