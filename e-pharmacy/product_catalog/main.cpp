#include <iostream>

#include "productManager.h"
#include "searchProduct.h"
#include "fileHandler.h"

using namespace std;

int main() {
    string productsFileName = "./products.json";
    ProductManager productManager;
    SearchProduct searchProduct((FileHandler(productsFileName)));
    int choice;
    string searchText;

    while (true) {
        choice = ProductManager::getMenu();

        switch (choice) {
            case 1:
                productManager.addProduct(productsFileName);
                break;
            case 2:
                cout << "Enter the product name to search: ";
                getline(cin, searchText);
                SearchProduct::showSearchResult(searchProduct.searchByName(searchText), searchText);
                break;
            case 3:
                cout << "Enter the product category to search: ";
                getline(cin, searchText);
                SearchProduct::showSearchResult(searchProduct.searchByCategory(searchText), searchText);
                break;
            case 4:
                cout << "Enter the product brand to search: ";
                getline(cin, searchText);
                SearchProduct::showSearchResult(searchProduct.searchByBrand(searchText), searchText);
                break;
            case 5:
                productManager.updateProduct(productsFileName);
                break;
            case 6:
                ProductManager::deleteProduct(productsFileName);
                break;
            case 7:
                cout << "Exiting the Product Catalog..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
