
namespace lso {

    template <typename Data>
    Queue<Data>::Node::Node(const Queue<Data>::Node & copyNode) {
        element = copyNode.element;
    }

    template <typename Data>
    Queue<Data>::Node::Node(Queue<Data>::Node && moveNode) noexcept {
        std::swap(element, moveNode.element);
        std::swap(next, moveNode.next);
    }

    template <typename Data>
    bool Queue<Data>::Node::operator == (const Queue<Data>::Node & node) const noexcept {
        return (element == node.element) &&
            (
                (next == nullptr && node.next == nullptr) ||
                (
                    next != nullptr == node.next != nullptr && *(next) == *(node.next)
                )
            );
    }

    // --------------------------------------------------------------------------------

    template <typename Data>
    void Queue<Data>::InsertAtBack(const Data & data) {
        Node * newNode = new Node(data);

        if (head == nullptr)
            head = newNode;
        else
            tail -> next = newNode;

        tail = newNode;
    }
    
    template <typename Data>
    void Queue<Data>::Enqueue(const Data & data) {
        if (stopped)
            throw std::runtime_error("Queue has been stopped");
        
        std::lock_guard<std::mutex> lock(access);
        InsertAtBack(data);

        waiting.release();
    };

    template <typename Data>
    void Queue<Data>::RemoveFromFront() {
        Node * removeNode = head;

        if (head == tail)
            head = tail = nullptr;
        else
            head = head -> next;

        removeNode -> next = nullptr;
        delete removeNode;
    }

    template <typename Data>
    bool Queue<Data>::Dequeue(Data & data) {
        if (this -> Empty())
            waiting.acquire();

        if (this -> Empty () && stopped)
            return false;

        std::lock_guard<std::mutex> lock(access);

        data = std::move(head -> element);
        RemoveFromFront();

        return true;
    }

    template <typename Data>
    void Queue<Data>::Shutdown() {        
        stopped = true;

        while (! this -> Empty()) {
            std::this_thread::yield();
        }

        waiting.release();
    }

    template <typename Data>
    bool Queue<Data>::Empty() noexcept {
        std::lock_guard<std::mutex> lock(access);

        return head == nullptr;
    }

}
