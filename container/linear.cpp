namespace lasd {

/* ************************************************************************** */

template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

/* ************************************************************************** */

template <typename Data>
void MutableLinearContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// Funzione ausiliaria: merge di due sottosequenze
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

/* ************************************************************************** */

// Funzione ausiliaria: chiamata ricorsiva di merge sort
template <typename Data>
void SortableLinearContainer<Data>::MergeSort(unsigned long left, unsigned long right) {
  if (left < right) {
    unsigned long mid = left + (right - left) / 2;
    MergeSort(left, mid);
    MergeSort(mid + 1, right);
    Merge(left, mid, right);
  }
}

/* ************************************************************************** */

// Funzione pubblica: chiama merge sort sull'intera sequenza
template <typename Data>
void SortableLinearContainer<Data>::Sort() {
  if (this->Size() > 1)
    MergeSort(0, this->Size() - 1);
}

/* ************************************************************************** */

}