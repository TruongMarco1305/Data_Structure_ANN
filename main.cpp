#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "list/listheader.h"
#include "util/Point.h"

// #include "ann/funtions.h"
// #include "ann/xtensor_lib.h"
// #include "ann/dataset.h"
// #include "loader/dataloader.h"
#include "demo/list/DLinkedListDemo.h"
#include "demo/list/XArrayListDemo.h"
#include "demo/list/SLinkedListDemo.h"
#include "demo/sorting/BubbleSortDemo.h"
#include "demo/sorting/HeapSortDemo.h"
#include "demo/sorting/QuickSortDemo.h"
#include "demo/sorting/ShellSortDemo.h"
#include "demo/sorting/ListSortDemo.h"
#include "demo/list/SLinkedListDemo.h"
#include "demo/sorting/StraightInsertionSortDemo.h"
#include "demo/sorting/StraightSelectionSortDemo.h"

using namespace std;

int main(int argc, char** argv) {
    // case_data_wo_label_1();
    // case_data_wi_label_1();
    // case_batch_larger_nsamples();
    dlistDemo();
    xlistDemo();
    slistDemo();
    BuubleSortDemo1();
    HeapSortDemo1();
    straightSDemo1();
    straightSelDemo1();
    QuickSortDemo1();
    ShellSortDemo1();
    listSortDemo();
    return 0;
}

