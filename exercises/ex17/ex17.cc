// Cedric Nagata
// nagatac@uw.edu

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <ctime>

#include "SimpleQueue.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;

const int NUM_PIES = 6;                 // # pies created by each producer
static SimpleQueue queue;               // queue of pies
static unsigned int seed = time(NULL);  // initialize random sleep time
static pthread_mutex_t write_lock;      // mutex for cout

// Thread safe print that prints the given str on a line
void thread_safe_print(string str) {
  pthread_mutex_lock(&write_lock);
  // Only one thread can hold the lock at a time, making it safe to
  // use cout. If we didn't lock before using cout, the order of things
  // put into the stream could be mixed up.
  cout << str << endl;
  pthread_mutex_unlock(&write_lock);
}

// Produces NUM_PIES pies of the given type
// You should NOT modify this method at all
void producer(string pie_type) {
  for (int i = 0; i < NUM_PIES; i++) {
    queue.Enqueue(pie_type);
    thread_safe_print(pie_type + " pie ready!");
    int sleep_time = rand_r(&seed) % 500 + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

// Eats 2 * NUM_PIES pies
// You should NOT modify this method at all
void consumer() {
  for (int i = 0; i < NUM_PIES * 2; i++) {
    bool successful = false;
    string pie_type;
    while (!successful) {
      while (queue.IsEmpty()) {
        // Sleep for a bit and then check again
        int sleep_time = rand_r(&seed) % 800 + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
      successful = queue.Dequeue(&pie_type);
    }
    thread_safe_print(pie_type + " pie eaten!");
  }
}

/*
 * Wrapper function for producer thread
 * Arguments: 
 *  - void * arg for argument to pass to producer
 * Return:
 *  - nullptr
*/
void *producer_thread_start(void *arg) {
  string *pie_type = reinterpret_cast<string *>(arg);
  std::cout << "[producer child thread] I'm alive!" << std::endl;
  std::cout << "[producer child thread] calling producer(" << *pie_type << ")" << std::endl;
  producer(*pie_type);
  std::cout << "[producer child thread] done." << std::endl;
  return nullptr;
}

/*
 * Wrapper function for consumer thread
 * Arguments: 
 *  - void *arg
 * Return:
 *  - nullptr
*/
void *consumer_thread_start(void *arg) {
  std::cout << "[consumer child thread] I'm alive!" << std::endl;
  std::cout << "[consumer child thread] calling consumer()" << std::endl;
  consumer();
  std::cout << "[consumer child thread] done." << std::endl;
  return nullptr;
}

int main(int argc, char **argv) {
  pthread_mutex_init(&write_lock, NULL);
  // Your task: Make the two producers and the single consumer
  // all run concurrently (hint: use pthreads)
  pthread_t threads[3];

  // thread arguments
  string thr_arg_1 = "Apple";
  string thr_arg_2 = "Blackberry";
  string thr_arg_3 = "";

  // create pthreads
  if (pthread_create(&threads[0], nullptr, &producer_thread_start,
                     reinterpret_cast<void *>(&thr_arg_1)) != 0) {
    std::cerr << "pthread_create() failed." << std::endl;
    return EXIT_FAILURE;
  }

  if (pthread_create(&threads[1], nullptr, &producer_thread_start,
                     reinterpret_cast<void *>(&thr_arg_2)) != 0) {
    std::cerr << "pthread_create() failed." << std::endl;
    return EXIT_FAILURE;
  }

  if (pthread_create(&threads[2], nullptr, &consumer_thread_start,
                     reinterpret_cast<void *>(&thr_arg_3)) != 0) {
    std::cerr << "pthread_create() failed." << std::endl;
    return EXIT_FAILURE;
  }

  // join pthreads
  for (pthread_t thread : threads) {
    void *retval;

    if (pthread_join(thread, &retval) != 0) {
      std::cerr << "pthread_join() failed." << std::endl;
    }
  }

  pthread_mutex_destroy(&write_lock);
  return EXIT_SUCCESS;
}