#include <iostream>
#include <functional>
#include "answer1.h"
#include "answer2.h"

Program program = Program();

void part1();

void part2();

void setUpProgram() {
    program.addRegion(new Region(Position(5000, 0), Position(0, 5000)));
    program.addSensor(new Sensor(Position(988.456, 3470.3)));
    program.addSensor(new Sensor(Position(4687.31, 216.378)));
    program.addSensor(new Sensor(Position(780.31, 1854.87)));
    program.addSensor(new Sensor(Position(3325.91, 2326.46)));
    program.addSensor(new Sensor(Position(106.577, 978.304)));
    program.addSensor(new Sensor(Position(40.3523, 3343.87)));
    program.addSensor(new Sensor(Position(578.758, 2952.94)));
    program.addSensor(new Sensor(Position(1484.58, 2824.1)));
}
void ingestEvent(double value, double latitude, double longitude, int timestamp) {
    program.addEvent(value, latitude, longitude, timestamp);
}
void addObserverToSensorAtPosition(std::function<void()> observer, double latitude,
                                   double longitude) {
    program.addObserverToSensorAtPosition(observer, latitude, longitude);
}

int main() {
    // part1();
    part2();
    return 0;
}

void part2() {
    Table<'#', 15> table(3,2);
    table.addCell(new TextCell("Karting Time:"));
    table.addCell(new TextCell("Price:"));
    table.addCell(new DurationCell(85));
    table.addCell(new CurrencyCell("GBP", 60.5, 2));
    table.addCell(new DurationCell(25));
    table.addCell(new CurrencyCell("USD", 25.4, 0, 3));
    table.print();
}

void part1() {// Example for event ingestions
    setUpProgram();
    ingestEvent(1709.88, 988.456, 3470.3, 1);
    ingestEvent(4856.02, 4687.31, 216.378, 2);
    ingestEvent(183.283, 780.31, 1854.87, 3);
    ingestEvent(1046.07, 3325.91, 2326.46, 4);
    ingestEvent(3768.23, 106.577, 978.304, 5);
    ingestEvent(2834.78, 40.3523, 3343.87, 6);
    ingestEvent(3690.92, 578.758, 2952.94, 7);
    ingestEvent(4051.8, 1484.58, 2824.1, 8);
///////////////////////////////////////////////
// Q1 b): Your code to add observers goes here: //
    addObserverToSensorAtPosition([] {
        std::cout << "extraordinary event observed" << std::endl;
    }, 988.456, 3470.3);
    ingestEvent(10000, 988.456, 3470.3, 1);
}
