#pragma once

#include <memory>

namespace pattern
{
	template <typename T>
	class singleton
	{
		static std::unique_ptr<T> m_pInstance;
	public:
		singleton<T>() = default;
		virtual ~singleton<T>() = default;
		singleton<T>(const singleton<T>&) = delete;
		singleton<T>(singleton<T>&&) = delete;
		singleton<T>& operator=(const singleton<T>&) = delete;
		singleton<T>& operator=(singleton<T>&&) = delete;
	public:
		static T* InstancePtr()
		{
			if (!m_pInstance)
				m_pInstance.reset(new T);
			return m_pInstance.get();
		}
		static T& Instance()
		{
			if (!m_pInstance)
				m_pInstance.reset(new T);
			return *m_pInstance;
		}
		static void Reset(T* pInstance_ = nullptr)
		{
			m_pInstance.reset(std::move(pInstance_));
		}
	};
	template <typename T> std::unique_ptr<T> singleton<T>::m_pInstance;
};