#pragma once

#include <chrono>

namespace alg
{

namespace chrono
{


	class Meter
	{
	public:
		Meter() {
			start_ = std::chrono::high_resolution_clock::now();
		}

		void reset() noexcept {
			start_ = std::chrono::high_resolution_clock::now();
		}

		double get() const noexcept {
			const auto end = std::chrono::high_resolution_clock::now();
			const auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start_);

			return time.count() / 1e9;
		}

	private:
		std::chrono::system_clock::time_point start_;
	};


}

}
