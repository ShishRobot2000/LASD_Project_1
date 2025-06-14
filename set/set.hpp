#ifndef SET_HPP
#define SET_HPP

/* ************************************************************************** */

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"
#include "../container/linear.hpp"


/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Set : public virtual OrderedDictionaryContainer<Data>,
            public virtual LinearContainer<Data>,
            public virtual ClearableContainer {

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~Set() = default;

  /* ************************************************************************ */

  // Copy assignment
  Set& operator=(const Set&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Set& operator=(Set&&) noexcept = delete; // Move assignment of abstract types is not possible.

};

/* ************************************************************************** */

}

#endif
