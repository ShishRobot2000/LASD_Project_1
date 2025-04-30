namespace lasd {

    /* ************************************************************************** */
    
    template <typename Data>
    bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& tc) {
      bool allInserted = true;
      tc.Traverse([&](const Data& d) {
        allInserted &= Insert(d); // Copy insert
      });
      return allInserted;
    }
    
    /* ************************************************************************** */
    
    template <typename Data>
    bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& mc) {
      bool allInserted = true;
      mc.Map([&](Data& d) {
        allInserted &= Insert(std::move(d)); // Move insert
      });
      return allInserted;
    }
    
    /* ************************************************************************** */
    
    template <typename Data>
    bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& tc) {
      bool allRemoved = true;
      tc.Traverse([&](const Data& d) {
        allRemoved &= Remove(d);
      });
      return allRemoved;
    }
    
    /* ************************************************************************** */
    
    template <typename Data>
    bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& tc) {
      bool anyInserted = false;
      tc.Traverse([&](const Data& d) {
        anyInserted |= Insert(d);
      });
      return anyInserted;
    }
    
    /* ************************************************************************** */
    
    template <typename Data>
    bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& mc) {
      bool anyInserted = false;
      mc.Map([&](Data& d) {
        anyInserted |= Insert(std::move(d));
      });
      return anyInserted;
    }
    
    /* ************************************************************************** */
    
    template <typename Data>
    bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& tc) {
      bool anyRemoved = false;
      tc.Traverse([&](const Data& d) {
        anyRemoved |= Remove(d);
      });
      return anyRemoved;
    }
    
    /* ************************************************************************** */
    
}
