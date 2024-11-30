#include <iostream>

#include <queue>

#include <iomanip>

#include <sstream>

#include <thread>

#include <chrono>

#include <mutex>

#include <atomic>

#include <condition_variable>



class Person {

public:

    std::string name;

    int ticket_number;



    Person(const std::string& name, int ticket_number) : name(name), ticket_number(ticket_number) {}

};



class Queue {

private:

    std::queue<Person> line;

    int next_ticket_number = 1;

    std::mutex mtx;

    std::atomic<bool> running{true};

    std::condition_variable cv;



public:

    void Enqueue(const std::string& name) {

        std::ostringstream ticket;

        ticket << "#" << std::setw(3) << std::setfill('0') << next_ticket_number++;

        {

            std::lock_guard<std::mutex> lock(mtx);

            line.push(Person(name, next_ticket_number - 1));

        }

        std::cout << name << " added to the queue with Ticket " << ticket.str() << "\n";

    }



    void AutoDequeue() {

        while (running) {

            std::unique_lock<std::mutex> lock(mtx);

            if (cv.wait_for(lock, std::chrono::minutes(1), [this]() { return !running; })) break;



            if (!line.empty()) {

                Person frontPerson = line.front();

                line.pop();

                std::ostringstream ticket;

                ticket << "#" << std::setw(3) << std::setfill('0') << frontPerson.ticket_number;



                std::cout << "\nAfter 1 minute...\nDequeued: " << frontPerson.name << " (Ticket " << ticket.str() << ")\n";

                std::cout << "Queue size: " << line.size() << "\n";

                if (!line.empty()) {

                    Person nextPerson = line.front();

                    std::ostringstream nextTicket;

                    nextTicket << "#" << std::setw(3) << std::setfill('0') << nextPerson.ticket_number;

                    std::cout << "Next in line: " << nextPerson.name << " (Ticket " << nextTicket.str() << ")\n";

                }

            } else {

                std::cout << "\nThe queue is empty. No one to dequeue.\n";

            }

        }

    }



    void StopAutoDequeue() {

        running = false;

        cv.notify_all();

    }

};



int main() {

    Queue concertQueue;

    std::thread autoDequeueThread(&Queue::AutoDequeue, &concertQueue);



    int option;

    std::string name;

    std::cout << "Welcome to the Concert Ticketing System!\n1. Enqueue a person\n2. Exit\n";

    while (true) {

        std::cout << "\nChoose an option: ";

        std::cin >> option;

        if (option == 1) {

            std::cout << "Enter the name: ";

            std::cin >> name;

            concertQueue.Enqueue(name);

        } else if (option == 2) {

            concertQueue.StopAutoDequeue();

            break;

        } else {

            std::cout << "Invalid option. Please choose again.\n";

        }

    }



    if (autoDequeueThread.joinable()) autoDequeueThread.join();

    return 0;

}