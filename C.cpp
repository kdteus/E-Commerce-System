#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <map>
using namespace std;
#define ll long long

// ================= Abstract Class =================
class Discountable {
public:
    virtual ll applyDiscount(ll rate) = 0;
    virtual ~Discountable() {}
};

// ================= Base Class: Product =================
class Product : public Discountable {
protected:
    int id;
    string name;
    string category;
    ll weight;
    ll price;
    int stock;
public:
    Product(int pID, string pName, string pCategory, ll pWeight, ll pPrice, int pStock)
        : name(pName), id(pID), category(pCategory), weight(pWeight), price(pPrice), stock(pStock) {}
    virtual ~Product() {}

    // Display product information
    virtual void displayInfo() {
        cout << "[ID]: " << id << endl;
        cout << "[Name]: " << name << endl;
        cout << "[Category]: " << category << endl;
        cout << "[Weight]: " << weight << " g\n";
        cout << "[Price]: " << price << " VND\n";
        cout << "[Stock]: " << stock << endl;
    }

    // Apply discount based on percentage rate
    ll applyDiscount(ll rate) override {
        if (rate > 100 || rate < 0) {
            throw invalid_argument("Invalid rate!");
        }
        cout << "Apply discount successful!\n";
        return price * (100 - rate) / 100;
    }

    // Reduce stock
    virtual void reduceStock(int num) {
        if (num > 0 && stock >= num) {
            stock -= num;
            cout << "Reducing product " << name << " by " << num << " units\n";
        } else {
            throw invalid_argument("Invalid number!");
        }
    }

    // Update stock
    virtual void updateStock(int num) {
        if (num > 0) {
            stock += num;
            cout << "Restocking " << name << " by " << num << " units\n";
        } else {
            throw invalid_argument("Invalid number!");
        }
    }

    // Operator overloading == to compare weight
    bool operator==(Product& other) {
        return this->weight == other.weight;
    }

    // Operator overloading < to compare price
    bool operator<(Product& other) {
        return this->price < other.price;
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    ll getWeight() const { return weight; }
    ll getPrice() const { return price; }
    int getStock() const { return stock; }
};

// ================= Derived Class: ElectricProduct =================
class ElectricProduct : public Product {
protected:
    int warrantyMonths;
public:
    ElectricProduct(int pID, string pName, string pCategory, ll pWeight, ll pPrice, int pStock, int warranty)
        : Product(pID, pName, pCategory, pWeight, pPrice, pStock), warrantyMonths(warranty) {}

    // Override displayInfo
    void displayInfo() override {
        cout << "[ID]: " << id << endl;
        cout << "[Name]: " << name << endl;
        cout << "[Category]: " << category << endl;
        cout << "[Weight]: " << weight << " g\n";
        cout << "[Price]: " << price << " VND\n";
        cout << "[Stock]: " << stock << endl;
        cout << "[Warranty Months]: " << warrantyMonths << " months\n";
    }

    // Override updateStock
    void updateStock(int num) override {
        if (num > 0) {
            stock += num;
            cout << "[Electronics] Restocking " << name << " by " << num << " units\n";
        } else {
            throw invalid_argument("Invalid number!");
        }
    }

    // Override applyDiscount
    ll applyDiscount(ll rate) override {
        if (rate > 100 || rate < 0) {
            throw invalid_argument("Invalid rate!");
        }
        cout << "Apply discount successful!\n";
        return price * (100 - rate) / 100;
    }

    // Override reduceStock
    void reduceStock(int num) override {
        if (num > 0 && stock >= num) {
            stock -= num;
            cout << "[Electronics] Reducing product " << name << " by " << num << " units\n";
        } else {
            throw invalid_argument("Invalid number!");
        }
    }
};

// ================= Template Class: InventoryList =================
template<typename T>
class InventoryList {
private:
    vector<T> items;
public:
    void addItem(const T& item) {
        items.push_back(item);
    }

    void removeItem(const T& item) {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end()) items.erase(it);
    }

    Product* findItemByID(int id) {
        for (auto& item : items) {
            if (item->getId() == id) {
                item->displayInfo();
                return item;
            }
        }
        return nullptr;
    }

    void displayItem() const {
        cout << "=== Inventory (" << items.size() << " items) ===\n";
        for (auto& it : items) {
            it->displayInfo();
        }
    }

    // Inside InventoryList<T>
    const vector<T>& getAll() const { return items; }   // For const objects
    vector<T>& getAll() { return items; }               // For non-const objects

};

// ================= ShoppingCart =================
class ShoppingCart : public Discountable {
private:
    InventoryList<Product*> itemList;
    ll total;
public:
    ShoppingCart() : total(0) {}

    // Operator += to add product to cart
    ShoppingCart& operator+=(Product* p) {
        if (!p) return *this;
        if (p->getStock() <= 0) {
            cout << "Product " << p->getName() << " is out of stock!\n";
            return *this;
        }
        itemList.addItem(p);
        total += p->getPrice();
        p->reduceStock(1);
        return *this;
    }

    // Operator -= to remove product from cart
    ShoppingCart& operator-=(Product* p) {
        if (!p) return *this;
        itemList.removeItem(p);
        total -= p->getPrice();
        if (total < 0) total = 0;
        return *this;
    }

    // Apply discount to total cart
    ll applyDiscount(ll rate) override {
        if (rate > 100 || rate < 0) {
            throw invalid_argument("Invalid rate!");
        }
        cout << "Apply discount successful!\n";
        return total * (100 - rate) / 100;
    }

