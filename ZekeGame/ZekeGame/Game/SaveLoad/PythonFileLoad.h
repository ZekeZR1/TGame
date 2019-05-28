#pragma once

class PythonFileLoad
{
public:
	static std::vector<std::string> FilesLoad();
	static std::vector<std::string> FilesLoadEnemy();
	static std::vector<std::string> FilesLoadOnlineEnemy();
};

class VisualAiFileLoad {
public:
	static std::vector<std::string> FilesLoad();
};