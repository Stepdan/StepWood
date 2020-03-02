#pragma once

#include <atomic>
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <thread>

namespace EyeFactive::Utils {

template<typename P, typename R>
class ThreadWorker
{
protected:
	using ParamType = P;
	using ResultType = R;
	using BaseType = ThreadWorker;

protected:
	enum class Priority
	{
		Normal = 0,
		Low,
	};

private:
	const std::string m_name;
	std::atomic<bool> m_threadRunning{ true };
	std::promise<void> m_threadStartedPromise;
	mutable std::mutex m_threadStartedGuard;
	mutable std::mutex m_parameterGuard;
	mutable std::condition_variable m_threadStartedCondition;
	std::thread m_thread;

protected:
	ThreadWorker(std::string_view name)
		: m_name(name)
	{
	}
	virtual ~ThreadWorker()
	{
	}

protected:
	void Enqueue(std::unique_ptr<ParamType> &&parameter) const
	{
		{
			std::unique_lock<std::mutex> lock(m_parameterGuard);
			EnqueueImpl(std::move(parameter));
		}
		std::unique_lock<std::mutex> lock(m_threadStartedGuard);
		m_threadStartedCondition.notify_all();
	}

	void Reset() const
	{
		std::unique_lock<std::mutex> lock(m_parameterGuard);
		ResetImpl();
	}

	bool IsReady() const
	{
		std::unique_lock<std::mutex> lock(m_parameterGuard);
		return IsReadyImpl();
	}

	void WaitForStart(Priority priority = Priority::Normal)
	{
		m_thread = std::thread(&ThreadWorker::ThreadFunction, this);
		auto waitForStart = m_threadStartedPromise.get_future();
		waitForStart.get();

//        if (priority == Priority::Low)
//            if (!SetThreadLowPriority(m_thread))
//                {}
	}
	void WaitForStop()
	{
		m_threadRunning = false;
		{
			std::lock_guard<std::mutex> lock(m_threadStartedGuard);
			m_threadStartedCondition.notify_all();
		}

		if (m_thread.joinable())
			m_thread.join();
	}

private:
	virtual void EnqueueImpl(std::unique_ptr<ParamType> &&parameter) const = 0;
	virtual void DequeueImpl(std::unique_ptr<ParamType> &parameter) const = 0;
	virtual void ResetImpl() const = 0;
	virtual bool IsReadyImpl() const = 0;
	virtual ResultType Work(const ParamType&) const = 0;
	virtual void ProcessResult(ResultType&&) = 0;
	virtual void ProcessError(std::unique_ptr<ParamType>&&) {}
	virtual void ThreadFunctionInit() {}
	virtual void ThreadFunctionRelease() {}

	void ThreadFunction()
	{
		m_threadStartedPromise.set_value();

		ThreadFunctionInit();

		while (m_threadRunning)
		{
			{
				std::unique_lock<std::mutex> lock(m_threadStartedGuard);
				m_threadStartedCondition.wait(lock, [this]() -> bool
				{
					if (!m_threadRunning)
						return true;

					return IsReady();
				});
			}

			if (!m_threadRunning)
				continue;

			std::unique_ptr<ParamType> parameter;
			{
				std::unique_lock<std::mutex> lock(m_parameterGuard);
				DequeueImpl(parameter);
			}
			if (!parameter)
				continue;

			try
			{
				auto res = Work(*parameter);
				ProcessResult(std::move(res));
				continue;
			}
			catch (const std::exception &ex)
			{
			}
			catch (...)
			{
			}

			ProcessError(std::move(parameter));
		}

		ThreadFunctionRelease();
	}
};

}
