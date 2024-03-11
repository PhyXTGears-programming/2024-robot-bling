#pragma once
#include <Wire.h>
#include <cmath>

//template <class uint8_t>
class CassiusRingBuffer {
  public:
  
    static const size_t max_size = 64;
    static const unsigned int NO_NUMBER = (unsigned int)(0) - 1;

    explicit CassiusRingBuffer() {/*emptyyyyyy..(echo)..(echo)..(echo)...*/}

    void put(uint8_t item) {
        if (m_full) {
          return;
        }//end of if statement

        m_buff[m_head] = item;
        m_head = (m_head + 1) % max_size;
        m_full = (m_head == m_tail);
    }//end of function put

    void put(char const * const str) {
      size_t len = strlen(str);

      for (size_t a = 0; a < len; a += 1) {
        put(str[a]);
      }
    }
      
    uint8_t get(){
        if (m_head == m_tail && ! m_full){
            return 0;
        }//end of if statement
        
        uint8_t value = m_buff[m_tail];
        m_tail = (m_tail + 1) % max_size;
        m_full = false;
        return value;
    }// end of get() function

    void drop(size_t count) {
      count = std::min(count, size());

      m_tail = (m_tail + count) % max_size;
      m_full = false;
    }

    unsigned int indexOf(char const * const needle) {
      size_t len = strlen(needle);

      if (len > size()) {
        return NO_NUMBER;
      }

      for (size_t a = 0; a < size() - len + 1; a += 1) {
        if (matches(a, needle)) {
          return a;
        }
      }

      return NO_NUMBER;
    }

    bool hasMessage () {
      for (int i = m_tail; i != m_head; i = ( i + 1 ) % max_size) {
        if (m_buff[i] == '\0') {
          return false;
        }
      }
      return true;
    }

    bool startsWith(char const * const str) {
      size_t slen = strlen(str);

      if (slen > size()) {
        return false;
      }

      for (size_t a = 0; a < slen; a += 1){
        if (str[a] != m_buff[(m_tail + a) % max_size]) {
          return false;
        }
      }

      return true;
    }

    bool matches(size_t offset, char const * const str) {
      size_t len = strlen(str);

      if (len > size()) {
        return false;
      }

      for (size_t a = 0; a < len; a += 1){
        if (str[a] != m_buff[(m_tail + a + offset) % max_size]) {
          return false;
        }
      }

      return true;
    }

    unsigned int getNumber() {
      if (isEmpty()) {
        return (unsigned int)(0) - 1;
      }

      if (!isNumeric(m_buff[m_tail])) {
        return (unsigned int)(0) - 1;
      }

      int acc = 0;
      
      while (!isEmpty() && isNumeric(m_buff[m_tail])) {
        acc *= 10;
        acc += get() - '0';
      }

      return acc;
    }
    
    void reset(){
        m_head = 0;
        m_tail = 0;
        m_full = true;
    }//end of reset() function
      
    bool isEmpty()    const {
        return (m_head == m_tail && ! m_full);
    }//end of isEmpty
    
    bool isFull()     const {
        return m_full;
    }//end of isFull
    
    size_t capacity() const {
      return max_size;
    }//end of capacity
    
    size_t size() {
      size_t num = m_head - m_tail;
      if (num > max_size) {
        return num + max_size;
      } else { 
        return num;
      }
    }//end of size

  private:
  uint8_t m_buff[64];
  size_t m_head = 0;
  size_t m_tail = 0;
  bool m_full = false;

  static bool isNumeric(uint8_t val) {
    return (val >= '0' && val <= '9');
  }
  
};//end of class CassiusRingBuffer
