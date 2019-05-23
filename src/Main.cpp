#include <iostream>
#include "Product.h"
#include <vector>
#include <string>
#include "Graph.h"
#include "Location.h"
#include "FileReader.h"

using namespace std;

int main() {
    char nextProduct = 'y';
    int id, qtty, vol, nTrucks;
    int city;
    vector<Product> products;
    string chosenCity;

    while (nextProduct == 'y') {
        cout << "Product Receiver: Insert the product id, quantity of each product and its volume (per unit)" << endl;
        cin >> id >> qtty >> vol;
        Product p = Product(id,qtty,vol); 
        products.push_back(p);
        cout << "Are there any more products? (y or n)\n";
        cin >> nextProduct;
    }
    cout << "What's the number of delivery trucks?" << endl;
    cin >> nTrucks;

    cout << "What's the city you want to choose (1 - 10)?\n 1) Aveiro \n 2) Braga \n 3) Coimbra \n 4) Ermesinde \n 5) Fafe \n 6) Gondomar \n 7) Lisboa \n 8) Maia \n 9) Porto \n 10) Viseu \n";
    cin >> city;
    Graph<Location> gr;
    switch(city) {
        case 1:
        chosenCity = "Aveiro";
        break;

        case 2:
        chosenCity = "Braga";
        break;

        case 3:
        chosenCity = "Coimbra";
        break;

        case 4:
        chosenCity = "Ermesinde";
        break;

        case 5:
        chosenCity = "Fafe";
        break;

        case 6:
        chosenCity = "Gondomar";
        break;

        case 7:
        chosenCity = "Lisboa";
        break;

        case 8:
        chosenCity = "Maia";
        break;

        case 9:
        chosenCity = "Porto";
        break;
        
        case 10:
        chosenCity = "Viseu";
        break;
    }

    if (readFile(chosenCity, &gr)) {
    	cout << "Read the file!" << endl;
    }
    else {
        cout << "Pqp!\n";
    }
    return 0;
}
