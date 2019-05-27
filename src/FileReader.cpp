#include "FileReader.h"
#include "graphviewer.h"
#include <iostream>

static int idEdge = 0;

bool readFile(std::string selectedLocation, Graph<Location> * graph){
    std::ifstream inputStream;
    std::string line;
    std::vector<Location> nodes;
    std::vector<tempEdge> edges;
    graph->gv = new GraphViewer(600,600,false);
    graph->gv->setBackground("background.jpg");

    graph->gv->createWindow(600, 600);


    graph->gv->defineVertexColor("blue");
    graph->gv->defineEdgeColor("black");


    std::string folderPath = "maps/" + selectedLocation;
    std::string nodesFileName = folderPath + "/T04_nodes_X_Y_" + selectedLocation + ".txt";
    std::string edgesFileName = folderPath + "/T04_edges_" + selectedLocation + ".txt";
    std::string tagsFileName = folderPath + "/T04_tags_" + selectedLocation + ".txt";

    //get nodes
    inputStream.open(nodesFileName);
    if(!inputStream.is_open()){
    	return false;
    }
    std::string id, x, y;
    getline(inputStream, line); //number of nodes extracted
    while(getline(inputStream,line)){
        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma);
        id = line.substr(1, firstComma);
        x = line.substr(firstComma+2, secondComma);
        y = line.substr(secondComma+2, line.find(')'));
        nodes.push_back(Location(std::stoi(id), std::stod(x), std::stod(y)));
        graph->gv->addNode(std::stoi(id), std::stod(x), std::stod(y));
    }
    inputStream.close();

    //get node tags and tag nodes
    inputStream.open(tagsFileName);
    if(!inputStream.is_open()){return false;}
    std::string tag1, tag2;
    getline(inputStream, line); //number of tags extracted
    while(getline(inputStream,line)){
        if(line.at(0) < '0' || line.at(0) > '9'){
            tag1 = line.substr(0, line.find('='));
            tag2 = line.substr(line.find('=')+1, line.size());
        }
        else if(line.size() < 5){
            //number of nodes with this tag, useless so far
        }
        else{
            std::vector<Location>::iterator it;
            Location tempLoc(std::stoi(line), 0, 0);
            it = find(nodes.begin(), nodes.end(), tempLoc);
            it->addTag(tag1);
            it->addTag(tag2);
        }
    }
    inputStream.close();


    //get edges
    inputStream.open(edgesFileName);
    if(!inputStream.is_open()){return false;}
    std::string originNode, destNode;
    getline(inputStream, line); //number of edges extracted
    while(getline(inputStream,line)){
    	originNode = line.substr(1, line.find(','));
        destNode = line.substr(line.find(' ')+1, line.find(')'));
        Location tempOriginLoc(std::stoi(originNode),0,0);
        Location tempDestLoc(std::stoi(destNode),0,0);
        std::vector<Location>::iterator originLoc = find(nodes.begin(), nodes.end(), tempOriginLoc);
        std::vector<Location>::iterator destLoc = find(nodes.begin(), nodes.end(), tempDestLoc);
        if (originLoc != nodes.end() && destLoc != nodes.end()) {
        	Location l1 = *originLoc;
        	Location l2 = *destLoc;
        	edges.push_back(tempEdge(l1, l2));
        	graph->gv->addEdge(idEdge,l1.getID(),l2.getID(),EdgeType::UNDIRECTED);
        	idEdge++;
        }
    }
    inputStream.close();
    graph->gv->rearrange();


    //push everything into the graph
    for(size_t i = 0; i < nodes.size(); i++){
        graph->addVertex(nodes.at(i));
    }
    for(size_t i = 0; i < edges.size(); i++){
        graph->addEdge(edges.at(i).getOrigin(), edges.at(i).getDest(), edges.at(i).getW());
    }
    return true;
}


tempEdge::tempEdge(Location &o, Location &d):origin(o) , dest(d) {

    this->w = sqrt(pow((d.getX() - o.getX()), 2) + pow((d.getY() - o.getY()), 2));
}

Location tempEdge::getOrigin(){
    return this->origin;
}

Location tempEdge::getDest(){
    return this->dest;
}

double tempEdge::getW(){
    return this->w;
}
