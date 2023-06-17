#include <iostream>
#include <random>
#include <string>
#include <fstream>

static unsigned int operations = 0;

std::string randomString(size_t length) {
    static std::string characters = "abcdefghijklmnopqrstuvwxyz";

    static std::mt19937 rgn{std::random_device{}()};
    static std::uniform_int_distribution<std::string::size_type> dis(0, characters.size() - 1);

    std::string str(length, ' ');
    for(size_t i = 0; i < length; i++) {
        str[i] = characters[dis(rgn)];
    }

    return str;
}

std::string longestCommonSubsequence(std::string str1, std::string str2) {
    size_t str1Len = str1.size();
    size_t str2Len = str2.size();

    std::vector<std::vector<size_t>> lcs(str1Len + 1, std::vector<size_t>(str2Len + 1));

    for(size_t i = 0;i <= str1Len; i++) {
        for(size_t j = 0; j <= str2Len ; j++) {
            if(i == 0 || j == 0) {
                lcs[i][j] = 0;
                operations++;
            }
            else if(str1[i - 1] == str2[j - 1]) {
                lcs[i][j] = 1 + lcs[i - 1][j - 1];
                operations++;
            }
            else {
                lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
                operations++;
            }
        }
    }

    std::string result;
    size_t i = str1Len, j = str2Len;
    while(i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            result = str1[i - 1] + result;
            i--;
            j--;
        } 
        else if (lcs[i - 1][j] > lcs[i][j - 1]) {
            i--;
        } 
        else {
            j--;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    if(argc == 5) {
        size_t n_min{static_cast<size_t>(std::stoi(argv[1]))};
        size_t n_max{static_cast<size_t>(std::stoi(argv[2]))};
        size_t step{static_cast<size_t>(std::stoi(argv[3]))};

        std::ofstream file{argv[4]};

        for(size_t n = n_min; n <= n_max; n += step) {
            std::string str1{randomString(n)};
            std::string str2{randomString(n)};

            size_t sum = 0;
            for(int i = 0; i < 10; i++) {
                operations = 0;
                longestCommonSubsequence(str1, str2);
                sum += operations;
            }

            file << n << " " << static_cast<float>(sum) / 10.0f << std::endl;
        }

        file.close();
    }
    else if(argc == 3) {
        std::string str1{argv[1]};
        std::string str2{argv[2]};

        std::cout << longestCommonSubsequence(str1, str2) << std::endl;
    }

    return 0;
}