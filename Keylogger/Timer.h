#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>
#include <functional>

class Timer
{
	std::thread Thread; // Thread to run the timer asynchronously
    bool Alive = false; // Flag to check if the timer is running
    long CallNumber = -1L; // Total number of times the function will be called
    long repeat_count = -1L; // Tracks how many times the function has been called
    std::chrono::milliseconds interval = std::chrono::milliseconds(0); // Interval in milliseconds between function calls
    std::function<void(void)> funct = nullptr; // Function to be executed


	void SleepAndRun()
	{
		std::this_thread::sleep_for(interval); //pause thread for certain time interval
		if (Alive)
			Function()(); // double parenthesis - first calls Function and second calls function that Function returns
	}

	void ThreadFunc()
	{
		 // If CallNumber is Infinite, run the function indefinitely
		if (CallNumber == Infinite)
			while (Alive)
				SleepAndRun();
		else
			 // If CallNumber is finite, repeat the function the specified number of times
			while (repeat_count--)
				SleepAndRun();
	}

public:
    // A constant for infinite repetitions
    static const long Infinite = -1L;

    // Default constructor
    Timer() {};

    // Constructor to initialize with a function to be executed
    Timer(const std::function<void(void)> &f) : funct(f) {};

    // Constructor to initialize with a function, interval, and optional repeat count
    Timer(const std::function<void(void)> &f, const unsigned long &i, const long repeat = Timer::Infinite) 
        : funct(f), interval(std::chrono::milliseconds(i)), CallNumber(repeat) {};

    // Start the timer, optionally asynchronously
    void Start(bool Async = true)
    {
        if (IsAlive()) // If the timer is already running, do nothing
            return;

        Alive = true; // Mark the timer as alive
        repeat_count = CallNumber; // Set repeat count based on the CallNumber

        // Run the timer in a new thread if Async is true, otherwise run it in the current thread
        if (Async)
            Thread = std::thread(&Timer::ThreadFunc, this); // Start in a separate thread
        else
            this->ThreadFunc(); // Run synchronously in the current thread
    }

    // Stop the timer and join the thread
    void Stop()
    {
        Alive = false; // Mark the timer as stopped
        Thread.join(); // Wait for the thread to finish its execution
    }

    // Set a new function to be executed by the timer
    void SetFunction(const std::function<void(void)> &f) 
    {
        funct = f; // Update the function to execute
    }

    // Check if the timer is currently running
    bool IsAlive() const { return Alive; }

    // Set the number of times the function should be called
    void RepeatCount(const long r) 
    {
        if (Alive) // If the timer is already running, don't change the repeat count
            return;
        CallNumber = r; // Update the repeat count
    }

    // Get the remaining number of calls
    long GetLeftCount() const { return repeat_count; }

    // Get the total number of calls (CallNumber)
    long RepeatCount() const { return CallNumber; }

    // Set the interval time in milliseconds
    void SetInterval(const unsigned long &i)
    {
        if (Alive) // If the timer is already running, don't change the interval
            return;
        interval = std::chrono::milliseconds(i); // Set the new interval
    }

    // Get the current interval in milliseconds
    unsigned long Interval() const { return (unsigned long)interval.count(); }

    // Get the function that will be executed
    const std::function<void(void)> &Function() const
    {
        return funct; // Return the function to be executed
    }
};

#endif // TIMER_H