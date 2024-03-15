#include <cstddef>

template<typename T>
class List_node {
public:
	List_node(T item);
	List_node(T item, List_node<T> *aNext);
	~List_node();

	int at(size_t idx, T& item) const;
	int push_back(T item);
	int insert(T item, size_t idx);
	int pop(size_t idx, T& item);

	size_t size() const;

private:
	size_t size(size_t count) const;

protected:
	T data;
	List_node<T>* next;
};

template <typename T>
List_node<T>::List_node(T item)
{
	this->next = nullptr;
	this->data = item;
}

template <typename T>
List_node<T>::List_node(T item, List_node<T> *aNext)
{
	this->next = aNext;
	this->data = item;
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
		this.next = new List_node<T>(item);
		return 0;
	}
	return this.next->push_back(item);
}

template <typename T>
int List_node<T>::insert(T item, size_t idx)
{
	if (idx >= this->size()) { return -1; }
	if (idx == 0) {
		List_node<T> *old_head = new List_node<T>(this->data, this->next);
		this->data = item;
		this->next = old_head;
		return 0;
	}
	if (idx == 1) {
		this->next = new List_node<T>(item, this->next);
		return 0;
	}
	return this.next->insert(item, idx - 1);
}

template <typename T>
int List_node<T>::pop(size_t idx, T& item)
{
    if (idx >= this->size()) { return -1; }
    if (idx == 0) {
        item = this->data;
        List_node<T> *temp = this->next;
        delete this;
        this = temp;
        return 0;
    }
    return this->next->pop(idx - 1, item);
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
