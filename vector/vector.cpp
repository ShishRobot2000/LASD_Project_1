#include <stdexcept>

namespace lasd {

  /* ************************************************************************** */
  /* Constructors */
  
  template <typename Data>
  Vector<Data>::Vector(const ulong newsize) {
    elements_ = new Data[newsize]();
    size = newsize;
  }
  
  template <typename Data>
  Vector<Data>::Vector(const TraversableContainer<Data>& container) {
    size = container.Size();
    elements_ = new Data[size];
    ulong i = 0;
    container.Traverse([&](const Data& dat) {
      elements_[i++] = dat;
    });
  }
  
  template <typename Data>
  Vector<Data>::Vector(MappableContainer<Data>&& container) {
    size = container.Size();
    elements_ = new Data[size];
    ulong i = 0;
    container.Map([&](Data& dat) {
      std::swap(elements_[i++], dat);
    });
  }
  
  template <typename Data>
  Vector<Data>::Vector(const Vector& vec) {
    size = vec.size;
    elements_ = new Data[size];
    for (ulong i = 0; i < size; ++i)
      elements_[i] = vec.elements_[i];
  }
  
  template <typename Data>
  Vector<Data>::Vector(Vector&& vec) noexcept {
    std::swap(elements_, vec.elements_);
    std::swap(size, vec.size);
  }
  
  template <typename Data>
  Vector<Data>::~Vector() {
    delete[] elements_;
  }
  
  /* ************************************************************************** */
  /* Assignment operators */
  
  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(const Vector& vec) {
    if (this != &vec) {
      Vector<Data> tmp(vec);
      std::swap(*this, tmp);
    }
    return *this;
  }
  
  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(Vector&& vec) noexcept {
    std::swap(elements_, vec.elements_);
    std::swap(size, vec.size);
    return *this;
  }
  
  /* ************************************************************************** */
  /* Comparison operators */
  
  template <typename Data>
  bool Vector<Data>::operator==(const LinearContainer<Data>& con) const noexcept {
    if (size != con.Size()) return false;
    for (ulong i = 0; i < size; ++i)
      if (!(elements_[i] == con[i])) return false;
    return true;
  }
  
  template <typename Data>
  bool Vector<Data>::operator!=(const LinearContainer<Data>& con) const noexcept {
    return !(*this == con);
  }
  
  /* ************************************************************************** */
  /* Access functions */
  
  template <typename Data>
  const Data& Vector<Data>::operator[](const ulong index) const {
    if (index >= size) throw std::out_of_range("Access out of range");
    return elements_[index];
  }
  
  template <typename Data>
  Data& Vector<Data>::operator[](const ulong index) {
    if (index >= size) throw std::out_of_range("Access out of range");
    return elements_[index];
  }
  
  template <typename Data>
  const Data& Vector<Data>::Front() const {
    if (size == 0) throw std::length_error("Vector is empty");
    return elements_[0];
  }
  
  template <typename Data>
  Data& Vector<Data>::Front() {
    if (size == 0) throw std::length_error("Vector is empty");
    return elements_[0];
  }
  
  template <typename Data>
  const Data& Vector<Data>::Back() const {
    if (size == 0) throw std::length_error("Vector is empty");
    return elements_[size - 1];
  }
  
  template <typename Data>
  Data& Vector<Data>::Back() {
    if (size == 0) throw std::length_error("Vector is empty");
    return elements_[size - 1];
  }
  
  /* ************************************************************************** */
  /* Clear / Resize */
  
  template <typename Data>
  void Vector<Data>::Clear() {
    delete[] elements_;
    elements_ = nullptr;
    size = 0;
  }
  
  template <typename Data>
  void Vector<Data>::Resize(const ulong newsize) {
    if (newsize == 0) {
      Clear();
    } else {
      Data* tmp = new Data[newsize]();
      ulong min = (newsize < size) ? newsize : size;
      for (ulong i = 0; i < min; ++i)
        tmp[i] = std::move(elements_[i]);
      delete[] elements_;
      elements_ = tmp;
      size = newsize;
    }
  }
  
  /* ************************************************************************** */
  /* Mappable */
  
  template <typename Data>
  void Vector<Data>::Map(typename MappableContainer<Data>::MapFun fun) {
    for (ulong i = 0; i < size; ++i)
      fun(elements_[i]);
  }
  
  template <typename Data>
  void Vector<Data>::PreOrderMap(typename MappableContainer<Data>::MapFun fun) {
    Map(fun);
  }
  
  template <typename Data>
  void Vector<Data>::PostOrderMap(typename MappableContainer<Data>::MapFun fun) {
    for (long i = size - 1; i >= 0; --i)
      fun(elements_[i]);
  }
  
  /* ************************************************************************** */
  /* Traversable */
  
  template <typename Data>
  void Vector<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const {
    for (ulong i = 0; i < size; ++i)
      fun(elements_[i]);
  }
  
  template <typename Data>
  void Vector<Data>::PreOrderTraverse(typename TraversableContainer<Data>::TraverseFun fun) const {
    Traverse(fun);
  }
  
  template <typename Data>
  void Vector<Data>::PostOrderTraverse(typename TraversableContainer<Data>::TraverseFun fun) const {
    for (long i = size - 1; i >= 0; --i)
      fun(elements_[i]);
  }
  
  // Auxiliary member function
  
  template <typename Data>
  void Vector<Data>::InsertAt(unsigned long index, const Data& dat) {
    if (index > size) throw std::out_of_range("Index out of range");
    Resize(size + 1);
    for (unsigned long i = size - 1; i > index; --i) {
      elements_[i] = std::move(elements_[i - 1]);
    }
    elements_[index] = dat;
  }
  
  template <typename Data>
  void Vector<Data>::InsertAt(unsigned long index, Data&& dat) {
    if (index > size) throw std::out_of_range("Index out of range");
    Resize(size + 1);
    for (unsigned long i = size - 1; i > index; --i) {
      elements_[i] = std::move(elements_[i - 1]);
    }
    elements_[index] = std::move(dat);
  }  

  /* ************************************************************************** */
  /* SortableVector */
  
  template <typename Data>
  SortableVector<Data>::SortableVector(const ulong size)
      : Vector<Data>(size) {}

  template <typename Data>
  SortableVector<Data>::SortableVector(const TraversableContainer<Data>& container)
      : Vector<Data>(container) {}

  template <typename Data>
  SortableVector<Data>::SortableVector(MappableContainer<Data>&& container)
      : Vector<Data>(std::move(container)) {}
  
  template <typename Data>
  SortableVector<Data>::SortableVector(const SortableVector& vec)
      : Vector<Data>(vec) {}
  
  template <typename Data>
  SortableVector<Data>::SortableVector(SortableVector&& vec) noexcept
      : Vector<Data>(std::move(vec)) {}
  
  template <typename Data>
  SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector& vec) {
    Vector<Data>::operator=(vec);
    return *this;
  }
  
  template <typename Data>
  SortableVector<Data>& SortableVector<Data>::operator=(SortableVector&& vec) noexcept {
    Vector<Data>::operator=(std::move(vec));
    return *this;
  }
  
  template <typename Data>
  void lasd::SortableVector<Data>::Sort() {
    for (unsigned long i = 1; i < this->Size(); ++i) {
      Data temp = std::move((*this)[i]);
      long j = i - 1;

      while (j >= 0 && temp < (*this)[j]) {
        (*this)[j + 1] = std::move((*this)[j]);
        --j;
      }
      (*this)[j + 1] = std::move(temp);
    }
  }
  
  /* ************************************************************************** */
  
  } // namespace lasd  