#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <atomic>

namespace lso {

    template <typename Data>
    class Queue {

        private:

            struct Node {

                private:

                    // ...

                protected:

                    // ...

                public:

                    Data element;
                    Node * next = nullptr;

                    Node() = default;
                    Node(const Data & data) : element(data) {};
                    Node(Data && data) noexcept { std::swap(element, data); };

                    Node(const Node &);
                
                    Node(Node &&) noexcept;

                    virtual ~Node() { delete next; };

                    bool operator == (const Node &) const noexcept;
                    inline bool operator != (const Node & node) const noexcept { return !( *(this) == node ); } 

            };

            Node * head = nullptr;
            Node * tail = nullptr;

            std::atomic<bool> stopped;

            std::mutex access;
            std::condition_variable waiting;

        private:

            void InsertAtBack(const Data & data);
            void RemoveFromFront();

            inline bool Empty() const noexcept { return head == nullptr; };

        protected:

            // ...

        public:

            Queue() : stopped(false) {};

            Queue(const Queue &) = delete;
            Queue(Queue &&) noexcept = delete;

            virtual ~Queue() { delete head; }

            Queue &operator = (const Queue &) = delete;
            Queue &operator = (Queue &&) noexcept = delete;

            inline bool operator == (const Queue &) const noexcept = delete;
            inline bool operator != (const Queue & queue) const noexcept = delete;

        public:

            void Enqueue(const Data &);
            bool Dequeue(Data &);
            
            void Shutdown();

    };
}

#include "Queue.cpp"

#endif
