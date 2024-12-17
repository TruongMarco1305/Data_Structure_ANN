/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Layer.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 10:54 AM
 */

#include "ann/Layer.h"

Layer::Layer() {
    /*TODO: Your code is here*/

}

Layer::Layer(const Layer& orig) {
    /*TODO: Your code is here*/ 
    this->is_training = orig.is_training;
    this->layer_idx = orig.layer_idx;
    this->name = orig.name;
}

Layer::~Layer() {
}

unsigned long long Layer::layer_idx =0;

