template <typename T>
ArrayQueue<T>::ArrayQueue(int i) {
    if (i <= 0) i = 100;
    maxSize = i;
    buffer = new T[maxSize];
    this->length = 0;
    frontIndex = 0;
    backIndex = -1;
}

template <typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& copyObj) {
    buffer = nullptr;
    copy(copyObj);
}

template <typename T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] buffer;
    buffer = nullptr;
    maxSize = 0;
    frontIndex = 0;
    backIndex = -1;
    this->length = 0;
}

template <typename T>
T ArrayQueue<T>::back() const {
    if (isEmpty()) throw string("queue is empty");
    return buffer[backIndex];
}

template <typename T>
void ArrayQueue<T>::clear() {
    this->length = 0;
    frontIndex = 0;
    backIndex = -1;
}

template <typename T>
void ArrayQueue<T>::copy(const ArrayQueue<T>& copyObj) {
    if (buffer) {
        delete[] buffer;
        buffer = nullptr;
    }
    maxSize = copyObj.maxSize;
    buffer = new T[maxSize];
    this->length = copyObj.length;
    frontIndex = 0;
    if (this->length == 0) {
        backIndex = -1;
        return;
    }
    for (int k = 0; k < this->length; ++k) {
        int idx = (copyObj.frontIndex + k) % copyObj.maxSize;
        buffer[k] = copyObj.buffer[idx];
    }
    backIndex = this->length - 1;
}

template <typename T>
void ArrayQueue<T>::dequeue() {
    if (isEmpty()) throw string("cannot dequeue from empty queue");
    frontIndex = (frontIndex + 1) % maxSize;
    this->length--;
    if (this->length == 0) {
        frontIndex = 0;
        backIndex = -1;
    }
}

template <typename T>
void ArrayQueue<T>::enqueue(const T& elem) {
    if (isFull()) throw string("queue is full");
    backIndex = (backIndex + 1) % maxSize;
    buffer[backIndex] = elem;
    this->length++;
}

template <typename T>
T ArrayQueue<T>::front() const {
    if (isEmpty()) throw string("queue is empty");
    return buffer[frontIndex];
}

template <typename T>
int ArrayQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
int ArrayQueue<T>::getMaxSize() const {
    return maxSize;
}

template <typename T>
bool ArrayQueue<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
bool ArrayQueue<T>::isFull() const {
    return this->length == maxSize;
}
