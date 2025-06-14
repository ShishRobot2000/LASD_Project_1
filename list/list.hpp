#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : public virtual MutableLinearContainer<Data>,
            public virtual ClearableContainer{

private:

// ...

protected:
  
  struct Node {

    Data element;
    Node* next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data&); // Copy constructor
    Node(Data&&) noexcept; // Move constructor

    /* ********************************************************************** */

    // Destructor
    ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const;
    bool operator!=(const Node&) const;

  };

  Node* head = nullptr;
  Node* tail = nullptr;            
  using Container::size;

  // Auxiliary functions
  Node* CopyList(const Node*);
  void ClearList();
  void RemoveAt(unsigned long); // for SetLst use

public:

  // Bring base class methods into scope to avoid -Woverloaded-virtual warnings
  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data>&); // Copy from TraversableContainer
  List(MappableContainer<Data>&&);         // Move from MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;
  
  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&);  // Copy
  void InsertAtFront(Data&&);       // Move
  void RemoveFromFront();           // Throws std::length_error if empty
  Data FrontNRemove();              // Throws std::length_error if empty

  void InsertAtBack(const Data&);   // Copy
  void InsertAtBack(Data&&);        // Move
  void RemoveFromBack();            // Throws std::length_error if empty
  Data BackNRemove();               // Throws std::length_error if empty

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)
  using typename MappableContainer<Data>::MapFun;
  Data& operator[](unsigned long) override;             // Mutable
  Data& Front() override;
  Data& Back() override;
  void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
  const Data& operator[](unsigned long) const override; // Immutable
  const Data& Front() const override;
  const Data& Back() const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderMappableContainer)
  void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderMappableContainer)
  void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderTraversableContainer)
  void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderTraversableContainer)
  void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  void Clear() override;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif

