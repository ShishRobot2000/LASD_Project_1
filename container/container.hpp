#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <cstddef>

namespace lasd {

/* ************************************************************************** */

class Container {

protected:

  unsigned long size = 0;

public:

  Container() = default;
  virtual ~Container() = default;

  Container(const Container&) = delete;
  Container& operator=(const Container&) = delete;
  Container(Container&&) noexcept = delete;
  Container& operator=(Container&&) noexcept = delete;

  virtual bool Empty() const noexcept { return (size == 0); }
  virtual unsigned long Size() const noexcept { return size; }

};

/* ************************************************************************** */

class ClearableContainer : public virtual Container {

public:

  virtual ~ClearableContainer() = default;

  ClearableContainer(const ClearableContainer&) = delete;
  ClearableContainer& operator=(const ClearableContainer&) = delete;
  ClearableContainer(ClearableContainer&&) noexcept = delete;
  ClearableContainer& operator=(ClearableContainer&&) noexcept = delete;

  virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer : public virtual ClearableContainer {

public:

  virtual ~ResizableContainer() = default;

  ResizableContainer(const ResizableContainer&) = delete;
  ResizableContainer& operator=(const ResizableContainer&) = delete;
  ResizableContainer(ResizableContainer&&) noexcept = delete;
  ResizableContainer& operator=(ResizableContainer&&) noexcept = delete;

  virtual void Resize(unsigned long) = 0;

  virtual void Clear() override { Resize(0); }

};

}

#endif


