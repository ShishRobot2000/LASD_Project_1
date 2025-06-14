#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public MutableLinearContainer<Data>, 
              virtual public ResizableContainer {

protected:

  using Container::size;
  Data* elements_ = nullptr;

public:
    
  // Bring base class methods into scope to avoid -Woverloaded-virtual warnings
  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;
  using MutableLinearContainer<Data>::operator[];
  using MutableLinearContainer<Data>::Front;
  using MutableLinearContainer<Data>::Back;

  // Default constructor
  Vector() = default;

  // Specific constructor
  Vector(ulong);

  // Constructor 
  Vector(const TraversableContainer<Data>&);
  Vector(MappableContainer<Data>&&);

  // Copy constructor
  Vector(const Vector&);

  // Move constructor
  Vector(Vector&&) noexcept;

  // Destructor
  ~Vector();

  /* ************************************************************************ */

  // Traversable
  void Traverse(typename TraversableContainer<Data>::TraverseFun) const override;
  void PreOrderTraverse(typename TraversableContainer<Data>::TraverseFun) const override;
  void PostOrderTraverse(typename TraversableContainer<Data>::TraverseFun) const override;

  // Mappable
  void Map(typename MappableContainer<Data>::MapFun) override;
  void PreOrderMap(typename MappableContainer<Data>::MapFun) override;
  void PostOrderMap(typename MappableContainer<Data>::MapFun) override;

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector&);

  // Move assignment
  Vector& operator=(Vector&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer<Data>&) const noexcept override;
  bool operator!=(const LinearContainer<Data>&) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions
  const Data& operator[](unsigned long) const override;
  Data& operator[](unsigned long) override;

  const Data& Front() const override;
  Data& Front() override;

  const Data& Back() const override;
  Data& Back() override;

  /* ************************************************************************ */

  void Clear() override;
  void Resize(ulong);

protected:

  // Auxiliary member function
  void InsertAt(unsigned long index, const Data&);
  void InsertAt(unsigned long index, Data&&);

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : public Vector<Data>, public virtual SortableLinearContainer<Data> {

protected:

public:

  // Default constructor
  SortableVector() = default;

  // Specific constructors
  SortableVector(ulong);
  SortableVector(const TraversableContainer<Data>&);
  SortableVector(MappableContainer<Data>&&);

  // Copy constructor
  SortableVector(const SortableVector&);

  // Move constructor
  SortableVector(SortableVector&&) noexcept;

  // Destructor
  ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector& operator=(const SortableVector&);

  // Move assignment
  SortableVector& operator=(SortableVector&&) noexcept;

  /* ************************************************************************ */

  // Sort
  void Sort() override;

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
