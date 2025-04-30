namespace lasd {

    /* ************************************************************************** */
    
    template <typename Data>
    bool TraversableContainer<Data>::Exists(const Data& dat) const noexcept {
      bool found = false;
      Traverse([&found, &dat](const Data& value) {
        if (value == dat) {
          found = true;
        }
      });
      return found;
    }
    
    /* ************************************************************************** */
    
}
