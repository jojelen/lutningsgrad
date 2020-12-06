#pragma once

#include <vector>

// Singleton class for interacting with the mnist data set. Use
// "download_example_data.sh" for downloading the data set. This class will look
// for the data in data/mnist directory.
class MnistDataSet {
    public:
        MnistDataSet(MnistDataSet const &) = delete;
        MnistDataSet& operator=(MnistDataSet const&) = delete;

        static MnistDataSet& instance() {
            static MnistDataSet mnist;

            return mnist;
        }

        void printNumber(size_t id);
        size_t getTrainSetSize() const;
        std::vector<char> getTrainX(size_t id) const;
        int getTrainY(size_t id) const;
    private:
        MnistDataSet();

        void loadData();

        struct DataSet {
            std::vector<char> data;
            std::vector<int> labels;
            int rows;
            int cols;
            size_t size;
            size_t elementSize;
            size_t metaDataSize;
        };

        DataSet trainSet_;
};
