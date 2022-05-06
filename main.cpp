//Include Directive - importing input/output library
#include <iostream>

//Include Directive - IO Manipulators
#include <iomanip>

//Include Directive - Open/Write Files
#include <fstream>

//Include Directive - needed to convert string to double
#include <string>

//Use standard namespace
using namespace std;

//Global Variables
int cartId = 0;

//Config - file location
string fileLocation = "qbc_menu_prices.txt";

//Declare Functions and Modules
void displayMenu(string itemName[], double price[], int SIZE, string cartItem[], double cartPrice[], int qty[], int cartSize);
void displaySalesReceipt(string itemName[], double price[], int SIZE, string cartItem[], double cartPrice[], int qty[], int cartSize);
void cart(string itemName[], double price[], int SIZE, string cartItem[], double cartPrice[], int qty[], int cartSize);
void viewCart(string itemName[], double price[], int SIZE, string cartItem[], double cartPrice[], int qty[], int cartSize);
int processArraySize();
void processArray(string itemName[], double price[], int SIZE);

//Main function entry point
int main()
{
    //Menu Variables
    const int SIZE = processArraySize();
    string itemName[SIZE];
    double price[SIZE];

    //Cart Variables
    const int cartSize = 100;
    string cartItem[cartSize];
    double cartPrice[cartSize];
    int qty[cartSize];

    //Import entries in txt file into array
    processArray(itemName, price, SIZE);

    //Display Header
    cout << "            Jon's Coffee Beans           " << endl;
    cout << "-----------------------------------------" << endl;
    for(int i = 0; i < SIZE; i++)
    {
        cout << setw(22) << right << itemName[i] << " $" << setprecision(2) << fixed << price[i] << endl;
    }
    cout << "-----------------------------------------" << endl;

    //Display Menu
    displayMenu(itemName, price, SIZE, cartItem, cartPrice, qty, cartSize);

    return 0;
}

//Display Menu
void displayMenu(string itemName[], double price[], int SIZE, string cartItem[], double cartPrice[], int qty[], int cartSize)
{
    //Display Menu
    cout << endl;
    cout << "   1) Add Item" << endl;
    cout << "   2) View Order" << endl;
    cout << "   3) Checkout" << endl;
    cout << "   4) Start Over" << endl;

    //Choose Option
    cout << endl;
    int chooseOption;
    cout << "Enter Selection: ";
    cin >> chooseOption;
    cout << endl;

    //Input Validation
    while(chooseOption < 1 || chooseOption > 4 || cin.fail())
    {
        cout << endl;
        cin.clear();
        cin.ignore();
        cout << "Selection is invalid." << endl;
        cout << endl;
        cout << "Enter Selection: ";
        cin >> chooseOption;
        cout << endl;
    }

    //If Add Item is chosen
    if(chooseOption == 1)
    {
        //Call cart function then proceed back to menu.
        cart(itemName, price, SIZE, cartItem, cartPrice, qty, cartSize);
        displayMenu(itemName, price, SIZE, cartItem, cartPrice, qty, cartSize);

    }

    //If View Order is chosen
    else if(chooseOption == 2)
    {
        //Display Items added to cart the proceed back to menu
        viewCart(itemName, price, SIZE, cartItem, cartPrice, qty, cartSize);
        displayMenu(itemName, price, SIZE, cartItem, cartPrice, qty, cartSize);
    }

    //If ready to checkout
    else if(chooseOption == 3)
    {
        //Confirm checkout
        string confirm;
        cout << "Ready to checkout? y/n: ";
        cin >> confirm;
        cout << endl;

        //If Y or y is chosen
        if (confirm == "y" || confirm == "Y")
        {
            //If cart is empty, display output and end program without printing a receipt
            if(cartId == 0)
            {
                cout << "No receipt required. Thanks!" << endl;
                exit(1);
            }
            //if cart is not empty, print receipt
            displaySalesReceipt(itemName, price, SIZE, cartItem, cartPrice, qty, cartSize);
        }
        //If user decides to go back to menu
        else
        {
            //display menu
            displayMenu(itemName, price, SIZE, cartItem, cartPrice, qty, cartSize);
        }
    }
    //If user wants to start order over
    else if(chooseOption == 4)
    {
        //get confirmation
        string confirm;
        cout << "Are you sure you want to start over? y/n: ";
        cin >> confirm;

        //if user confirms, clear the screen, set cartId to 0, then call main function
        if(confirm == "y" || confirm == "Y")
        {
            system("CLS");
            cartId = 0;
            main();
        }
        //If user decides not to start over, go back to menu
        else
        {
            //display menu
            displayMenu(itemName, price, SIZE, cartItem, cartPrice, qty, cartSize);
        }
    }
}

