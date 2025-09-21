E-commerce_Management_System
## Overview

This project is a **Shopee E-commerce Product Management System** implemented in C++ using Object-Oriented Programming (OOP) principles.  
It simulates managing products, shopping carts, orders, and invoices while demonstrating real-world e-commerce operations.

The program provides:
- A **Shopping Cart** for adding/removing products and applying discounts.  
- An **Order System** to confirm purchases.  
- An **Invoice System** to calculate totals and shipping fees.  
- A **Shopee Manager** to maintain all products and orders.  

The goal of this project is to apply **encapsulation, inheritance, polymorphism, operator overloading, abstract classes, templates**, and simulate a real-world online shopping system.

---

## Build & Run Instruction

### On Linux/macOS/WSL
```bash
g++ main.cpp -o main
./main
```
## On Windows (MinGW++)
```bash
g++ main.cpp -o main.exe
.\main.exe
```
## AI Disclosure

This project was built with the assistance of ChatGPT for:
  - Brainstorming OOA steps, UML class/sequence diagrams, and operator overloading design.
  - Debugging issues with templates (InventoryList<T>) and abstract classes (Discountable).
  - Generating extra test cases for ShoppingCart, Order, and Invoice.
 All final implementation decisions, code integration, and testing were done manually by the developer.

## Product Management
## Base class: Product.

  - Derived class: ElectricProduct with warranty support.
  - Attributes: ID, name, category, weight, price, stock.
  - Methods: display info, update stock, reduce stock, apply discount.
  - Operator overloading:
      + == → compare weights.
      + < → compare prices.
## Shopping Cart
  - Uses template class InventoryList<T> to store products.
  - Supports:
    + += → add product to cart.
    + -= → remove product from cart.
  - Applies discounts to cart total.
  - Displays cart contents and calculates total.
## Orders
  - Created during checkout.
  - Stores: Order ID, items, total.
  - Displays order details.
## Invoices
  - Generated after an order.
  - Calculates grand total with shipping fee.
  - Displays detailed invoice.
## Shopee Management
  - Stores all products and orders.
  - Provides methods to:
    + Add and display products.
    + Create and manage orders.
    + Display all existing orders.
## Reflection

Through this project, I learned how to:
  - Apply OOP concepts to a practical online shopping system.
  - Use abstract classes to enforce polymorphic behaviors (Discountable).
  - Implement template classes (InventoryList<T>) for generic product storage.
  - Apply operator overloading to make cart/product interactions natural.
  - Design UML diagrams (class and sequence) for documentation.
## Challenges

  - Handling stock reductions correctly during cart checkout.
  - Managing ownership of dynamically allocated Product objects.
  - Ensuring discount logic worked at both product-level and cart-level.
