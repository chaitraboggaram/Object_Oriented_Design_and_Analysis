#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Define a product structure
struct Product {
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
        {"Apples", 10.99, 50},
        {"Bananas", 5.99, 30},
        {"Oranges", 8.49, 20}
    };

    // Initialize the shopping cart
    vector<pair<Product, int>> cart;

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
        cout << endl << "Enter the ID of the product to add to cart (or 0 to checkout): ";
        cin >> choice;
        choice -= 1;
        int cartSize = cart.size(); // Get the current size of the cart
        
        if (choice == -1) {
            // Checkout process
            double totalCost = 0.0;

            cout << "\nYour Shopping Cart:" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "|  Item Name\t|  Quantity\t|  Price\t|" << endl;
            cout << "|--------------------------------------------|" << endl;

            for (auto item : cart) {
                cout << "|  " << item.first.name << "\t|  " << item.second << "\t\t|  $" << item.first.price << "\t|" << endl;
                totalCost += item.first.price * item.second;
            }

            cout << "|--------------------------------------------|" << endl;
            cout << "|  Total Cost: \t\t\t   $" << totalCost << "    |" << endl;
            cout << "----------------------------------------------" << endl;

            // Option to delete an item
            if (cartSize > 0) {
                int deleteChoice;
                cout << "Enter the number of the item to delete (1-" << cartSize << ") or 0 to continue to checkout: ";
                cin >> deleteChoice;

                if (deleteChoice > 0 && deleteChoice <= cartSize) {
                    // Delete the selected item from the cart
                    cart.erase(cart.begin() + deleteChoice - 1);
                    cout << "Item deleted from the cart." << endl << endl;
                } else if (deleteChoice != 0) {
                    cout << "Invalid choice. Please try again." << endl << endl;
                }
            }

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
        } else if (choice >= 0 && choice < inventory.size()) {
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

                // Updating the quantity after adding to cart
                inventory[choice].availableQuantity = inventory[choice].availableQuantity - quantity;
            }
        } else {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    }

    return 0;
}