//AddItem
void cart(string itemName[], double price[], int SIZE, string cartItem[], double cartPrice[], int qty[], int cartSize)
{
    //Increment cartId everytime cart function is called
    cartId++;

    //Loop that displays available menu items
    for (int i = 0; i < SIZE; i++)
    {
        //output
        cout << i + 1 << ") " << setw(6) << right << itemName[i];
        cout << " | $" << price[i] << endl;
    }

    //Get user input
    cout << endl;
    int addItemSelect;
    cout << "Enter Selection: ";
    cin >> addItemSelect;
    cout << endl;

    //Add Item to cart
    cartItem[cartId] = itemName[addItemSelect - 1];
    cartPrice[cartId] = price[addItemSelect - 1];

    //Enter Item quantity
    cout << " Enter Qty: ";
    cin >> qty[cartId];

    //Input validation
    while(qty[cartId] < 1 || cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Invalid Qty." << endl;
        cout << endl;
        cout << "Enter Qty: ";
        cin >> qty[cartId];
    }

    //Display Item, quantity, and total
    cout << endl;
    cout << cartItem[cartId] << " | " <<setprecision(2) << fixed << "$" << cartPrice[cartId]
         << " x " << qty[cartId] << "| Total: $" << (cartPrice[cartId] * qty[cartId]) << endl;

}

//View Order
void viewCart(string itemName[], double price[], int SIZE, string cartItem[], double cartPrice[], int qty[], int cartSize)
{
    //Declare Variables
    double subTotal;
    double grandTotal;

    //Display View Cart Header
    cout << "                  Cart                   " << endl;
    cout << "-----------------------------------------" << endl;

    //Loop that displays items currently in cart
    for(int i = 1; i < cartId + 1; i++)
    {
        cout << setw(10) << right << cartItem[i];
        cout << " | " <<setprecision(2) << fixed << "$" << cartPrice[i]
             << " x " << qty[i] << "| Total: $" << (cartPrice[i] * qty[i]) << endl;
        subTotal += (cartPrice[i] * qty[i]);
    }
    //Displays Subtotal, Tax, and grandTotal
    cout << "_________________________________________" << endl;
    cout << endl;
    cout << setw(24) << right << "  Sub Total: $" << subTotal << endl;
    cout << setw(24) << right << "    Tax(8%): $" << (subTotal * .08) << endl;
    cout << setw(24) << right << "Grand Total: $" << subTotal + (subTotal * .08) << endl;
    cout << "-----------------------------------------" << endl;
}

