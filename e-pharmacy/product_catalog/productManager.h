#ifndef E_PHARMACY_PRODUCTMANAGER_H
#define E_PHARMACY_PRODUCTMANAGER_H

#include "product.h"

class ProductManager {
    Product product;

public:
    static int getMenu();

    static int getUpdateMenu();

    void addProduct(const string &filename);

    void updateProduct(const string &filename);

    static void deleteProduct(const string &filename);
};

#endif //E_PHARMACY_PRODUCTMANAGER_H
