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
    int city, iteration;
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

    while (iteration != 4) {
    	cout << "\nWhat iteration do you want to test?(1 2 3 4)\n 1) One vehicle with unlimited capacity makes one delivery \n 2) One vehicle with unlimited capacity makes all the deliveries\n 3) The fleet of vehicles with limited capacity makes the deliveries\n 4) Exit" << endl;
    	cin >> iteration;
    	switch(iteration) {
    		case 1:
    			{
    				double xCoordOr, yCoordOr, xCoordDest, yCoordDest;
    				int orId,destId;

    				cout << "Origin's id?\n";
					cin >> orId;

					cout << "Destination's id?\n";
					cin >> destId;


					for (auto v : gr.vertexSet) {
						if (v->getInfo().getID() == orId) {
							xCoordOr = v->getInfo().getX();
							yCoordOr = v->getInfo().getY();
						}
					}
					for (auto v : gr.vertexSet) {
						if (v->getInfo().getID() == destId) {
							xCoordDest = v->getInfo().getX();
							yCoordDest = v->getInfo().getY();
						}
					}

					Location orig = Location(orId,xCoordOr,yCoordOr);
					Location dest = Location(destId,xCoordDest, yCoordDest);
					gr.dijkstraShortestPath(orig, dest);
					vector<Location> l = gr.getPath(orig, dest);
					if(l.size() > 1){
						for(unsigned int i = 0; i < l.size()-1; i++){
							cout << l.at(i).getID() << " -> ";
						}
						cout << l.at(l.size()-1).getID();
					}
					else cout << "Error?\n";

					break;
    			}
    		case 2:
    		{
    			cout << "caso 2\n";
    			//FAZER FLOYD-WARSHALL PARA 1 VEICULO
    			//BSF
    			double xCoordOr, yCoordOr, xCoordDest, yCoordDest;
				int orId,destId;
				cout << "Origin's id?\n";
				cin >> orId;
				cout << "Origin's X coordinate?\n";
				cin >> xCoordOr;
				cout << "Origin's Y coordinate?\n";
				cin >> yCoordOr;

				cout << "Destination's id?\n";
				cin >> destId;
				cout << "Destination's X coordinate?\n";
				cin >> xCoordDest;
				cout << "Destination's Y coordinate?\n";
				cin >> yCoordDest;
				Location orig1 = Location(orId,xCoordOr,yCoordOr);
				Location dest1 = Location(destId,xCoordDest, yCoordDest);

				gr.bfs(orig1);
				//gr.floydWarshallShortestPath();
				gr.getfloydWarshallPath(orig1,dest1);


    		}
    		break;

    		case 3:
    			cout << "caso 3\n";
    			//FAZER A FUNÇAO PARA DISTRIBUIÇAO DE AREAS
    			//FAZER FLOYD-WARSHALL PARA TODOS OS VEICULOS
    		break;
    	}
    }
    return 0;
}
