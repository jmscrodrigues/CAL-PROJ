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
    int id, qtty, vol;
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
				int orId, garId;
				bool ret = false;
				double xCoord, yCoord;
				bool orig = false, destin = false;

				cout << "Origin's id?\n";
				cin >> orId;

				cout << "Last destination (garage) id? \n";
				cin >> garId;

				cout << "Number of destinations? \n";
				cin >> numb;

				vector<int> idDest;
				vector <bool> valid;

				int idD;
				for (int i = 1; i <= numb; i++) {

					cout << "Destination " << i << " id? \n";
					cin >> idD;
					idDest.push_back(idD);
					for(unsigned int j = 0; j < gr.Ids.size();j++) {
						if (gr.Ids[j] == idD) {
							ret = true;
							break;
						}
					}
					valid.push_back(ret);
					ret = false;
				}

				cout << "IM HERE \n";
				cout << idDest.size()<< endl;
				for (unsigned int k = 0; k < valid.size(); k++) {
					cout << valid[k] << endl;
				}


				for(unsigned int i = 0; i < gr.Ids.size();i++) {
					if (gr.Ids[i] == orId) {
						orig = true;
					}
				}

				for(unsigned int t = 0; t < gr.Ids.size();t++) {
					if (gr.Ids[t] == garId) {
						destin = true;
					}
				}

				if ((orig != true) || (destin != true)) {
					cout << "Wrong id's no 2\n";
					break;
				}

				cout << "GOT HERE" << endl;

				if (idDest.size() != 1) {
					for (unsigned int t = 0; t < idDest.size(); t++) {
						cout << idDest[t] << endl;
						for(unsigned int j = 0; j < gr.Ids.size();j++) {
							cout << "Testing \n";
							if (gr.Ids[j] == idDest[t]) {
								//ret = false;
								valid[t] = false;
								break;
							}
						}
					}
					for (unsigned int k = 0; k < valid.size(); k++) {
						if (valid[k] == true) {
							ret = true;
							break;
						}
					}
				}

				else {
					ret = true;
					for (unsigned int k = 0; k < gr.Ids.size(); k++) {
						if (gr.Ids[k] == idD) {
							cout << "AGORA DÁ\n";
							ret = false;
						}
					}
				}


				if (ret) {
					cout << "Wrong id's no 1\n";
					break;
				}

				cout << "GOT HERE\n";
				vector<Location> locations;

				for (size_t t = 0; t < idDest.size(); t++) {
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
					}
				}

				cout << "Got here 2 \n";

				Location origL = Location(orId,xCoord,yCoord);

				for (auto v : gr.vertexSet) {
					if (v->getInfo().getID() == garId) {
						xCoord = v->getInfo().getX();
						yCoord = v->getInfo().getY();
					}
				}

				cout << "Got here 3 \n";

				Location garage = Location(garId,xCoord,yCoord);

				for (auto v : gr.vertexSet) {
					if (v->getInfo().getID() == garId) {
						xCoord = v->getInfo().getX();
						yCoord = v->getInfo().getY();
					}
				}

				cout << "Got here 4\n";

				vector<Location> result;
				size_t minSize = INT_MAX;
				Location minLocation = Location(0,0,0);
				int index;
				vector<Location> l;

				cout << "Got here\n";


				while (locations.size() != 0) {
					for (size_t s; s < locations.size(); s++) {
						gr.dijkstraShortestPath(origL, locations[s]);
						l = gr.getPath(origL, locations[s]);
						if (l.size() < minSize) {
							cout << "Found one\n";
							minLocation = locations[s];
							minSize = l.size();
							index = s;
						}
					}
					minSize = INT_MAX;
					l = gr.getPath(origL, minLocation);
					for (size_t t = 0; t < l.size(); t++) {
						result.push_back(l[t]);
					}
					cout << "Pushed back, now erasing \n";
					locations.erase(locations.begin() + index);
				}

				gr.dijkstraShortestPath(minLocation,garage);
				l = gr.getPath(minLocation, garage);

				for (size_t t = 0; t < l.size(); t++) {
					if (t != 0) {
						result.push_back(l[t]);
					}
				}

				for(size_t i = 0; i < result.size(); i++)
				{
					if (i != result.size() -1) {
						cout << result.at(i).getID() << " -> ";
					}
					else {cout << result.at(i).getID();}
				}
				break;
    		}

    		case 3:
    		{
			cout << "caso 2\n";
			//FAZER FLOYD-WARSHALL PARA 1 VEICULO
			//BSF
			int numb;
			int orId;
			bool ret = false;
			double xCoord, yCoord;
			bool orig = false;
			int numTr;
			int maxCargo;
			bool end = true;

			cout << "Origin's id?\n";
			cin >> orId;

			cout << "Number of trucks of the fleet?\n";
			cin >> numTr;

			cout << "Max cargo of each truck? \n";
			cin >> maxCargo;

			cout << "Number of destinations? \n";
			cin >> numb;

			vector<int> idDest;
			vector <bool> valid;

			int idD;
			for (int i = 1; i <= numb; i++) {

				cout << "Destination " << i << " id? \n";
				cin >> idD;
				idDest.push_back(idD);
				for(unsigned int j = 0; j < gr.Ids.size();j++) {
					if (gr.Ids[j] == idD) {
						ret = true;
						break;
					}
				}
				valid.push_back(ret);
				ret = false;
			}

			int carga;

			for(unsigned int i = 0; i < products.size();i++)
			{
				carga += products.at(i).getQuantity() * products.at(i).getVolume();
			}

			if (maxCargo * numTr < carga) {
				end = false;
				carga -= (maxCargo * numTr);
			}

			cout << "IM HERE \n";
			cout << idDest.size()<< endl;
			for (unsigned int k = 0; k < valid.size(); k++) {
				cout << valid[k] << endl;
			}


			for(unsigned int i = 0; i < gr.Ids.size();i++) {
				if (gr.Ids[i] == orId) {
					orig = true;
				}
			}

			if (orig != true) {
				cout << "Wrong id's no 2\n";
				break;
			}

			cout << "GOT HERE" << endl;

			if (idDest.size() != 1) {
				for (unsigned int t = 0; t < idDest.size(); t++) {
					cout << idDest[t] << endl;
					for(unsigned int j = 0; j < gr.Ids.size();j++) {
						cout << "Testing \n";
						if (gr.Ids[j] == idDest[t]) {
							//ret = false;
							valid[t] = false;
							break;
						}
					}
				}
				for (unsigned int k = 0; k < valid.size(); k++) {
					if (valid[k] == true) {
						ret = true;
						break;
					}
				}
			}

			else {
				ret = true;
				for (unsigned int k = 0; k < gr.Ids.size(); k++) {
					if (gr.Ids[k] == idD) {
						cout << "AGORA DÁ\n";
						ret = false;
					}
				}
			}


			if (ret) {
				cout << "Wrong id's no 1\n";
				break;
			}

			cout << "GOT HERE\n";
			vector<Location> locations;

			for (size_t t = 0; t < idDest.size(); t++) {
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
				}
			}

			cout << "Got here 2 \n";

			Location origL = Location(orId,xCoord,yCoord);

			cout << "Got here 4\n";

			vector<Location> result;
			size_t minSize = INT_MAX;
			Location minLocation = Location(0,0,0);
			int index;
			vector<Location> l;

			cout << "Got here\n";


			while (locations.size() != 0) {
				for (size_t s; s < locations.size(); s++) {
					gr.dijkstraShortestPath(origL, locations[s]);
					l = gr.getPath(origL, locations[s]);
					if (l.size() < minSize) {
						cout << "Found one\n";
						minLocation = locations[s];
						minSize = l.size();
						index = s;
					}
				}
				minSize = INT_MAX;
				l = gr.getPath(origL, minLocation);
				for (size_t t = 0; t < l.size(); t++) {
					result.push_back(l[t]);
				}
				cout << "Pushed back, now erasing \n";
				locations.erase(locations.begin() + index);
			}


			if (!end) {
				gr.dijkstraShortestPath(minLocation,origL);
				l = gr.getPath(minLocation, origL);

				for (size_t t = 0; t < l.size(); t++) {
					if (t != 0) {
						result.push_back(l[t]);
					}
				}

			}

			while (!end) {
				for(size_t i = 0; i < result.size(); i++)
				{
					if (i != result.size() -1) {
						cout << result.at(i).getID() << " -> ";
					}
					else {cout << result.at(i).getID();}
				}

				carga -= maxCargo * numTr;

				if (carga < 0) {
					end = true;
				}
			}

			for(size_t i = 0; i < result.size(); i++)
			{
				if (i != result.size() -1) {
					cout << result.at(i).getID() << " -> ";
				}
				else {cout << result.at(i).getID();}
			}

			break;
			}

    		case 4:
    		{
    			break;
    		}
    }
    return 0;
}
