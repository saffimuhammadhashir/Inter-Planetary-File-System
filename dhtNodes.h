#pragma once
#include <iostream>
#include <time.h>
#include "B-tree.h"
#include "BigInteger.h"
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
using namespace std;

class Node;
class FingerTable;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class trackkeeping
{
public:
    trackkeeping()
    {
        link = nullptr;
        next = prev = nullptr;
    }
    Node* link;
    trackkeeping* next, * prev;
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class FingerTable
{
    int index;
    BigInteger machineId;

public:
    Node* pointerToNode;
    FingerTable* next;

    FingerTable()
    {
        next = nullptr;
        pointerToNode = nullptr;
    }

    void setIndex(int val)
    {
        index = val;
    }

    int getIndex()
    {
        return index;
    }

    void setMachineId(BigInteger val)
    {
        machineId = val;
    }

    BigInteger getMachineId()
    {
        return machineId;
    }

    friend class router;
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class Node
{

    BigInteger id, modulus_value;
    bool active;
    std::string filename;
    FingerTable* finger_table;
    BigInteger base;
    int bitcount;

    void searchNextActiveNode(BigInteger val, FingerTable*& obj)
    {
        // cout << "\n\nFor :" << id.value << endl;
        Node* curr = DHT_start;
        while (curr != DHT_end)
        {

            if (val <= curr->getId())
            {
                //  cout << "inner1 " << curr->getId().value << "    " << val.value << endl;
                obj->setMachineId(curr->getId());
                obj->pointerToNode = curr;
                return;
            }

            curr = curr->next;
        }
        if (curr->getId() >= val)
        {
            //cout << "outer1 " << curr->getId().value << "    " << val.value << endl;
            obj->setMachineId(curr->getId());
            obj->pointerToNode = curr;
            return;
        }
        //   cout << "outer2 " << curr->getId().value << "    " << val.value << endl;
        obj->setMachineId(DHT_start->getId());
        obj->pointerToNode = DHT_start;
    }

public:
    Node* next;
    Node* prev;
    Node* DHT_start, * DHT_end;
    BTree* filesystem;

    Node(int order = 5)
    {
        DHT_start = DHT_end = nullptr;
        active = true;
        next = prev = nullptr;
        finger_table = nullptr;
        filesystem = new BTree(order);
    }

    Node(BigInteger id_val, int bit_val, int order)
    {
        DHT_start = DHT_end = nullptr;
        bitcount = bit_val;
        id = id_val;
        active = true;
        next = prev = nullptr;
        filesystem = new BTree(order);
        base.value = "2";
        modulus_value = base.power(bitcount);
        // for (int i = 0; i < bitcount; i++)
        // {
        //     addFingerTable();
        // }
    }

    BigInteger getId()
    {
        return id;
    }

    void setId(BigInteger id_val)
    {
        id = id_val;
    }

    bool getActivity()
    {
        return active;
    }

    void deactivate()
    {
        active = false;
        deleteFingerTableList();
    }

    void add_remove_file(std::string key, std::string filepath, bool insert)
    {
        //filename = fname;
        if (insert) {
            FileNode** f = NULL;
            int sizef = 0;

            filesystem->searchrecurs(filesystem->root, f, sizef, key);

            cout <<CYAN <<"\nDuplicates: " << sizef <<RESET <<endl<<endl;

            std::string newpath = append_duplicates(filepath, sizef);

            newpath = filename_extractions(newpath);
            cout <<RED<<"FILE NAME : "<<GREEN << newpath <<RESET <<endl;
            std::string dupsdirectory = base_directory + "\\dups";
            createDirectory(dupsdirectory);


            copyFileToDuplicateDirectory(filepath, dupsdirectory, newpath);

            filepath = dupsdirectory + "\\" + newpath;
            cout << RED <<"\nPATH TO FILE : "<<GREEN <<filepath <<RESET <<endl;
            std::string destination = base_directory + "\\" + id.value;
            copyFileToDirectory(filepath, destination);
            filepath = base_directory + "\\" + this->getId().value + "\\" + newpath;
            filesystem->insert(key, filepath);
            // deleteFile(filepath);
            // removeDirectory(dupsdirectory);
        }
        else {
            //leave for duplicates
            filesystem->deleteNode(key);
           
            deleteFile(filepath);
        }

        filesystem->print(filesystem->root);
    }

    std::string getFilename()
    {
        return filename;
    }

    FingerTable* getFingertable() {
        return finger_table;
    }

    void createFingerTable()
    {
        deleteFingerTableList();
        finger_table = nullptr;
        for (int i = 0; i < bitcount; i++)
        {
            addFingerTable();
        }
        if (active)
        {
            FingerTable* curr = finger_table;
            for (int i = 0; i < bitcount; i++)
            {

                curr->setIndex(i + 1);
                BigInteger powervalue = base.power(i);
                BigInteger estd_value = id + powervalue;
                estd_value = estd_value % modulus_value;

                searchNextActiveNode(estd_value, curr);
                curr = curr->next;
            }
        }
    }

    void addFingerTable()
    {
        FingerTable* create = new FingerTable();
        if (finger_table == nullptr)
        {
            finger_table = create;
        }
        else
        {
            FingerTable* curr = finger_table;
            while (curr->next != nullptr)
            {
                curr = curr->next;
            }
            curr->next = create;
        }
    }

    void deleteFingerTableList()
    {
        finger_table = nullptr;
        // if (finger_table != nullptr) {
        //     FingerTable* curr = finger_table;
        //     FingerTable* nextNode;
        //     while (curr != nullptr)
        //     {
        //         nextNode = curr->next;
        //         delete curr;
        //         curr = nextNode;
        //     }
        // finger_table = nullptr;
        // }
    }

    void drawFingerTable()
    {
        cout <<GREEN <<"Finger Table for " << id.value <<RESET <<endl
            << endl;
        FingerTable* curr = finger_table;
        while (curr != nullptr)
        {
            std::cout << curr->getIndex() << "   " << curr->getMachineId().value << std::endl;
            curr = curr->next;
        }
    }
    //...............................................................
    void splitaddmachine(Node* added, Node* nextadd) {
        if (nextadd->filesystem->root->keycount > 0) {
            nextadd->filesystem->additionmachineB(added->filesystem, added->id.value, nextadd->id.value);
        }
    }

    void splitdeletemachine(Node* added, Node* nextadd) {
        if (added->filesystem->root->keycount > 0) {
            added->filesystem->deletionmachineB(nextadd->filesystem, added->id.value, nextadd->id.value);
        }
    }
    //...............................................................

    friend class router;
};
