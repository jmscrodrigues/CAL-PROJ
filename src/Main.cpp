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
    				bool orig = false, destin = false;

    				cout << "Origin's id?\n";
					cin >> orId;

					cout << "Destination's id?\n";
					cin >> destId;

					for(unsigned int i = 0; i < gr.Ids.size();i++) {
						if (gr.Ids[i] == orId) {
							orig = true;
						}
					}

					for(unsigned int t = 0; t < gr.Ids.size();t++) {
						if (gr.Ids[t] == destId) {
							destin = true;
						}
					}

					if ((orig != true) || (destin != true)) {
						cout << "Wrong id's\n";
						break;
					}


					for (auto v : gr.vertexSet) {
						if (v->getInfo().getID() == orId) {
							xCoordOr = v->getInfo().getX();
							cout << v->getInfo().getX() << "\n";
							yCoordOr = v->getInfo().getY();
							cout << v->getInfo().getY() << "\n";
						}
					}
					for (auto v : gr.vertexSet) {
						if (v->getInfo().getID() == destId) {
							xCoordDest = v->getInfo().getX();
							cout << v->getInfo().getX() << "\n";
							yCoordDest = v->getInfo().getY();
							cout << v->getInfo().getY() << "\n";
						}
					}

					Location origLoc = Location(orId,xCoordOr,yCoordOr);
					Location destLoc = Location(destId,xCoordDest, yCoordDest);
					gr.dijkstraShortestPath(origLoc, destLoc);
					vector<Location> l = gr.getPath(origLoc, destLoc);
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
    			int numb;
				int orId;
				bool ret;
				double xCoord, yCoord;

				cout << "Origin's id?\n";
				cin >> orId;

				cout << "Number of destinations? \n";
				cin >> numb;

				vector<int> idDest;
				vector<bool> valid;

				int idD;
				for (int i = 1; i <= numb; i++) {

					cout << "Destination " << i << "id? \n";
					cin >> idD;
					idDest.push_back(idD);
					valid.push_back(false);
				}

				for (int t = 0; t < idDest.size(); t++) {
					for(unsigned int j = 0; j < gr.Ids.size();j++) {
						if (gr.Ids[t] == idDest[t]) {
							valid[t] = true;
						}
					}
				}

				for (int t = 0; t < valid.size(); t++)
				{
					if (valid[t] == false) {
						ret = true;
						break;
					}
				}

				if (ret) {
					break;
				}

				vector<Location> locations;

				for (int t = 0; t < idDest.size(); t++) {
					for (auto v : gr.vertexSet) {
						if (v->getInfo().getID() == idDest[t]) {
							xCoord = v->getInfo().getX();
							yCoord = v->getInfo().getY();
							locations.push_back(Location(idDest[t],xCoord,yCoord));
						}
					}
				}

				for (auto v : gr.vertexSet) {
					if (v->getInfo().getID() == orId) {
						xCoord = v->getInfo().getX();
						yCoord = v->getInfo().getY();
						Location origLoc = Location(orId,xCoord,yCoord);
					}
				}


				vector<Location> deliveryPoints = gr.bfs(origLoc);
				vector<Location>::iterator it = deliveryPoints.begin();
				while(it != deliveryPoints.end()){
					if(!(it->checkIfHasTag("shop")))
						deliveryPoints.erase(it);
					it++;
				}
				//gr.floydWarshallShortestPath();
				//gr.getfloydWarshallPath(orig1,dest1);
				vector<Location> result = gr.getSingleDeliveryPath(orig1, dest1, deliveryPoints);
				for(int i = 0; i < result.size(); i++)
				{
					cout << result.at(i).getID() << " -> ";
				}

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
