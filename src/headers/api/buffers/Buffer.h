#pragma once

namespace iamaprogrammer {
  
  template <typename T>
  class Buffer {
  public:
    Buffer() {
      this->size = 0;
      this->data = new T[0];
    };

    Buffer(int size) {
      this->size = size;
      this->data = new T[size];
    };

    ~Buffer() {
      delete[] data;
    };

    int getSize() {
      return size;
    };

    void resize(int size) {
      T* newData = new T[size];
      std::copy(data, data + this->size, newData);
      delete[] data;
      
      this->size = size;
      this->data = newData;
    };

    T* getBuffer() {
      return data;
    };

    std::string toString() {
      if (this->data == nullptr || this->size == 0) {
        return "[]";
      }

      std::string str = "[";
      for (int i = 0; i < this->size; i++) {
        str += std::to_string(this->data[i]);
        if (i < this->size - 1) str += ", ";
      }
      str += "]";
      return str;
    };
    
  private:
    T* data;
    int size;
  };
}