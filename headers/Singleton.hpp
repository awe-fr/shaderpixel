#ifndef SINGLETON_HPP
# define SINGLETON_HPP

# include "./Object.hpp"
# include "./main.h"

class Object;

template <typename T, typename L>
class Singleton {
	protected:
		static T *_instance;
		std::vector<L *> _list;
		static std::mutex _mutex;

		Singleton() {};
		virtual ~Singleton() {};
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
	public:
		static T *getInstance() {
			std::lock_guard<std::mutex> lock(_mutex);
			if (_instance == nullptr)
				_instance = new T();
			return (_instance);
		}

		std::vector<L *> getList() {
			std::lock_guard<std::mutex> lock(_mutex);
			return (this->_list);
		};

		void    add(L *toAdd) {
			std::lock_guard<std::mutex> lock(_mutex);
			if (toAdd != nullptr)
				this->_list.push_back(toAdd);
		};

		void    remove(L *toRm) {
			std::lock_guard<std::mutex> lock(_mutex);
			if (toRm != nullptr) {
				for (int i = this->_list.size(); i > 0; i--) {
					if (this->_list[i - 1] == toRm) {
						this->_list.erase(this->_list.begin() + i - 1);
						break;
					}
				}
			}
		};

		void    cleanup() {
			std::lock_guard<std::mutex> lock(_mutex);
			for (int i = this->_list.size(); i > 0; i--) {
				delete this->_list[i - 1];
			}
		};
};

template <typename T, typename L>
T* Singleton<T, L>::_instance = nullptr;

template <typename T, typename L>
std::mutex Singleton<T, L>::_mutex;

class ObjectList : public Singleton<ObjectList, Object> {
	private:

	public:
};

#endif