    // Display shopping cart content
    void displayCart() const {
        cout << "\n=== Shopping Cart ===" << endl;

        map<int, pair<Product*, int>> counts;
        for (auto p : itemList.getAll()) {
            counts[p->getId()].first = p;
            counts[p->getId()].second++;
        }

        int i = 1;
        for (auto& pair : counts) {
            Product* p = pair.second.first;
            int qty = pair.second.second;
            cout << i++ << ". " << p->getName()
                 << " x" << qty
                 << " | Price per unit: " << p->getPrice()
                 << " | Subtotal: " << p->getPrice() * qty
                 << endl;
        }
        cout << "Cart Total: " << fixed << setprecision(2) << (double)total << " VND\n";
    }

    double getTotal() const { return (double)total; }

    // Checkout -> return list of products and reset cart
    pair<vector<Product*>, ll> checkout() {
        vector<Product*> orderItems = itemList.getAll();
        ll orderTotal = total;
        itemList.getAll().clear();
        total = 0;
        return {orderItems, orderTotal};
    }
};

// ================= Order =================
class Order {
private:
    int orderID;
    vector<Product*> items;
    ll total;
public:
    Order(int _id, const vector<Product*>& _items, ll _total)
        : orderID(_id), items(_items), total(_total) {}

    void display() const {
        cout << "\n===Order #" << orderID << "===" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". ";
            items[i]->displayInfo();
        }
        cout << "Order Total: " << fixed << setprecision(2) << (double)total << " VND\n";
    }
};

// ================= Invoice =================
class Invoice {
private:
    vector<Product*> items;
    double shippingFee;
public:
    Invoice(const vector<Product*>& list, double ship = 0)
        : items(list), shippingFee(ship) {}

    double calcTotal() const {
        double sum = 0;
        for (auto p : items) sum += p->getPrice();
        return sum + shippingFee;
    }

    void displayInvoice() const {
        cout << "\n=== Invoice ===" << endl;
        int i = 1;
        for (auto p : items) {
            cout << i++ << ". ";
            p->displayInfo();
        }
        cout << "Shipping Fee: " << shippingFee << " VND\n";
        cout << "Grand Total: " << fixed << setprecision(2) << calcTotal() << " VND\n";
    }
};
class Shopee {
private:
    InventoryList<Product*> inventory;   // List of all products in the shop
    vector<Order> orders;                // List of all orders
    int nextOrderId;                     // Auto increment order ID
public:
    Shopee() : nextOrderId(1000) {}

    // Add product to shop inventory
    void addProduct(Product* p) {
        inventory.addItem(p);
    }

    // Show inventory
    void showInventory() const {
        inventory.displayItem();
    }

    // Find a product by ID
    Product* findProduct(int id) {
        return inventory.findItemByID(id);
    }

    // Create an order from checkout result
    void createOrder(const pair<vector<Product*>, ll>& checkoutResult) {
        orders.emplace_back(nextOrderId++, checkoutResult.first, checkoutResult.second);
        cout << "Order created successfully!\n";
    }

    // Show all orders
    void showOrders() const {
        cout << "\n=== All Orders in Shopee ===\n";
        for (auto& o : orders) {
            o.display();
        }
    }
};
int main() {
    try {
        Shopee shop; // create shop system

        // ---------- Test 1: Add products ----------
        Product* book = new Product(101, "C++ Primer", "Book", 500, 150000, 5);
        ElectricProduct* laptop = new ElectricProduct(102, "Gaming Laptop", "Electronics", 2500, 20000000, 3, 24);
        Product* phone = new Product(103, "Smartphone", "Electronics", 180, 12000000, 0);
        shop.addProduct(book);
        shop.addProduct(laptop);
        shop.addProduct(phone);

        cout << "\n=== Test 1: Show Inventory ===" << endl;
        shop.showInventory();

        // ---------- Test 2: Apply discount ----------
        cout << "\n=== Test 2: Discount on Product ===" << endl;
        cout << "Book price after 30% discount: " << book->applyDiscount(30) << " VND\n";

        // ---------- Test 3: Operator Overloading ----------
        cout << "\n=== Test 3: Operator Overloading ===" << endl;
        cout << "Laptop cheaper than Book? " << ((*laptop < *book) ? "Yes" : "No") << endl;
        cout << "Book == Phone (weight)? " << ((*book == *phone) ? "Yes" : "No") << endl;

        // ---------- Test 4: ShoppingCart ----------
        cout << "\n=== Test 4: ShoppingCart Operations ===" << endl;
        ShoppingCart cart;
        cart += book;
        cart += laptop;
        cart += phone;  // out of stock
        cart.displayCart();

        cout << "\nCart total after 15% discount: " << cart.applyDiscount(15) << " VND\n";

        // ---------- Test 5: Checkout + Order ----------
        cout << "\n=== Test 5: Checkout ===" << endl;
        auto result = cart.checkout();
        shop.createOrder(result);
        shop.showOrders();

        // ---------- Test 6: Invoice ----------
        cout << "\n=== Test 6: Invoice ===" << endl;
        Invoice invoice(result.first, 50000);
        invoice.displayInvoice();

        // ---------- Test 7: Restock ----------
        cout << "\n=== Test 7: Restocking Products ===" << endl;
        laptop->updateStock(5); // restock laptop
        phone->updateStock(10); // restock phone
        shop.showInventory();

        // ---------- Test 8: New Order after Restock ----------
        cout << "\n=== Test 8: New Order ===" << endl;
        ShoppingCart cart2;
        cart2 += laptop;
        cart2 += phone;
        cart2.displayCart();

        auto result2 = cart2.checkout();
        shop.createOrder(result2);
        shop.showOrders();

        // ---------- Test 9: Invoice for 2nd Order ----------
        cout << "\n=== Test 9: Invoice for Order 2 ===" << endl;
        Invoice invoice2(result2.first, 75000);
        invoice2.displayInvoice();

        // Clean up
        delete book;
        delete laptop;
        delete phone;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
