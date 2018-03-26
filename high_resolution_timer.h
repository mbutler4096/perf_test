#include <chrono>
#include <stdint.h>


struct high_resolution_timer
{
	high_resolution_timer() :  start_time_(take_time_stamp()) {}

	void restart() { start_time_ = take_time_stamp(); }

	double elapsed() const // Return elapsed time in seconds.
	{
		return double(take_time_stamp() - start_time_)*1e-9;
	}

	uint64_t elapsed_nanoseconds() const { return take_time_stamp() - start_time_; }

protected:
	static uint64_t take_time_stamp()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>
			(std::chrono::steady_clock::now().time_since_epoch()).count();
	}

private:
	uint64_t start_time_;
};