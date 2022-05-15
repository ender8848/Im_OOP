//
// Created by 85378 on 5/8/2022.
//

#ifndef OOP2019_V2_ANSWER2_H
#define OOP2019_V2_ANSWER2_H

#include <string>
#include <set>
#include <iostream>

class Printable {
public:
    virtual void print() const = 0;
};

class Classifiable {
public:
    virtual bool isPremium() = 0;
};


class Fruit: public Printable, public Classifiable {
protected:
    float weight;
    int bestBeforeDate; // margin
    std::string variety; // 厂家？
public:
    Fruit(float weight, int bestBeforeDate, std::string const& variety):
                weight(weight), bestBeforeDate(bestBeforeDate), variety(variety) {}
    bool isFitForSale() const { return bestBeforeDate > 3;}
    void print() const override{
        std::cout << "variety: " << variety << " weight: " << weight
        << " bestBeforeDate: " << bestBeforeDate << std::endl;
    }
};


class Apple : public Fruit {
protected:
    float redRatio;
public:
    Apple(float weight, int bestBeforeDate, std::string const& variety, float redRatio = 0.):
                        Fruit(weight, bestBeforeDate, variety), redRatio(redRatio) {}
};


class RedApple : public Apple {
public:
    RedApple(float weight, int bestBeforeDate, std::string const& variety, float redRatio):
                            Apple(weight, bestBeforeDate, variety, redRatio) {}
    bool isPremium() override { return weight > 90. && redRatio > 0.75;}
};


class MixedApple : public Apple {
public:
    MixedApple(float weight, int bestBeforeDate, std::string const& variety, float redRatio):
            Apple(weight, bestBeforeDate, variety, redRatio) {}
    bool isPremium() override { return weight > 90. && redRatio > 0.5;}
};


class Pear : public Fruit {
protected:
    bool intactStalk;
public:
    Pear(float weight, int bestBeforeDate, std::string const& variety, bool intactStalk = true):
                        Fruit(weight, bestBeforeDate, variety), intactStalk(intactStalk) {}
    bool isPremium() override { return weight > 130 && intactStalk;}
};


template<typename T, int maxSize>
class Basket : public Printable {
private:
    std::set<T*> items;
public:
    Basket() = default;

    ~Basket() {
        for (auto const& item : items) { delete item; }
    }
    void add(T* item) {
        if (!isFull()) { items.insert(item); }
    }

    void print() const override {
        for (auto const& item : items) { item->print(); }
    }

    bool isEmpty() { return items.empty();}

    bool isFull() { return items.size() == maxSize;}

    T* popFirst() {
        if (!isEmpty()) {
            auto item = *items.begin();
            items.erase(items.begin());
            return item;
        }
        return nullptr;
    }
};



#endif //OOP2019_V2_ANSWER2_H
