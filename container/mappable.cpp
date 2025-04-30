namespace lasd {

/* ************************************************************************** */

template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun fun) {
  PostOrderMap(fun);
}

/* ************************************************************************** */

}
