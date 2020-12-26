#pragma once


namespace ck {

template<typename T>
class Allocator {
public:
    static T* allocate(const size_t size) {
        return static_cast<T*>(::operator new(size * sizeof(T)));
    }

    static void deallocate(T* const pointer) {
        ::operator delete(pointer);
    }

    template<typename ...Args>
    static void construct(T* const pointer, Args&& ... args) {
        ::new(static_cast<void*>(pointer)) T{std::forward<Args>(args)...};
    }

    static void destroy(T* const pointer) {
        pointer->~T();
    }

    template<typename U>
    struct rebind {
        using type = Allocator<U>;
    };
};

}
