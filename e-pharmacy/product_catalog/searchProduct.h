#ifndef E_PHARMACY_SEARCHPRODUCT_H
#define E_PHARMACY_SEARCHPRODUCT_H

#include <iostream>
#include <vector>

#include "product.h"
#include "fileHandler.h"

using namespace std;

class SearchProduct {
    FileHandler fHandler;

public:
    explicit SearchProduct(FileHandler fHandler);

    static string to_lowercase(const string &text);

    vector<Product> searchByName(const string &name) const;

    vector<Product> searchByCategory(const string &category) const;

    vector<Product> searchByBrand(const string &brand) const;

    static void showSearchResult(const vector<Product> &plist, const string &sTxt);
};

#endif //E_PHARMACY_SEARCHPRODUCT_H
