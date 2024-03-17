
template <typename T>
class Ssl{
public:
	Ssl(T &item);
	Ssl(T &item, Ssl<T> *aNext);

	~Ssl();

private:
	T data;
	Ssl<T>* next;
};

template <typename T>
Ssl<T>::Ssl(T &item) {
	data = item;
	next = nullptr;
}

template <typename T>
Ssl<T>::Ssl(T &item, Ssl<T> *aNext) {
	data = item;
	next = aNext;
}

template <typename T>
Ssl<T>::~Ssl() {
	delete this;
	this = nullptr;
}


template <typename T>
class Dsl{
public:
	Dsl(T &item);
	Dsl(T &item, Dsl<T> *aNext);
	Dsl(T &item, Dsl<T> *aNext, Dsl<T> *aPrev);

	~Dsl();

private:
	T data;
	Dsl<T>* next;
	Dsl<T>* prev;
};

template <typename T>
Dsl::Dsl(T &item) {
	data = item;
	next = nullptr;
}

template <typename T>
Dsl::Dsl(T &item, Dsl<T> *aNext) {
	data = item;
	next = aNext;
}

template <typename T>
Dsl::Dsl(T &item, Dsl<T> *aNext, Dsl<T> *aPrev) {
	data = item;
	next = aNext;
	prev = aPrev;
}

template <typename T>
Dsl::~Dsl() {
	delete this;
	this = nullptr;
}
