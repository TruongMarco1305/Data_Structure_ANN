/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/*
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"

using namespace std;

template <typename DType, typename LType>
class DataLoader
{
public:
    class Iterator;

private:
    Dataset<DType, LType> *ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    xt::xarray<unsigned long> index_of_dataset;
    int total_sample;
    unsigned long num_batches;
    int m_seed;

    /*TODO: add more member variables to support the iteration*/
public:
    DataLoader(Dataset<DType, LType> *ptr_dataset,
               int batch_size,
               bool shuffle = true,
               bool drop_last = false, int seed=-1)
    {
        /*TODO: Add your code to do the initialization */
        this->ptr_dataset = ptr_dataset;
        this->batch_size = batch_size;
        this->shuffle = shuffle;
        this->drop_last = drop_last;
        this->total_sample = ptr_dataset->len();
        this->index_of_dataset = xt::arange<unsigned long>(0, this->total_sample);
        this->m_seed = seed;
        if (this->shuffle)
        {
            if (seed >= 0){
                xt::random::seed(this->m_seed);
                xt::random::shuffle(this->index_of_dataset);
            } else {
                xt::random::shuffle(this->index_of_dataset);
            }
        }
        this->num_batches = this->total_sample / this->batch_size;
    }
    virtual ~DataLoader()
    {
    }

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////

    Iterator begin()
    {
        return Iterator(this, 0);
    }

    Iterator end()
    {
        return Iterator(this, this->num_batches);
    }

    /*TODO: Add your code here to support iteration on batch*/
    class Iterator
    {
    private:
        DataLoader<DType, LType> *dataloader;
        int cursor;

    public:
        Iterator(DataLoader<DType, LType> *dataloader = 0, int index = 0)
        {
            this->dataloader = dataloader;
            this->cursor = index;
        }

        Iterator &operator=(const Iterator &iterator)
        {
            this->cursor = iterator.cursor;
            this->dataloader = iterator.dataloader;
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return this->cursor != other.cursor;
        }

        Iterator &operator++()
        {
            this->cursor++;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        Batch<DType, LType> operator*() const
        {
            unsigned long start = this->cursor * this->dataloader->batch_size;
            unsigned long current_size;
            unsigned long total = this->dataloader->num_batches;

            if (cursor < total - 1)
            {
                current_size = this->dataloader->batch_size;
            }
            else
            {
                if (!this->dataloader->drop_last)
                    current_size = this->dataloader->total_sample - start;
                else
                    current_size = this->dataloader->batch_size;
            }

            if (current_size == 0)
            {
                return Batch<DType, LType>(xt::xarray<DType>(), xt::xarray<LType>());
            }

            DataLabel<DType, LType> first = this->dataloader->ptr_dataset->getitem(this->dataloader->index_of_dataset(start));
            xt::svector<unsigned long> first_data_shape = first.getData().shape();
            xt::svector<unsigned long> first_label_shape = first.getLabel().shape();

            xt::svector<unsigned long> full_data_shape = {current_size};
            full_data_shape.insert(full_data_shape.end(), first_data_shape.begin(), first_data_shape.end());

            xt::svector<unsigned long> full_label_shape = {current_size};
            full_label_shape.insert(full_label_shape.end(), first_label_shape.begin(), first_label_shape.end());

            xt::xarray<DType> data = xt::empty<DType>(full_data_shape);
            xt::xarray<LType> label = xt::empty<LType>(full_label_shape);
            for (unsigned long i = 0; i < current_size; ++i)
            {
                unsigned long idx = this->dataloader->index_of_dataset[start + i];
                DataLabel<DType, LType> sample = this->dataloader->ptr_dataset->getitem(idx);

                xt::view(data, i) = sample.getData();

                xt::view(label, i) = sample.getLabel();
            }

            if (this->dataloader->ptr_dataset->get_label_shape().size() == 0)
            {
                return Batch<DType, LType>(data, xt::xarray<LType>());
            }
            else if (this->dataloader->ptr_dataset->get_data_shape().size() == 0)
            {
                return Batch<DType, LType>(xt::xarray<DType>(), label);
            }
            return Batch<DType, LType>(data, label);
        }
    };

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
};

#endif /* DATALOADER_H */
