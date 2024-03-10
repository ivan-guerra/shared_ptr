#ifndef SHARED_PTR_HPP_
#define SHARED_PTR_HPP_

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace memory {

template <typename T>
class SharedPtr {
 public:
  SharedPtr() : data_(nullptr), ref_count_(nullptr) {}
  explicit SharedPtr(T* data);
  ~SharedPtr();

  SharedPtr(const SharedPtr& sp);
  SharedPtr& operator=(SharedPtr rhs);
  SharedPtr(SharedPtr&& sp);
  SharedPtr& operator=(SharedPtr&& rhs);

  const T& operator*() const;
  T& operator*();

  bool Empty() const { return (!data_ && !ref_count_); }
  std::size_t RefCount() const;
  void Reset(T* data);

  template <typename U>
  friend void Swap(SharedPtr<U>& a, SharedPtr<U>& b) {
    using std::swap;
    swap(a.data_, b.data_);
    swap(a.ref_count_, b.ref_count_);
  }

 private:
  void DecrementRefCount();

  T* data_;
  std::size_t* ref_count_;
};

template <typename T>
void SharedPtr<T>::DecrementRefCount() {
  if (Empty()) {
    return;
  }

  *ref_count_ -= 1;
  if (0 == *ref_count_) {
    delete data_;
    delete ref_count_;
    data_ = nullptr;
    ref_count_ = nullptr;
  }
}

template <typename T>
SharedPtr<T>::SharedPtr(T* data)
    : data_(data), ref_count_(new std::size_t(1)) {}

template <typename T>
SharedPtr<T>::~SharedPtr() {
  DecrementRefCount();
  data_ = nullptr;
  ref_count_ = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& sp)
    : data_(sp.data_), ref_count_(sp.ref_count_) {
  *ref_count_ += 1;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr rhs) {
  DecrementRefCount();
  Swap(*this, rhs);

  return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& sp) : SharedPtr<T>() {
  Swap(*this, sp);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& rhs) {
  DecrementRefCount();

  Swap(*this, rhs);

  return *this;
}

template <typename T>
std::size_t SharedPtr<T>::RefCount() const {
  if (Empty()) {
    throw std::runtime_error("cannot return ref count of NULL SharedPtr");
  }
  return *ref_count_;
}

template <typename T>
const T& SharedPtr<T>::operator*() const {
  if (Empty()) {
    throw std::runtime_error("cannot dereference NULL SharedPtr");
  }
  return *data_;
}

template <typename T>
T& SharedPtr<T>::operator*() {
  if (Empty()) {
    throw std::runtime_error("cannot dereference NULL SharedPtr");
  }
  return *data_;
}

template <typename T>
void SharedPtr<T>::Reset(T* data) {
  DecrementRefCount();

  data_ = data;
  ref_count_ = new std::size_t(1);
}

}  // namespace memory

#endif
