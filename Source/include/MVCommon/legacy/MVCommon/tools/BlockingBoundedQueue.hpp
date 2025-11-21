#pragma once

#include <queue>
#include <mutex>
#include "Semaphore.hpp"

namespace MVCommon
{
	template <class T>
	class BlockingBoundedQueue
	{
	public:
		BlockingBoundedQueue(int capacity) :
			_capacity(capacity),
			_producerSemaphore(capacity),
			_consumerSemaphore()
		{}

		void Push(T obj)
		{
			_producerSemaphore.wait();

			_mutex.lock();
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

			_producerSemaphore.notify();

			return value;
		}

    T PullNonblock()
    {
      _mutex.lock();

      if (_queue.empty())
      {
        _mutex.unlock();
        return T();
      }
      
      T value = _queue.front();
      _queue.pop();
      _mutex.unlock();
      _producerSemaphore.notify();
      return value;
    }

    T Top()
    {
      // wait until there is at least one value
      _consumerSemaphore.wait();

      _mutex.lock();
      T value = _queue.front();
      _mutex.unlock();

      // Top() does not consume the value -> re-notify about the value available
      _consumerSemaphore.notify();

      return value; 
    }

    T TopNonblock() const
    {
      std::lock_guard<std::mutex> lock(_mutex);
      if (_queue.empty())
        return T();

      return _queue.front();
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
		Semaphore _producerSemaphore;
		Semaphore _consumerSemaphore;
	};
}

