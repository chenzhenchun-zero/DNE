#pragma once

#include <mutex>
#include <condition_variable>

namespace MVCommon
{
	class Semaphore
	{
	public:
		Semaphore(int count = 0) :
			_count(count)
		{}

		void notify()
		{
			std::unique_lock<std::mutex> lck(_mutex);
			++_count;
			_cv.notify_one();
		}

		void wait()
		{
			std::unique_lock<std::mutex> lck(_mutex);
			while (_count == 0)
			{
				_cv.wait(lck);
			}

			--_count;
		}

	private:
		std::mutex _mutex;
		std::condition_variable _cv;
		int _count;
	};
}
