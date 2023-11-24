#include <array>
#include <cstdint>
#include <iostream>
#include <ranges>

constexpr std ::array<u_int32_t, 11> fib = {0, 1,  1,  2,  3, 5, 8, 13, 21, 34, 55};

auto main() -> int {
	auto fib_mod {
		::fib | std::views::filter([](const auto &fib_num) {
				std::cout << '%' << fib_num << std::endl;
				return fib_num % 2 == 1;
			}) | std::views::drop(1)
			| std::views::take(3)
			| std::views::transform([](const auto &fib_uneven) {
				std::cout << '*' << fib_uneven * 2 + 1 << std::endl;
				return fib_uneven * 2 + 1;
			})};

	std::cout << "> Starting Iteration" << std::endl;
	for (const auto &f : fib_mod) {
		std::cout << f << std::endl;
  }
}