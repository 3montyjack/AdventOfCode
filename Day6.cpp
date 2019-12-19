
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct OrbitsT {
    string body,
        orbiter;
};

#define numberOfLines 1651
struct namesOfCelestiaBodies {
    OrbitsT orbits[numberOfLines];
};


class SpaceObject {
    
    public:

    string id;
    SpaceObject * child,
                * parent,
                * sibling;

    SpaceObject(string idt) {
        id = idt;
        child = NULL;
        parent = NULL;
        sibling = NULL;
    }

};

struct unconnectedGraphs
{
    SpaceObject *parent[numberOfLines];
};

class Orbits {

    private:

    int indirectOrbitTotal;

    SpaceObject* findBody(SpaceObject* object, string id) { 
        SpaceObject* returned = NULL;
        if (object != NULL) {
        
            if (object->id == id) {
                returned = object;
            } else {
                returned = findBody(object->child, id);
                if (returned == NULL) {
                    returned = findBody(object->sibling, id);
                }
            }
        }
        return returned;
    }

    SpaceObject* findBodyInUnconnected(string id) {
        SpaceObject* temp = NULL;
        for (int i = 0; i < currentIndex; i++) {
            temp = findBody(graph.parent[i], id);
            if (temp != NULL) {
                break;
            }
        }
        return temp;
    }

    int currentIndex;
    public:
    namesOfCelestiaBodies bodyName;
    unconnectedGraphs graph;
    int graphCurrentIndex;

    Orbits()
    {
        indirectOrbitTotal = 0;
        currentIndex = 0;
        graphCurrentIndex = 0;

        for (int i = 0; i < numberOfLines; i++) {
            graph.parent[i] = NULL;
        }
    }

    void addToOrbit(SpaceObject* parent, SpaceObject* child) {
        if (parent == NULL) {
            return;
        }
        if (parent->child == NULL) {
            indirectOrbitTotal++;
            parent->child = child;
            child->parent = parent;
        }
        else {
            SpaceObject* temp = parent->child;
            parent->child = child;
            child->parent = parent;
            child->sibling = temp;
        }


    }

    SpaceObject* createSpaceObject(string id) {
        return new SpaceObject(id);
    }

    int findNextFree() {
        return graphCurrentIndex;
    }

    void insertIntoGraph(SpaceObject* object) {
        graph.parent[graphCurrentIndex] = object;
        graphCurrentIndex++;
    }

    void moveLastToPosition(int index) {
        graphCurrentIndex--;
        graph.parent[index] = graph.parent[graphCurrentIndex];
        graph.parent[graphCurrentIndex] = NULL;
    }

    void printGraph(SpaceObject* object) {
        if (object != NULL) {
            cout << object->id;
            cout << "      ";
            printGraph(object->sibling);
            cout << endl;
            printGraph(object->child);
        }
    }

    void insertIntoUnconnected(OrbitsT currentWorkingOrbit)
    {
        SpaceObject* bodyToAddTo = NULL;
        SpaceObject *bodyNeededToBeAdded = NULL;
        int indexBodeyNeededToBeAdded= 0;
        // cout << "Trying to connect: " << currentWorkingOrbit.body << " with " << currentWorkingOrbit.orbiter << endl;
        for (int i = 0; i < graphCurrentIndex; i++)
        {
            if (graph.parent[i] == NULL || graph.parent[i]->id == "") {
                break;
            }

            SpaceObject *tempBody = findBody(graph.parent[i], currentWorkingOrbit.body);
            // cout << "Here is the Node: " << tempBody << endl;
            if (tempBody != NULL) {
                bodyToAddTo = tempBody;
            }
            
            if (graph.parent[i]->id == currentWorkingOrbit.orbiter)
            {
                bodyNeededToBeAdded = graph.parent[i];
                indexBodeyNeededToBeAdded = i;
            }
        }
        if (bodyToAddTo == NULL)
        {
            bodyToAddTo = createSpaceObject(currentWorkingOrbit.body);
            insertIntoGraph(bodyToAddTo);
            // cout << "New Node and  " << bodyToAddTo << endl;
        }
        if (bodyNeededToBeAdded != NULL)
        {
            // cout << "Moving the past position to  " << indexBodeyNeededToBeAdded << " with " << currentWorkingOrbit.orbiter << endl;
            moveLastToPosition(indexBodeyNeededToBeAdded);
        } else {

            bodyNeededToBeAdded = createSpaceObject(currentWorkingOrbit.orbiter);
            // cout << "CurrentThing  " << bodyToAddTo << " NewOrbiter " << bodyNeededToBeAdded << endl;
        }
        addToOrbit(bodyToAddTo, bodyNeededToBeAdded);
    }

    void doOntoThisWhatIsNeeded(string argument) {
        string first = argument.substr(0, argument.find_first_of(')'));
        string second = argument.substr(argument.find_first_of(')') + 1, argument.find_first_of(')') + 4);

        bodyName.orbits[currentIndex].body = first;
        bodyName.orbits[currentIndex].orbiter = second;

        currentIndex++;
    }

    void makeMap() {
        int tempIndex = 0;

        while (tempIndex < currentIndex) {
            insertIntoUnconnected(bodyName.orbits[tempIndex]);
                tempIndex++;
        }
        cout << "Printing Graph" << endl;
        // printGraph(graph.parent[0]);
        // printGraph(graph.parent[1]);
    }

    int getDistanceFromSanta() {
        // Go left until hitting the root, cutting out parts of the tree that are not needed
        // Identify smallest subtree and then with that get the heights of each

        string arrayTemp[1651];
        string arrayTempYou[1651];
        SpaceObject* tempSanta = findBody(graph.parent[0], "SAN");
        SpaceObject* tempYou = findBody(graph.parent[0], "YOU");
        cout << "Found: " << tempSanta << " and " << tempYou << endl;
        SpaceObject *parentFinder = tempSanta;
        int i = 0;
        while (parentFinder->parent != NULL) {
            parentFinder = parentFinder->parent;
            arrayTemp[i] = parentFinder->id;
            i++;
        }
        parentFinder = tempYou;
        int j = 0;
        while (parentFinder->parent != NULL) {
            parentFinder = parentFinder->parent;
            arrayTempYou[j] = parentFinder->id;
            j++;
        }
        string sharedNode = "";
        for (int k = i-1; k > 0; k--) {
            int l = k - (j-i); 
            if (arrayTemp[k] != arrayTempYou[l]) {
                sharedNode = arrayTemp[k];
                cout << arrayTemp[k] << " " << arrayTempYou[l] << endl;
                
            }
        }
        cout << sharedNode << endl;

        return 0;

    }

    int getOrbitNumber() {
        SpaceObject* graphTemp = graph.parent[0];
        return countToLeaf(graphTemp, 0);        
    }

    int countToLeaf(SpaceObject* tempPtr, int depth) {
        int total = depth;

        
        if (tempPtr == NULL) {
            cout << depth << endl;
            return 0;
        }
        total = total + countToLeaf(tempPtr->sibling, depth);
        total = total + countToLeaf(tempPtr->child, depth+1);
        
        return total;

    }
};

int main(int argc, char const *argv[])
{
    ifstream myfile;
    Orbits *orbits = new Orbits();
    myfile.open("Day6Data.txt");
    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            string argument;
            myfile >> argument;
            
            orbits->doOntoThisWhatIsNeeded(argument);
        }
    }
    myfile.close();
    orbits->makeMap();
    // cout << orbits->getOrbitNumber() << endl;
    orbits->getDistanceFromSanta();
    return 0;
}


