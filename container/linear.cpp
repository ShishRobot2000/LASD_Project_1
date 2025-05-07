namespace lasd {

/* ************************** */

// LinearContainer

template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer& other) const noexcept {
  if (this->Size() != other.Size())
    return false;
  for (unsigned long i = 0; i < this->Size(); ++i) {
    if ((*this)[i] != other[i])
      return false;
  }
  return true;
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer& other) const noexcept {
  return !(*this == other);
}

template <typename Data>
const Data& LinearContainer<Data>::Front() const {
  if (this->Size() == 0)
    throw std::length_error("Access to front of an empty container");
  return (*this)[0];
}

template <typename Data>
const Data& LinearContainer<Data>::Back() const {
  if (this->Size() == 0)
    throw std::length_error("Access to back of an empty container");
  return (*this)[this->Size() - 1];
}

template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
  for (unsigned long i = 0; i < this->Size(); ++i)
    fun((*this)[i]);
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
  for (unsigned long i = this->Size(); i > 0; --i)
    fun((*this)[i - 1]);
}

/* ************************** */

// MutableLinearContainer

template <typename Data>
void MutableLinearContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

template <typename Data>
Data& MutableLinearContainer<Data>::Front() {
  if (this->Size() == 0)
    throw std::length_error("Access to front of an empty container");
  return (*this)[0];
}

template <typename Data>
Data& MutableLinearContainer<Data>::Back() {
  if (this->Size() == 0)
    throw std::length_error("Access to back of an empty container");
  return (*this)[this->Size() - 1];
}

template <typename Data>
void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
  for (unsigned long i = 0; i < this->Size(); ++i)
    fun((*this)[i]);
}

template <typename Data>
void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
  for (unsigned long i = this->Size(); i > 0; --i)
    fun((*this)[i - 1]);
}

/* ************************** */

// SortableLinearContainer

template <typename Data>
void SortableLinearContainer<Data>::Merge(unsigned long left, unsigned long mid, unsigned long right) {
  unsigned long n1 = mid - left + 1;
  unsigned long n2 = right - mid;

  std::vector<Data> leftVec(n1);
  std::vector<Data> rightVec(n2);

  for (unsigned long i = 0; i < n1; ++i)
    leftVec[i] = (*this)[left + i];
  for (unsigned long j = 0; j < n2; ++j)
    rightVec[j] = (*this)[mid + 1 + j];

  unsigned long i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (leftVec[i] <= rightVec[j]) {
      (*this)[k++] = std::move(leftVec[i++]);
    } else {
      (*this)[k++] = std::move(rightVec[j++]);
    }
  }

  while (i < n1) {
    (*this)[k++] = std::move(leftVec[i++]);
  }
  while (j < n2) {
    (*this)[k++] = std::move(rightVec[j++]);
  }
}

template <typename Data>
void SortableLinearContainer<Data>::MergeSort(unsigned long left, unsigned long right) {
  if (left < right) {
    unsigned long mid = left + (right - left) / 2;
    MergeSort(left, mid);
    MergeSort(mid + 1, right);
    Merge(left, mid, right);
  }
}

template <typename Data>
void SortableLinearContainer<Data>::Sort() {
  if (this->Size() > 1)
    MergeSort(0, this->Size() - 1);
}

/* ************************** */

} // namespace lasd
