#pragma once

#include <queue>
#include <mutex>
#include "Semaphore.hpp"

namespace MVCommon
{
  /**
  * A bounded queue with blocking 'pull' operation. 'Push' operation causes removal of the oldest elements and therefore never blocks.
  */
	template <class T>
	class PullBlockingBoundedQueue
	{
	public:
    PullBlockingBoundedQueue(int capacity) :
			_capacity(capacity),
			_consumerSemaphore()
		{}

		void Push(T obj)
		{
			_mutex.lock();
      if (_queue.size() == _capacity)
        _queue.pop();
			_queue.push(obj);
			_mutex.unlock();

			_consumerSemaphore.notify();
		}

		T Pull()
		{
			_consumerSemaphore.wait();

			_mutex.lock();
			T value = _queue.front();
			_queue.pop();
			_mutex.unlock();

			return value;
		}

		void FlushAndPutExitToken(T exitToken)
		{
			Flush();
			Push(exitToken);
		}

		void Flush()
		{
			while (!_queue.empty())
			{
				Pull();
			}
		}

		int Size()
		{
			std::lock_guard<std::mutex> lock(_mutex);
			
			return static_cast<int>(_queue.size());
		}

    bool HasFreeSlot()
		{
      std::lock_guard<std::mutex> lock(_mutex);

      return (static_cast<int>(_queue.size()) < _capacity);
		}

    bool IsEmpty()
		{
      std::lock_guard<std::mutex> lock(_mutex);

      return _queue.empty();
		}

	private:
		int _capacity;
		std::queue<T> _queue;
		mutable std::mutex _mutex;
		Semaphore _consumerSemaphore;
	};
}