//Checkout
void displaySalesReceipt(string itemName[], double price[], int SIZE, string cartItem[], double cartPrice[], int qty[], int cartSize)
{
    //Declare Variables
    double subTotal;
    double grandTotal;
    ofstream cartReceipt;

    //Get customer Name
    string customerName;
    cout << "Enter Customer Name: ";
    cin >> customerName;
    cout << endl;

    //Create file with naming convention: customerName-Receipt
    string fileTitle = customerName + "-Receipt";
    cartReceipt.open(fileTitle);

    //Throw error if file fails to open
    if(cartReceipt.fail())
    {
        //display output and exit program
        cout << "Error! Export to file failed!" << endl;
        exit(1);
    }

    //Print receipt
    cartReceipt << "            Jon's Coffee Beans           " << endl;
    cartReceipt << endl;
    cartReceipt << "               Fort Collins              " << endl;
    cartReceipt << "            1234 S College Ave           " << endl;
    cartReceipt << "               (970)123-4567             " << endl;
    cartReceipt << "-----------------------------------------" << endl;
    cartReceipt << endl;
    cartReceipt << "Items for: " << customerName << endl;
    cartReceipt << endl;
    cartReceipt << endl;

    //Loop that writes all items order: Item, unit price, quantity, total to file
    for(int i = 1; i < cartId + 1; i++)
    {
        cartReceipt << setw(10) << right << cartItem[i];
        cartReceipt << " | " <<setprecision(2) << fixed << "$" << cartPrice[i]
             << " x " << qty[i] << "| Total: $" << (cartPrice[i] * qty[i]) << endl;
        subTotal += (cartPrice[i] * qty[i]);
    }

    //Write Sub Total, Tax, and grand total to file
    cartReceipt << "_________________________________________" << endl;
    cartReceipt << endl;
    cartReceipt << setw(24) << right << "  Sub Total: $" << subTotal << endl;
    cartReceipt << setw(24) << right << "    Tax(8%): $" << (subTotal * .08) << endl;
    cartReceipt << setw(24) << right << "Grand Total: $" << subTotal + (subTotal * .08) << endl;
    cartReceipt << "-----------------------------------------" << endl;
    cartReceipt << "      Thank You! Have a great day!" << endl;

    //Close the file
    cartReceipt.close();

    //Display Checkout
    cout << endl;
    cout << "-----------------------------------------" << endl;
    cout << "            Jon's Coffee Beans           " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Items for:" << customerName << endl;
    cout << endl;
    cout << endl;

    //Resets subtotal
    subTotal = 0;

    //Loop that displays items in cart
    for(int i = 1; i < cartId + 1; i++)
    {
        cout << setw(10) << right << cartItem[i];
        cout << " | " <<setprecision(2) << fixed << "$" << cartPrice[i]
             << " x " << qty[i] << "| Total: $" << (cartPrice[i] * qty[i]) << endl;
        subTotal += (cartPrice[i] * qty[i]);
    }

    //Display Sub Total, Tax, and grand total
    cout << "_________________________________________" << endl;
    cout << endl;
    cout << setw(24) << right << "  Sub Total: $" << subTotal << endl;
    cout << setw(24) << right << "    Tax(8%): $" << (subTotal * .08) << endl;
    cout << setw(24) << right << "Grand Total: $" << subTotal + (subTotal * .08) << endl;
    cout << "-----------------------------------------" << endl;
    cout << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Receipt Printed Successfully." << endl;
}

//Gets the number of lines in file and returns value to set array size
int processArraySize()
{
    //used to open txt file
    ifstream coffeeFile;

    //used to get line from txt file
    string line;

    //declare variable
    int count = 0;

    //opens txt file
    coffeeFile.open(fileLocation);

    //Throw error if file fails to open
    if(coffeeFile.fail())
    {
        cout << "Error! File failed to open" << endl;
        exit(1);
    }
    //loops while not at end of document
    while(!coffeeFile.eof())
    {
        //gets line from txt file
        getline(coffeeFile, line);

        //increments per line
        count++;
    }
    //Close the file
    coffeeFile.close();

    //returns last line number of document
    return count;
}

//Adds lines in txt file into array
void processArray(string itemName[], double price[], int SIZE)
{
    //used to open txt file
    ifstream coffeeFile;

    //Declare variable
    string item;
    string cost;

    //opens txt file
    coffeeFile.open(fileLocation);

    //loop that get each line and inserts into array
    for(int i = 0; i < SIZE; i++)
    {
        //gets line from txt file
        coffeeFile >> item >> cost;

        //inserts each line into array
        itemName[i] = item;
        price[i] = stod(cost);
    }
    //Close the File
    coffeeFile.close();
}
