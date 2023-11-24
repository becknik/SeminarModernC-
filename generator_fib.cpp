#include <generator>
#include <coroutine>
#include <iostream>
#include <ranges>
#include <cstdint>

// <generator> header isn't available anywhere at the time of writing, so this is only a guess rn
std::generator<u_int64_t> fib_generator() {
	u_int64_t a = 0;
	u_int64_t b = 1;
	co_yield a; co_yield b;
	while (true) {
		const u_int64_t tmp = b;
		b = a + b;
		a = tmp;
		co_yield b;
	}
}

auto main() -> int {
    for (const char ch : fib_generator() | std::views::take(26))
        std::cout << ch << ' ';
    std::cout << '\n';
}