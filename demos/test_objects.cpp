/* Simple C++ object test program */

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

#include <stdio.h>
#include <string.h>

#include <cpu.h>

// Define an object class

class testclass1
{
public:

  testclass1(unsigned int d)
  {
    this->param = d;
  }

  unsigned int param;
};

// Define another object class

class testclass2
{
public:

  testclass2(unsigned int e)
  {
    this->param = e;
  }

  unsigned int param;
};

// Create some global objects--constructors should be called from startup.S
// before main() is called

testclass1 mytest1 = testclass1(1);

testclass1 mytest2(2);

testclass2 mytest3 = testclass2(3);

testclass2 mytest4(4);

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

#ifdef CONSOLE_SERIAL
  serial_stdio(CONSOLE_PORT);
#endif

#ifdef CONSOLE_SEMIHOSTING
  semihosting_stdio(CONSOLE_PORT)
#endif

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#endif

  printf("\033[H\033[2J%s C++ Object Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%u Hz  Compiler:%s %s %s\n\n", (unsigned int) SystemCoreClock,
    __COMPILER__, __VERSION__, __ABI__);

// Create some local objects

  testclass1 mytest5 = testclass1(5);

  testclass1 mytest6(6);

  testclass2 mytest7 = testclass2(7);

  testclass2 mytest8(8);

// Test the objects

  if (mytest1.param == 1)
  {
    puts("Object mytest1 was created successfully!");
  }

  if (mytest2.param == 2)
  {
    puts("Object mytest2 was created successfully!");
  }

  if (mytest3.param == 3)
  {
    puts("Object mytest3 was created successfully!");
  }

  if (mytest4.param == 4)
  {
    puts("Object mytest4 was created successfully!");
  }

  if (mytest5.param == 5)
  {
    puts("Object mytest5 was created successfully!");
  }

  if (mytest6.param == 6)
  {
    puts("Object mytest6 was created successfully!");
  }

  if (mytest7.param == 7)
  {
    puts("Object mytest7 was created successfully!");
  }

  if (mytest8.param == 8)
  {
    puts("Object mytest8 was created successfully!");
  }
}
