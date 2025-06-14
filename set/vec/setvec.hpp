#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : public virtual Set<Data>,
               public virtual ResizableContainer {
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // Auxiliary attributes for circular buffer
  Data* elements = nullptr;         // Dynamic array
  unsigned long head = 0;           // Index of first element
  unsigned long tail = 0;           // Index of insertion point (after last)
  unsigned long capacity = 0;       // Allocated capacity

protected:

  using Container::size;

  // Utility methods
  unsigned long CircularIndex(unsigned long) const;
  void ExpandCapacity();
  void ReduceCapacity();
  void InsertAt(unsigned long, const Data&);
  void InsertAt(unsigned long, Data&&);
  void RemoveAt(unsigned long);
  long BinarySearch(const Data&) const;

public:

  // Bring base class methods into scope
  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;

  // Default constructor
  SetVec() = default;

  // Specific constructors
  SetVec(const TraversableContainer<Data>&); // Copy from TraversableContainer
  SetVec(MappableContainer<Data>&&);         // Move from MappableContainer

  // Copy constructor
  SetVec(const SetVec&);

  // Move constructor
  SetVec(SetVec&&) noexcept;

  // Destructor
  ~SetVec();

  // Copy assignment
  SetVec& operator=(const SetVec&);

  // Move assignment
  SetVec& operator=(SetVec&&) noexcept;

  // Comparison operators
  bool operator==(const SetVec&) const;
  bool operator!=(const SetVec&) const;

  // OrderedDictionary functions
  const Data& Min() const override;
  Data MinNRemove() override;
  void RemoveMin() override;

  const Data& Max() const override;
  Data MaxNRemove() override;
  void RemoveMax() override;

  const Data& Predecessor(const Data&) const override;
  Data PredecessorNRemove(const Data&) override;
  void RemovePredecessor(const Data&) override;

  const Data& Successor(const Data&) const override;
  Data SuccessorNRemove(const Data&) override;
  void RemoveSuccessor(const Data&) override;

  // Dictionary functions
  bool Insert(const Data&) override;    // Copy
  bool Insert(Data&&) override;         // Move
  bool Remove(const Data&) override;

  bool InsertAll(const TraversableContainer<Data>&) override;
  bool InsertAll(MappableContainer<Data>&&) override;

  bool RemoveAll(const TraversableContainer<Data>&) override;

  bool InsertSome(const TraversableContainer<Data>&) override;
  bool InsertSome(MappableContainer<Data>&&) override;

  bool RemoveSome(const TraversableContainer<Data>&) override;

  // LinearContainer functions
  const Data& operator[](unsigned long) const override;

  // TestableContainer function
  bool Exists(const Data&) const noexcept override;

  // ClearableContainer function
  void Clear() override;

  // ResizableContainer functions
  void Resize(unsigned long) override;
  bool Empty() const noexcept override { return (size == 0); }
  unsigned long Size() const noexcept override { return size; }

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
