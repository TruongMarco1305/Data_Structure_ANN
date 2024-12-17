// /*
//  * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
//  * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
//  */

// /* 
//  * File:   Softmax.cpp
//  * Author: ltsach
//  * 
//  * Created on August 25, 2024, 2:46 PM
//  */

// #include "layer/Softmax.h"
// #include "ann/functions.h"
// #include "sformat/fmt_lib.h"
// #include <filesystem> //require C++17
// namespace fs = std::filesystem;

// Softmax::Softmax(int axis, string name): m_nAxis(axis) {
//     if(trim(name).size() != 0) m_sName = name;
//     else m_sName = "Softmax_" + to_string(++m_unLayer_idx);
// }

// Softmax::Softmax(const Softmax& orig) {
// }

// Softmax::~Softmax() {
// }

// xt::xarray<double> Softmax::forward(xt::xarray<double> X) {
//   // Todo CODE YOUR
//   // Compute exponentials
    // this->m_aCached_Y = softmax(X);
    // return this->m_aCached_Y;
//   xt::xarray<double> exp_X = xt::exp(X);

//   // Sum of exponentials along the specified axis
//   xt::xarray<double> sum_exp_X = xt::sum(exp_X, {m_nAxis}, xt::keep_dims);

//   // Compute softmax output
//   m_aCached_Y = exp_X / sum_exp_X;

//   return m_aCached_Y;
// }

// xt::xarray<double> Softmax::backward(xt::xarray<double> DY) {
//     //YOUR CODE IS HERE
    // xt::xarray<double> sum_DY_Y = xt::sum(DY * m_aCached_Y, {m_nAxis}, xt::keep_dims);

    // // Compute DX
    // xt::xarray<double> DX = m_aCached_Y * (DY - sum_DY_Y);

    // return DX;
// }

// string Softmax::get_desc(){
//     string desc = fmt::format("{:<10s}, {:<15s}: {:4d}",
//                     "Softmax", this->getname(), m_nAxis);
//     return desc;
// }

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Softmax.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:46 PM
 */

#include "layer/Softmax.h"
#include "ann/functions.h"
#include "sformat/fmt_lib.h"
#include <filesystem> //require C++17
namespace fs = std::filesystem;

Softmax::Softmax(int axis, string name): m_nAxis(axis) {
    if(trim(name).size() != 0) m_sName = name;
    else m_sName = "Softmax_" + to_string(++m_unLayer_idx);
}

Softmax::Softmax(const Softmax& orig) {
}

Softmax::~Softmax() {
}

xt::xarray<double> Softmax::forward(xt::xarray<double> X) {
  // Todo CODE YOUR
  this->m_aCached_Y = softmax(X);
  return this->m_aCached_Y;
}

xt::xarray<double> Softmax::backward(xt::xarray<double> DY) {
  // Todo CODE YOUR
//   // Compute dot product of DY and Y along the softmax axis
//   xt::xarray<double> sum_DY_Y = xt::sum(DY * m_aCached_Y, {m_nAxis}, xt::keep_dims);
//   // Compute DX
//   return m_aCached_Y * (DY - sum_DY_Y);

    // Compute outer product of y (m_aCached_Y) with itself: y ⊗ y^T
    xt::xarray<double> y_outer = xt::linalg::dot(m_aCached_Y,xt::transpose(m_aCached_Y));

    // Create diagonal matrix DIAG(y)
    xt::xarray<double> diag_y = xt::diag(m_aCached_Y);

    // Compute Jacobian: DIAG(y) - (y ⊗ y^T)
    xt::xarray<double> jacobian = diag_y - y_outer;

    // Compute ∆z by multiplying Jacobian with ∆y
    xt::xarray<double> dZ = xt::linalg::dot(jacobian, DY);

    return dZ;
}


string Softmax::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}: {:4d}",
                    "Softmax", this->getname(), m_nAxis);
    return desc;
}
