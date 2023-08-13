#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class User {
public:
    string username;
    string password;

    User(string _username, string _password) : username(_username), password(_password) {}
};

// Class to represent a bakery item
class BakeryItem {
public:
    string name;
    double price;

    BakeryItem(string _name, double _price) : name(_name), price(_price) {}
};

// Class to represent a sales record
class SalesRecord {
public:
    string itemName;
    int quantity;
    double totalAmount;

    SalesRecord(string _itemName, int _quantity, double _totalAmount)
        : itemName(_itemName), quantity(_quantity), totalAmount(_totalAmount) {}
};

class BakerySystem {
private:
    bool loggedIn;
    string currentUser;
    vector<User> users; // User database
    vector<SalesRecord> salesRecords; // Sales records database
    vector<BakeryItem> bakeryItems; // Bakery items database

    
public:
	BakerySystem() : loggedIn(false) {
        // Initialize the loggedIn status
        users.push_back(User("admin", "password"));
        loadItems();
        
    }
    
    bool isLoggedIn() const {
        return loggedIn;
    }
    
    string getCurrentUser() const {
        return currentUser;
    }


    void loadItems();
    void viewItems();
    void viewSales();
    void addItem();
    void editItem();
    void deleteItem();
    void manageSales();
    void viewCompanyDetails();
    void saveSales();
    void login();
    void logout();
};

void BakerySystem::login() {
    if (loggedIn) {
        cout << "Already logged in.\n";
        return;
    }

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check if the entered username and password match any user in the users vector
    for (const auto &user : users) {
        if (user.username == username && user.password == password) {
            loggedIn = true;
            currentUser = username;
            cout << "\n\nLogged in successfully as " << username << ".\n";
            return;
        }
    }

    cout << "Invalid username or password.\n";
}

void BakerySystem::logout() {
    if (!loggedIn) {
        cout << "Not logged in.\n";
        return;
    }

    loggedIn = false;
    currentUser = "";
    cout << "Logged out successfully.\n";
}

void BakerySystem::viewSales() {
    cout << "Sales Records:\n";
    cout << "Item Name\tQuantity\tTotal Amount\n";
    for (const auto &record : salesRecords) {
        cout << record.itemName << "\t\t" << record.quantity << "\t\t$" << record.totalAmount << endl;
    }
}

void BakerySystem::loadItems() {
    
    // Add more items as needed
    ifstream itemsFile("items.txt");
    if (!itemsFile) {
        cout << "No items found in the database.\n";
        return;
    }

    string name;
    double price;
    while (itemsFile >> name >> price) {
        bakeryItems.push_back(BakeryItem(name, price));
    }

    itemsFile.close();

}

void BakerySystem::viewItems() {
    cout << "Available Bakery Items:\n";
    cout << "Name\t\tPrice\n";
    for (const auto &item : bakeryItems) {
        cout << item.name << "\t\t$" << item.price << endl;
    }
}

void BakerySystem::addItem() {
    string name;
    double price;

    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter item price: ";
    cin >> price;
    
    

      
    ofstream itemsFile("items.txt", ios::app); // Open the file in append mode
    if (!itemsFile) {
        cout << "Error saving item record.\n";
        return;
    }

    itemsFile << name << " " << price << endl;
    itemsFile.close();
    bakeryItems.push_back(BakeryItem(name, price));
    cout << "Item added successfully.\n";

}

void BakerySystem::manageSales() {
    string itemName;
    int quantity;

    viewItems();
    cout << "Enter item name to purchase: ";
    cin >> itemName;
    cout << "Enter quantity: ";
    cin >> quantity;

    double totalAmount = 0.0;
    bool itemFound=false;
    for (const auto &item : bakeryItems) {
        if (item.name == itemName) {
            totalAmount = item.price * quantity;
            itemFound=true;

            break;
        }
    
        	
	
    }
    
    if (!itemFound) {
        cout << "Item not found in the bakery.\n";
        return; // No sales recorded if the item is not found
    }

    

    salesRecords.push_back(SalesRecord(itemName, quantity, totalAmount));
    cout << "Purchase recorded successfully.\n";
}

