#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : public virtual TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer& operator=(const TraversableContainer&) = delete;
  TraversableContainer& operator=(TraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TraversableContainer&) const = delete;
  bool operator!=(const TraversableContainer&) const = delete;

  /* ************************************************************************ */

  // Specific member function

  using TraverseFun = std::function<void(const Data&)>;

  virtual void Traverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Accumulator&, const Data&)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator> fun, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data&) const noexcept override;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : public virtual TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderTraversableContainer& operator=(const PreOrderTraversableContainer&) = delete;
  PreOrderTraversableContainer& operator=(PreOrderTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderTraversableContainer&) const = delete;
  bool operator!=(const PreOrderTraversableContainer&) const = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PreOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : public virtual TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderTraversableContainer& operator=(const PostOrderTraversableContainer&) = delete;
  PostOrderTraversableContainer& operator=(PostOrderTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderTraversableContainer&) const = delete;
  bool operator!=(const PostOrderTraversableContainer&) const = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator> fun, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif

