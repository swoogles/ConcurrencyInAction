/* This is an example of how you would guarantee that a thread is finished
 * before moving on and possibly deallocating resources that it references.
 *
 * A variant could be made that automatically detaches, rather than joins,
 * the thread in question.
 */

#include <iostream>
#include <thread>

class thread_guard
{
  std::thread& t;

  public:
    explicit thread_guard(std::thread& t_):
      t(t_)
    {}

    ~thread_guard()
    {
      if( t.joinable() )
      {
        t.join();
      }
    }
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
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

void f()
{
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);
  do_something(1);

  std::cout << "Done.\n";
}

int main()
{
  f();
}
