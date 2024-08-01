#pragma once  
#define _NODISCARD [[nodiscard]]  
 
template<typename T> 
struct unique_ptr_ref 
{ 
    T* reference; 
 
    explicit unique_ptr_ref(T* other) 
        : reference(other) 
    {} 
}; 
 
template<typename T> 
class unique_ptr 
{ 
private: 
    T* pointer; 
 
public: 
    using element_type = T; 
 
    explicit unique_ptr(T* ptr = nullptr) noexcept 
        : pointer(ptr) 
    {} 
 
    unique_ptr(const unique_ptr& other) = delete;//T& operator=( const T& r ) 
 
    unique_ptr(unique_ptr&& other) noexcept 
        : pointer(other.pointer) 
    { 
        other.pointer = nullptr; 
    } 
 
    ~unique_ptr() 
    { 
        delete pointer; 
    } 
 
    T& operator=(const unique_ptr& other) = delete;//T& operator=( const T& r ) 
    //T& operator=( const T& r )тоб-то так неможна робити  
    //та і + у нас класс унікальний значить [переміщатись він може] або більше ніяк 
 
    unique_ptr& operator=(unique_ptr&& other) noexcept 
    { 
        if (this != &other) 
        { 
            reset(other.release()); 
        } 
        return *this; 
    } 
 
    [[nodiscard]] T& operator*() const noexcept//T& operator*() const 
    { 
#if _ITERATOR_DEBUG_LEVEL == 2  
        if (pointer == nullptr) 
        { 
            throw std::runtime_error("unique_ptr not dereferenceable"); 
        } 
#endif  
        return *pointer; 
    } 
 
    [[nodiscard]] T* operator->() const noexcept 
    { 
#if _ITERATOR_DEBUG_LEVEL == 2  
        if (pointer == nullptr) 
        { 
            throw std::runtime_error("unique_ptr not dereferenceable"); 
        } 
#endif  
        return pointer; 
    } 
 
    [[nodiscard]] T* get() const noexcept//T* get() const 
    { 
        return pointer; 
    } 
 
    explicit operator bool() const noexcept//explicit operator bool() const noexcept 
    { 
        return pointer != nullptr; 
    } 
 
    void reset(T* ptr = nullptr) noexcept 
    { 
        if (ptr != pointer) 
        { 
            delete pointer; 
            pointer = ptr; 
        } 
    } 
 
};
