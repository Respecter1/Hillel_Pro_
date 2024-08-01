#include <iostream> 
#include <thread> 
#include <queue> 
#include <mutex> 
#include <condition_variable> 
 
std::queue<int> q; 
std::mutex mtx; 
std::condition_variable cv; 
bool done = false; 
 
void producer() { 
    for (int i = 0; i < 10; ++i) { 
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        { 
            std::lock_guard<std::mutex> lock(mtx); 
            q.push(i); 
            std::cout << "Produced: " << i << std::endl; 
        } 
        cv.notify_one(); 
    } 
    { 
        std::lock_guard<std::mutex> lock(mtx); 
        done = true; 
    } 
    cv.notify_one(); 
} 
 
void consumer() { 
    while (true) { 
        std::unique_lock<std::mutex> lock(mtx); 
        cv.wait(lock, [] { return !q.empty() || done; }); 
 
        if (!q.empty()) { 
            int item = q.front(); 
            q.pop(); 
            std::cout << "Consumed: " << item << std::endl; 
        } else if (done) { 
            break; 
        } 
    } 
} 
 
int main() { 
    std::thread prod(producer); 
    std::thread cons(consumer); 
 
    prod.join(); 
    cons.join(); 
 
    return 0; 
}
