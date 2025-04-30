#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : public virtual PreOrderTraversableContainer<Data>,
                        public virtual PostOrderTraversableContainer<Data> {
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete;

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const LinearContainer&) const = 0;
  virtual bool operator!=(const LinearContainer&) const = 0;

  /* ************************************************************************ */

  // Specific member functions
  virtual const Data& operator[](unsigned long) const = 0; // (non-mutable version; throws std::out_of_range)

  virtual const Data& Front() const = 0; // throws std::length_error if empty
  virtual const Data& Back() const = 0;  // throws std::length_error if empty

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void Traverse(TraverseFun) const override = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  virtual void PreOrderTraverse(TraverseFun) const override = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  virtual void PostOrderTraverse(TraverseFun) const override = 0;

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : public virtual LinearContainer<Data>,
                                public virtual PreOrderMappableContainer<Data>,
                                public virtual PostOrderMappableContainer<Data> {
  // Must extend LinearContainer<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer& operator=(const MutableLinearContainer&) = delete;

  // Move assignment
  MutableLinearContainer& operator=(MutableLinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  virtual Data& operator[](unsigned long) = 0; // (mutable version; throws std::out_of_range)
  virtual Data& Front() = 0;                   // throws std::length_error if empty
  virtual Data& Back() = 0;                    // throws std::length_error if empty

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;
  virtual void Map(MapFun) override = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  virtual void PreOrderMap(MapFun) override = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  virtual void PostOrderMap(MapFun) override = 0;

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer : public virtual MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&) = delete;

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member function
  virtual void Sort() = 0;

protected:

  // Auxiliary member functions

  // ...

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
