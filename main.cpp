#include <iostream>

using namespace std;

class Dog;

class Cat;

class Animal {
public:
    virtual ~Animal() = default;

    virtual void Meeting(Animal* other) = 0;

    virtual void MeetingWith(Dog* dog) = 0;

    virtual void MeetingWith(Cat* cat) = 0;

};

//Тут я реализовал CRTP — Curiously recurring template pattern, в задание не входило, но надо же на чем то тренироваться.
template<typename T>
class MeetingOrganizer : public Animal {
public:
    void Meeting(Animal* other) override {
        other->MeetingWith(static_cast<T*>(this));
    }
};

class Dog : public MeetingOrganizer<Dog> {
public:
    void MeetingWith(Dog* dog) override {
        cout << "Woof Woof";
    }

    void MeetingWith(Cat* cat) override {
        cout << "Meow Bark";
    }
};

class Cat : public MeetingOrganizer<Cat> {
public:
    void MeetingWith(Dog* dog) override {
        cout << "Bark Meow";
    }

    void MeetingWith(Cat* cat) override {
        cout << "Purr Purr";
    }
};

void meeting(Animal* a, Animal* b) {
    a->Meeting(b);
}

int main() {
    Animal* a = new Dog();
    Animal* b = new Cat();
    meeting(a, b);
    return 0;
}
