/* Simple C++ object test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>

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

#ifdef CONSOLE_USB
  usb_serial_stdio(NULL);
  getch();
#else
  serial_stdio((char *) CONSOLE_PORT);
#endif

  printf("\033[H\033[2J%s C++ Object Test (" __DATE__ " " __TIME__ ")\n\n", MCUFAMILYNAME);
  puts(revision);
  printf("\nCPU Freq:%ld Hz  Compiler:%s %s %s\n\n", CPUFREQ, __COMPILER__, __VERSION__, __ABI__);

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
