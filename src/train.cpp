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
    }
    else {
        Car* last = first->prev;
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
    bool initialLight = first->light;
    int steps = 0;
    while (true) {
        moveForward(current);
        steps++;
        if (current->light == initialLight) {
            current->light = !initialLight;
            Car* backWalker = current;
            int backSteps = steps;
            for (int i = 0; i < backSteps; ++i) {
                moveBackward(backWalker);
            }
            if (backWalker->light != initialLight) {
                return backSteps;
            }
            current = backWalker;
            steps = 0;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
