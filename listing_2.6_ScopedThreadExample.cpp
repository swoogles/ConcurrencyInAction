#include <iostream>
#include <thread>
#include <stdexcept>

class scoped_thread
{
  std::thread t;

  public:

  explicit scoped_thread(std::thread t_):
    t(std::move(t_))
  {
    if( !t.joinable())
    {
      throw std::logic_error("No thread");
    }
  }

  ~scoped_thread()
  {
    t.join();
  }

  scoped_thread(scoped_thread const&)=delete;
  scoped_thread& operator=(scoped_thread const&)=delete;
};

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

void do_something_in_current_thread()
{
  int i = 5;
  int x = i*i*i;
  x += i;
}

void f()
{
  int some_local_state = 1;
  scoped_thread t(std::thread(func(some_local_state)));

  do_something_in_current_thread();
}

int main()
{
  f();
}
