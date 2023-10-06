#ifndef E_PHARMACY_FILEHANDLER_H
#define E_PHARMACY_FILEHANDLER_H

#include <vector>

#include "product.h"

using namespace std;

class FileHandler {
    string filename;

public:
    explicit FileHandler(const string &filename);

    vector<Product> readJsonFile() const;

    void saveToJsonFile(const Product &product) const;

    void saveToJsonFileMultiple(const vector<Product> &products) const;
};

#endif //E_PHARMACY_FILEHANDLER_H
