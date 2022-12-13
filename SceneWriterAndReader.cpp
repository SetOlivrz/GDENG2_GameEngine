#include "SceneWriterAndReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef std::fstream FileWriter;
typedef std::fstream FileReader;


SceneWriterAndReader::SceneWriterAndReader()
{
}

SceneWriterAndReader::~SceneWriterAndReader()
{
}

void SceneWriterAndReader::writeToFile()
{
	String fileDir = "C:\\Users\\Setiel Olivarez\\Desktop\\School\\GDENG2\\Project\\Game Engine\\SavedFiles\\" + to_string(1) + ".json";

	FileWriter  sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected filename " << fileDir << "\n";

	vector<AGameObject*> allObjects = GameObjectManager::get()->getAllObjects();
	
	// WRITE IN JSON FORMAT
	sceneFile << "{" << std::endl;
	sceneFile << "\"sceneObjectData\": [" << std::endl;

	for (int i = 0; i < allObjects.size(); i++) {

		sceneFile << "{" << std::endl;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		sceneFile << "\"name\":"			<< "\" " << allObjects[i]->getName()			<< " \"," << std::endl;
		sceneFile << "\"type\":"			<< "\" " << allObjects[i]->gameObjectType		<< " \"," << std::endl;
		sceneFile << "\"hasRigidBody\":"	<< "\" "<< allObjects[i]->hasRigidBody			<< " \"," << std::endl;
		sceneFile << "\"rbType\":"			<< "\"" << allObjects[i]->rbType				<< "\" ," << std::endl;


		sceneFile << "\"position\":{\n"		<< "\"x\": " << position.m_x	<< " ,\n"		<< "\"y\": " << position.m_y	<< " ,\n" << "\"z\": " << position.m_z*-1		<< "\n },"									<< std::endl;
		sceneFile << "\"scale\":{\n"		<< "\"x\": " << scale.m_x		<< " ,\n"		<< "\"y\": " << scale.m_y		<< " ,\n" << "\"z\": " << scale.m_z			<< "\n },"									<< std::endl;
		sceneFile << "\"rotation\":{\n"		<< "\"x\": " << Utils::radToDeg(rotation.m_x)	<< " ,\n"	 << "\"y\": "		<< Utils::radToDeg(rotation.m_y) << " ,\n" << "\"z\": " << Utils::radToDeg(rotation.m_z) << " ,\n"	<< "\"w\": "	<< 0 << "\n }"	<< std::endl;
		// has more elements
		if (i < allObjects.size() - 1) 
		{
			sceneFile << "}," << std::endl;
		}
		// last element
		else 
		{
			sceneFile << "}" << std::endl;
		}
	}
	sceneFile << "] \n}" << std::endl;
	sceneFile.close();
}

std::vector<std::string> split(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}


void SceneWriterAndReader::readFromUnityFile()
{
	String fileDir = "C:\\Users\\Setiel Olivarez\\Desktop\\School\\GDENG2\\Project\\Game Engine\\SavedFiles\\Unity\\" + to_string(1) + ".json";

	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;
	String source = "Editor";

	String objectName;
	String objectType;
	String hasRigidBody;
	String rbType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	int counter = 0;;
	if (source == "Editor") {
		while (std::getline(sceneFile, readLine)) {
			//Spacer
			if (index < 3)
			{
				index++;
			}
			else if (index == 3) //name
			{
				std::vector<std::string> stringSplit = split(readLine, ' ');
				//To block last char
				if (stringSplit.size() > 2)
					objectName = stringSplit[14];
				index++;
			}
			else if (index == (4)) //type
			{
				std::vector<std::string> stringSplit = split(readLine, ' ');
				objectType = stringSplit[14];
				index++;
			}
			else if (index == (5)) //rigidbody
			{
				std::vector<std::string> stringSplit = split(readLine, ' ');
				hasRigidBody = stringSplit[14];
				index++;
			}
			else if (index == (6)) //rbtype
			{
				std::vector<std::string> stringSplit = split(readLine, ' ');
				rbType = stringSplit[14];
				index++;
			}
			//Spacer
			else if (index < (8))
			{
				index++;
			}
			//Position
			else if (index == (8)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				position.m_x = std::stof(val[0]);
				index++;
			}
			else if (index == (9)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				position.m_y = std::stof(val[0]);
				index++;
			}
			else if (index == (10)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				position.m_z = std::stof(val[0]);
				index++;
			}
			//Spacer
			else if (index < (13)) {
				index++;
			}
			//Scale
			else if (index == (13)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				scale.m_x = std::stof(val[0]);
				index++;
			}
			else if (index == (14)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				scale.m_y = std::stof(val[0]);
				index++;
			}
			else if (index == (15)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				scale.m_z = std::stof(val[0]);
				index++;
			}
			//Spacer
			else if (index < (18)) {
				index++;
			}
			//Rotation
			else if (index == (18)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				rotation.m_x = std::stof(val[0]);
				index++;
			}
			else if (index == (19)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				rotation.m_y = std::stof(val[0]);
				index++;
			}
			else if (index == (20)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				std::vector<std::string> val = split(stringSplit[17], ',');
				rotation.m_z = std::stof(val[0]);
				index = 0;
				counter++;
				GameObjectManager::get()->createObjectFromFile(objectName, objectType, hasRigidBody, rbType, position, scale, rotation);

			}

		}
	}
}


void SceneWriterAndReader::readFromEngineFile()
{
	String fileDir = "C:\\Users\\Setiel Olivarez\\Desktop\\School\\GDENG2\\Project\\Game Engine\\SavedFiles\\" + to_string(1) + ".json";

	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;
	String source = "Editor";

	String objectName;
	String objectType;
	String hasRigidBody;
	String rbType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	int counter = 0;;
	if (source == "Editor") {
		while (std::getline(sceneFile, readLine)) {
			//Spacer
			if (index < 3) 
			{
				index++;
			}
			else if (index == 3) //name
			{
				std::vector<std::string> stringSplit = split(readLine, ' ');
				//To block last char
				if (stringSplit.size() > 2)
					objectName = stringSplit[1];
				index++;
			}
			else if (index == (4)) //type
			{
				std::vector<std::string> stringSplit = split(readLine, ' ');
				objectType = stringSplit[1];
				index++;
			}
			else if (index == (5)) //rigidbody
			{
				std::vector<std::string> stringSplit = split(readLine, ' ');
				hasRigidBody = stringSplit[1];
				index++;
			}
			else if (index == (6)) //rbtype
			{
				std::vector<std::string> stringSplit = split(readLine, ' ');
				rbType = stringSplit[1];
				index++;
			}
			//Spacer
			else if (index < (8)) 
			{
				index++;
			}
			//Position
			else if (index == (8)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				position.m_x = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (9)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				position.m_y = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (10)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				position.m_z = std::stof(stringSplit[1]);
				index++;
			}
			//Spacer
			else if (index < (13)) {
				index++;
			}
			//Scale
			else if (index == (13)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				scale.m_x = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (14)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				scale.m_y = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (15)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				scale.m_z = std::stof(stringSplit[1]);
				index++;
			}
			//Spacer
			else if (index < (18)) {
				index++;
			}
			//Rotation
			else if (index == (18)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				rotation.m_x = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (19)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				rotation.m_y = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (20)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				rotation.m_z = std::stof(stringSplit[1]);
				index = -1;
				counter++;
				GameObjectManager::get()->createObjectFromFile(objectName, objectType,hasRigidBody,rbType, position, scale, rotation);

			}
			
		}
	}
}

