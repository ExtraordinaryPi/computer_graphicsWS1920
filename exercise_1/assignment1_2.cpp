//
// Created by christian on 17.10.19.
//
#include "assignment1_2.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Mesh {

    long id;
    long numberVertices = 0;
    vector<double> centerPosition;
    long numberFaces = 0;
    string name = "New Mesh";
    double scalingProperties = 1.0;

public:

    Mesh() {
        id = currentId;
        currentId++;
        centerPosition.push_back(0.0);
        centerPosition.push_back(0.0);
        centerPosition.push_back(0.0);
    };

    Mesh(long loadId, long loadNV, vector<double> loadCP, long loadNF, string loadName, double loadSP) {
        id = loadId;
        numberVertices = loadNV;
        centerPosition = loadCP;
        numberFaces = loadNF;
        name = loadName;
        scalingProperties = loadSP;
    };


    long getId() {
        return id;
    }

    long getNumberVertices() const {
        return numberVertices;
    }

    const vector<double> &getCenterPosition() const {
        return centerPosition;
    }

    long getNumberFaces() const {
        return numberFaces;
    }

    double getScalingProperties() const {
        return scalingProperties;
    }

    string getName() const {
        return name;
    }

    void setId(long id) {
        Mesh::id = id;
    }

    void setNumberVertices(long numberVertices) {
        Mesh::numberVertices = numberVertices;
    }

    void setCenterPosition(const vector<double> &centerPosition) {
        Mesh::centerPosition = centerPosition;
    }

    void setNumberFaces(long numberFaces) {
        Mesh::numberFaces = numberFaces;
    }

    void setName(const string &name) {
        Mesh::name = name;
    }

    void setScalingProperties(double scalingProperties) {
        Mesh::scalingProperties = scalingProperties;
    }
};

struct node {
    Mesh data;
    node *next;

    node() {
        currentId--;
    }
};

class SingleLinkedList {

    node *head, *tail;
public:
    SingleLinkedList() {
        head = NULL;
        tail = NULL;
    }

