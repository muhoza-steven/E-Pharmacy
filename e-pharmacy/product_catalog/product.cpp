#include <iostream>
#include <chrono>
#include <random>

#include "product.h"

using namespace std;
using namespace std::chrono;

void Product::setName(const string &text) {
    this->name = text;
}

void Product::setBrand(const string &text) {
    this->brand = text;
}

void Product::setDescription(const string &text) {
    this->description = text;
}

void Product::setDosageInstructions(const string &text) {
    this->dosageInstruction = text;
}

void Product::setCategory(const string &text) {
    this->category = text;
}

void Product::setQuantity(const int &num) {
    this->quantity = num;
}

void Product::setPrice(const float &num) {
    this->price = num;
}

void Product::setRequiresPrescription(const bool &require) {
    this->requiresPrescription = require;
}

string Product::getCode() const {
    return this->code;
}

string Product::getName() const {
    return this->name;
}

string Product::getBrand() const {
    return this->brand;
}

string Product::getDescription() const {
    return this->description;
}

string Product::getDosageInstruction() const {
    return this->dosageInstruction;
}

string Product::getCategory() const {
    return this->category;
}

int Product::getQuantity() const {
    return this->quantity;
}

float Product::getPrice() const {
    return this->price;
}

bool Product::getRequiresPrescription() const {
    return this->requiresPrescription;
}

string Product::generateUniqueCode() {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    string uniqueCode;
    auto now = system_clock::now();
    auto millis = duration_cast<milliseconds>(now.time_since_epoch());
    mt19937 generator(millis.count());
    uniform_int_distribution<int> distribution(0, 100000);

    for (int i = 0; i <= 10; i++) {
        size_t random_index = distribution(generator) % characters.length();
        uniqueCode += characters[random_index];
    }

    return uniqueCode;
}

string Product::promptTextField(const string &promptText) {
    string userInput;
    cout << promptText;
    getline(cin, userInput);
    return userInput;
}

float Product::promptNumberField(const string &promptText) {
    float userInput;
    cout << promptText;
    cin >> userInput;
    cin.ignore();
    return userInput;
}

bool Product::promptRequirePrescription() {
    int userInput = -1;

    while (true) {
        cout << "Does the product require a prescription? (1 for yes, 0 for no): ";
        cin >> userInput;
        cin.ignore();

        if (userInput < 0 || userInput > 1) {
            cout << "Only 0 and 1 allowed!";
        } else {
            break;
        }
    }

    return userInput == 1;
}

void Product::createProduct() {
    this->name = promptTextField("Enter Product Name: ");
    this->brand = promptTextField("Enter Product Brand: ");
    this->description = promptTextField("Enter Product Description: ");
    this->category = promptTextField("Enter Product Category: ");
    this->dosageInstruction = promptTextField("Enter Product Dosage Instruction: ");
    this->quantity = static_cast<int>(promptNumberField("Enter Product Quantity: "));
    this->price = promptNumberField("Enter Product Price: ");
    this->requiresPrescription = promptRequirePrescription();
    this->code = generateUniqueCode();
}

string Product::toJson() const {
    // The Output should look like:
    //{"code":"tgtwdNbCnwx","name":"name 1","brand":"br 2","description":"df","dosage_instruction":"dfg","price":123.000000,"quantity":13,"category":"des","requires_prescription":1}

    string productInJson = R"({"code":")" + this->code + "\",";
    productInJson += R"("name":")" + this->name + "\",";
    productInJson += R"("brand":")" + this->brand + "\",";
    productInJson += R"("description":")" + this->description + "\",";
    productInJson += R"("dosage_instruction":")" + this->dosageInstruction + "\",";
    productInJson += R"("price":)" + to_string(this->price) + ",";
    productInJson += R"("quantity":)" + to_string(this->quantity) + ",";
    productInJson += R"("category":")" + this->category + "\",";
    productInJson += R"("requires_prescription":)" + to_string(this->requiresPrescription) + "}";
    return productInJson;
}

void Product::productFromJson(const string &text) {
    // string is in the form below
    //{"code":"tgtwdNbCnwx","name":"name 1","brand":"br 2","description":"df","dosage_instruction":"dfg","price":123.000000,"quantity":13,"category":"des","requires_prescription":1}

    size_t code_pos = text.find(R"("code":")");
    size_t name_pos = text.find(R"("name":")");
    size_t brand_pos = text.find(R"("brand":")");
    size_t desc_pos = text.find(R"("description":")");
    size_t dosage_pos = text.find(R"("dosage_instruction":")");
    size_t price_pos = text.find(R"("price":)");
    size_t quantity_pos = text.find(R"("quantity":)");
    size_t category_pos = text.find(R"("category":")");
    size_t requires_prescription_pos = text.find(R"("requires_prescription":)");

    this->code = text.substr(code_pos + 8, text.find('\"', code_pos + 8) - (code_pos + 8));
    this->name = text.substr(name_pos + 8, text.find('\"', name_pos + 8) - (name_pos + 8));
    this->brand = text.substr(brand_pos + 9, text.find('\"', brand_pos + 9) - (brand_pos + 9));
    this->description = text.substr(desc_pos + 15, text.find('\"', desc_pos + 15) - (desc_pos + 15));
    this->dosageInstruction = text.substr(dosage_pos + 22, text.find('\"', dosage_pos + 22) - (dosage_pos + 22));
    this->price = stof(text.substr(price_pos + 8, text.find(',', price_pos + 8) - (price_pos + 8)));
    this->quantity = stoi(text.substr(quantity_pos + 11, text.find(',', quantity_pos + 11) - (quantity_pos + 11)));
    this->category = text.substr(category_pos + 12, text.find('\"', category_pos + 12) - (category_pos + 12));
    this->requiresPrescription = stoi(
            text.substr(requires_prescription_pos + 24, text.find('}', requires_prescription_pos + 24) - (requires_prescription_pos + 24))
    ) != 0;
}
