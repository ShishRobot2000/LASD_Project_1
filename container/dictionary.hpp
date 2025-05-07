#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : public virtual TestableContainer<Data>,
                            public virtual MappableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer&) = delete; // Copy assignment of abstract types is not possible.
  DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer&) const = delete; // Comparison of abstract types is not possible.
  bool operator!=(const DictionaryContainer&) const = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data&) = 0; // Copy of the value
  virtual bool Insert(Data&&) = 0;      // Move of the value
  virtual bool Remove(const Data&) = 0;

  virtual bool InsertAll(const TraversableContainer<Data>&);   // Copy from TraversableContainer
  virtual bool InsertAll(MappableContainer<Data>&&);           // Move from MappableContainer

  virtual bool RemoveAll(const TraversableContainer<Data>&);

  virtual bool InsertSome(const TraversableContainer<Data>&);  // Copy
  virtual bool InsertSome(MappableContainer<Data>&&);          // Move

  virtual bool RemoveSome(const TraversableContainer<Data>&);

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : public virtual DictionaryContainer<Data> {
  // Must extend DictionaryContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~OrderedDictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  OrderedDictionaryContainer& operator=(const OrderedDictionaryContainer&) = delete;
  OrderedDictionaryContainer& operator=(OrderedDictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const OrderedDictionaryContainer&) const = delete;
  bool operator!=(const OrderedDictionaryContainer&) const = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& Min() const = 0;
  virtual Data MinNRemove() = 0;
  virtual void RemoveMin() = 0;

  virtual const Data& Max() const = 0;
  virtual Data MaxNRemove() = 0;
  virtual void RemoveMax() = 0;

  virtual const Data& Predecessor(const Data&) const = 0;
  virtual Data PredecessorNRemove(const Data&) = 0;
  virtual void RemovePredecessor(const Data&) = 0;

  virtual const Data& Successor(const Data&) const = 0;
  virtual Data SuccessorNRemove(const Data&) = 0;
  virtual void RemoveSuccessor(const Data&) = 0;

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
