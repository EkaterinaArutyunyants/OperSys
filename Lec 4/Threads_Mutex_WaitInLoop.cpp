#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>

using namespace std;

#define NUM_OF_THREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int global_data = 0;

void* do_some_work(void* tpid)
{
    pthread_mutex_lock(&mutex1);
    cout << "Hello world! Greetings from thread #" << (long)tpid << "\n";

    for (int i = 0; i < 1e7; ++i)
    {
        global_data = global_data + 1;
    }

    cout << "Thread #" << (long)tpid << " thinks the value of the global_data is now " << global_data << "\n";

    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);
}



int main()
{
    /* 10 threads are created and print Hello World! */
    pthread_t Threads[NUM_OF_THREADS];

    int status;

    for (long i = 0; i < NUM_OF_THREADS; ++i)
    {
        status = pthread_create(&Threads[i], NULL, do_some_work, (void*)i);

        if (status) {
            cout << "ERROR; return code from pthread_create() is " << status << "\n";
            exit(-1);
        }

        status = pthread_join(Threads[i],NULL);
        if (status) {
            cout << "ERROR; return code from pthread_join() is " << status << "\n";
            exit(-1);
        }
    }

    return 0;
}