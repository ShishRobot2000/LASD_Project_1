#include <stdexcept>

namespace lasd {

/* ************************** */

// LinearContainer

template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer& other) const noexcept {
  if (this->Size() != other.Size())
    return false;
  for (unsigned long i = 0; i < this->Size(); ++i) {
    if ((*this)[i] != other[i])
      return false;
  }
  return true;
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer& other) const noexcept {
  return !(*this == other);
}

template <typename Data>
const Data& LinearContainer<Data>::Front() const {
  if (this->Size() == 0)
    throw std::length_error("Access to front of an empty container");
  return (*this)[0];
}

template <typename Data>
const Data& LinearContainer<Data>::Back() const {
  if (this->Size() == 0)
    throw std::length_error("Access to back of an empty container");
  return (*this)[this->Size() - 1];
}

template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
  for (unsigned long i = 0; i < this->Size(); ++i)
    fun((*this)[i]);
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
  for (unsigned long i = this->Size(); i > 0; --i)
    fun((*this)[i - 1]);
}

/* ************************** */

// MutableLinearContainer

template <typename Data>
void MutableLinearContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

template <typename Data>
Data& MutableLinearContainer<Data>::Front() {
  if (this->Size() == 0)
    throw std::length_error("Access to front of an empty container");
  return (*this)[0];
}

template <typename Data>
Data& MutableLinearContainer<Data>::Back() {
  if (this->Size() == 0)
    throw std::length_error("Access to back of an empty container");
  return (*this)[this->Size() - 1];
}

template <typename Data>
void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
  for (unsigned long i = 0; i < this->Size(); ++i)
    fun((*this)[i]);
}

template <typename Data>
void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
  for (unsigned long i = this->Size(); i > 0; --i)
    fun((*this)[i - 1]);
}

/* ************************** */

// SortableLinearContainer

template <typename Data>
void lasd::SortableLinearContainer<Data>::Sort() {
  for (unsigned long i = 1; i < this->Size(); ++i) {
    Data tmp = std::move((*this)[i]);
    long j = i - 1;
    while (j >= 0 && tmp < (*this)[j]) {
      (*this)[j + 1] = std::move((*this)[j]);
      --j;
    }
    (*this)[j + 1] = std::move(tmp);
  }
}

/* ************************** */

} // namespace lasd