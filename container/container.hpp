#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <cstddef>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

protected:

  unsigned long size = 0;

  /* ************************************************************************ */

  // Default constructor
  Container() = default;

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Container& operator=(Container&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&) const = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Container&) const = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual bool Empty() const noexcept { return (size == 0); }
  virtual unsigned long Size() const noexcept { return size; }

};

/* ************************************************************************** */

class ClearableContainer : public virtual Container {

public:

  // Destructor
  virtual ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete;

  // Move assignment
  ClearableContainer& operator=(ClearableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer&) const = delete;
  bool operator!=(const ClearableContainer&) const = delete;

  /* ************************************************************************ */

  // Specific member function
  virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer : public virtual ClearableContainer {

public:

  // Destructor
  virtual ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer& operator=(const ResizableContainer&) = delete;

  // Move assignment
  ResizableContainer& operator=(ResizableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer&) const = delete;
  bool operator!=(const ResizableContainer&) const = delete;

  /* ************************************************************************ */

  // Specific member function
  virtual void Resize(unsigned long) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  virtual void Clear() override { Resize(0); }

};

/* ************************************************************************** */

}

#endif


