#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual public Set<Data>,
               virtual protected List<Data>,
               virtual public ResizableContainer{
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  using Container::size;

public:

  // Bring base class methods into scope to avoid -Woverloaded-virtual warnings
  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;
  using LinearContainer<Data>::Traverse;
  using LinearContainer<Data>::PreOrderTraverse;
  using LinearContainer<Data>::PostOrderTraverse;

  // Default constructor
  SetLst() = default;

  /* ************************************************************************ */

  // Specific constructors
  SetLst(const TraversableContainer<Data>&); // Copy from TraversableContainer
  SetLst(MappableContainer<Data>&&);         // Move from MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetLst(const SetLst&);

  // Move constructor
  SetLst(SetLst&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SetLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  SetLst& operator=(const SetLst&);

  // Move assignment
  SetLst& operator=(SetLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetLst&) const;
  bool operator!=(const SetLst&) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

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

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Copy
  bool Insert(Data&&) override;      // Move
  bool Remove(const Data&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](unsigned long) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  // Resize the container to the given size by removing elements from the back if the size is reduced.
  void Resize(unsigned long) override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
