namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data& dat) const noexcept {
  bool found = false;
  Traverse([&found, &dat](const Data& val) {
    if (val == dat) found = true;
  });
  return found;
}

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const {
  Accumulator result = acc;
  Traverse([&result, &fun](const Data& d) {
    result = fun(d, result);
  });
  return result;
}

/* ************************************************************************** */

template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
  Accumulator result = acc;
  PreOrderTraverse([&result, &fun](const Data& d) {
    result = fun(d, result);
  });
  return result;
}

/* ************************************************************************** */

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
  PostOrderTraverse(fun);
}

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
  Accumulator result = acc;
  PostOrderTraverse([&result, &fun](const Data& d) {
    result = fun(d, result);
  });
  return result;
}

/* ************************************************************************** */

}

    
