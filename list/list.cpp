namespace lasd {

    /* ************************************************************************** */
    /* Node */
    
    // Copy constructor
    template <typename Data>
    List<Data>::Node::Node(const Data& dat) : element(dat) {}
    
    // Move constructor
    template <typename Data>
    List<Data>::Node::Node(Data&& dat) noexcept : element(std::move(dat)) {}
    
    // Comparison operators
    template <typename Data>
    bool List<Data>::Node::operator==(const Node& other) const {
      return element == other.element;
    }
    
    template <typename Data>
    bool List<Data>::Node::operator!=(const Node& other) const {
      return !(*this == other);
    }
    
    /* ************************************************************************** */
    /* Utility functions */
    
    template <typename Data>
    typename List<Data>::Node* List<Data>::CopyList(const Node* src) {
      if (src == nullptr) return nullptr;
      Node* newHead = new Node(src->element);
      Node* newTail = newHead;
      src = src->next;
      while (src != nullptr) {
        newTail->next = new Node(src->element);
        newTail = newTail->next;
        src = src->next;
      }
      return newHead;
    }
    
    template <typename Data>
    void List<Data>::ClearList() {
      while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
      }
      tail = nullptr;
      size = 0;
    }

    template <typename Data>
    void List<Data>::RemoveAt(unsigned long index) {
      if (index >= size)
        throw std::out_of_range("Index out of range");

      if (index == 0) {
        RemoveFromFront();
      } else {
        Node* prev = head;
        for (unsigned long i = 1; i < index; ++i) {
          prev = prev->next;
        }
        Node* target = prev->next;
        prev->next = target->next;
        if (target == tail) {
          tail = prev;
        }
        delete target;
        --size;
      }
    }

    
    /* ************************************************************************** */
    /* Constructors and Destructor */
    
    template <typename Data>
    List<Data>::List(const TraversableContainer<Data>& container) {
      container.Traverse([this](const Data& dat) { InsertAtBack(dat); });
    }
    
    template <typename Data>
    List<Data>::List(MappableContainer<Data>&& container) {
      container.Map([this](Data& dat) { InsertAtBack(std::move(dat)); });
    }
    
    template <typename Data>
    List<Data>::List(const List& other) {
      head = CopyList(other.head);
      size = other.size;
      if (head == nullptr)
        tail = nullptr;
      else {
        tail = head;
        while (tail->next != nullptr) {
          tail = tail->next;
        }
      }
    }
    
    template <typename Data>
    List<Data>::List(List&& other) noexcept {
      std::swap(head, other.head);
      std::swap(tail, other.tail);
      std::swap(size, other.size);
    }
    
    template <typename Data>
    List<Data>::~List() {
      Clear();
    }
    
    /* ************************************************************************** */
    /* Assignment operators */
    
    template <typename Data>
    List<Data>& List<Data>::operator=(const List& other) {
      if (this != &other) {
        Clear();
        head = CopyList(other.head);
        size = other.size;
        if (head == nullptr)
          tail = nullptr;
        else {
          tail = head;
          while (tail->next != nullptr) {
            tail = tail->next;
          }
        }
      }
      return *this;
    }
    
    template <typename Data>
    List<Data>& List<Data>::operator=(List&& other) noexcept {
      if (this != &other) {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
      }
      return *this;
    }
    
    /* ************************************************************************** */
    /* Comparison operators */
    
    template <typename Data>
    bool List<Data>::operator==(const List& other) const noexcept  {
      if (size != other.size) return false;
      Node* thisNode = head;
      Node* otherNode = other.head;
      while (thisNode != nullptr) {
        if (thisNode->element != otherNode->element) return false;
        thisNode = thisNode->next;
        otherNode = otherNode->next;
      }
      return true;
    }
    
    template <typename Data>
    bool List<Data>::operator!=(const List& other) const noexcept {
      return !(*this == other);
    }
    
    /* ************************************************************************** */
    /* Clear */
    
    template <typename Data>
    void List<Data>::Clear() {
      ClearList();
    }
    
    /* ************************************************************************** */
    /* Insert / Remove Front */
    
    template <typename Data>
    void List<Data>::InsertAtFront(const Data& dat) {
      Node* newNode = new Node(dat);
      newNode->next = head;
      head = newNode;
      if (tail == nullptr) tail = newNode;
      ++size;
    }
    
    template <typename Data>
    void List<Data>::InsertAtFront(Data&& dat) {
      Node* newNode = new Node(std::move(dat));
      newNode->next = head;
      head = newNode;
      if (tail == nullptr) tail = newNode;
      ++size;
    }
    
    template <typename Data>
    void List<Data>::RemoveFromFront() {
      if (size == 0) throw std::length_error("List is empty");
      Node* tmp = head;
      head = head->next;
      delete tmp;
      --size;
      if (size == 0) tail = nullptr;
    }
    
    template <typename Data>
    Data List<Data>::FrontNRemove() {
      if (size == 0) throw std::length_error("List is empty");
      Data ret = std::move(Front());
      RemoveFromFront();
      return ret;
    }
    
    /* ************************************************************************** */
    /* Insert / Remove Back */
    
    template <typename Data>
    void List<Data>::InsertAtBack(const Data& dat) {
      Node* newNode = new Node(dat);
      if (tail == nullptr) {
        head = tail = newNode;
      } else {
        tail->next = newNode;
        tail = newNode;
      }
      ++size;
    }
    
    template <typename Data>
    void List<Data>::InsertAtBack(Data&& dat) {
      Node* newNode = new Node(std::move(dat));
      if (tail == nullptr) {
        head = tail = newNode;
      } else {
        tail->next = newNode;
        tail = newNode;
      }
      ++size;
    }
    
    template <typename Data>
    void List<Data>::RemoveFromBack() {
      if (size == 0) throw std::length_error("List is empty");
      if (size == 1) {
        delete head;
        head = tail = nullptr;
      } else {
        Node* prev = head;
        while (prev->next != tail) {
          prev = prev->next;
        }
        delete tail;
        tail = prev;
        tail->next = nullptr;
      }
      --size;
    }
    
    template <typename Data>
    Data List<Data>::BackNRemove() {
      if (size == 0) throw std::length_error("List is empty");
      Data ret = std::move(Back());
      RemoveFromBack();
      return ret;
    }
    
    /* ************************************************************************** */
    /* Accessors */
    
    template <typename Data>
    Data& List<Data>::operator[](unsigned long index) {
      if (index >= size) throw std::out_of_range("Index out of range");
      Node* current = head;
      for (unsigned long i = 0; i < index; ++i) {
        current = current->next;
      }
      return current->element;
    }
    
    template <typename Data>
    const Data& List<Data>::operator[](unsigned long index) const {
      if (index >= size) throw std::out_of_range("Index out of range");
      Node* current = head;
      for (unsigned long i = 0; i < index; ++i) {
        current = current->next;
      }
      return current->element;
    }
    
    template <typename Data>
    Data& List<Data>::Front() {
      if (size == 0) throw std::length_error("List is empty");
      return head->element;
    }
    
    template <typename Data>
    const Data& List<Data>::Front() const {
      if (size == 0) throw std::length_error("List is empty");
      return head->element;
    }
    
    template <typename Data>
    Data& List<Data>::Back() {
      if (size == 0) throw std::length_error("List is empty");
      return tail->element;
    }
    
    template <typename Data>
    const Data& List<Data>::Back() const {
      if (size == 0) throw std::length_error("List is empty");
      return tail->element;
    }
    
    /* ************************************************************************** */
    /* Traverse & Map */
    
    template <typename Data>
    void List<Data>::Traverse(TraverseFun fun) const {
      PreOrderTraverse(fun);
    }
    
    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const {
      Node* current = head;
      while (current != nullptr) {
        fun(current->element);
        current = current->next;
      }
    }
    
    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const {
      if (head != nullptr) {
        std::function<void(Node*)> postTraverse = [&](Node* node) {
          if (node->next != nullptr) postTraverse(node->next);
          fun(node->element);
        };
        postTraverse(head);
      }
    }
    
    /* ************************************************************************** */
    
    template <typename Data>
    void List<Data>::Map(MapFun fun) {
      PreOrderMap(fun);
    }
    
    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun) {
      Node* current = head;
      while (current != nullptr) {
        fun(current->element);
        current = current->next;
      }
    }
    
    template <typename Data>
    void List<Data>::PostOrderMap(MapFun fun) {
      if (head != nullptr) {
        std::function<void(Node*)> postMap = [&](Node* node) {
          if (node->next != nullptr) postMap(node->next);
          fun(node->element);
        };
        postMap(head);
      }
    }
    
    /* ************************************************************************** */
    
    }
    
