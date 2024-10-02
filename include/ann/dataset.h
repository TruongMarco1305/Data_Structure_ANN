/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/*
 * File:   dataset.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 3:59 PM
 */

#ifndef DATASET_H
#define DATASET_H
#include "ann/xtensor_lib.h"
using namespace std;

template <typename DType, typename LType>
class DataLabel
{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;

public:
    DataLabel(xt::xarray<DType> data, xt::xarray<LType> label) : data(data), label(label)
    {
    }
    xt::xarray<DType> getData() const { return data; }
    xt::xarray<LType> getLabel() const { return label; }
};

template <typename DType, typename LType>
class Batch
{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;

public:
    Batch(xt::xarray<DType> data, xt::xarray<LType> label) : data(data), label(label)
    {
    }
    virtual ~Batch() {}
    xt::xarray<DType> &getData() { return data; }
    xt::xarray<LType> &getLabel() { return label; }
};

template <typename DType, typename LType>
class Dataset
{
private:
public:
    Dataset() {};
    virtual ~Dataset() {};

    virtual int len() = 0;
    virtual DataLabel<DType, LType> getitem(int index) = 0;
    virtual xt::svector<unsigned long> get_data_shape() = 0;
    virtual xt::svector<unsigned long> get_label_shape() = 0;
};

//////////////////////////////////////////////////////////////////////
template <typename DType, typename LType>
class TensorDataset : public Dataset<DType, LType>
{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;
    xt::svector<unsigned long> data_shape, label_shape;

public:
    /* TensorDataset:
     * need to initialize:
     * 1. data, label;
     * 2. data_shape, label_shape
     */
    TensorDataset(xt::xarray<DType> data, xt::xarray<LType> label)
    {
        /* TODO: your code is here for the initialization
         */
        this->data = data;
        this->label = label;
        auto auto_shape = this->data.shape();
        xt::svector<unsigned long> dataShape(auto_shape.begin(), auto_shape.end());
        this->data_shape = dataShape;
        auto_shape = this->label.shape();
        xt::svector<unsigned long> labelShape(auto_shape.begin(), auto_shape.end());
        this->label_shape = labelShape;
    }
    /* len():
     *  return the size of dimension 0
     */
    int len()
    {
        /* TODO: your code is here to return the dataset's length
         */
        return this->data_shape[0];
    }

    /* getitem:
     * return the data item (of type: DataLabel) that is specified by index
     */
    DataLabel<DType, LType> getitem(int index)
    {
        /* TODO: your code is here
         */
        if (index < 0 || index >= this->len())
            throw out_of_range("Index is out of range!");

        auto data_slice = xt::view(this->data,index,xt::all());
        auto label_slice = xt::view(this->label,index,xt::all());

        if(this->label_shape.size() == 0 && this->data_shape.size() == 0){
            return {this->data,this->label};
        } else {
            if(this->label_shape.size() == 0) return {data_slice,this->label};
            if(this->data_shape.size() == 0) return {this->data,label_slice};
        }
        return {data_slice, label_slice};
    }

    xt::svector<unsigned long> get_data_shape()
    {
        /* TODO: your code is here to return data_shape
         */
        if(this->data_shape.size() == 0) return {};
        return this->data_shape;
    }
    xt::svector<unsigned long> get_label_shape()
    {
        /* TODO: your code is here to return label_shape
         */
        if(this->label_shape.size() == 0) return {};
        return this->label_shape;
    }
};

#endif /* DATASET_H */
