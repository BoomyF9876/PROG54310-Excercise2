#pragma once
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <typename T>
class Singleton
{
public:
	inline explicit Singleton(Singleton const&) = delete;
	inline Singleton& operator=(Singleton const&) = delete;

	inline static T& Instance()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return *instance;
	}

	static void DestroyInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}

protected:
	inline explicit Singleton() = default;
	inline ~Singleton() = default;

private:
	static T* instance;
};

template <class T> T* Singleton<T>::instance = nullptr;

#endif
