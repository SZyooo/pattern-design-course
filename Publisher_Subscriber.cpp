#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;


class Message
{
public:
    virtual ~Message(){}
    virtual string MSG() const= 0;
};

class Subscriber{
public:
    virtual ~Subscriber(){}
    virtual void Run(const Message& msg) = 0;
    virtual string Code() = 0;
};

class DayMSG: public Message
{
public:
    virtual string MSG() const{
        return string("Day");
    }
};
class NightMSG: public Message
{
public: 
    virtual string MSG() const
    {
        return string("Night");
    }
};

class Publisher{
public:
    virtual ~Publisher(){};
    virtual void Notify(const Message& msg){
        for(auto& sub:_subscribers)
        {
            sub->Run(msg);
        }
    }
    virtual void Subscribe(shared_ptr<Subscriber> sub){
        _subscribers.push_back(sub);
    }
    void Desubscribe(string& code)
    {
        auto it = _subscribers.begin();
        while(it!=_subscribers.end() && (*it)->Code()!=code)
        {
            ++it;
        }
        if(it!=_subscribers.end())
        {
            _subscribers.erase(it);
        }
    }
private:
    vector<shared_ptr<Subscriber>> _subscribers;
};


enum class Time{
    DAY,
    NIGHT
};

class Sensor: public Publisher{
public:
    void SetTime(Time time)
    {
        if(time == Time::DAY)
        {
            Notify(DayMSG());
        }
        else
        {
            Notify(NightMSG());
        }
    }
};
class Phone: public Subscriber{
public:
    Phone(string code,Time time = Time::DAY):PhoneCode(code),currentState(time){}
    virtual void Run(const Message& msg){
        if(msg.MSG() == string("Day"))
        {
            currentState = Time::DAY;
        }
        else if(msg.MSG() == string("Night"))
        {
            currentState = Time::NIGHT;
        }
    }
    void Show()
    {
        switch(currentState)
        {
            case Time::DAY:
            default:
                cout << "now is day mode" << endl;
                break;
            case Time::NIGHT:
                cout << "now is night mode" << endl;
        }
    }
    virtual string Code(){
        return PhoneCode;
    }
private:
    string PhoneCode;
    Time currentState;
};

int main()
{
    shared_ptr<Phone> myPhone(new Phone("IPhone"));
    Sensor lightSensor;
    lightSensor.Subscribe(myPhone);
    myPhone->Show();
    lightSensor.SetTime(Time::NIGHT);
    myPhone->Show();
}