void BakerySystem::viewCompanyDetails() {
    cout << "Amber Bakery - Serving Delicious Treats!\n";
    cout << "Contact: contact@amberbakery.com\n";
    cout << "Visit us at: www.amberbakery.com\n";
}

void BakerySystem::saveSales() {
    ofstream salesFile("sales.txt");
    if (!salesFile) {
        cout << "Error saving sales records.\n";
        return;
    }

    for (const auto &record : salesRecords) {
        salesFile << record.itemName << "\t" << record.quantity << "\t" << record.totalAmount << endl;
    }

    salesFile.close();
    cout << "Sales records saved.\n";
}

void BakerySystem::editItem() {
    string itemName;
    double newPrice;
	
	viewItems();
    cout << "Enter item name to edit: ";
    cin >> itemName;
	
	bool itemFound = false;
    for (auto &item : bakeryItems) {
        if (item.name == itemName) {
            cout << "Enter new price: ";
            cin >> newPrice;
            item.price = newPrice;
           
            itemFound = true;
            break;
            
        }
   
    }
    
   if (!itemFound) {
        cout << "Item not found.\n";
        return;
    }


	
	ofstream itemsFile("items.txt");
	    if (!itemsFile) {
	        cout << "Error saving item record.\n";
	        return;
	    }
	
	    for (const auto &item : bakeryItems) {
	        itemsFile << item.name << " " << item.price << endl;
	    }
	
	    itemsFile.close();
	    cout << "Item updated successfully.\n";
	}

void BakerySystem::deleteItem() {
    string itemName;

    viewItems();
    cout << "Enter item name to delete: ";
    cin >> itemName;

    auto it = bakeryItems.begin();
    bool itemFound = false;
    while (it != bakeryItems.end()) {
        if (it->name == itemName) {
            bakeryItems.erase(it);
            itemFound = true;
            break;
        }
        ++it;
    }


    if (!itemFound) {
        cout << "Item not found.\n";
        return;
    }
    
    ofstream itemsFile("items.txt");
    if (!itemsFile) {
        cout << "Error saving item record.\n";
        return;
    }

    for (const auto &item : bakeryItems) {
        itemsFile << item.name << " " << item.price << endl;
    }

    itemsFile.close();
    cout << "Item deleted successfully.\n";
}
    


int main() {
    BakerySystem bakerySystem;
    bakerySystem.loadItems();

    int choice;
    do {
        cout << "\n\n\nWelcome to Amber Bakery Billing System\n\n";

        if (!bakerySystem.isLoggedIn()) {
            cout << "Please login to continue.\n";
            bakerySystem.login();
        }

        cout << "1. View Available Items\n";
        cout << "2. Add Item\n";
        cout << "3. Edit Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Manage Sales\n";
        cout << "6. View Sales Records\n";
        cout << "7. View Company Details\n";
        cout << "8. Save Sales Records\n";
        cout << "9. " << (bakerySystem.isLoggedIn() ? "Logout" : "Exit") << "\n\n";
        
        if (bakerySystem.isLoggedIn()) {
            cout << "Logged in as: " << bakerySystem.getCurrentUser() << "\n";
        }

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bakerySystem.viewItems();
                break;
            case 2:
                bakerySystem.addItem();
                break;
            case 3:
                bakerySystem.editItem();
                break;
            case 4:
                bakerySystem.deleteItem();
                break;    
            case 5:
                bakerySystem.manageSales();
                break;
            case 6:
                bakerySystem.viewSales();
                break;
            case 7:
                bakerySystem.viewCompanyDetails();
                break;
            case 8:
                bakerySystem.saveSales();
                break;
            case 9:
                if (bakerySystem.isLoggedIn()) {
                    bakerySystem.logout();
                } else {
                    cout << "Exiting the system.\n";
                }
                break;
            
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 9);

    return 0;
}