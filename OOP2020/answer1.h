//
// Created by 85378 on 5/7/2022.
//

#ifndef OOP2020_V2_ANSWER1_H
#define OOP2020_V2_ANSWER1_H

#include <cmath>
#include <stdexcept>
#include <functional>

#define MAX_SENSOR_NUM_PER_REGION 32
#define MAX_REGION_NUM 32

template<typename T, int maxSize>
class MyQueue {
protected:
    // require: T implements the copy assignment operator
    T items[maxSize];
    int head = 0; // index of first element
    int rear = 0; // rear is the index of the last element
    int count = 0; // number of elements

public:
    MyQueue() = default;

    int size() const { return count; }

    bool isEmpty() { return count == 0; }

    bool isFull() { return count == maxSize; }

    void enqueue(T const &item) {
        if (isFull()) {
            dequeue();
            enqueue(item);
            return;
        }
        ++count;
        items[rear] = item;
        rear = (rear + 1) % maxSize;
    }

    // should check if the queue is empty
    T dequeue() {
        if (isEmpty()) { throw std::runtime_error("queue is empty"); }
        T *item = &items[head];
        --count;
        head = (head + 1) % maxSize;
        return *item;
    }

    T &operator[](int index) {
        if (index < 0 || index >= maxSize) { throw std::runtime_error("index out of range"); }
        int real_index = (head + index) % maxSize;
        return items[real_index];
    }
};


class Measurement {
private:
    int timestamp;
    double value;
public:
    // default constructor
    Measurement() : timestamp(-1), value(-1) {}

    Measurement(int timestamp, double value) : timestamp(timestamp), value(value) {};

    Measurement &operator=(Measurement const &other) {
        this->timestamp = other.timestamp;
        this->value = other.value;
        return *this;
    }

    Measurement(Measurement const &other) { *this = other; }

    double getValue() const { return value; }
};


class Position {
public:
    double const latitude;
    double const longitude;

    Position(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

    Position(Position const &other) : latitude(other.latitude), longitude(other.longitude) {}

    bool operator==(Position const &other) const {
        return abs(latitude - other.latitude) < 0.01 && abs(longitude - other.longitude) < 0.01;
    }
};


class Sensor {
private:
    static int const MAX_SIZE = 1000;
    std::function<void()> observer = nullptr;
    MyQueue<Measurement, 1000> measurements;
    Position position = {0, 0};

public:
    friend class Program;

    Sensor() = default;

    Sensor(Position const &position) : position(position) {}

    int getSize() const { return measurements.size(); }

    Position const &getPosition() const { return position; }

    // only hold the recent 1000 measurements, implement using a queue
    void addMeasurement(int timestamp, double value, double region_mean, int &count) {
        if (((getMean() - region_mean) / region_mean > 0.2 || (getMean() - region_mean) / region_mean < -0.2)
            && observer != nullptr) {
            observer();
            ++count;
            exit(1);
        }
        measurements.enqueue(Measurement(timestamp, value));
    }

    double getMean() {
        double mean = 0;
        for (int i = 0; i < measurements.size(); ++i) {
            mean += measurements[i].getValue() / measurements.size();
        }
        return mean;
    }
};

class Region {
private:
    int size = 0;
    Position topLeft;
    Position bottomRight;
    Sensor *sensors[MAX_SENSOR_NUM_PER_REGION]; // region owns sensors, ownership is always transferred to region
public:
    friend class Program;

    Region(Position const &topLeft, Position const &bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {}

    ~Region() {
        for (int i = 0; i < size; i++) {
            delete sensors[i];
        }
    }

    int getSize() const { return size; }

    bool contains(Position const &position) const {
        return position.latitude <= topLeft.latitude && position.latitude >= bottomRight.latitude &&
               position.longitude >= topLeft.longitude && position.longitude <= bottomRight.longitude;
    }

    void addSensor(Sensor *pSensor) {
        if (size < MAX_SENSOR_NUM_PER_REGION) {
            sensors[size] = pSensor;
            size++;
        } else {
            throw std::runtime_error("Region is full");
        }
    }

    double getMean() const {
        double mean = 0;
        for (int i = 0; i < size; i++) {
            mean += sensors[i]->getMean() / size;
        }
        return mean;
    }
};


class Program {
private:
    int size = 0;
    // program owns region
    Region *regions[MAX_REGION_NUM];
    Sensor *observed = nullptr;
    int extraordinary_count = 0;


public:
    Program() {}

    void addRegion(Region *region) {
        if (size < MAX_REGION_NUM) {
            regions[size++] = region;
        } else {
            throw std::runtime_error("no more place for new regions");
        }
    }

    void addEvent(double value, double latitude, double longitude, int timestamp) {
        for (int i = 0; i < size; i++) {
            if (regions[i]->contains({latitude, longitude})) {
                for (int j = 0; j < regions[i]->getSize(); j++) {
                    if (regions[i]->sensors[j]->getPosition() == Position(latitude, longitude)) {
                        double region_mean = regions[i]->getMean();
                        regions[i]->sensors[j]->addMeasurement(timestamp, value, region_mean, extraordinary_count);
                        return;
                    }
                }
            }
        }
        throw std::runtime_error("no region contains this position");
    }

    ~Program() {
        for (int i = 0; i < size; i++) {
            delete regions[i];
        }
    }

    void addSensor(Sensor *pSensor) {
        for (int i = 0; i < size; i++) {
            if (regions[i]->contains(pSensor->getPosition())) {
                regions[i]->addSensor(pSensor);
                return;
            }
        }
        throw std::runtime_error("no region contains this position");
    }

    void addObserverToSensorAtPosition(std::function<void()> observer, double latitude, double longitude) {
        for (int i = 0; i < size; i++) {
            if (regions[i]->contains({latitude, longitude})) {
                for (int j = 0; j < regions[i]->getSize(); j++) {
                    if (regions[i]->sensors[j]->getPosition() == Position(latitude, longitude)) {
                        // remove previous observer
                        if (observed != nullptr) { observed->observer = nullptr; }
                        // add new observer
                        observed = regions[i]->sensors[j];
                        observed->observer = observer;
                        return;
                    }
                }
            }
        }
        throw std::runtime_error("no region contains this position");
    }
};


#endif //OOP2020_V2_ANSWER1_H
