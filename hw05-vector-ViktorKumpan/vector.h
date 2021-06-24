#pragma once
#include <vector>

template<typename T>
class vector_t{
public:
  vector_t();
  vector_t(size_t count, const T & value = T());
  vector_t(const vector_t& other);
  ~vector_t();

  vector_t& operator=(const vector_t &);
  const T& operator[](size_t pos) const;
  T& operator[](size_t pos);

  T& front();
  const T& front() const;
  T& back();
  const T& back() const;

  T* data();
  const T* data() const;

  bool empty() const;

  size_t size() const;

  void reserve(size_t new_cap);
  size_t capacity() const;
  void shrink_to_fit();
  void clear();

  void insert(size_t, const T&);
  void insert(size_t, size_t,const T&);

  void erase(size_t);
  void erase(size_t,size_t);

  void push_back(const T &);

  void pop_back();
  void resize(size_t, const T &val = T());
  void swap(vector_t& other);

  bool operator > (const vector_t &) const;
  bool operator <= (const vector_t &) const;

  bool operator < (const vector_t &) const;
  bool operator >= (const vector_t &) const ;

  bool  operator == (const vector_t&) const;
  bool  operator != (const vector_t &) const;

private:
  T * arr;
  size_t capacity_;
  size_t pos;

  void relocate();
  void push(size_t pos, const T&, size_t count = 0);
  void erase_val(size_t,size_t);
  size_t detect_min_size(size_t size);
};


template <typename T>
vector_t<T>::vector_t() {
  arr = nullptr;
  capacity_ = 0;
  pos = 0;
}

template <typename T>
vector_t<T>::vector_t(size_t count, const T &value) {
  if (count == 0){
    arr = nullptr;
    capacity_ = 0;
    pos = 0;
  }
  else{
    pos = count;
    capacity_ = detect_min_size(count);
    arr = new T[capacity_];
    for (size_t i = 0; i < count; i ++){
      arr[i] = value;
    }
  }
}

template <typename T>
size_t vector_t<T>::detect_min_size(size_t size) {
  size_t p2=1;
  while (true) {
    if (p2>=size) return p2;
    p2<<=1;
  }
}

template <typename T>
vector_t<T>::vector_t(const vector_t &other) {
  pos = other.pos;
  if (other.pos == 0){
    arr = nullptr;
    capacity_ = 0;
    pos = 0;
  }
  else{
    capacity_ = detect_min_size(other.pos);
    arr = new T[capacity_];
    for (size_t i = 0; i < other.pos; i ++){
      arr[i] = other.arr[i];
    }
  }
}


template <typename T>
vector_t<T>::~vector_t() {
  delete[] arr;
}

template <typename T>
void vector_t<T>::swap(vector_t & other) {
  // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom

  std::swap(this->pos, other.pos);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->arr, other.arr);
}

template <typename T>
vector_t<T> &vector_t<T>::operator=(const vector_t & other) {
  vector_t other_c = other;
  swap(other_c);
  return *this;
}

template <typename T>
const T &vector_t<T>::operator[](size_t  pos) const {
  return arr[pos];
}

template <typename T>
T &vector_t<T>::operator[](size_t pos) {
  return arr[pos];
}
template <typename T>
T &vector_t<T>::front() {
  return arr[0];
}
template <typename T>
const T &vector_t<T>::front() const {
  return arr[0];
}
template <typename T>
T &vector_t<T>::back() {
  return arr[pos-1];
}
template <typename T>
const T&vector_t<T>::back() const {
  return arr[pos-1];
}
template <typename T>
T *vector_t<T>::data() {
  return arr;
}
template <typename T>
const T *vector_t<T>::data() const {
  return arr;
}
template <typename T>
bool vector_t<T>::empty() const {
  return pos == 0;
}
template <typename T>
size_t vector_t<T>::size() const {
  return pos;
}

template <typename T>
void vector_t<T>::relocate() {
  T* newArr = new T[capacity_];
  for (size_t i = 0; i < pos; i++){
    newArr[i] = arr[i];
  }
  delete [] arr;
  arr = newArr;
//  delete[] newArr;
  return;
}

