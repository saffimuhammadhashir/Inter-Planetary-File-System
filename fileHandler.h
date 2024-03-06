#pragma once
// these will be only functions | made by Tauha Imran 22i1239
#include<iostream>
#include<string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <windows.h>
#include <locale>
#include <codecvt>
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
using namespace std;

// Base directory for file operations
string base_directory = "C:\\IPFS data";
std::string filename_extractions(std::string path)
{
    int len = path.length();
    std::string newfilename;
    char newfiletoken = '\\';
    for (int i = len - 1; i > 0; i--)
    {
        if (path[i] != newfiletoken)
        {
            newfilename = path[i] + newfilename;
        }
        else
        {
          //  newfilename = "\\" + newfilename;
            return (newfilename);
        }
    }
}

std::string append_duplicates(std::string path, int id)
{

    int len = path.length();
    std::string newfilename;
    char newfiletoken = '.';
    for (int i = 0; i < len; i++)
    {
        if (path[i] != newfiletoken)
        {
            newfilename = newfilename + path[i];
        }
        else
        {
            newfilename = newfilename + to_string(id);
            newfilename = newfilename + path[i];
        }
    }
    return newfilename;
}

std::string mergepath(std::string path, std::string newname)
{

    int len = path.length();
    std::string newfilename;
    char newfiletoken = '\\';
    bool found = false;
    for (int i = len - 1; i >= 0; i--)
    {
        if (path[i] == newfiletoken && !found)
        {
            found = true;
        }
        else if (found)
        {
            newfilename = path[i] + newfilename;
        }

    }

    return newfilename + newname;
}
// Function to copy a file to a specified directory
bool copyFileToDirectory(const string& sourceFilePath, const string& targetDirectoryPath) {
    // Construct the target file path
    string targetFilePath = targetDirectoryPath + "\\" + sourceFilePath.substr(sourceFilePath.find_last_of("\\") + 1);

    // Attempt to copy the file
    if (CopyFileA(sourceFilePath.c_str(), targetFilePath.c_str(), FALSE) != 0) {
        cout <<GREEN <<"File copied to: " << CYAN << targetFilePath <<RESET <<endl;
        return true;
    }
    else {
        cout <<RED <<"Failed to copy file to directory." << CYAN << targetFilePath << RESET <<endl;
        return false;
    }
}


bool copyFileToDuplicateDirectory(const string& sourceFilePath, const string& targetDirectoryPath, const string& newFileName) {

    string targetFilePath = targetDirectoryPath + "\\" + newFileName;


    if (CopyFileA(sourceFilePath.c_str(), targetFilePath.c_str(), FALSE) != 0) {
        cout << GREEN << "File copied to: " << CYAN << targetFilePath <<RESET <<endl;
        return true;
    }
    else {
        cout <<RED <<"Failed to copy file to directory: " << CYAN << targetFilePath <<RESET <<endl;
        return false;
    }
}

// Function to delete a file
bool deleteFile(const string& filePath) {
    if (DeleteFileA(filePath.c_str()) != 0) {
        cout <<GREEN <<"File deleted: " << CYAN << filePath << endl;
        return true;
    }
    else {
        cout <<RED<< "Failed to delete file: " <<CYAN<< filePath <<RESET <<endl;
        return false;
    }
}

// Function to create a directory
bool createDirectory(const string& directoryPath) {
    if (CreateDirectoryA(directoryPath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
        cout <<GREEN <<"Directory created: " << CYAN << directoryPath <<RESET<< endl;
        return true;
    }
    else {
        cout <<RED <<"Failed to create directory: " << CYAN << directoryPath << RESET << endl;
        return false;
    }
}

// Function to remove a directory and its contents recursively
bool removeDirectory(const std::string& directoryPath) {
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((directoryPath + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        // No files or subdirectories found
        FindClose(hFind);
        return RemoveDirectoryA(directoryPath.c_str()) != 0;
    }

    do {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            // Construct full file/directory path
            std::string filePath = directoryPath + "\\" + findFileData.cFileName;

            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // Recursively remove subdirectories
                if (!removeDirectory(filePath)) {
                    FindClose(hFind);
                    return false;
                }
            }
            else {
                // Remove files
                if (DeleteFileA(filePath.c_str()) == 0) {
                    FindClose(hFind);
                    return false;
                }
            }
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    // Remove the empty directory itself
    FindClose(hFind);
    return RemoveDirectoryA(directoryPath.c_str()) != 0;
}

// Function to convert std::string to LPCWSTR
LPCWSTR stringToLPCWSTR(const std::string& str) {
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wideStr = new wchar_t[bufferSize];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wideStr, bufferSize);
    return wideStr;
}

// Function to open a file dialog for file selection
std::string searchfile(const std::string& initialPath) {
    OPENFILENAME ofn;
    TCHAR szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(*szFile);
    ofn.lpstrFilter = L"All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrTitle = L"Select a File";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.lpstrInitialDir = stringToLPCWSTR(initialPath);

    if (GetOpenFileName(&ofn) == TRUE) {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(ofn.lpstrFile);
    }
    else {
        return "File selection canceled";
    }
}

// Log file paths
string filename_log_IPFS = "C:\\IPFS data\\IPFSlog.txt";
string filename_log_ROUTER = "C:\\IPFS data\\IPFSRouterlog.txt";

// Function to read content from a file
string read_file_from_path(string filepath = "?") {
    // If the string passed was incorrect...
    if (filepath == "?") {
        return "?";
    }

    fstream file; // File reading object
    file.open(filepath, ios::in); // Open the file in reading mode

    if (!file.is_open()) {
        // If file error, abort reading
        cout <<RED <<"\n ::: FILE CAN'T BE OPENED ::: return \"?\" ; \n"<<RESET;
        file.close(); // Close the file
        return "?"; // Return exception value
    }
    else {
        string content_str = ""; // Buffer string
        while (!file.eof()) {
            // eof() = end of file, boolean for if the end of file is reached
            string line = "";
            getline(file, line); // Put file content in the string content_str
            content_str += line;
        }
        file.close(); // Close the file
        // Return the content
        return content_str;
    }
}

// Function to write content to a file with optional timestamp
void writeToFile(const string& content, const string& filename, bool append = true, bool time = true) {
    ios_base::openmode mode = append ? ios::app : ios::out;
    ofstream file(filename, mode);
    file.is_open();
    if (time) {
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        file << "\n==>" << ctime(&now) << "   " << content;
    }
    else {
        file << "\n   " << content;
    }
    file.close();
}
ifstream openFile(const string& filePath) {
    ifstream file(filePath);

    if (file.is_open()) {
        cout << GREEN<<"File opened successfully: "<<CYAN << filePath << RESET << endl;
    }
    else {
        cout <<RED <<"Failed to open file: " << CYAN << filePath << RESET << endl;
    }

    return file;
}

void passfile_path(string filePath) {

    ifstream inputFile = openFile(filePath);


    if (inputFile.is_open()) {

        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;
        }
        inputFile.close();
    }


}