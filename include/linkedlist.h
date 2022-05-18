#pragma once

#include <iostream>
#include <exception>
#include <initializer_list>
#include <stdexcept>

/// Односвязный список.
template <class T>
class LinkedList
{
public:
    /// Узел списка.
    class Node
    {
    public:
        Node(const T& value, Node* next = nullptr);

        Node(const Node&);

        ~Node();

        /// Возвращает значение, которое содержит узел.
        T value() const;

        /// Задаёт значение узла.
        void setValue(const T& value);

        /// Возращает следующий узел.
        Node* next() const;

        /// Задаёт следующий узел
        void setNext(Node* node);

        Node& operator=(const Node&);

        bool operator==(const Node&) const;

    private:
        T m_value;
        Node* m_next = nullptr;
    };

    LinkedList() = default;

    LinkedList(std::initializer_list<T> values);

    LinkedList(const LinkedList&);

    ~LinkedList();

    /// Добавляет значение `value` в начало списка.
    void addFirst(const T& value);

    /// Добавляет значение `value` в конец списка.
    void addLast(const T& value);

    /// Добавляет значение `value` перед узлом `nextNode`. 
    void addBefore(const Node* nextNode, const T& value);

    /// Добавляет значение `value` после узла `previousNode`.
    void addAfter(const Node* previousNode, const T& value);

    /// Удаляет первый элемент списка.
    void removeFirst();

    /// Удаляет последний элемент списка.
    void removeLast();

    /// Удаляет первый найденый узел со значением `value` из списка.
    void remove(const T& value);

    /// Удаляет узел `node` из списка.
    void remove(const Node* node);

    /// Возвращает первый узел, который содержит значение `value`.
    const Node* find(const T& value) const;

    /// Возвращает последний узел, который содержит значение `value`.
    const Node* findLast(const T& value) const;

    /// Проверяет наличие узла со значением `value` в списке.
    bool contains(const T& value) const;

    /// Очищает список.
    void clear();

    /// Возвращает первый элемент списка.
    const Node* first() const;

    /// Возвращает последний элемент списка.
    const Node* last() const;

    /// Возвращает длину списка.
    int length() const;

    /// Проверяет является ли список пустым.
    bool isEmpty() const;

    LinkedList<T>& operator=(const LinkedList<T>&);

private:
    Node* m_first = nullptr;
    Node* m_last = nullptr;
    int m_length = 0;
};

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& obj)
{
    const Node* node = obj.first();
    while (node != nullptr) {
        addLast(node->value());
        node = node->next();
    }
}

template <class T>
LinkedList<T>::LinkedList(std::initializer_list<T> values)
{
    for (const T& value : values)
        addLast(value);
}

template <class T>
inline LinkedList<T>::~LinkedList()
{
    if (!isEmpty())
        delete m_first;
}

template <class T>
void LinkedList<T>::addFirst(const T& value)
{
    Node* node = nullptr;
    if (isEmpty()) {
        node = new Node(value);
        m_first = m_last = node;
    }
    else {
        node = new Node(value, m_first);
        m_first = node;
    }

    m_length++;
}

template <class T>
void LinkedList<T>::addLast(const T& value)
{
    Node* node = new Node(value);
    if (isEmpty())
        m_first = m_last = node;
    else {
        m_last->setNext(node);
        m_last = node;
    }

    m_length++;
}

template <class T>
void LinkedList<T>::addBefore(const Node* nextNode, const T& value)
{
    if (isEmpty())
        throw std::logic_error("List is empty.");

    if (nextNode == m_first)
        addFirst(value);
    else {
        Node* previousNode = m_first;
        while (previousNode != nullptr && previousNode->next() != nextNode)
            previousNode = previousNode->next();

        if (previousNode == nullptr)
            throw std::logic_error("List does not contains `nextNode`.");

        Node* node = new Node(value, const_cast<Node*>(nextNode));
        previousNode->setNext(node);

        m_length++;
    }
}

template <class T>
void LinkedList<T>::addAfter(const Node* previousNode, const T& value)
{
    if (isEmpty())
        throw std::logic_error("List is empty.");

    if (previousNode == m_last)
        addLast(value);
    else {
        Node* nextNode = m_first;
        while (nextNode != previousNode->next() && nextNode != nullptr)
            nextNode = nextNode->next();

        if (nextNode == nullptr)
            throw std::logic_error("List does not contains `previousNode`.");

        Node* node = new Node(value, nextNode);
        const_cast<Node*>(previousNode)->setNext(node);

        m_length++;
    }
}

