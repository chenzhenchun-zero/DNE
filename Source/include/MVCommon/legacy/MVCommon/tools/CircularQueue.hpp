#pragma once

#include <queue>
#include <mutex>

namespace MVCommon
{
  /**
  * A circular queue collection which discards the oldest elements when is full and new element is about to be enqueued.
  * The collection is thread-safe.
  */
	template <class T>
	class CircularQueue
	{
	public:
    CircularQueue(int capacity) :
			_capacity(std::max(1, capacity))
		{}

		void Push(T obj)
		{
      std::lock_guard<std::mutex> lock(_mutex);

			if (_queue.size() == _capacity)
        _queue.pop();
			_queue.push(obj);
		}

		T Pull()
		{
      std::lock_guard<std::mutex> lock(_mutex);
			
      T value{};
      if (_queue.size() > 0)
      {
        value = _queue.front();
        _queue.pop();
      }

			return value;
		}

		void Flush()
		{
      std::lock_guard<std::mutex> lock(_mutex);

			while (!_queue.empty())
        _queue.pop();
		}

    void Flush(void(*deallocator)(T))
    {
      std::lock_guard<std::mutex> lock(_mutex);

      while (!_queue.empty())
      {
        T dequeuedItem = _queue.front();
        _queue.pop();
        deallocator(dequeuedItem);
      }
    }

		int Size() const
		{
			std::lock_guard<std::mutex> lock(_mutex);
			
			return static_cast<int>(_queue.size());
		}

    bool HasFreeSlot() const
		{
      std::lock_guard<std::mutex> lock(_mutex);

      return (static_cast<int>(_queue.size()) < _capacity);
		}

    bool IsEmpty() const
		{
      std::lock_guard<std::mutex> lock(_mutex);

      return _queue.empty();
		}

	private:
		int _capacity;
		std::queue<T> _queue;
		mutable std::mutex _mutex;
	};
}

