#include <iostream>
#include <string>

using namespace std;

int main()
{
    int units; // initializes variables
    double basePrice, royalty, royaltyRate;
    string title, premium;
    
    cout << "Units sent: "; // takes input of units
    cin >> units;
    cin.ignore(10000, '\n');
    if (units < 0) // checks if units is nonnegative, otherwise returns error message
    {
        cout << "---" << endl << "The number of units sent must be nonnegative." << endl;
        return 1;
    }
    
    cout << "Title: "; // takes input of title
    getline(cin, title);
    if (title == "") // checks if title is not an empty string, otherwise returns error message
    {
        cout << "---" << endl << "You must enter a title." << endl;
        return 1;
    }
    
    cout << "Base price: "; // takes input of base price
    cin >> basePrice;
    cin.ignore(10000, '\n');
    if (basePrice < 0) // checks if base price is nonnegative, otherwise returns error message
    {
        cout << "---" << endl << "The base price must be nonnegative." << endl;
        return 1;
    }
    
    cout << "Premium item? (y/n): "; // takes input of whether item is premium
    getline(cin, premium);
    if (premium != "y" && premium != "n") // checks if input is "y" or "n", otherwise returns error message
    {
        cout << "---" << endl << "You must enter y or n." << endl;
        return 1;
    }
    
    if (premium == "y") // uses the proper royalty rate depending on item's premium status
        royaltyRate = 0.16;
    else
        royaltyRate = 0.13;
    
    if (units <= 400) // calculates royalty for 400 or fewer units
        royalty = units * basePrice * 0.09;
    else if (units <= 1200) // calculates royalty for 1200 or fewer units
        royalty = (400 * basePrice * 0.09) + ((units - 400) * basePrice * royaltyRate);
    else // calculates royalty for greater than 1200 units
        royalty = (400 * basePrice * 0.09) + (800 * basePrice * royaltyRate) + ((units - 1200) * basePrice * 0.14);
    
    cout.setf(ios::fixed); // sets the correct format for displaying royalty
    cout.precision(2);

    cout << "---" << endl << title << " earned $" << royalty << " in royalties." << endl; // output sentence
}
