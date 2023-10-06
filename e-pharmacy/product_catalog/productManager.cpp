#include <algorithm>

#include "product.h"
#include "fileHandler.h"
#include "productManager.h"

int ProductManager::getMenu() {
    int choice;
    cout << "========== Product Manager ==========" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Search Product By Name" << endl;
    cout << "3. Search Product By Category" << endl;
    cout << "4. Search Product By Brand" << endl;
    cout << "5. Update Product" << endl;
    cout << "6. Delete Product" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

int ProductManager::getUpdateMenu() {
    int choice;
    cout << "========== Update product ==========" << endl;
    cout << "Choose the attribute to update" << endl;
    cout << "1. Name" << endl;
    cout << "2. Brand" << endl;
    cout << "3. Description" << endl;
    cout << "4. Dosage instructions" << endl;
    cout << "5. Price" << endl;
    cout << "6. Quantity" << endl;
    cout << "7. Category" << endl;
    cout << "8. Requires prescription" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

void ProductManager::addProduct(const string &filename) {
    product.createProduct();
    FileHandler fHandler(filename);
    fHandler.saveToJsonFile(product);
    cout << "Product added successfully!" << endl;
}

void ProductManager::updateProduct(const string &filename) {
    string productCode;
    cout << "Enter the product code to update: ";
    getline(cin, productCode);

    FileHandler fHandler(filename);
    vector<Product> productList = fHandler.readJsonFile();
    vector<Product> newProductList;

    for (Product p : productList) {
        if (p.getCode() == productCode) {
            int choice = this->getUpdateMenu();
            string updatedAttribute;
            bool toExit = false;

            while (!toExit) {
                switch (choice) {
                    case 1:
                        cout << "Enter new name: ";
                        getline(cin, updatedAttribute);
                        p.setName(updatedAttribute);
                        toExit = true;
                        break;
                    case 2:
                        cout << "Enter new brand: ";
                        getline(cin, updatedAttribute);
                        p.setBrand(updatedAttribute);
                        toExit = true;
                        break;
                    case 3:
                        cout << "Enter new description: ";
                        getline(cin, updatedAttribute);
                        p.setDescription(updatedAttribute);
                        toExit = true;
                        break;
                    case 4:
                        cout << "Enter new dosage instructions: ";
                        getline(cin, updatedAttribute);
                        p.setDosageInstructions(updatedAttribute);
                        toExit = true;
                        break;
                    case 5:
                        cout << "Enter new price: ";
                        getline(cin, updatedAttribute);
                        p.setPrice(stof(updatedAttribute));
                        toExit = true;
                        break;
                    case 6:
                        cout << "Enter new quantity: ";
                        getline(cin, updatedAttribute);
                        p.setQuantity(stoi(updatedAttribute));
                        toExit = true;
                        break;
                    case 7:
                        cout << "Enter new category: ";
                        getline(cin, updatedAttribute);
                        p.setCategory(updatedAttribute);
                        toExit = true;
                        break;
                    case 8:
                        cout << "Requires prescription? 1 for yes, 0 for no: ";
                        getline(cin, updatedAttribute);
                        p.setRequiresPrescription(updatedAttribute == "1");
                        toExit = true;
                        break;
                    default:
                        cout << "Wrong choice. Only [1-8] accepted.";
                        break;
                }
            }
        }
        newProductList.push_back(p);
    }

    fHandler.saveToJsonFileMultiple(newProductList);
    cout << "Product updated successfully!" << endl;
}

void ProductManager::deleteProduct(const string &filename) {
    string productCode;
    cout << "Enter the product code to delete: ";
    getline(cin, productCode);

    FileHandler fHandler(filename);
    vector<Product> productList = fHandler.readJsonFile();
    vector<Product> newProductList;

    for (const Product& p : productList) {
        if (p.getCode() != productCode) {
            newProductList.push_back(p);
        }
    }

    fHandler.saveToJsonFileMultiple(newProductList);
    cout << "Product deleted successfully!" << endl;
}
