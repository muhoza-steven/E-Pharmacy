#ifndef E_PHARMACY_PRODUCT_H
#define E_PHARMACY_PRODUCT_H

#include <iostream>

using namespace std;

class Product {
    int quantity;
    string name;
    string brand;
    string description;
    string code;
    float price;
    string dosageInstruction;
    string category;
    bool requiresPrescription;

public:
    string getCode() const;

    void setName(const string &text);

    string getName() const;

    void setBrand(const string &text);

    string getBrand() const;

    void setDescription(const string &text);

    string getDescription() const;

    void setDosageInstructions(const string &text);

    string getDosageInstruction() const;

    void setCategory(const string &text);

    string getCategory() const;

    void setQuantity(const int &num);

    int getQuantity() const;

    void setPrice(const float &num);

    float getPrice() const;

    void setRequiresPrescription(const bool &require);

    bool getRequiresPrescription() const;

    static string generateUniqueCode();

    static string promptTextField(const string &promptText);

    static float promptNumberField(const string &promptText);

    static bool promptRequirePrescription();

    void createProduct();

    string toJson() const;

    void productFromJson(const string &txt);
};

#endif //E_PHARMACY_PRODUCT_H
