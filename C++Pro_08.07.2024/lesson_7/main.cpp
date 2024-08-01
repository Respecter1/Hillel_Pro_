#include <iostream>
#include <vector>
#include <future>
#include <numeric> // For std::accumulate

int main() {

    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


    size_t vec_size = vec.size();
    size_t mid = vec_size / 2;

  
    auto sum1 = std::async(std::launch::async, [&vec, mid]() {
        return std::accumulate(vec.begin(), vec.begin() + mid, 0);
        });

    auto sum2 = std::async(std::launch::async, [&vec, mid]() {
        return std::accumulate(vec.begin() + mid, vec.end(), 0);
        });


    int result1 = sum1.get();
    int result2 = sum2.get();


    int total_sum = result1 + result2;


    std::cout << "Sum of the first half of the vector: " << result1 << std::endl;
    std::cout << "Sum of the second half of the vector: " << result2 << std::endl;
    std::cout << "Total sum: " << total_sum << std::endl;

    return 0;
}

