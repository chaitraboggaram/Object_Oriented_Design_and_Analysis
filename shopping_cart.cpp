#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Define a product structure
struct Product {
    int uid;
    string name;
    double price;
    int availableQuantity;
};

// Function to simulate payment processing with a chance of failure
bool processPayment() {
    // Simulate a 10% chance of payment failure
    return rand() % 10 != 0;
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Create a list of products
    vector<Product> inventory = {
        {1, "Apples", 1.89, 50},
        {2, "Bananas", 1.25, 30},
        {3, "Oranges", 1.44, 20},
        {4, "Grapes", 1.99, 25}
    };

    // Initialize the shopping cart
    vector<pair<Product, int>> cart;

    int cartSize = 0;

    while (true) {
        cout << endl << "Available Products:" << endl;
        cout << "\033[31m------------------------------------------------------------\033[0m" << endl;
        cout << "\033[31m| Kindly note that products are sold in 1-pound quantities.|\033[0m" << endl;
        cout << "\033[31m------------------------------------------------------------\033[0m" << endl << endl;
        
        cout << "------------------------------------------------------" << endl;
        cout << "|  Item     |  Item\t|  Price\t|  Available |  " << endl;
        cout << "|  Number   |  Name\t|  per Pound\t|  Quantity  |" << endl;
        cout << "------------------------------------------------------" << endl;

        // Display the inventory in a table-like format
        for (int i = 0; i < inventory.size(); i++) {
            cout << "|  " << i + 1 << "\t    |  " << inventory[i].name << "\t|  $" << inventory[i].price << "\t|  " << inventory[i].availableQuantity << "        |" << endl;
        }
        cout << "------------------------------------------------------" << endl;

        int choice;
        if (cartSize == 0)
            cout << endl << "Enter the ID of the product to add to cart: ";
        else {
            cout << endl << "Enter the ID of the product to add to cart ";
            cout << endl << "Enter -1 remove a product from cart or 0 to checkout): ";
        }

        cin >> choice;
        choice -= 1;        
        
        if (choice == -1) {
            // Checkout process
            double totalCost = 0.0;

            cout << "\nYour Shopping Cart:" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "|  Item Name\t|  Quantity\t|  Price\t|" << endl;
            cout << "|-----------------------------------------------|" << endl;

            for (auto item : cart) {
                cout << "|  " << item.first.name << "\t|  " << item.second << "\t\t|  $" << item.first.price << "\t|" << endl;
                totalCost += item.first.price * item.second;
            }

            cout << "|-----------------------------------------------|" << endl;
            cout << "|  Total Cost: \t\t\t   $" << totalCost << "\t|" << endl;
            cout << "-------------------------------------------------" << endl;

            // Option to proceed to payment or go back to the cart
            cout << "Press 1 to proceed to payment, or any other key to go back to the cart: ";
            int paymentChoice;
            cin >> paymentChoice;

            if (paymentChoice == 1) {
                // Simulate payment processing
                if (processPayment()) {
                    cout << "Payment successful! Your order has been placed." << endl << endl;
                    
                    // Update available quantities
                    for (auto item : cart) {
                        for (auto &product : inventory) {
                            if (product.name == item.first.name) {
                                product.availableQuantity -= item.second;
                                break;
                            }
                        }
                    }
                    cart.clear(); // Clear the cart after successful payment

                    // Ask the user if they want to place another order or exit
                    cout << endl << "Press 1 to place another order, or any other key to exit: ";
                    int orderChoice;
                    cin >> orderChoice;

                    if (orderChoice != 1) {
                        cout << endl << "Thank you for shopping. Goodbye!" << endl << endl << endl;
                        return 0;
                    }
                } else {
                    cout << "Payment failed. Please try again." << endl << endl;
                }
            }

        } 

        else if (choice == -2) {
            // Option to delete an item
            
            cout << "\nYour Shopping Cart:" << endl;
            cout << "-----------------------------------------------------------------" << endl;
            cout << "|  Number\t|  Item Name\t|  Quantity\t|  Price\t|" << endl;
            cout << "|---------------------------------------------------------------|" << endl;

            int uid_val, k = 1;
            for (auto item : cart) {
                cout << "|  " << k << "\t\t|  " << item.first.name << "\t|  " << item.second << "\t\t|  $" << item.first.price << "\t|" << endl;
                k += 1;
            }
            cout << "-----------------------------------------------------------------" << endl;


            int deleteChoice;
            cout << "Enter the number of the item to delete or 0 to continue to checkout: ";
            cin >> deleteChoice;

            if (deleteChoice > 0 && deleteChoice <= cartSize) {
                // Delete the selected item from the cart
                cart.erase(cart.begin() + deleteChoice - 1);
                cout << "Item deleted from the cart." << endl << endl;
                cartSize -= 1;

            } else if (deleteChoice != 0) {
                cout << "Invalid choice. Please try again." << endl << endl;
            }

            if (cartSize == 0)
                cout << "No items in cart to display\n";
            else {
                cout << "\nYour Updated Shopping Cart:" << endl;
                cout << "-----------------------------------------------------------------" << endl;
                cout << "|  Number\t|  Item Name\t|  Quantity\t|  Price\t|" << endl;
                cout << "|---------------------------------------------------------------|" << endl;
                k = 0;
                    for (auto item : cart) {
                    cout << "|  " << k << "\t\t|  " << item.first.name << "\t|  " << item.second << "\t\t|  $" << item.first.price << "\t|" << endl;
                    k += 1;
                    uid_val = item.first.uid; // Capture the uid into uid_val
                    inventory[uid_val].availableQuantity += item.second;
                }
                cout << "-----------------------------------------------------------------" << endl;
            }
        }

        else if (choice >= 0 && choice < inventory.size()) {
            int quantity = 0;
            cout << "Enter the quantity to add: ";
            cin >> quantity;

            // Validate quantity and availability
            if (quantity <= 0) {
                cout << "Item is out of stock" << endl << endl;
            }
            else if (quantity > inventory[choice].availableQuantity) {
                cout << "There is only " << inventory[choice].availableQuantity << " quantity in stock." << endl << endl;
            } else {
                cart.push_back({inventory[choice], quantity});
                cout << "Added to cart!" << endl << endl;
                cartSize += 1;

                // Updating the quantity after adding to cart
                inventory[choice].availableQuantity = inventory[choice].availableQuantity - quantity;
            }
        } else {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    }

    return 0;
}
