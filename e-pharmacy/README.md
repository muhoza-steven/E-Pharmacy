# E-pharmacy application

Design, implementation, and deployment of the first version of e-pharmacy application.

A pharmaceutical company wants to digitize its business processes to fully take advantage of new technologies. Six
features:

1. User management
2. Product catalog
3. Prescription management
4. Order management
5. Analytics and reporting

## F1. User management (B)

- The application should allow users to register, create accounts, and subsequently manage their accounts
- Users should be able to log in securely using email/username and password
- User authentication and authorisation should be implemented to ensure access to the application

| Feature           | Description                                                                                                                       | Type of service (Front vs Back end) | Languages |
|-------------------|-----------------------------------------------------------------------------------------------------------------------------------|-------------------------------------|-----------|
| User registration | A user goes to the application and registers their account. After that the record is added to a file that can be read back later. | Both                                | Bash      |
| Account creation  | An admin would create an account for a less privileged user                                                                       | Both                                | Bash      |
| Logging in        | A user inputs their username and password, and gets access to the application                                                     | Front-end                           | Bash      |

## F2. Product catalog (M)

- A product is characterized by a unique code, name, description, price, dosage instructions, etc. + quantity available
in the pharmacy
- The application should have a comprehensive and up-to-date product catalog
- To ease product retrieval, the catalog should be searchable based on various criteria such as brand, category and name

| Feature          | Description                                                                                                                       | Type of service (Front vs Back end) | Languages  |
|------------------|-----------------------------------------------------------------------------------------------------------------------------------|-------------------------------------|------------|
| Adding a product | Using an interactive form/interface, input all the information needed to add a new product to the catalog along with the quantity | Both                                | C++        |
| Search a product | Given a certain number of criteria, search for a product and display the results to the user                                      | Front-end                           | C++        |


## F3. Prescription management (M)

- Users should be able to upload and manage their prescriptions
- Pharmacists should have access to view and process prescriptions

| Feature               | Description                                                                                                     | Type of service (Front vs Back end) | Languages |
|-----------------------|-----------------------------------------------------------------------------------------------------------------|-------------------------------------|-----------|
| Add a prescription    | A user fills in the details of medication, the quantity (dosage) in a form that is recorded to a file on disk   | Both                                | Java      |
| View prescriptions    | Pharmacists can view prescriptions that users have added                                                        | Front-end                           | Java      |
| Process prescriptions | Pharmacists can sell the medications on the prescriptions directly. The catalog needs to be updated after that. | Both                                | Java      |

## F4. Order management (A)

- Users should be able to add products to their shopping cart for purchase
- The application should provide a seamless checkout process
- Users should have the option to save favorite products or create a wishlist

| Feature                            | Description                                                                                                                                            | Type of service (Front vs Back end) | Languages |
|------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------|-----------|
| Add a product to the shopping cart | Users can pick products from the catalog, and in the limit of what is available, add them to their shopping cart                                       | Both                                | Python    |
| Complete the checkout process      | Users should get a confirmation of their orders with all the details and proceed with ordering. The catalog needs to be updated at the end of process. | Both                                | Python    |
| Create a wishlist                  | Users can combine multiple products from the catalog into a wishlist                                                                                   | Both                                | Python    |

## F5. Analytics and reporting (B)

- The system should collect and analyze data to generate various reports such as:
  - Report on current stock
  - Report on sales (on a certain period)
  - Top 10 products sold
  - Report by salesperson
  - Report on the prescription

| Feature                  | Description                                                                              | Type of service (Front vs Back end) | Languages |
|--------------------------|------------------------------------------------------------------------------------------|-------------------------------------|-----------|
| Report on current stock  | Which products does the pharmacy currently have and how many of them?                    | Front-end                           | Python    |
| Report on sales          | Query the list of products that were sold, their quantity, and the corresponding amounts | Front-end                           | Python    |
| Report by salesperson    | Query the sales performed by a specific agent                                            | Front-end                           | Python    |
| Report by customer       | Query the purchases of a customer (we can retrieve top n of those)                       | Front-end                           | Python    |
| Reports on prescriptions | Get details of how many prescriptions were validated                                     | Front-end                           | Python    |

## F6. Integration using service-oriented architecture

(This section is empty)

## Deliverables

| Time            | Features              | Expected deliverables                                     |
|-----------------|-----------------------|-----------------------------------------------------------|
| Day 1 - Day 4   | Design                | - Use case diagram<br/>- Class diagram<br/>- Architecture |
| Day 5 - Day 6   | F1+F2                 | Video demo/Code/Self assessment                           |
| Day 7 - Day 8   | F3+F4                 | Video demo/Code/Self assessment                           |
| Day 9 - Day 10  | F5                    | Video demo/Code/Self assessment                           |
| Day 11 - Day 12 | F6                    | Video demo/Code/Self assessment                           |
| Day 13 - Day 14 | Final report and demo | Final report and demo                                     |

## Team composition

1. Rock Agon
2. Abdallah Bitunguramye
3. Odile Nzambazamariya
4. Clifford Onyonka
