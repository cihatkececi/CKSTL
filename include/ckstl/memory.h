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

template<typename Alloc>
struct AllocatorTraits {
    using allocator_type = Alloc;
    using value_type = typename Alloc::value_type;
    using pointer = typename Alloc::pointer;
    using const_pointer = typename Alloc::const_pointer;
    using void_pointer = typename Alloc::void_pointer;
    using const_void_pointer = typename Alloc::const_void_pointer;
    using difference_type = typename Alloc::difference_type;
    using size_type = typename Alloc::size_type;
    using propagate_on_container_copy_assignment = typename Alloc::propagate_on_container_copy_assignment;
    using propagate_on_container_move_assignment = typename Alloc::propagate_on_container_move_assignment;
    using propagate_on_container_swap = typename Alloc::propagate_on_container_swap;
    using is_always_equal = typename Alloc::is_always_equal;

    template<typename T>
    using rebind_alloc = typename Alloc::template rebind<T>::other;

    template<typename T>
    using rebind_traits = AllocatorTraits<rebind_alloc<T>>;

    [[nodiscard]] static constexpr pointer allocate(Alloc& a, size_type n) {
        return a.allocate(n);
    }

    [[nodiscard]] static constexpr pointer allocate(Alloc& a, size_type n, const_void_pointer hint) {
        return a.allocate(n, hint);
    }

    static constexpr void deallocate(Alloc& a, pointer p, size_type n) {
        a.deallocate(p, n);
    }

    template<class T, class... Args>
    static constexpr void construct(Alloc& a, T* p, Args&& ... args) {
        a.construct(p, std::forward<Args>(args)...);
    }

    template<class T>
    static constexpr void destroy(Alloc& a, T* p) {
        a.destroy(p);
    }

    static constexpr size_type max_size(const Alloc& a) noexcept {
        return a.max_size();
    }

    static constexpr Alloc select_on_container_copy_construction(const Alloc& a) {
        a.select_on_container_copy_construction();
    }
};

}
