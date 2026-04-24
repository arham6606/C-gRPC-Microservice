#include "client.h"

int main(void)
{
    const int NUM_CLIENTS = 100;
    vector<thread> threads;

    for (int i = 0; i < NUM_CLIENTS; i++)
    {
        threads.emplace_back(send_create_request, i);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    cout << "All " << NUM_CLIENTS << " requests done" << endl;
}