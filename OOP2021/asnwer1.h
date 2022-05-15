//
// Created by 85378 on 5/6/2022.
//

#ifndef OOP2021_V2_ASNWER1_H
#define OOP2021_V2_ASNWER1_H

#include <string>
#include <list>

class Client;
class Agent;
class Property;
class Appointment;
class DB;


class Agent {
public:
    int const phoneNumber; // key
    std::string const name;

    Agent(int const phoneNumber, std::string const& name) : phoneNumber(phoneNumber), name(name) {}

    bool operator==(Agent const &other) const {
        return phoneNumber == other.phoneNumber;
    }

};

class Client {
public:
    int const phoneNumber; // key

    Client(int const phoneNumber) : phoneNumber(phoneNumber) {}

    bool operator==(Client const& other) const {
        return phoneNumber == other.phoneNumber;
    }
};

class Property {
public:
    double const latitude;
    double const longitude;

    Property(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

    bool operator==(Property const& other) const {
        return latitude == other.latitude && longitude == other.longitude;
    }
};

class Appointment {
private:
    Agent* agent;
    Client*  client;
    Property*  property;
    DB* db;

public:
    int time; // key

    int getTime() const {
        return time;
    }

    Agent const& getAgent() const {
        return *agent;
    }

    Client const& getClient() const {
        return *client;
    }

    Property const& getProperty() const {
        return *property;
    }

    Appointment(int time, Agent* agent, Client* client, Property* property, DB* db) : time(time), agent(agent), client(client), property(property),  db(db) {}

    Appointment& cancel();

};



class DB {
    std::list<Appointment> db;
    std::list<Agent> agents;
    std::list<Property> properties;
    std::list<Client> clients;
public:
    Appointment& makeAppointment(Agent& a, Property& p, Client& v, int time) {
        db.push_back(*new Appointment(time, &a, &v, &p, this));
        return db.back();
    }
    bool clientIsAvailable(Client const& client, int time) {
        for (auto& a : db) {
            if (a.getClient() == client && a.getTime() == time) {
                return false;
            }
        }
        return true;
    }
    bool agentIsAvailable(Agent const& agent, int time) {
        for (auto& a : db) {
            if (a.getAgent() == agent && a.getTime() == time) {
                return false;
            }
        }
        return true;
    }
    bool propertyIsAvailable(Property const& property, int time) {
        for (auto& a : db) {
            if (a.getProperty() == property && a.getTime() == time) {
                return false;
            }
        }
        return true;
    }
    Property& getProperty(int latitude, int longitude) {
        for (auto& p : properties) {
            if (p.latitude == latitude && p.longitude == longitude) {
                return p;
            }
        }
        properties.push_back( *new Property(latitude, longitude));
        return properties.back();
    }
    Agent& getAgent(int phoneNumber, std::string name) {
        for (auto& a : agents) {
            if (a.phoneNumber == phoneNumber && a.name == name) {
                return a;
            }
        }
        agents.push_back( *new Agent(phoneNumber, name));
        return agents.back();
    }
    Client& getClient(int phoneNumber) {
        for (auto& c : clients) {
            if (c.phoneNumber == phoneNumber) {
                return c;
            }
        }
        clients.push_back( *new Client(phoneNumber));
        return clients.back();
    }

    void allocateNewTime(Appointment* appointment) {
        int newTime = 0;
        while (!clientIsAvailable(appointment->getClient(), newTime) ||
               !agentIsAvailable(appointment->getAgent(), newTime) ||
               !propertyIsAvailable(appointment->getProperty(), newTime)) {
            newTime++;
        }
        appointment->time = newTime;
    }
};

Appointment &Appointment::cancel() {
    db->allocateNewTime(this);
    return *this;
}


int now() { return 0; }




#endif //OOP2021_V2_ASNWER1_H
