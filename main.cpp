#include "mbed.h"

// Define the LED pins
DigitalOut led1(LED1);
DigitalOut led2(LED2);

// Create event queues for toggling LEDs
EventQueue queue1;
EventQueue queue2;

// Function to toggle LED1
void toggle_led1() {
    led1 = !led1;
    printf("LED1 toggled\n");
}

// Function to toggle LED2
void toggle_led2() {
    led2 = !led2;
    printf("LED2 toggled\n");
}

int main() {
    // Start event queues in separate threads
    Thread thread1;
    Thread thread2;
    
    thread1.start(callback(&queue1, &EventQueue::dispatch_forever));
    thread2.start(callback(&queue2, &EventQueue::dispatch_forever));

    // Schedule the LED toggles
    queue1.call_every(2000, toggle_led1); // 2000 ms = 2 seconds
    queue2.call_every(5000, toggle_led2); // 5000 ms = 5 seconds

    // Keep the main function alive
    while (true) {
        // Sleep to save power while waiting for events
        ThisThread::sleep_for(100ms);
    }
}