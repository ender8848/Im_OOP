#include <iostream>
#include "asnwer1.h"
#include "answer2.h"

int main(int /*argc*/ , char* /*argv*/ []) {
    // q1
    DB db;
    auto p1 = db.getProperty(0, 0);
    auto a1 = db.getAgent(12345, "Jules");
    auto c1 = db.getClient(54321);
    auto app = db.makeAppointment(a1, p1, c1, now() + 8);
    // circular dependency
    auto newAppointment = app.cancel();
    std::cout << newAppointment.time << std::endl;

    // q2
    auto vaccineA = VaccineA("Covid-Protect", 0.45, 0.3, 1.8);
    auto vaccineB = VaccineB("Covid-Begone", 5, 0.5, 15);
    Vial vial1 = Vial(&vaccineA, 3);
    Vial vial2 = Vial(&vaccineB, 6);
    vial1.dilute(1.1);

    Tray<10> tray;
    tray.add(vial1);
    tray.add(vial2);

    while (tray.getCurrentSize() > 0) {
        Vial vial = tray.getVial();
        while (vial.giveDose()) {
            vial.print();
            std::cout << std::endl;
            tray.print();
        }
    }

    return 0;
}