template <typename T>
void vector_t<T>::reserve(size_t new_cap) {
  if (capacity_ >= new_cap){
    return;
  }else{
    capacity_ = detect_min_size(new_cap);
    relocate();
  }
}
template <typename T>
size_t vector_t<T>::capacity() const{
  return capacity_;
}

template <typename T>
void vector_t<T>::shrink_to_fit() {
  if(pos == 0){
    *this = vector_t();
    // случай если вектор пуст то после работы этого метода вектор должен стать таким же как вектор,
    // созданный конструктором без аргументов
  }else if (capacity_ == detect_min_size(pos)){
    //Если же сужать некуда, то метод не должен ничего делать
    return;
  }else{
    capacity_ = detect_min_size(pos);
    relocate();
  }
}
template <typename T>
void vector_t<T>::clear() {
  delete [] arr;
  arr = nullptr;
  pos = 0;
  capacity_ = 0;
}
template <typename T>
void vector_t<T>::push(size_t palce, const T& val, size_t count) {
  if (palce == pos){
    for(size_t i = pos; i < pos + count; i++){
      arr[i] = val;
    }

  }
  else{
    T* newArr = new T[capacity_];
    size_t checker = 0;
    for(size_t i = 0; i < pos; i++){
      if (palce == i) {
        while (count != checker){
          newArr[i + checker] = val;
          checker++;
        }
      }
      newArr[i + checker] = arr[i];
    }
    delete [] arr;
    arr = newArr;
//  delete [] newArr;
  }
  pos += count;
  return;
}
template <typename T>
void vector_t<T>::insert(size_t place, const T & val) {
  long long temp = capacity_ - pos - 1;
  if (temp < 0){
    capacity_ = detect_min_size(pos + 1);
    relocate();
  }
  push(place,val,1);

}
template <typename T>
void vector_t<T>::insert(size_t place, size_t count, const T & val) {
  long long temp = capacity_ - pos - count;
  if (temp < 0){
    capacity_ = detect_min_size(pos + count);
    relocate();
  }
  push(place,val,count);
}
template <typename T>
void vector_t<T>::erase_val(size_t first, size_t last) {
  if (first == last){
    return;
  }else{
    T* newArr = new T[capacity_];
    size_t count = 0;
    for(size_t i = 0; i < pos; i ++){
      if (i >= first && i < last){
        count++;
        continue;
      }else{
        newArr[i-count] = arr[i];
      }
    }
    delete [] arr;
    arr = newArr;
    pos -= count;
    return;
  }

}
template <typename T>
void vector_t<T>::erase(size_t place) {
  erase_val(place,place+1);
  return;
}
template <typename T>
void vector_t<T>::erase(size_t first, size_t last) {
  erase_val(first,last);
}
template <typename T>
void vector_t<T>::push_back(const T & val) {
  long long temp = capacity_ - pos - 1;
  if (temp < 0){
    capacity_ = detect_min_size(pos + 1);
    relocate();
  }
  push(size(),val,1);
}
template <typename T>
void vector_t<T>::pop_back() {
  pos --;
//  erase_val(size()-1,size());
}
template <typename T>
void vector_t<T>::resize(size_t new_size, const T &val) {
  if (size() >= new_size){
    erase_val(new_size,size());
  }else{
    if (capacity_ < new_size) {
      capacity_ = detect_min_size(new_size);
      relocate();
    }
    push(size(),val,new_size-size());
  }
}
template <typename T>
bool vector_t<T>::operator>(const vector_t<T> & other) const {
  return (other < *this);
}

template <typename T>
bool vector_t<T>::operator<=(const vector_t<T> & other) const {
  return !(other < *this);
}
template <typename T>
bool vector_t<T>::operator<(const vector_t<T> & other) const {
  return std::lexicographical_compare(arr,arr+pos,other.arr,other.arr+other.pos);

}

template <typename T>
bool vector_t<T>::operator>=(const vector_t<T> & other) const {
  return !(*this < other);
}

template <typename T>
bool vector_t<T>::operator==(const vector_t<T> & other) const {
  if (pos != other.pos){
    return false;
  }
  size_t max_len = std::max(pos,other.pos);
  for(size_t i = 0; i < max_len; i++){
    if (arr[i] != other.arr[i]){
      return false;
    }
  }
  return true;
}

template <typename T>
bool vector_t<T>::operator!=(const vector_t<T> & other) const {
  return !(*this == other);
}
