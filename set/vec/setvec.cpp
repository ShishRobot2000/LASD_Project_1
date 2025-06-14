namespace lasd {

/* ************************************************************************** */
/* Constructors */

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) {
  container.Traverse([this](const Data& dat) {
    Insert(dat);
  });
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& container) {
  container.Map([this](Data& dat) {
    Insert(std::move(dat));
  });
}

template <typename Data>
SetVec<Data>::SetVec(const SetVec& other) {
  for (unsigned long i = 0; i < other.size; ++i) {
    Insert(other[i]); 
  }
}

template <typename Data>
SetVec<Data>::SetVec(SetVec&& other) noexcept {
  std::swap(elements, other.elements);
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
  std::swap(capacity, other.capacity);
}

/* ************************************************************************** */
/* Destructor */

template <typename Data>
SetVec<Data>::~SetVec() {
  if (elements != nullptr) {
    delete[] elements;
    elements = nullptr;
  }
}

/* ************************************************************************** */
/* Assignment operators */

template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec& other) {
  if (this != &other) {
    SetVec tmp(other);
    std::swap(*this, tmp);
  }
  return *this;
}

template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) noexcept {
  std::swap(elements, other.elements);
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
  std::swap(capacity, other.capacity);
  return *this;
}

/* ************************************************************************** */
/* Comparison operators */

template <typename Data>
bool SetVec<Data>::operator==(const SetVec& other) const {
  if (size != other.size) return false;
  for (unsigned long i = 0; i < size; ++i) {
    if ((*this)[i] != other[i]) return false;
  }
  return true;
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec& other) const {
  return !(*this == other);
}

/* ************************************************************************** */
/* Access and modification */

template <typename Data>
unsigned long SetVec<Data>::CircularIndex(unsigned long index) const {
  return (head + index) % capacity;
}

template <typename Data>
const Data& SetVec<Data>::operator[](unsigned long index) const {
  if (index >= size) throw std::out_of_range("Index out of range");
  return elements[CircularIndex(index)];
}

/* ************************************************************************** */
/* Resize */

template <typename Data>
void SetVec<Data>::Resize(unsigned long newCap) {
  if (newCap < size)
    throw std::length_error("Resize too small");

  Data* newElems = new Data[newCap];

  for (unsigned long i = 0; i < size; ++i)
    newElems[i] = std::move((*this)[i]);

  if (elements != nullptr) {
    delete[] elements;
  }

  elements = newElems;
  capacity = newCap;
  head = 0;
  tail = size % capacity;
}

/* ************************************************************************** */
/* Insert & Remove helpers */

template <typename Data>
void SetVec<Data>::InsertAt(unsigned long index, const Data& dat) {
  if (size == capacity) {
    Resize(capacity == 0 ? 1 : capacity * 2);
  }
  for (unsigned long i = size; i > index; --i) {
    elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
  }
  elements[CircularIndex(index)] = dat;
  ++size;
  tail = (head + size) % capacity;
}

template <typename Data>
void SetVec<Data>::InsertAt(unsigned long index, Data&& dat) {
  if (size == capacity) {
    Resize(capacity == 0 ? 1 : capacity * 2);
  }
  for (unsigned long i = size; i > index; --i) {
    elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
  }
  elements[CircularIndex(index)] = std::move(dat);
  ++size;
  tail = (head + size) % capacity;
}

template <typename Data>
void SetVec<Data>::RemoveAt(unsigned long index) {
  for (unsigned long i = index; i < size - 1; ++i) {
    elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
  }
  --size;
  tail = (head + size) % capacity;
}

/* ************************************************************************** */
/* Clear */

template <typename Data>
void SetVec<Data>::Clear() {
  delete[] elements;
  elements = nullptr;
  size = 0;
  capacity = 0;
  head = 0;
  tail = 0;
}

/* ************************************************************************** */
/* Exists */

template <typename Data>
bool SetVec<Data>::Exists(const Data& dat) const noexcept {
  return BinarySearch(dat) != -1;
}


/* ************************************************************************** */
/* Insert / Remove */

