#include "Payment.cpp"

class Booking{
    int bookingId;
    Show show;
    int numberOfTickets;
    vector<int> seatNumbers;
    Payment payment;
public:
    Booking(int id, const Show& show, int tickets, const vector<int>& seats)
        : bookingId(id), show(show), numberOfTickets(tickets), seatNumbers(seats) {}

    int getBookingId() const { return bookingId; }
    Show getShow() const { return show; }
    int getNumberOfTickets() const { return numberOfTickets; }
    vector<int> getSeatNumbers() const { return seatNumbers; }

    
public:
    Booking(int id, const Show& show, int tickets, const vector<int>& seats)
        : bookingId(id), show(show), numberOfTickets(tickets), seatNumbers(seats) {}

    int getBookingId() const { return bookingId; }
    Show getShow() const { return show; }
    int getNumberOfTickets() const { return numberOfTickets; }
    vector<int> getSeatNumbers() const { return seatNumbers; }
    void processPayment(const Payment& payment) {
        this->payment = payment;
    }

};
