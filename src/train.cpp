// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
    if (!first) return;
    Car* current = first->next;
    while (current != first) {
        Car* nextCar = current->next;
        delete current;
        current = nextCar;
    }
    delete first;
    first = nullptr;
}

void Train::addCar(bool lightOn) {
    Car* newCar = new Car{ lightOn, nullptr, nullptr };
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Car* currentTrainCar = first;
    if (!currentTrainCar->light) {
        currentTrainCar->light = true;
    }
    int trainLength = 0;
    while (true) {
        int traversalSteps = 0;
        while (true) {
            currentTrainCar = currentTrainCar->next;
            traversalSteps++;
            countOp++;
            if (currentTrainCar->light || currentTrainCar == first) break;
        }
        if (currentTrainCar == first && !currentTrainCar->light) break;
        if (currentTrainCar->light) {
            currentTrainCar->light = false;
        }
        for (int i = 0; i < traversalSteps; i++) {
            currentTrainCar = currentTrainCar->prev;
            countOp++;
        }
        if (!currentTrainCar->light) {
            trainLength = traversalSteps;
            break;
        }
    }
    return trainLength;
}

int Train::getOpCount() {
    return countOp;
}