template <typename Data>
bool SetVec<Data>::Insert(const Data& dat) {
  for (unsigned long i = 0; i < size; ++i) {
    if (dat == (*this)[i]) return false;
    if (dat < (*this)[i]) {
      InsertAt(i, dat);
      return true;
    }
  }
  InsertAt(size, dat);
  return true;
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& dat) {
  if (size == capacity) {
    Resize(capacity == 0 ? 1 : capacity * 2);
  }

  long left = 0;
  long right = size - 1;
  long insertPos = 0;
  bool exists = false;

  while (left <= right) {
    long mid = (left + right) / 2;
    const Data& midVal = elements[CircularIndex(mid)];

    if (midVal == dat) {
      exists = true;
      break;
    } else if (midVal < dat) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  if (exists) return false;

  insertPos = left;
  InsertAt(insertPos, std::move(dat)); 
  return true;
}


template <typename Data>
bool SetVec<Data>::Remove(const Data& dat) {
  long index = BinarySearch(dat);
  if (index == -1) return false;

  for (unsigned long i = index; i < size - 1; ++i) {
    elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
  }

  --size;
  tail = (head + size) % capacity;

  if (size < capacity / 4 && capacity > 1)
    Resize(capacity / 2);

  return true;
}

/* ************************************************************************** */
/* Min / Max */

template <typename Data>
const Data& SetVec<Data>::Min() const {
  if (Empty()) throw std::length_error("Empty set");
  return (*this)[0];
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
  if (Empty()) throw std::length_error("Empty set");
  Data tmp = (*this)[0];
  RemoveAt(0);
  return tmp;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
  if (Empty()) throw std::length_error("Empty set");
  RemoveAt(0);
}

template <typename Data>
const Data& SetVec<Data>::Max() const {
  if (Empty()) throw std::length_error("Empty set");
  return (*this)[size - 1];
}

template <typename Data>
Data SetVec<Data>::MaxNRemove() {
  if (Empty()) throw std::length_error("Empty set");
  Data tmp = (*this)[size - 1];
  RemoveAt(size - 1);
  return tmp;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (Empty()) throw std::length_error("Empty set");
  RemoveAt(size - 1);
}

/* ************************************************************************** */
/* Predecessor / Successor */

template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& dat) const {
  const Data* pred = nullptr;
  for (unsigned long i = 0; i < size; ++i) {
    if ((*this)[i] < dat) pred = &(*this)[i];
    else break;
  }
  if (!pred) throw std::length_error("No predecessor");
  return *pred;
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& dat) {
  for (unsigned long i = 0; i < size; ++i) {
    if ((*this)[i] < dat) {
      if (i + 1 == size || (*this)[i + 1] >= dat) {
        Data tmp = (*this)[i];
        RemoveAt(i);
        return tmp;
      }
    }
  }
  throw std::length_error("No predecessor");
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& dat) {
  (void)PredecessorNRemove(dat);
}

template <typename Data>
const Data& SetVec<Data>::Successor(const Data& dat) const {
  for (unsigned long i = 0; i < size; ++i) {
    if ((*this)[i] > dat) return (*this)[i];
  }
  throw std::length_error("No successor");
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& dat) {
  for (unsigned long i = 0; i < size; ++i) {
    if ((*this)[i] > dat) {
      Data tmp = (*this)[i];
      RemoveAt(i);
      return tmp;
    }
  }
  throw std::length_error("No successor");
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& dat) {
  (void)SuccessorNRemove(dat);
}

/* ************************************************************************** */
/* InsertAll / RemoveAll / InsertSome / RemoveSome */

template <typename Data>
bool SetVec<Data>::InsertAll(const TraversableContainer<Data>& container) {
  bool modified = false;
  container.Traverse([&](const Data& dat) { modified |= Insert(dat); });
  return modified;
}

template <typename Data>
bool SetVec<Data>::InsertAll(MappableContainer<Data>&& container) {
  bool modified = false;
  container.Map([&](Data& dat) { modified |= Insert(std::move(dat)); });
  return modified;
}

template <typename Data>
bool SetVec<Data>::RemoveAll(const TraversableContainer<Data>& container) {
  bool modified = false;
  container.Traverse([&](const Data& dat) { modified |= Remove(dat); });
  return modified;
}

template <typename Data>
bool SetVec<Data>::InsertSome(const TraversableContainer<Data>& container) {
  bool modified = false;
  container.Traverse([&](const Data& dat) {
    if (!modified && Insert(dat)) modified = true;
  });
  return modified;
}

template <typename Data>
bool SetVec<Data>::InsertSome(MappableContainer<Data>&& container) {
  bool modified = false;
  container.Map([&](Data& dat) {
    if (!modified && Insert(std::move(dat))) modified = true;
  });
  return modified;
}

template <typename Data>
bool SetVec<Data>::RemoveSome(const TraversableContainer<Data>& container) {
  bool modified = false;
  container.Traverse([&](const Data& dat) {
    if (!modified && Remove(dat)) modified = true;
  });
  return modified;
}

template <typename Data>
long SetVec<Data>::BinarySearch(const Data& dat) const {
  if (size == 0) return -1;

  long left = 0;
  long right = size - 1;

  while (left <= right) {
    long mid = (left + right) / 2;
    const Data& midVal = elements[CircularIndex(mid)];

    if (midVal == dat)
      return mid;
    else if (midVal < dat)
      left = mid + 1;
    else
      right = mid - 1;
  }

  return -1;
}

} // namespace lasd
