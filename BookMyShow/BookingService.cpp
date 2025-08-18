#include "Show.cpp"
#include "Booking.cpp"

class BookingService{
    vector<Booking> bookings;
public:
    void createBooking(const Show& show, int tickets, const vector<int>& seats) {
        static int idCounter = 1;
        Booking booking(idCounter++, show, tickets, seats);
        bookings.push_back(booking);
    }

    void processPayment(int bookingId, const Payment& payment) {
        for (auto& booking : bookings) {
            if (booking.getBookingId() == bookingId) {
                booking.processPayment(payment);
                return;
            }
        }
        std::cout << "Booking not found!" << std::endl;
    }
};
