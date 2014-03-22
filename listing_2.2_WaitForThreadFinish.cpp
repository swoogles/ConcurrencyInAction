#include <iostream>
#include <thread>

void do_something(int i)
{
  int x = i*i*i;
  x += i;
}

struct func
{
  int& i;

  func(int& i_):i(i_) { }

  void operator()()
  {
    for (unsigned j = 0; j < 1000000; ++j)
    {
      do_something(i);
    }
  }
};

void f()
{
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try
  {
    do_something(1);
  }
  catch(...)
  {
    t.join();
  }
  t.join();
  std::cout << "Done.\n";
}

int main()
{
  f();
}

