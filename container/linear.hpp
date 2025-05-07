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
  virtual bool operator==(const LinearContainer&) const noexcept;
  virtual bool operator!=(const LinearContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  virtual const Data& operator[](unsigned long) const = 0; // (non-mutable version; throws std::out_of_range)

  virtual const Data& Front() const; // throws std::length_error if empty
  virtual const Data& Back() const;  // throws std::length_error if empty

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  virtual void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  virtual void PostOrderTraverse(TraverseFun) const override;

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
  
  // Bring base class versions into scope to avoid hiding warnings
  using LinearContainer<Data>::operator[];
  using LinearContainer<Data>::Front;
  using LinearContainer<Data>::Back;
  
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
  virtual Data& Front();                   // throws std::length_error if empty
  virtual Data& Back();                    // throws std::length_error if empty

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;
  virtual void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  virtual void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  virtual void PostOrderMap(MapFun) override;

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer : public virtual MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>

private:

  // ...

protected:

  // Auxiliary member functions
  void MergeSort(unsigned long left, unsigned long right);
  void Merge(unsigned long left, unsigned long mid, unsigned long right);

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
  virtual void Sort();

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
