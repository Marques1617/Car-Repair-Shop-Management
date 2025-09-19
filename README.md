# Car-Repair-Shop-Management
Project C - 2023

The goal is to create a software application that helps workshop staff manage customer bookings efficiently. The system should store information about clients, available appointment slots, and any reservations on hold. Users should be able to perform the following tasks interactively:
Book a wash or maintenance service: Allow a customer to schedule a car wash or maintenance appointment.
Pre-book a service: If no suitable time slots are available, a customer can join a waiting list to get priority if an existing booking is canceled.
Cancel a reservation: Remove an existing booking. If a pre-booked appointment fits the newly freed time and date, it should be scheduled immediately.
Cancel a pre-booking: Remove a waiting list request.
List bookings and pre-bookings by date: Display all car wash and maintenance appointments, as well as pre-bookings, sorted chronologically (oldest first). It should also allow viewing a customer’s bookings in reverse chronological order (most recent first).
Working hours are from 8 a.m. to 6 p.m., with no lunch break. Car washes take 30 minutes, and maintenance services take 1 hour. Completed appointments should be removed from the booking lists.
You must define and use appropriate data structures, keeping efficiency and memory usage in mind. Preferably, use sorting methods that manipulate pointers to records rather than copying entire structures.
All important data should be stored in text files, and the program must provide options to load and save the current state of bookings. Additionally, the application should be designed with proper security measures.
