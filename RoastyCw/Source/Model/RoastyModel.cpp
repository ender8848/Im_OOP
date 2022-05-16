#include "RoastyModel.hpp"
#include <string>
#include <algorithm>


/* ----Bean---- */
std::string const& Bean::getName() const { return name; }
/* ====Bean==== */



/* ----Ingredient---- */
Bean const& Ingredient::getBean() const {return bean;}

int Ingredient::getAmount() const {return amount;}

void Ingredient::setAmount(int newAmount) {amount = newAmount;}
/* ====Ingredient==== */



/* ----EventValue---- */
long const& EventValue::getValue() const {return value;}

void EventValue::setValue(long newValue) { value = newValue; }
/* ====EventValue==== */



/* ----Event---- */
std::string const& Event::getType() const { return type; }

long Event::getTimestamp() const { return timestamp; }

EventValue* Event::getValue() const { return eventValue; }

bool Event::hasValue() const {return eventValue != NULL;}
/* ====Event==== */



/* ----IngredientVector---- */
void IngredientVector::reNew(size_t newCapacity) {
    if (newCapacity < occupancy) {occupancy = newCapacity;}

    Ingredient* newData = new Ingredient[newCapacity];
    for (size_t i = 0; i < occupancy; i++) {newData[i] = std::move(data[i]);}
    delete [] data;
    data = newData;
    capacity = newCapacity;
}

IngredientVector::Iterator IngredientVector::begin() const { 
    return Iterator(&data[0]); 
}

IngredientVector::Iterator IngredientVector::end() const { 
    return Iterator(&data[occupancy]); 
} 

void IngredientVector::push_back(Ingredient const& ingredient) {
    if (occupancy >= capacity) {reNew(capacity + capacity/2);}
    data[occupancy++] = ingredient;
} 

void IngredientVector::push_back(Ingredient&& ingredient) {
    if (occupancy >= capacity) {reNew(capacity + capacity/2);}
    data[occupancy++] = std::move(ingredient);
}

size_t IngredientVector::size() const { return occupancy; }

void IngredientVector::remove(size_t index) {
    for (size_t i = index; i < occupancy-1; i++) {data[i] = data[i+1];}
    occupancy--;
}
/* ====IngredientVector==== */



/* ----EventVector---- */
void EventVector::reNew(size_t newCapacity) {
    if (newCapacity < occupancy) {occupancy = newCapacity;}

    Event* newData = new Event[newCapacity];
    for (size_t i = 0; i < occupancy; i++) {newData[i] = std::move(data[i]);}
    delete [] data;
    data = newData;
    capacity = newCapacity;
}

EventVector::Iterator EventVector::begin() const { 
    return Iterator(&data[0]); 
}

EventVector::Iterator EventVector::end() const { 
    return Iterator(&data[occupancy]); 
} 

void EventVector::push_back(Event const& event) {
    if (occupancy >= capacity) {reNew(capacity + capacity/2);}
    data[occupancy++] = event;
} 

void EventVector::push_back(Event&& event) {
    if (occupancy >= capacity) {reNew(capacity + capacity/2);}
    data[occupancy++] = std::move(event);
}

size_t EventVector::size() const { return occupancy; }

void EventVector::remove(size_t index) {
    for (size_t i = index; i < occupancy-1; i++) {data[i] = data[i+1];}
    occupancy--;
}
/* ====EventVector==== */



/* ----Roast---- */
long const& Roast::getTimestamp() const { return timestamp; }

Ingredient const& Roast::getIngredient(size_t i) const {
    auto ingredientFront = ingredients.begin();
    std::advance(ingredientFront, i);
    return *ingredientFront;
}

Ingredient& Roast::getIngredient(size_t i) {
    auto ingredientFront = ingredients.begin();
    std::advance(ingredientFront, i);
    return *ingredientFront;
}

size_t Roast::getIngredientsCount() const {
    return static_cast<size_t>(ingredients.size());
}

Event const& Roast::getEvent(size_t i) const {  
    auto eventFront = events.begin();
    std::advance(eventFront, i);
    return *eventFront;
} 

Event& Roast::getEvent(size_t i) {
    auto eventFront = events.begin();
    std::advance(eventFront, i);
    return *eventFront;
}

size_t Roast::getEventCount() const {
    return static_cast<size_t>(events.size());
}

Event const& Roast::getEventByTimestamp(long timestamp) const { 
    return *std::find_if(events.begin(), events.end(), [&timestamp](Event const& event) { 
        return event.getTimestamp() == timestamp; });
}

Event& Roast::getEventByTimestamp(long timestamp) { 
    return *std::find_if(events.begin(), events.end(), [&timestamp](Event const& event) { 
        return event.getTimestamp() == timestamp; });
}

void Roast::addIngredient(Ingredient const& ingredient) {
    ingredients.push_back(Ingredient(ingredient.getBean(), ingredient.getAmount()));
}

void Roast::removeIngredientByBeanName(std::string const& beanName) {
    for (size_t i = 0; i < ingredients.size(); i++) {
        if (ingredients[i].getBean().getName() == beanName) {
            ingredients.remove(i);
            break;
        } 
    }
}

void Roast::addEvent(Event const& event) { events.push_back(event); }

void Roast::removeEventByTimestamp(long const& oldEventTimestamp) {
    for (size_t i = 0; i < events.size(); i++) {
        if (events[i].getTimestamp() == oldEventTimestamp) {
            events.remove(i);
            break;
        } 
    }
}
/* ====Roast==== */