template <class T>
void LinkedList<T>::removeFirst()
{
    if (isEmpty())
        throw std::logic_error("List is empty.");

    if (length() == 1) {
        clear();
    } else {
        Node* first = m_first;
        m_first = first->next();
        first->setNext(nullptr);

        delete first;

        m_length--;
    }
}

template <class T>
void LinkedList<T>::removeLast()
{
    if (isEmpty())
        throw std::logic_error("List is empty.");

    if (length() == 1) {
        clear();
    } else {
        Node* last = m_last;
        m_last = m_first;
        while (m_last->next() != last)
            m_last = m_last->next();

        m_last->setNext(nullptr);

        delete last;

        m_length--;
    }
}

template <class T>
void LinkedList<T>::remove(const T& value)
{
    if (isEmpty())
        throw std::logic_error("List is empty.");

    if (value == m_first->value())
        removeFirst();
    else {
        if (length() == 1)
            clear();
        else {
            Node* previousNode = m_first;
            while (previousNode->next() != nullptr && previousNode->next()->value() != value)
                previousNode = previousNode->next();

            if (previousNode == m_last)
                throw std::logic_error("List does not contains `value`.");

            Node* node = previousNode->next();
            Node* nextNode = node->next();

            previousNode->setNext(nextNode);
            node->setNext(nullptr);

            delete node;

            m_length--;
        }
    }
}

template <class T>
void LinkedList<T>::remove(const Node* node)
{
    if (isEmpty())
        throw std::logic_error("List is empty.");

    if (node == m_first)
        removeFirst();
    else if (node == m_last)
        removeLast();
    else {
        if (length() == 1) {
            clear();
        } else {
            Node* previousNode = m_first;
            while (previousNode->next() != nullptr && previousNode->next() != node)
                previousNode = previousNode->next();

            if (previousNode == m_last)
                throw std::logic_error("List does not contains `node`.");

            Node* nextNode = node->next();

            previousNode->setNext(nextNode);
            const_cast<Node*>(node)->setNext(nullptr);

            delete node;

            m_length--;
        }
    }
}

template <class T>
const typename LinkedList<T>::Node* LinkedList<T>::find(const T& value) const
{
    if (isEmpty())
        return nullptr;

    Node* result = m_first;
    while (result != nullptr && result->value() != value)
        result = result->next();

    return result;
}

template <class T>
const typename LinkedList<T>::Node* LinkedList<T>::findLast(const T& value) const
{
    if (isEmpty())
        return nullptr;

    Node* result = nullptr;
    Node* node = m_first;
    while (node != nullptr) {
        if (node->value() == value)
            result = node;

        node = node->next();
    }

    return result;
}

template <class T>
bool LinkedList<T>::contains(const T& value) const
{
    if (isEmpty())
        return false;

    Node* node = m_first;
    while (node != nullptr && node->value() != value)
        node = node->next();

    return node != nullptr;
}

template <class T>
void LinkedList<T>::clear()
{
    if (m_first != nullptr) {
        delete m_first;
        m_first = m_last = nullptr;
        m_length = 0;
    }
}

template <class T>
inline const typename LinkedList<T>::Node* LinkedList<T>::first() const
{
    return m_first;
}

template <class T>
inline const typename LinkedList<T>::Node* LinkedList<T>::last() const
{
    return m_last;
}

template <class T>
inline int LinkedList<T>::length() const
{
    return m_length;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return m_length == 0;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& obj)
{
    if (this != &obj) {
        clear();

        const Node* node = obj.first();
        while (node != nullptr) {
            addLast(node->value());
            node = node->next();
        }
    }
    
    return *this;
}

// ---- Node methods ----

template <class T>
LinkedList<T>::Node::Node(const T& value, Node* next) : m_value(value), m_next(next) { }

template <class T>
LinkedList<T>::Node::Node(const Node& obj) : m_value(obj.m_value) { }

template <class T>
LinkedList<T>::Node::~Node()
{
    if (m_next != nullptr)
        delete m_next;
}

template <class T>
inline T LinkedList<T>::Node::value() const 
{
    return m_value;
}

template <class T>
inline void LinkedList<T>::Node::setValue(const T& value)
{
    m_value = value;
}

template <class T>
inline typename LinkedList<T>::Node* LinkedList<T>::Node::next() const
{
    return m_next;
}

template <class T>
inline void LinkedList<T>::Node::setNext(Node* node)
{
    m_next = node;
}

template <class T>
inline typename LinkedList<T>::Node& LinkedList<T>::Node::operator=(const Node& obj)
{
    if (this != &obj)
        m_value = obj.m_value;
    return *this;
}

template <class T>
inline bool LinkedList<T>::Node::operator==(const Node& obj) const
{
    return m_value == obj.m_value && m_next == obj.m_next; 
}

