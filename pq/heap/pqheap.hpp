#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : public virtual PQ<Data>,
               public HeapVec<Data> {

private:

  unsigned long capacity = 0; // capacità fisica allocata 

protected:

  using Container::size;              // dimensione logica (elementi effettivi)
  using Vector<Data>::operator[];     // accesso agli elementi

  using HeapVec<Data>::HeapifyDown;
  using HeapVec<Data>::HeapifyUp;

public:

  // Default constructor
  PQHeap() = default;

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data>&); // Costruisce da container
  PQHeap(MappableContainer<Data>&&);         // Costruisce da container rvalue

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap&);

  // Move constructor
  PQHeap(PQHeap&&) noexcept;

  // Destructor
  ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQHeap& operator=(const PQHeap&);

  // Move assignment
  PQHeap& operator=(PQHeap&&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  const Data& Tip() const override;       // Ritorna il top (errore se vuoto)
  void RemoveTip() override;              // Rimuove il top (errore se vuoto)
  Data TipNRemove() override;             // Estrae e rimuove top (errore se vuoto)

  void Insert(const Data&) override;      // Inserimento (copia)
  void Insert(Data&&) override;           // Inserimento (move)

  void Change(const unsigned long, const Data&) override; // Cambia (copia)
  void Change(const unsigned long, Data&&) override;      // Cambia (move)

  void Clear() override;                  // Pulisce tutta la struttura
  void Resize(const unsigned long);       // Nuovo Resize che aggiorna solo capacity, non size

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif


