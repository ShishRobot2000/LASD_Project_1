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
    
}
