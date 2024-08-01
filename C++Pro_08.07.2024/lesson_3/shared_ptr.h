#pragma once
#define _NODISCARD [[nodiscard]]

// Структура для управління лічильником посилань 
struct shared_ptr_ref {
    shared_ptr_ref() : reference(1) {}

    void increment() { ++reference; }

    int decrement() { return --reference; }

    int getReference() const { return reference; }

private:
    int reference;
};

template <class T>
class shared_ptr {
private:
    T* pointer;
    shared_ptr_ref* ref;

public:
    //----------------
    // --- typedef ---
    //----------------

    using element_type = T;

    //--------------------
    // --- Constructor ---
    //--------------------

    explicit shared_ptr(T* ptr = nullptr) noexcept
        : pointer(ptr), ref(ptr ? new shared_ptr_ref() : nullptr)
    {}

    shared_ptr(const shared_ptr& other) noexcept
        : pointer(other.pointer), ref(other.ref)
    {
        if (ref) {
            ref->increment();
        }
    }

    template <class OtherT>
    shared_ptr(const shared_ptr<OtherT>& other) noexcept
        : pointer(other.pointer), ref(other.ref)
    {
        if (ref) {
            ref->increment();
        }
    }

    shared_ptr(shared_ptr&& other) noexcept
        : pointer(nullptr), ref(nullptr)
    {
        Move(other);
    }

    //-------------------
    // --- Destructor ---
    //-------------------

    ~shared_ptr() noexcept {
        Clear();
    }

    //---------------
    // --- Method ---
    //---------------

    int use_count() const noexcept {
        return ref ? ref->getReference() : 0;
    }

    void reset(T* ptr = nullptr) noexcept {
        Clear();
        pointer = ptr;
        ref = ptr ? new shared_ptr_ref() : nullptr;
    }

    [[nodiscard]] T* get() const noexcept {
        return pointer;
    }

    void Move(shared_ptr& other) noexcept {
        pointer = other.pointer;
        ref = other.ref;
        other.pointer = nullptr;
        other.ref = nullptr;
    }

    void Clear() noexcept {
        if (ref && ref->decrement() == 0) {
            delete pointer;
            delete ref;
        }
        pointer = nullptr;
        ref = nullptr;
    }

    void Add(shared_ptr& other)
    {
        pointer = other.pointer;
        ref = other.ref;
        ref->increment();
    }

    //-----------------
    // --- Operator ---
    //-----------------
    
    template <class OtherT>
    shared_ptr& operator=(const shared_ptr<OtherT>& other) noexcept {
        if (this != reinterpret_cast<const shared_ptr*>(&other)) {
            Clear();
            Add(other);
        }
        return *this;
    }

    shared_ptr& operator=(const shared_ptr& other) noexcept {
        if (this != &other) {
            Clear();
            Add(other);
        }
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            Clear();
            Move(other);
        }
        return *this;
    }

    template <class OtherT>
    shared_ptr& operator=(shared_ptr<OtherT>&& other) noexcept {
        if (this != reinterpret_cast<const shared_ptr*>(&other)) {
            Clear();
            Move(other);
        }
        return *this;
    }

    [[nodiscard]] T& operator*() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2  
        if (pointer == nullptr) {
            throw std::runtime_error("shared_ptr not dereferenceable");
        }
#endif  
        return *pointer;
    }

    [[nodiscard]] T* operator->() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2  
        if (pointer == nullptr) {
            throw std::runtime_error("shared_ptr not dereferenceable");
        }
#endif  
        return pointer;
    }

    explicit operator bool() const noexcept {
        return pointer != nullptr;
    }
};

// Спеціалізація шаблону для типу void 
template <>
class shared_ptr<void> {
public:
    using element_type = void;
};
