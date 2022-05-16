#pragma once
#include <string>

/* Implemented two simple vector class which has an iterator inside.
   The vector enlarges its size by 50% if boundry is reached. 
   Since template is not allowed, two vector classes generally
   look similar */ 

class Bean {
    std::string name = "Unknown"; 

public: 
    /* constructor, rule of 3 */ 
    Bean(std::string const& name = "Unknown"): name(name) {}  
    Bean& operator=(Bean const& otherBean) {
        this->name = otherBean.name;
        return *this;
    } 
    Bean(Bean const& otherBean) { *this = otherBean; }
    ~Bean() = default;

    std::string const& getName() const;
};


class Ingredient {
    Bean bean;
    /* I think size_t is better for amount,
       but using size_t results in compiler warning */
    int amount = 0;

public:
    /* constructor, rule of 3 */
    Ingredient(Bean const& bean, int const amount): bean(bean), amount(amount) {}
    Ingredient() = default;
    Ingredient& operator= (Ingredient const& otherIngredient) {
        this->bean = otherIngredient.bean;
        this->amount = otherIngredient.amount;
        return *this;
    }
    Ingredient(Ingredient const& otherIngredient) { *this = otherIngredient; }
    ~Ingredient() = default;

    Bean const& getBean() const;
    int getAmount() const;
    void setAmount(int newAmount);
};


class EventValue {
    long value = 0;

public: 
    /* cosntructor and  The rule of 3 */
    EventValue(long const value = 0): value(value) {}
    EventValue& operator= (EventValue const& otherEventValue) {
        this->value = otherEventValue.value;
        return *this;
    }
    EventValue(EventValue const& otherEventValue) { *this = otherEventValue; }
    ~EventValue() = default;

    long const& getValue() const;
    void setValue(long newValue);
};


class Event {
    std::string type = "Unknown";
    long timestamp = 0;
    EventValue* eventValue = nullptr; 

public:
    /* constructor and the rule of 3 */
    Event() = default;
    Event(std::string const type, long const timestamp, EventValue* eventValue = nullptr): 
        type(type), timestamp(timestamp), eventValue(eventValue) {}
    Event& operator= (Event const& otherEvent) {
        this->type = otherEvent.type;
        this->timestamp = otherEvent.timestamp;
            delete eventValue;
            this->eventValue = nullptr;
        if (otherEvent.eventValue != NULL) {
            this->eventValue = new EventValue(otherEvent.eventValue->getValue()); 
        }
        return *this;
    }
    Event(Event const& otherEvent) { *this = otherEvent; }
    ~Event() { delete eventValue; }

    std::string const& getType() const; 
    long getTimestamp() const; 
    EventValue* getValue() const;
    bool hasValue() const; 
};


/* bonus marks :-) */
class IngredientVector {
private: 
    Ingredient* data = nullptr;
    size_t occupancy = 0;
    size_t capacity = 2; 
    /* allocate a new heap area with copy/move of previous elements */
    void reNew(size_t newCapacity); 

public: 
    /* iterator referenced and imitated this article "Writing a custom iterator in modern C++"
       https://internalpointers.com/post/writing-custom-iterators-modern-cpp */
    struct Iterator {
    private: 
        Ingredient* IngredientPtr;

    public:
        /* tags */
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Ingredient;
        using pointer           = Ingredient*; 
        using reference         = Ingredient&; 
        /* iterator constructor*/
        Iterator(Ingredient* ptr) : IngredientPtr(ptr) {}
        /* operator overloading to make it behave like a common iterator */
        Ingredient& operator*() const { return *IngredientPtr; }
        Ingredient* operator->() { return IngredientPtr; }
        Iterator& operator++() { IngredientPtr++; return *this; }  
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (Iterator const& a, Iterator const& b) { return a.IngredientPtr == b.IngredientPtr; };
        friend bool operator!= (Iterator const& a, Iterator const& b) { return a.IngredientPtr != b.IngredientPtr; };     
    };
 
