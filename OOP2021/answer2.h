//
// Created by 85378 on 5/6/2022.
//

#ifndef OOP2021_V2_ANSWER2_H
#define OOP2021_V2_ANSWER2_H

#include <string>
#include <vector>

float getTemp() {
    return 0;
}


class Vaccine {
protected:
    std::string name;
    float amount;
    float dose;

public:
    Vaccine(std::string name, float amount, float dose) : name(name), amount(amount), dose(dose) {}
    std::string getName() const { return name; }
    float getAmount() const { return amount; }
    float getDose() const { return dose; }
    virtual bool giveDose(float& vaccineAmount, float& dilutionAmount) = 0;
    void print() const {
        std::cout << "Vaccine: " << name << " Amount: " << amount << " Dose: " << dose << std::endl;
    }
};

class VaccineA: public Vaccine {
    float dilution;

public:
    VaccineA(std::string name, float amount, float dose, float dilutionAmount) : Vaccine(name, amount, dose), dilution(dilutionAmount) {}

    bool giveDose(float& vaccineAmount, float& dilutionAmount) override {
        if (vaccineAmount + dilutionAmount >= dose && vaccineAmount/dilutionAmount == amount/dilution) {
            vaccineAmount -= dose/(amount+dilution)*amount;
            dilutionAmount -= dose/(amount+dilution)*dilution;
            return true;
        }
        return false;
    }
};

class VaccineB: public Vaccine {
    float safeTemperature;

public:
    VaccineB(std::string name, float amount, float dose, float safeTemperature) : Vaccine(name, amount, dose), safeTemperature(safeTemperature) {}

    bool giveDose(float& vaccineAmount, float& dilutionAmount) override {
        if (vaccineAmount + dilutionAmount >= dose && dilutionAmount == 0 && getTemp()<=safeTemperature) {
            vaccineAmount -= dose;
            return true;
        }
        return false;
    }
};


class Vial {
    Vaccine *vaccine;
    float maxAmount;
    float vaccineAmount;
    float dilutionAmount;

public:
    Vial(Vaccine *vaccine, float maxAmount) :
    vaccine(vaccine), maxAmount(maxAmount), vaccineAmount(vaccine->getAmount()) {
        if (maxAmount< vaccineAmount) {
            throw std::invalid_argument("Vial is too small to hold the vaccine!");
        }
        dilutionAmount = 0;
    }

    void dilute(float amount) {
        dilutionAmount += amount;
        if (dilutionAmount + vaccineAmount > maxAmount) {
            throw std::invalid_argument("Vial cannot hold that much dilution amount!");
        }
    }

    bool giveDose() {
        return vaccine->giveDose(vaccineAmount, dilutionAmount);
    }

    void print() const {
        std::cout << "holding vaccine: ";
        vaccine->print();
        std::cout << "with vaccine amount left: " << vaccineAmount << std::endl;
        std::cout << "with dilution amount left: " << dilutionAmount << std::endl;
    }

};

template<size_t maxSize>
class Tray {
    std::vector<Vial*> vials;
    int currentSize = 0;


public:
    int getCurrentSize() const { return currentSize; }
    Vial& getVial() {
        auto ptr = vials.back();
        vials.pop_back();
        currentSize--;
        return *ptr;

    }
    void print() const {
        std::cout << "Tray has " << currentSize << " vials left: " << std::endl;
        for (auto vial : vials) {
            vial->print();
        }
        std::cout << std::endl;
    }
    void add(Vial& vial) {
        if (currentSize < maxSize) {
            vials.push_back(&vial);
            currentSize++;
        }
    }

};




#endif //OOP2021_V2_ANSWER2_H
