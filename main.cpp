#include "ring_buffer.hpp"
#include <chrono>
#include <iostream>

template <bool magic>
auto demonstrate_ring_buffer() -> void {
    magic::RingBuffer<int, 4096> buffer;

    auto start = std::chrono::high_resolution_clock::now();

    static size_t index { 0 };
    for (auto& i : buffer.peek()) {
        buffer.write(index++);
    }

    for (const auto& i : buffer.c_peek()) {
        std::cerr << i << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;

    magic::RingBuffer<int, 4096> buffer2 { std::move(buffer) };
}

int main() {
    try {
        for (size_t i { 0 }; i < 100; ++i) {
            demonstrate_ring_buffer<true>();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
