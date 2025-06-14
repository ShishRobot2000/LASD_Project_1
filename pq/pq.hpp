#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"
#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQ : public virtual LinearContainer<Data>,
           public virtual ClearableContainer {

private:

protected:

public:

  // Destructor
  virtual ~PQ() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQ<Data>& operator=(const PQ<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PQ<Data>& operator=(PQ<Data>&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& Tip() const = 0;         // Must throw std::length_error when empty
  virtual void RemoveTip() = 0;                // Must throw std::length_error when empty
  virtual Data TipNRemove() = 0;               // Must throw std::length_error when empty

  virtual void Insert(const Data&) = 0;        // Copy of the value
  virtual void Insert(Data&&) = 0;             // Move of the value

  virtual void Change(const unsigned long, const Data&) = 0; // Copy of the value
  virtual void Change(const unsigned long, Data&&) = 0;       // Move of the value

};

/* ************************************************************************** */

}

#endif

