#include <Arduino.h>
#include <functional>
#include <exception>

#include "RingBuffer.h"

#define ASSERT(x) return (x)

void runTest(char const * const, std::function<bool()>);

void setup() {
  Serial.begin(9600);

  delay(1000);

  runTest(
    "ring buffer - empty buffer - is empty",
    [] () {
      CassiusRingBuffer buff;

      ASSERT(buff.isEmpty());
    }
  );

  runTest(
    "ring buffer - empty buffer - is not full",
    [] () {
      CassiusRingBuffer buff;

      ASSERT(!buff.isFull());
    }
  );
  
  runTest(
    "ring buffer - add 1 byte - is not empty",
    [] () {
      CassiusRingBuffer buff;

      buff.put('a');

      ASSERT(!buff.isEmpty());
    }
  );
  
  runTest(
    "ring buffer - add all bytes - is full",
    [] () {
      CassiusRingBuffer buff;

      for (size_t a = 0; a < CassiusRingBuffer::max_size; a += 1) {
        buff.put('a');
      }

      ASSERT(buff.isFull());
    }
  );
  
  runTest(
    "ring buffer - add all bytes - is not empty",
    [] () {
      CassiusRingBuffer buff;

      for (size_t a = 0; a < CassiusRingBuffer::max_size; a += 1) {
        buff.put('a');
      }

      ASSERT(!buff.isEmpty());
    }
  );
  
  runTest(
    "ring buffer - add all bytes then remove all - is empty",
    [] () {
      CassiusRingBuffer buff;

      for (size_t a = 0; a < CassiusRingBuffer::max_size; a += 1) {
        buff.put('a');
      }
      
      for (size_t a = 0; a < CassiusRingBuffer::max_size; a += 1) {
        buff.get();
      }

      ASSERT(buff.isEmpty());
    }
  );

  runTest(
    "ring buffer - add all bytes then remove one - is not empty",
    [] () {
      CassiusRingBuffer buff;

      for (size_t a = 0; a < CassiusRingBuffer::max_size; a += 1) {
        buff.put('a');
      }
      
      buff.get();

      ASSERT(!buff.isEmpty());
    }
  );
  
  runTest(
    "ring buffer - add all bytes then add one more - last add is ignored",
    [] () {
      CassiusRingBuffer buff;

      for (size_t a = 0; a < CassiusRingBuffer::max_size; a += 1) {
        buff.put('a');
      }

      buff.put('b');

      bool pass = true;
      
      while (!buff.isEmpty()) {
        if ('b' == buff.get()) {
          pass = false;
        }
      }

      ASSERT(pass);
    }
  );
  
  runTest(
    "ring buffer matches - has matches - works",
    [] () {
      CassiusRingBuffer buff;

      buff.put("M 0abc\r\n");

      bool pass = true;

      pass = pass && buff.matches(0, "M 0");

      pass = pass && buff.matches(3, "abc");

      pass = pass && buff.matches(6, "\r\n");

      pass = pass && ! buff.matches(0, "abc");
      
      ASSERT(pass);
    }
  );
  
  runTest(
    "ring buffer index of - has matches - works",
    [] () {
      CassiusRingBuffer buff;

      buff.put("M 0abc\r\n");

      bool pass = true;

      pass = pass && 0 == buff.indexOf("M 0");

      pass = pass && 3 == buff.indexOf("abc");

      pass = pass && 6 == buff.indexOf("\r\n");
      
      ASSERT(pass);
    }
  );
  
  runTest(
    "ring buffer - add command - can parse command",
    [] () {
      CassiusRingBuffer buff;

      buff.put("M 0abc\r\n");

      bool pass = true;

      pass = pass && buff.startsWith("M ");
      buff.drop(2);

      unsigned int num = buff.getNumber();

      pass = pass && num == 0;

      buff.drop(buff.indexOf("\r\n") + 2); // drop crlf.

      pass = pass && buff.isEmpty();
      
      ASSERT(pass);
    }
  );

  // P 24
  // if (buff.startWith("P ")) {
  //   buff.drop(2);
  //   int pNum = buff.getNumber();

  //   switch (pNum) {
  //     case 24:
  //       p24();
  //       break;

  //     case
  //   }
  // }
}

void loop() {
}

void runTest(char const * const name, std::function<bool()> testF) {
  if (testF()) {
    Serial.print("PASS: ");
    Serial.println(name);
  } else {
    Serial.print("FAIL: ");
    Serial.println(name);
  }
}