    void createnode(Mesh value) {
        node *temp = new node;
        temp->data = value;
        temp->next = NULL;
        if (head == NULL) {
            head = temp;
            tail = temp;
            temp = NULL;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    void display() {
        node *temp = new node;
        temp = head;
        cout << endl;
        while (temp != NULL) {
            cout << "ID: "  <<  temp->data.getId() << "; Name: " <<  temp->data.getName() << "; Center position: X: "
                 << temp->data.getCenterPosition().at(0) << " Y: " << temp->data.getCenterPosition().at(1) << " Z: "
                 << temp->data.getCenterPosition().at(2) << "; Faces: " << temp->data.getNumberFaces() << "; Vertices: "
                 << temp->data.getNumberVertices() << "\n";
            temp = temp->next;
        }
        cout << endl;
    }

    void saveMesh(ofstream *saveMeshes) {
        *saveMeshes << currentId << "\n";
        node *temp = new node;
        temp = head;
        cout << endl;
        while (temp != NULL) {
            *saveMeshes << temp->data.getId() << "\n" << temp->data.getName() << "\n"
                        << temp->data.getCenterPosition().at(0) << "\n" << temp->data.getCenterPosition().at(1) << "\n"
                        << temp->data.getCenterPosition().at(2) << "\n" << temp->data.getNumberFaces() << "\n"
                        << temp->data.getNumberVertices() << "\n" << temp->data.getScalingProperties() << "\n";
            temp = temp->next;
        }
    }

    bool editMesh(long id) {
        node *temp = new node;
        temp = head;
        cout << endl;
        string name;
        double inDouble;
        long inLong;
        vector<double> center;
        while (temp != NULL) {
            if (id == temp->data.getId()) {
                cout << "Please enter a name for the mesh (old Name:" + temp->data.getName() + " ).\n";
                cin >> name;
                temp->data.setName(name);
                cout << "Please enter X coordinate of center position.\n";
                cin >> name;
                try {
                    inDouble = stod(name);
                }
                catch (std::invalid_argument &) {
                    cout << "Invalid Entry\nOnly numbers from 0-9 and dots. Please enter a new one." << endl;
                    break;
                }
                center.push_back(inDouble);
                cout << "Please enter Y coordinate of center position.\n";
                cin >> name;
                try {
                    inDouble = stod(name);
                }
                catch (std::invalid_argument &) {
                    cout << "Invalid Entry\nOnly numbers from 0-9 and dots. Please enter a new one." << endl;
                    break;
                }
                center.push_back(inDouble);
                cout << "Please enter Z coordinate of center position.\n";
                cin >> name;
                try {
                    inDouble = stod(name);
                }
                catch (std::invalid_argument &) {
                    cout << "Invalid Entry\nOnly numbers from 0-9 and dots. Please enter a new one." << endl;
                    break;
                }
                center.push_back(inDouble);
                temp->data.setCenterPosition(center);
                cout << "Please enter the number of faces.\n";
                cin >> name;
                try {
                    inLong = stol(name);
                }
                catch (std::invalid_argument &) {
                    cout << "Invalid Entry\nOnly numbers from 0-9 and dots. Please enter a new one." << endl;
                    break;
                }
                temp->data.setNumberFaces(inLong);
                cout << "Please enter the number of vertices.\n";
                cin >> name;
                try {
                    inLong = stol(name);
                }
                catch (std::invalid_argument &) {
                    cout << "Invalid Entry\nOnly numbers from 0-9 and dots. Please enter a new one." << endl;
                    break;
                }
                temp->data.setNumberVertices(inLong);
                cout << "Please enter the scaling.\n";
                cin >> name;
                try {
                    inDouble = stod(name);
                }
                catch (std::invalid_argument &) {
                    cout << "Invalid Entry\nOnly numbers from 0-9 and dots. Please enter a new one." << endl;
                    break;
                }
                temp->data.setScalingProperties(inDouble);

                return true;
            }
            temp = temp->next;
        }
        return false;
    }


    SingleLinkedList loadMesh(ifstream *loadMeshes) {
        SingleLinkedList singleLinkedList;
        string line;
        int indicator = 0;
        Mesh mesh;
        long currentIdSetter = 1;
        vector<double> centerPosition;
        centerPosition.resize(3);
        while (getline(*loadMeshes, line)) {
            switch (indicator) {
                case 0:
                    currentIdSetter = stol(line);
                    indicator++;
                    break;
                case 1:
                    mesh.setId(stol(line));
                    indicator++;
                    break;
                case 2:
                    mesh.setName(line);
                    indicator++;
                    break;
                case 3:
                    centerPosition.at(0) = stod(line);
                    indicator++;
                    break;
                case 4:
                    centerPosition.at(1) = stod(line);
                    indicator++;
                    break;
                case 5:
                    centerPosition.at(2) = stod(line);
                    mesh.setCenterPosition(centerPosition);
                    indicator++;
                    break;
                case 6:
                    mesh.setNumberFaces(stol(line));
                    indicator++;
                    break;
                case 7:
                    mesh.setNumberVertices(stol(line));
                    indicator++;
                    break;
                case 8:
                    mesh.setScalingProperties(stod(line));
                    singleLinkedList.createnode(mesh);
                    indicator = 1;
                    break;
                default:
                    break;

            }
        }
        currentId = currentIdSetter;
        return singleLinkedList;
    }

    void deleteById(long id) {
        node *temp = new node;
        temp = head;
        int pos = 1;
        int deletePos = -1;
        while (temp != NULL) {
            if (id == temp->data.getId()) {
                deletePos = pos;
            }
            pos++;
            temp = temp->next;
        }
        if (deletePos > 1 && deletePos + 1 < pos) {
            this->delete_position(deletePos);
        }
        if (deletePos + 1 == pos) {
            this->delete_last();
        }
        if (deletePos == 1) {
            this->delete_first();
        }

    }


    void delete_first() {
        node *temp = new node;
        temp = head;
        head = head->next;
        delete temp;
    }

    void delete_last() {
        node *current = new node;
        node *previous = new node;
        current = head;
        while (current->next != NULL) {
            previous = current;
            current = current->next;
        }
        tail = previous;
        previous->next = NULL;
        delete current;
    }

    void delete_position(int pos) {
        node *current = new node;
        node *previous = new node;
        current = head;
        for (int i = 1; i < pos; i++) {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
    }

    bool isThere(long pos) {
        node *temp = new node;
        temp = head;
        cout << endl;
        while (temp != NULL) {
            if (pos == temp->data.getId()) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};


class SceneManager {

    SingleLinkedList meshObjects;

public:

    SceneManager() {

    }

    void setMeshObjects(const SingleLinkedList &meshObjects) {
        SceneManager::meshObjects = meshObjects;
    }

    void addMesh(Mesh &data) {
        this->meshObjects.createnode(data);
    }

    void deleteMesh(SceneManager *sceneManager, long delId) {
        if (sceneManager->meshObjects.isThere(delId)) {
            this->meshObjects.deleteById(delId);
        } else {
            cout << "This ID does'nt exist please choose another one.\n" << endl;
        }
    }

    void displayMesh() {
        this->meshObjects.display();
    }


    void saveScene() {
        ofstream saveScene("scene_" + currentScene + ".save");
        this->meshObjects.saveMesh(&saveScene);
        saveScene.close();
    }

    void loadScene(SceneManager *scene) {
        ifstream loadScene;
        loadScene.open("scene_" + currentScene + ".save");
        scene->setMeshObjects(this->meshObjects.loadMesh(&loadScene));
        loadScene.close();
    }

    void editMesh(long id) {
        if (this->meshObjects.editMesh(id)) {

        } else {
            cout << "Theres no Mesh with this ID" << endl;
        }
    }
};

void addMesh(SceneManager *sceneManager) {
    Mesh newMesh;
    sceneManager->addMesh(newMesh);
}


void assignment2() {
    SceneManager sceneManager;
    sceneManager.loadScene(&sceneManager);

    string input;
    int switchCase;
    long inLong;
    string chooseScene;

    bool exit = false;

    while (exit == false) {
        input = "";
        inLong = -1;

        cout
                << "Please choose one of the following options by number:\n1: Add a new mesh object\n2: Delete a mesh object by ID\n3: List of existing objects by ID and name\n4: Edit mesh\n5: Change Scene (default is 0)\n6: Exit\n "
                << endl;
        cin >> input;

        switchCase = stoi(input);
        switch (switchCase) {
            case 1:
                addMesh(&sceneManager);
                break;
            case 2:
                cout << "Please enter the ID of the Object you want to delete. \n";
                cin >> inLong;
                sceneManager.deleteMesh(&sceneManager, inLong);
                break;
            case 3:
                sceneManager.displayMesh();
                break;
            case 4:
                cout << "Please enter the ID of the Object you want to edit. \n";
                cin >> inLong;
                sceneManager.editMesh(inLong);
                break;
            case 5:
                sceneManager.saveScene();
                cout << "Please enter name of the Scene you want to enter. (Default: default). \n";
                cin >> chooseScene;
                currentScene = chooseScene;
                sceneManager.loadScene(&sceneManager);
                break;
            case 6:
                sceneManager.saveScene();
                exit = true;
                break;
            default:
                cout << "Please enter a valid option" << endl;
        }

    }
}