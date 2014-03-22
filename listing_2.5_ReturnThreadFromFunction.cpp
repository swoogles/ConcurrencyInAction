#include <iostream>
#include <thread>

void some_function()
{
  int i = 5;
  int x = i*i*i;
  x += i;
  std::cout << "some_function return.\n";
}

void some_other_function()
{
  int i = 3;
  int x = i*i*i;
  x += i;
  std::cout << "some_other_function return.\n";
}

std::thread f()
{
  void some_function();
  return std::thread(some_function);
}


std::thread g()
{
  void some_other_function();
  std::thread t(some_other_function);
  return t;
}
int main()
{
  std::thread f_ret = f();
  std::thread g_ret = g();

  f_ret.join();
  g_ret.join();

  std::cout << "Done.\n";
}

