#include <cstddef>

template<typename T>
class List_node {
public:
	List_node(T item, List_node<T> *aPrev);
	List_node(T item, List_node<T> *aPrev, List_node<T> *aNext);
	List_node(const List_node<T>* aNode);
	~List_node();

	int at(size_t idx, T& item) const;
	int push_back(T item);
	int insert(T item, size_t idx);
	int pop(T &item, size_t idx);
	int retrieve(T &item, size_t idx);
	int remove(size_t idx);
	int pop_back(T &item);
	int replace(const T &item, size_t idx);
	void traverse(void (*visit)(T&));
	void clear();
	bool empty();
	bool full();

	size_t size() const;

	void operator=(const List_node<T> *node);

private:
	size_t size(size_t count) const;

protected:
	T data;
	List_node<T>* next;
	List_node<T>* prev;
};

template <typename T>
List_node<T>::List_node(T item, List_node<T> *aPrev)
{
	this->next = nullptr;
	this->prev = aPrev;
	this->data = item;
}

template <typename T>
List_node<T>::List_node(T item, List_node<T> *aPrev, List_node<T> *aNext)
{
	this->next = aNext;
	this->prev = aPrev;
	this->data = item;
}

template<typename T>
List_node<T>::List_node(const List_node<T>* aNode)
{
	this.data = aNode->data;
	this.prev = aNode->prev;
	if (aNode->next != nullptr) {
        this.next = new List_node<T>(*aNode->next);
    } else {
        this.next = nullptr;
    }
}

template <typename T>
List_node<T>::~List_node()
{
	delete next;
	delete prev;
}

template <typename T>
int List_node<T>::at(size_t idx, T& item) const
{
	if (idx >= this.size()) { return -1; }
	if (idx == 0) {
		item = this.data;
		return 0;
	}
	return this.next->at(idx - 1, item);
}

template <typename T>
int List_node<T>::push_back(T item)
{
	if (this.next == nullptr) {
		this.next = new List_node<T>(item, this);
		return 0;
	}
	return this.next->push_back(item);
}

template <typename T>
int List_node<T>::insert(T item, size_t idx)
{
	if (idx >= this->size()) { return -1; }
	if (idx == 0) {
		List_node<T> *cpy = new List_node<T>(this->data, this->prev, this->next);
		this->next = cpy;
		cpy->prev = this;
		return 0;
	}
	return this->next->insert(item, idx - 1);
}

template <typename T>
int List_node<T>::pop(T& item, size_t idx)
{
    if (idx > 0 && this->next == nullptr) { return -1; }
    if (idx == 0) {
        item = this->data;
		this->next->prev = this->prev;
		this->prev->next = this->next;
		this->next = nullptr;
		this->prev = nullptr;
		delete this;
        return 0;
    }
    return this->next->pop(item, idx - 1);
}

template <typename T>
int List_node<T>::retrieve(T& item, size_t idx)
{
	return this->pop(item, idx);
}

template <typename T>
int List_node<T>::remove(size_t idx)
{
	T item;
	return this->pop(item, idx);
}

template <typename T>
int List_node<T>::pop_back(T& item)
{
	if (next == nullptr) { 
		item = data;
		delete this;
		this = nullptr;
		return 0;
	}
	if (next->next == nullptr) {
		item = next->data;
		delete next;
		next = nullptr;
		return 0;
	}
	return next->pop_back(item);
}

template <typename T>
int List_node<T>::replace(const T &item, size_t idx)
{
	if (idx == 0) {
		this->data = item;
		return 0;
	}
	if (this->next == nullptr) {
		return -1;
	}
	this->next->replace(item, idx - 1);
}

template<typename T>
void List_node<T>::traverse(void (*visit)(T&)) {
    List_node<T>* current = this;
	while (current != nullptr) {
        visit(current->data);
        current = current->next;
    }
}

template <typename T>
void List_node<T>::clear()
{
	while (this != nullptr) {
		List_node<T>* temp = this->next;
		delete this;
		this = temp;
	}
}

template <typename T>
bool List_node<T>::empty()
{
	return (this == nullptr);
}

template <typename T>
bool List_node<T>::full()
{
	return false;
}

template <typename T>
size_t List_node<T>::size() const
{
	if (this->next == nullptr) {
		return 1;
	}
	return this->next->size(2);
}

template <typename T>
size_t List_node<T>::size(size_t count) const
{
	if (this->next == nullptr) {
		return count;
	}
	return this->next->size(count + 1);
}

template <typename T>
void List_node<T>::operator=(const List_node<T> *node) 
{
	this.data = node->data;
	this.next = node->next;
	this.prev = node->prev;
}
