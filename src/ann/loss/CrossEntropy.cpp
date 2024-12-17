/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CrossEntropy.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"
#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction): ILossLayer(reduction){
    
}

CrossEntropy::CrossEntropy(const CrossEntropy& orig):
ILossLayer(orig){
}

CrossEntropy::~CrossEntropy() {
}

double CrossEntropy::forward(xt::xarray<double> X, xt::xarray<double> t){
    //YOUR CODE IS HERE
    this->m_aCached_Ypred = X;
    this->m_aYtarget = t;
    auto N = this->m_eReduction == REDUCE_MEAN ? X.shape(0) : 1;
    double norm = N;
    xt::xarray<double> log_y = xt::log(X + 1e-7);
    xt::xarray<double> loss_matrix = -1.0 * this->m_aYtarget * log_y;
    return xt::sum(loss_matrix)() / norm;
}
xt::xarray<double> CrossEntropy::backward() {
    //YOUR CODE IS HERE
    auto N = this->m_eReduction == REDUCE_MEAN ? this->m_aCached_Ypred.shape(0) : 1;
    double norm = N;
    xt::xarray<double> temp = this->m_aYtarget/(this->m_aCached_Ypred + 1e-7);
    return -temp / norm;
}