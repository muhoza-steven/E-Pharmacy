#include "fileHandler.h"
#include "searchProduct.h"

SearchProduct::SearchProduct(FileHandler fHandler) : fHandler(std::move(fHandler)) {
}

string SearchProduct::to_lowercase(const string &text) {
    string lowercase_text;
    for (char c: text) {
        lowercase_text += char(tolower(c));
    }
    return lowercase_text;
}

vector<Product> SearchProduct::searchByName(const string &name) const {
    vector<Product> foundProducts;
    string lowercaseName = to_lowercase(name);

    vector<Product> productList = fHandler.readJsonFile();

    for (const auto &product: productList) {
        string lowercaseProductName = to_lowercase(product.getName());
        if (lowercaseProductName.find(lowercaseName) != string::npos) {
            foundProducts.push_back(product);
        }
    }

    return foundProducts;

}

vector<Product> SearchProduct::searchByCategory(const string &category) const {
    vector<Product> foundProducts;
    string lowercaseCategory = to_lowercase(category);

    vector<Product> productList = fHandler.readJsonFile();

    for (const auto &product: productList) {
        string lowercaseProductCategory = to_lowercase(product.getCategory());
        if (lowercaseProductCategory.find(lowercaseCategory) != string::npos) {
            foundProducts.push_back(product);
        }
    }
    return foundProducts;
}

vector<Product> SearchProduct::searchByBrand(const string &brand) const {
    vector<Product> foundProducts;
    string lowercaseBrand = to_lowercase(brand);

    vector<Product> productList = fHandler.readJsonFile();

    for (const auto &product: productList) {
        string lowercaseProductBrand = to_lowercase(product.getBrand());
        if (lowercaseProductBrand.find(lowercaseBrand) != string::npos) {
            foundProducts.push_back(product);
        }
    }

    return foundProducts;
}

void SearchProduct::showSearchResult(const vector<Product> &plist, const string &sTxt) {
    if (plist.empty()) {
        cout << "No products found for \"" << sTxt << "\"." << endl;
        return;
    }

    cout << "Search results for \"" << sTxt << "\":" << endl;
    for (const auto &product: plist) {
        cout << "Product Code: " << Product::generateUniqueCode() << endl;
        cout << "Name: " << product.getName() << endl;
        cout << "Brand: " << product.getBrand() << endl;
        cout << "Description: " << product.getDescription() << endl;
        cout << "Category: " << product.getCategory() << endl;
        cout << "Dosage Instruction: " << product.getDosageInstruction() << endl;
        cout << "Price: " << product.getPrice() << endl;
        cout << "Quantity: " << product.getQuantity() << endl;
        cout << "Requires Prescription: " << (product.getRequiresPrescription() ? "Yes" : "No") << endl;
        cout << "-----------------------" << endl;
    }

}
