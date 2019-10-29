#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

bool IsValidUnsigned(std::string input)
{
	for(unsigned i = 0; i < input.length(); ++i)
	{
		if(input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}

bool IsValidFloat(std::string input)
{
	bool floatingPoint = false;
	unsigned start = 0;

	if(input[0] == '-')
		++start;

	for(unsigned i = start; i < input.length(); ++i)
	{
		if(input[i] == '.')
		{
			if(floatingPoint)
				return false;
			else
				floatingPoint = true;
		}
		else if(input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}

struct Vector
{
	Vector() : x(0.f), y(0.f), z(0.f) {}
	Vector(float value) : x(value), y(value), z(value) {}
	Vector(float x, float y, float z) : x(x), y(y), z(z) {}

	float x, y, z;
};
struct Mesh
{
	unsigned id = 0;
	unsigned numVertices;
	unsigned numFaces;
	float scale;
	Vector centerPosition;
	std::string name;
};
struct ListObject
{
	Mesh mesh;
	ListObject* next = nullptr;
};

class SceneManager
{
public:
	void AddMesh(unsigned numVertices, unsigned numFaces, unsigned scale, Vector centerPosition, std::string name)
	{
		Mesh mesh;
		mesh.numVertices = numVertices;
		mesh.numFaces = numFaces;
		mesh.scale = scale;
		mesh.centerPosition = centerPosition;
		mesh.name = name;

		ListObject* listObject = new ListObject();
		listObject->mesh = mesh;

		if (m_Meshes == nullptr)
			m_Meshes = listObject;
		else
		{
			ListObject* last = m_Meshes;
			while (last->next != nullptr)
				last = last->next;

			listObject->mesh.id = last->mesh.id + 1;
			last->next = listObject;
		}
	}

	void RemoveMesh(unsigned id)
	{
		if (m_Meshes == nullptr)
			return;

		ListObject* previous = nullptr;
		ListObject* current = m_Meshes;

		while (current->mesh.id < id && current->next != nullptr)
		{
			previous = current;
			current = current->next;
		}


		if (current->mesh.id == id)
		{
			if (previous == nullptr)
				m_Meshes = current->next;
			else
				previous->next = current->next;

			delete current;
		}
	}

	void RemoveMesh(std::string name)
	{
		if (m_Meshes == nullptr)
			return;

		ListObject* previous = nullptr;
		ListObject* current = m_Meshes;

		while (current != nullptr)
		{
			if (current->mesh.name == name)
			{
				if (previous == nullptr)
				{
					m_Meshes = current->next;

					delete current;

					current = m_Meshes;
				}
				else
				{
					previous->next = current->next;

					delete current;

					current = previous->next;
				}


			}
			else
			{
				previous = current;
				current = current->next;
			}

		}
	}

	void PrintMeshes()
	{
		std::cout << "\n";

		ListObject* current = m_Meshes;

		while (current != nullptr)
		{
			Mesh mesh = current->mesh;
			std::cout << "\nID: " << mesh.id;
			std::cout << "\nNumber of vertices: " << mesh.numVertices;
			std::cout << "\nCenter position: " << mesh.centerPosition.x << ", " << mesh.centerPosition.y << ", " << mesh.centerPosition.z;
			std::cout << "\nNumber of faces: " << mesh.numFaces;
			std::cout << "\nName: " << mesh.name;
			std::cout << "\nScale: " << mesh.scale;
			std::cout << "\n\n";

			current = current->next;
		}
	}

	void SaveState()
	{
		std::ofstream saveFile;
		saveFile.open("meshes.txt", std::ios::trunc);

		ListObject* current = m_Meshes;

		while(current != nullptr)
		{
			Mesh mesh = current->mesh;	
			saveFile << std::to_string(mesh.id) << "\n";
			saveFile << std::to_string(mesh.numVertices) << "\n";
			saveFile << std::to_string(mesh.numFaces) << "\n";
			saveFile << std::to_string(mesh.scale) << "\n";
			saveFile << std::to_string(mesh.centerPosition.x) << "\n";
			saveFile << std::to_string(mesh.centerPosition.y) << "\n";
			saveFile << std::to_string(mesh.centerPosition.z) << "\n";
			saveFile << mesh.name;

			if(current->next != nullptr)
				saveFile << "\n";

			current = current->next;
		}
		saveFile.close();
	}

	void LoadState()
	{
		std::ifstream saveFile;
		saveFile.open("meshes.txt");

		std::string line;

		while(saveFile.is_open())
		{
			Mesh mesh;

			if(saveFile.eof())
				break;
			std::getline(saveFile, line);
			mesh.id = std::atoi(line.c_str());

			if(saveFile.eof())
			{
				std::cout << "\n\nSave file is corrupted\n\n";
				break;
			}
			std::getline(saveFile, line);
			mesh.numVertices = std::atoi(line.c_str());

			if(saveFile.eof())
			{
				std::cout << "\n\nSave file is corrupted\n\n";
				break;
			}
			std::getline(saveFile, line);
			mesh.numFaces = std::atoi(line.c_str());

			if(saveFile.eof())
			{
				std::cout << "\n\nSave file is corrupted\n\n";
				break;
			}
			std::getline(saveFile, line);
			mesh.scale = std::atof(line.c_str());

			if(saveFile.eof())
			{
				std::cout << "\n\nSave file is corrupted\n\n";
				break;
			}
			std::getline(saveFile, line);
			mesh.centerPosition.x = std::atof(line.c_str());

			if(saveFile.eof())
			{
				std::cout << "\n\nSave file is corrupted\n\n";
				break;
			}
			std::getline(saveFile, line);
			mesh.centerPosition.y = std::atof(line.c_str());

			if(saveFile.eof())
			{
				std::cout << "\n\nSave file is corrupted\n\n";
				break;
			}
			std::getline(saveFile, line);
			mesh.centerPosition.z = std::atof(line.c_str());

			if(saveFile.eof())
			{
				std::cout << "\n\nSave file is corrupted\n\n";
				break;
			}
			std::getline(saveFile, line);
			mesh.name = line;

			ListObject* listObject = new ListObject();
			listObject->mesh = mesh;
			listObject->next = nullptr;
			
			if(m_Meshes == nullptr)
				m_Meshes = listObject;
			else
			{
				ListObject* current = m_Meshes;
				while(current->next != nullptr)
					current = current->next;
				current->next = listObject;
			}
		}

		saveFile.close();
	}

private:
	ListObject* m_Meshes = nullptr;
};

int main()
{
	unsigned status = 0;

	SceneManager sceneManager;
	sceneManager.LoadState();

	while (status != 4)
	{
		std::cout << "Select an action:\n----------------------\n";
		std::cout << "\n(1) Add a new mesh";
		std::cout << "\n(2) Remove a mesh";
		std::cout << "\n(3) Print all meshes";
		std::cout << "\n(4) Exit";
		
		std::cout << "\n\nSelection: ";
		std::cin >> status;

		switch (status)
		{
			case 1:
			{
				std::string numVertices = "";
				std::string numFaces = "";
				std::string scale = "";
				std::string centerPositionX = "";
				std::string centerPositionY = "";
				std::string centerPositionZ = "";
				std::string name = "";

				std::cout << "\n\n(1) Add a new mesh";

				while(numVertices == "")
				{
					std::cout << "\n\nNumber of vertices: ";
					std::cin >> numVertices;

					if(!IsValidUnsigned(numVertices))
					{
						std::cout << "\nInvalid input. The number of vertices must be a positive integer";
						numVertices = "";
					}
				}

				while(numFaces == "")
				{
					std::cout << "\nNumber of faces: ";
					std::cin >> numFaces;

					if(!IsValidUnsigned(numFaces))
					{
						std::cout << "\nInvalid input. The number of faces must be a positive integer";
						numFaces = "";
					}
				}

				while(scale == "")
				{
					std::cout << "\nScale: ";
					std::cin >> scale;

					if(!IsValidFloat(scale))
					{
						std::cout << "\nInvalid input. The scale must be a valid number";
						scale = "";
					}
				}

				while(centerPositionX == "")
				{
					std::cout << "\nCenter position x coordinate: ";
					std::cin >> centerPositionX;

					if(!IsValidFloat(centerPositionX))
					{
						std::cout << "\nInvalid input. The center position x component must be a valid number";
						centerPositionX = "";
					}
				}

				while(centerPositionY == "")
				{
					std::cout << "\nCenter position y coordinate: ";
					std::cin >> centerPositionY;

					if(!IsValidFloat(centerPositionY))
					{
						std::cout << "\nInvalid input. The center position y component must be a valid number";
						centerPositionY = "";
					}
				}

				while(centerPositionZ == "")
				{
					std::cout << "\nCenter position z coordinate: ";
					std::cin >> centerPositionZ;

					if(!IsValidFloat(centerPositionZ))
					{
						std::cout << "\nInvalid input. The center position z component must be a valid number";
						centerPositionZ = "";
					}
				}

				std::cout << "\nName: ";
				std::cin >> name;

				sceneManager.AddMesh(std::atoi(numVertices.c_str()), std::atoi(numFaces.c_str()), std::atof(scale.c_str()), Vector(std::atof(centerPositionX.c_str()), std::atof(centerPositionY.c_str()), std::atof(centerPositionZ.c_str())), name);
			}break;

			case 2:
			{
				std::string id = "";

				std::cout << "\n\n(2) Remove a mesh";

				while(id == "")
				{
					std::cout << "\n\nID: ";
					std::cin >> id;

					if(!IsValidUnsigned(id))
					{
						std::cout << "\nInvalid input. The id must be a positive integer";
						id = "";
					}
				}

				sceneManager.RemoveMesh(std::atoi(id.c_str()));
			}break;

			case 3:
			{
				sceneManager.PrintMeshes();
			}break;

			case 4:
			{
				sceneManager.SaveState();
				return 0;
			}break;

			default:
			{
				std::cout << "\n\nInvalid input\n\n";
			}break;
		}
	}

	return 0;
}
