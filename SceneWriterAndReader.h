#pragma once
#include <string>

class SceneWriterAndReader
{
public:
	typedef std::string String;
	SceneWriterAndReader();
	~SceneWriterAndReader();

	void writeToFile();
	void readFromUnityFile();
	void readFromEngineFile();


private:
	String directory;
};