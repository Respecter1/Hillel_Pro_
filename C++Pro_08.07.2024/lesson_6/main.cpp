#include <iostream>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>

template <typename T>
class Thread_safe_vector {
public:
  
    void push_back(const T& value) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        vector_.push_back(value);
    }


    T get(size_t index) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        if (index >= vector_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return vector_[index];
    }


    size_t size() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return vector_.size();
    }


    void erase(size_t index) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (index >= vector_.size()) {
            throw std::out_of_range("Index out of range");
        }
        vector_.erase(vector_.begin() + index);
    }

private:
    std::vector<T> vector_;
    mutable std::shared_mutex mutex_;
};

int main() {
    Thread_safe_vector<int> ts_vector;


    ts_vector.push_back(10);
    ts_vector.push_back(20);

    try {
        std::cout << "Element at index 0: " << ts_vector.get(0) << std::endl;
        std::cout << "Size: " << ts_vector.size() << std::endl;
        ts_vector.erase(0);
        std::cout << "Size after erase: " << ts_vector.size() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

