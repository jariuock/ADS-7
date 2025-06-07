// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
    if (!first) return;
    Car* current = first->next;
    while (current != first) {
        Car* next = current->next;
        delete current;
        current = next;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* newCar = new Car{ light, nullptr, nullptr };
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else 
    { Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

void Train::moveForward(Car*& current) {
    current = current->next;
    countOp++;
}

void Train::moveBackward(Car*& current) {
    current = current->prev;
    countOp++;
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Car* current = first;
    bool first_light = first->light;
    int steps = 1;
    current = current->next;
    countOp++;
    while (current != first) {
        steps++;
        if (current->light != first_light) {
            return steps - 1;
        }
        current = current->next;
        countOp++;
    }
    return steps;
}


int Train::getOpCount() {
    return countOp;
}