    /* constructor and rule of 3 */
    IngredientVector() { reNew(capacity); }
    IngredientVector& operator= (IngredientVector const& otherVector) {
        this->occupancy = otherVector.occupancy;
        this->reNew(otherVector.capacity);
        for (size_t i = 0; i < occupancy; i++) {
            data[i] = otherVector.data[i];
        }
        return *this;
    } 
    IngredientVector(IngredientVector const& otherVector) { *this = otherVector; }
    ~IngredientVector() { delete [] data; }
    
    Iterator begin() const;
    Iterator end() const;
    /* copy and move, make it more efficient if possible */
    void push_back(Ingredient const& ingredient);
    void push_back(Ingredient&& ingredient);
    size_t size() const;
    void remove(size_t index);

    Ingredient const& operator[](size_t i) const {return data[i];}
    Ingredient& operator[](size_t i) {return data[i];}
};


/* bonus marks :-) */
class EventVector {
private: 
    Event* data = nullptr;
    size_t occupancy = 0;
    size_t capacity = 2;
    /* allocate a new heap area with copy of previous elements */
    void reNew(size_t newCapacity);

public: 
    /* iterator referenced and imitated this article "Writing a custom iterator in modern C++"
       https://internalpointers.com/post/writing-custom-iterators-modern-cpp */
    struct Iterator {
    private: 
        Event* EventPtr;

    public:
        /* tags */
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Event;
        using pointer           = Event*;  
        using reference         = Event&;  
        /* iterator constructor*/
        Iterator(Event* ptr) : EventPtr(ptr) {}
        /* operator overloading to make it behave like a common iterator */
        Event& operator*() const { return *EventPtr; }
        Event* operator->() { return EventPtr; }
        Iterator& operator++() { EventPtr++; return *this; }  
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (Iterator const& a, Iterator const& b) { return a.EventPtr == b.EventPtr; };
        friend bool operator!= (Iterator const& a, Iterator const& b) { return a.EventPtr != b.EventPtr; };     
    };
 
    /* constructor and rule of 3 */
    EventVector() { reNew(capacity); }
    EventVector& operator= (EventVector const& otherVector) {
        this->occupancy = otherVector.occupancy;
        this->reNew(otherVector.capacity);
        for (size_t i = 0; i < occupancy; i++) {
            data[i] = otherVector.data[i];
        }
        return *this;
    } 
    EventVector(EventVector const& otherVector) { *this = otherVector; }
    ~EventVector() { delete [] data; }
    
    Iterator begin() const ;
    Iterator end() const ;
    /* copy and move, make it more efficient if possible */
    void push_back(Event const& event) ;
    void push_back(Event&& event);
    size_t size() const ;
    void remove(size_t index);

    Event const& operator[](size_t i) const {return data[i];}
    Event& operator[](size_t i) {return data[i];}
};


class Roast {
    long timestamp = 0;
    IngredientVector ingredients;
    EventVector events;
public: 
    /* constructor and the rule of 3 */
    Roast(long timestamp): timestamp(timestamp) {}
    Roast& operator=(const Roast& otherRoast) {
        this->timestamp = otherRoast.timestamp;
        this->ingredients = otherRoast.ingredients;
        this->events = otherRoast.events;
        return *this;
    }
    Roast(const Roast& otherRoast) { *this = otherRoast; }
    ~Roast() = default;

    long const& getTimestamp() const; 

    Ingredient const& getIngredient(size_t i) const;
    Ingredient& getIngredient(size_t i);
    size_t getIngredientsCount() const; 

    /* get the ith event in event list */
    Event const& getEvent(size_t i) const;
    Event& getEvent(size_t i);
    size_t getEventCount() const;
    Event const& getEventByTimestamp(long timestamp) const; 
    Event& getEventByTimestamp(long timestamp); 

    void addIngredient(Ingredient const& ingredient); 
    void removeIngredientByBeanName(std::string const& beanName); 

    void addEvent(Event const& event); 
    void removeEventByTimestamp(long const& oldEventTimestamp);
};