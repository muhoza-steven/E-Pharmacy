#include <vector>
#include <fstream>

#include "product.h"
#include "fileHandler.h"

using namespace std;


FileHandler::FileHandler(const string &filename) {
    if (filename.empty()) {
        throw invalid_argument("Filename is an empty string");
    }

    this->filename = filename;
}

vector<Product> FileHandler::readJsonFile() const {
    vector<Product> products;
    vector<string> lines;
    string line;
    Product product;
    ifstream file(this->filename);

    while (getline(file, line)) {
        lines.push_back(line);
        if (line.substr(0, 1) == "{") {
            product.productFromJson(line);
            products.push_back(product);
        }
    }

    file.close();

    return products;
}

void FileHandler::saveToJsonFile(const Product &product) const {
    vector<Product> products = this->readJsonFile();
    ofstream file(this->filename);

    products.push_back(product);

    file << "[" << endl;
    for (int i = 0; i < products.size(); i++) {
        file << products.at(i).toJson() << (i < products.size() - 1 ? "," : "") << endl;
    }
    file << "]" << endl;

    file.close();
}

void FileHandler::saveToJsonFileMultiple(const vector<Product> &products) const {
    ofstream file(this->filename);

    file << "[" << endl;
    for (int i = 0; i < products.size(); i++) {
        file << products.at(i).toJson() << (i < products.size() - 1 ? "," : "") << endl;
    }
    file << "]" << endl;

    file.close();
}
