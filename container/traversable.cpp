#include <string> // se usi std::string da qualche parte

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

/* ************************************************************************** */

template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

/* ************************************************************************** */

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
  PostOrderTraverse(fun);
}

/* ************************************************************************** */

}
