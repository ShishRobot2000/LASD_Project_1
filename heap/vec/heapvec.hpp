#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : public virtual Heap<Data>,
                public SortableVector<Data> {

private:

  // No additional attributes

protected:

  // using Container::???;
  using SortableVector<Data>::size;


public:
  
  using SortableVector<Data>::Resize;
  using SortableVector<Data>::operator[];
  using SortableVector<Data>::operator==;
  using SortableVector<Data>::operator!=;
  
  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const TraversableContainer<Data>&); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data>&&);         // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec&);

  // Move constructor
  HeapVec(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec& operator=(const HeapVec&);

  // Move assignment
  HeapVec& operator=(HeapVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec&) const noexcept;
  bool operator!=(const HeapVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept override;     // Override Heap member

  void Heapify() noexcept override;          // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override;             // Override SortableLinearContainer member

protected:

  // Auxiliary functions, if necessary!
  void HeapifyDown(unsigned long) noexcept;
  void HeapifyUp(unsigned long) noexcept;    

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif

