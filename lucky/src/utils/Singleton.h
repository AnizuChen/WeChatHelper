#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace lucky{
namespace utils {
template <typename T>
class Singleton {
 protected:
  Singleton() {}
  ~Singleton() {}

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;

 public:
  static T& GetInstance() {
    static T instance{};
    return instance;
  }
};
}  // namespace utils
}//namespace lucky
#endif