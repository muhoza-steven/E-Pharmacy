cmake_minimum_required(VERSION 3.25)
project(E_pharmacy)

set(CMAKE_CXX_STANDARD 14)

add_executable(E_pharmacy
        product_catalog/FileHandler.cpp product_catalog/FileHandler.h
        product_catalog/Product.cpp product_catalog/Product.h
        product_catalog/ProductManager.cpp product_catalog/ProductManager.h
        product_catalog/SearchProduct.cpp product_catalog/SearchProduct.h
        product_catalog/main.cpp)
