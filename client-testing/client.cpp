#include "client.h"

int main(void)
{
    const int NUM_CLIENTS = 10000;
    vector<thread> threads;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_CLIENTS; i++)
    {
        threads.emplace_back(send_create_request, i);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "\nTime:" << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << endl;

    cout << "All " << NUM_CLIENTS << " requests done" << endl;

    send_get_request(1);
    send_get_request(10);
    send_get_request(50);
    send_get_request(300);
    send_get_request(622);

}