#pragma once
#include <iostream>
#include <time.h>
//#include "B-tree.h"
//#include "BigInteger.h"
#include "router.h"
#include "fileHandler.h"
#include "hashing.h"
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
using namespace std;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class DHT_ring
{
    BigInteger count_machines;
    BigInteger adding_val;
    BigInteger bitcount;
    BigInteger base;
    int bits;
    int tree_order;
    Node* start;
    Node* end;
    trackkeeping* searchinglist_start, * searchinglist_end;

public:
    DHT_ring()
    {
        std::string val = "2";
        base.value = val;
        start = end = nullptr;
        count_machines.value = "0";
        adding_val.value = "1";
    }

    DHT_ring(int bit_val, int BtreeOrder = 5)
    {
        if (bit_val > 160)
        {
            bit_val = 160;
        }
        tree_order = BtreeOrder;
        std::string val = "2";
        base.value = val;
        bitcount.value = base.power(bit_val).value;
        bits = bit_val;
        start = end = nullptr;
        count_machines.value = "0";
        adding_val.value = "1";

    }


    void addmachine(std::string val)
    {
        writeToFile("Manual addition of " + val + " Machine", filename_log_IPFS);
        insert(val);
        createfingertable();
    }


    void pass_limits(Node* create)
    {

        create->DHT_start = start;
        create->DHT_end = end;
    }

    bool insert(std::string val)
    {
        std::string newfolder = base_directory + "\\" + val;

        BigInteger machineid(val);
        if (machineid >= bitcount)
        {
            std::cout << "MACHINE OUT OF RING DOMAIN" << std::endl;
            writeToFile("MACHINE OUT OF RING DOMAIN, MACHINE ADDITION FAILED FOR: " + val, filename_log_IPFS, true, false);
            return false;
        }
        Node* create = new Node(machineid, bits, tree_order);

        if (start == nullptr)
        {
            start = create;
            end = create;
            cout << "Machine added successfully!\n";
            writeToFile("Machine added successfully! :" + val, filename_log_IPFS, true, false);
            createDirectory(newfolder);
            //create->splitaddmachine(create, create->next);
            count_machines = count_machines + adding_val;
            return true;
        }
        else
        {
            if (create->getId() < start->getId())
            {
                create->next = start;
                start->prev = create;
                end->next = create;
                create->prev = end;
                start = create;
                cout << "Machine added successfully!\n";
                writeToFile("Machine added successfully! :" + val, filename_log_IPFS, true, false);
                createDirectory(newfolder);
                create->splitaddmachine(create, create->next);
                count_machines = count_machines + adding_val;
                return true;
            }

            Node* curr = start;
            Node* prev = start;
            while (curr != end)
            {

                if (curr->getId() == create->getId())
                {
                    cout << "Machine already exists!\n";
                    writeToFile("Machine already exists!:" + val, filename_log_IPFS, true, false);
                    return false;
                }
                else if (curr->getId() > create->getId())
                {
                    prev->next = create;
                    create->prev = prev;
                    curr->prev = create;
                    create->next = curr;
                    if (curr == start)
                    {
                        start = create;
                    }
                    cout << "Machine added successfully!\n";
                    writeToFile("Machine added successfully! :" + val, filename_log_IPFS, true, false);
                    createDirectory(newfolder);
                    create->splitaddmachine(create, create->next); //splits files amongs sets
                    count_machines = count_machines + adding_val;
                    return true;
                }
                prev = curr;
                curr = curr->next;
            }
            if (curr->getId() == create->getId())
            {
                cout << "Machine already exists!\n";
                return false;
            }
            else if (curr->getId() > create->getId())
            {
                prev->next = create;
                create->prev = prev;
                curr->prev = create;
                create->next = curr;
                cout << "Machine added successfully!\n";
                writeToFile("Machine added successfully! :" + val, filename_log_IPFS, true, false);
                createDirectory(newfolder);
                create->splitaddmachine(create, create->next); //splits files amongs sets
                count_machines = count_machines + adding_val;
                return true;
            }
            else
            {
                end->next = create;
                create->next = start;
                start->prev = create;
                create->prev = end;
                end = create;
                cout << "Machine added successfully!\n";
                writeToFile("Machine added successfully! :" + val, filename_log_IPFS, true, false);
                createDirectory(newfolder);
                create->splitaddmachine(create, create->next); //splits files amongs sets
                count_machines = count_machines + adding_val;
                return true;
            }
        }
    }

    void print_fwd()
    {
        cout <<GREEN <<"ASCENDING PRINTING" << RESET<<endl;
        writeToFile("ASCENDING PRINTING FUNCTION CALLED!", filename_log_IPFS);
        if (start != nullptr)
        {

            Node* curr = start;
            while (curr != end)
            {
                std::cout << curr->getId().value <<"     ";
                curr = curr->next;
                if (curr == end) {
                    break;
                }
                std::cout << curr->getId().value <<"     ";
                curr = curr->next;
                if (curr == end) {
                    break;
                }
                std::cout << curr->getId().value <<endl;
                curr = curr->next;
            }
            std::cout << curr->getId().value << std::endl;
        }
    }

    void print_rev()
    {
        cout << GREEN << "DESCENDING PRINTING" << RESET << endl;
        writeToFile("DESCENDING PRINTING FUNCTION CALLED!", filename_log_IPFS);
        if (start != nullptr)
        {
            Node* curr = end;
            while (curr != start)
            {
                std::cout << curr->getId().value << "     ";
                curr = curr->prev;
                if (curr == start) {
                    break;
                }
                std::cout << curr->getId().value << "     ";
                curr = curr->prev;
                if (curr == start) {
                    break;
                }
                std::cout << curr->getId().value << endl;
                curr = curr->prev;
            }
            std::cout << curr->getId().value << std::endl;
        }
    }

    void print_fingertable()
    {

        if (start == nullptr) {
            cout << "NO ACTIVE MACHINE!" << endl;
            return;
        }
        writeToFile("FINGER TABLE PRINTING FUNCTION CALLED!", filename_log_IPFS);
        createfingertable();
        system("cls");
        cout <<RED <<"FINGER TABLE PRINTING"<<YELLOW << endl;
        int choice = 0;
        cout << RED << "Choose Finger table printing type:" << endl;
        cout <<GREEN <<"1. Printing  of specific Machine's Finger table." << endl;
        cout << "2. Printing  of all the Machine's Finger table." << endl;
        do {
            cout <<YELLOW <<"Enter your choice: "<<CYAN; cin >> choice;
        } while (choice != 1 && choice != 2);
        std::string machine_id;
        BigInteger value_ft;
        router lookup;
        Node* curr;
        switch (choice) {
        case 1:
            cout << "Enter machine id to view routing :"; cin >> machine_id;
            value_ft.value = machine_id;
            if (value_ft >= bitcount) {
                std::cout << "MACHINE OUT OF RING DOMAIN" << std::endl;
                return;
            }
            curr = lookup.route_to_node(start, BigInteger(machine_id));
            cout << endl;
            writeToFile("FINGER TABLE PRINTED FOR: " + machine_id, filename_log_IPFS, true, false);
            writeToFile("FINGER TABLE PRINTED FOR: " + curr->getId().value, filename_log_IPFS, true, false);
            curr->drawFingerTable();

            break;

        case 2:


            curr = start;
            while (curr != end)
            {
                curr->drawFingerTable();
                writeToFile("FINGER TABLE PRINTED FOR: " + curr->getId().value, filename_log_IPFS, true, false);
                curr = curr->next;
            }
            curr->drawFingerTable();
            writeToFile("FINGER TABLE PRINTED FOR: " + curr->getId().value, filename_log_IPFS, true, false);

            break;
        }

    }

    void createfingertable()
    {

        Node* curr = start;
        while (curr != end)
        {
            pass_limits(curr);
            curr->createFingerTable();
            curr = curr->next;
        }
        pass_limits(curr);
        curr->createFingerTable();
    }

    void automatic_activation(int val)
    {
        writeToFile("Auto-Matic addition of " + std::to_string(val) + " Machines", filename_log_IPFS);

        for (int i = 0; i < val; i++)
        {
            if (insert("0")) {
                std::cout << GREEN << i + 1 << " AUTOMATICALLY GENERATED MACHINE: " << 0 << RESET << std::endl;
                i++;
            }

            if (count_machines >= bitcount) {
                cout << "RING DHT IS FULL" << endl;
                return;
            }
            BigInteger value;
            BigInteger add("1");
            std::string value_is;

            do
            {
                int a = rand() % 5 + 1;
                value = value.generateRandomBigInteger(a);
                value = (value % bitcount) - add;
                value = value + add;
                value_is = value.toString();

            } while (!insert(value_is));

            std::cout << GREEN << i + 1 << " AUTOMATICALLY GENERATED MACHINE: " << value_is << RESET << std::endl;
        }
        createfingertable();
    }

    //...........................................................
    void inputfile(std::string Machineid, std::string filepath, bool input = true)
    {          //- id to search from , id to go to/hashmakerVal

        if (start == nullptr)
        {
            cout << "NO MACHINE IN THE SYSTEM, ADD MACHINE FIRST" << endl;
            return;
        }
        /*else if (start->getFingertable() == nullptr) {
                createfingertable();
                print_fingertable();
        }*/

        router lookup; //obj of the router class...
        hashing key(bits);

        //BigInteger id(key.generate_key(filepath));
        BigInteger id(filepath);
        std::string hashvalue = filepath; //is used as avariable when in deletion...

        //****************************************************
        //***** Hashing call of file inout via filepaths *****
        //****************************************************
     //   if (input) { //if a filepath is sent to input the stuff 
        hashing hashFunction(bits);
        id.value = (hashFunction.generate_key(sha1x(read_file_from_path(filepath)))).value;
        hashvalue = id.value;
        cout << "\n\n HASH VALUE OF THE FILE : " << id.value << "\n\n";
        // }
         //****************************************************
         //****************************************************

        Node* curr = lookup.route_to_node(start, BigInteger(Machineid));

        // // caseX-node-0 node ringDHT.... //if routing to the zero node and headt-tail ambiguity
        if (start->getId() <= id && end->getId() < id && start->getId() == BigInteger("0")) {
            cout << "-->our case \n";
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
            curr = start;
            router lookup;
            start->add_remove_file(hashvalue, filepath, input);
            lookup.route_to_node(start, start->getId());
            writeToFile("File " + filepath + " added to machine " + start->getId().value + " Machine", filename_log_IPFS);
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }


         // case 0 1 node ringDHT....
        if (start->next == start && end->prev == end) {
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
            curr = start;
            router lookup;
            start->add_remove_file(hashvalue, filepath, input);
            lookup.route_to_node(start, start->getId());
            writeToFile("File " + filepath + " added to machine " + start->getId().value + " Machine", filename_log_IPFS);
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }


        

        // case 1  out of ranges
        if (id > bitcount || BigInteger(Machineid) > bitcount) {
            cout << "NO SUCH MACHINE EXISTS IN THE SYSTEM, ADD MACHINE FIRST" << endl;
            return;
        }

        // case 2-A - if LOOKUP NODE to search from is in range && >end.id && <=max_val
        // case 2-B - if NODE for file insertion is in range && >end.id && <=max_val
        if (id > end->getId() && BigInteger(Machineid) > end->getId()) {
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
            curr = start;
            curr->add_remove_file(hashvalue, filepath, input);
            lookup.route_to_node(curr, curr->getId());
            writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }

        // case 2-C - if NODE for file insertion is same as the
        if (id == end->getId() && BigInteger(Machineid) == end->getId()) {
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
            curr = end;
            lookup.route_to_node(curr, curr->getId());
            curr->add_remove_file(hashvalue, filepath, input);
            writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }


        // end to start linking case-3 / already on machine set
        if ((BigInteger(hashvalue) <= id && curr->prev->getId() < BigInteger(hashvalue))) {
            if (BigInteger(Machineid) <= end->getId() && BigInteger(Machineid) > end->prev->getId()) {
                cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
                curr = end;
                lookup.route_to_node(curr, curr->getId());
                lookup.terminate_routing(true);//stores and clears routing history buffers
                return;
            }
        }

        // end to start linking case-4 / less than start set already
        if (curr == start && id <= start->getId() && end->next == curr && bitcount > id) {
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
            curr->add_remove_file(hashvalue, filepath, input);
            writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
            lookup.route_to_node(curr, curr->getId());
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }

        // end to start linking case-5 / greater than end set already
        if (curr == start && id > end->getId() && end->next == curr && bitcount > id) {
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
            curr->add_remove_file(hashvalue, filepath, input);
            writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
            lookup.route_to_node(curr, curr->getId());
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }

        // end to start linking case-5.5 / greater than end set already
        if (id > end->getId() && bitcount > id) {
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
            curr = end;
            curr->add_remove_file(hashvalue, filepath, input);
            writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
            lookup.route_to_node(curr, curr->getId());
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }

        //already on the requiored location...
        if (lookup.is_in_correct_set(start, curr, hashvalue, bitcount)) {
            curr->add_remove_file(hashvalue, filepath, input);
            writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << filepath << endl;
            lookup.route_to_node(curr, curr->getId());
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }

        //case = 6 we can go about normal traversals...
        // if not cases start routing traversals...
        //!(BigInteger(hashvalue) <= id && curr->prev->getId() < BigInteger(hashvalue))
        //
        while (!lookup.is_in_correct_set(start, curr, hashvalue, bitcount))
        {

            //curr = curr->next - w/ FT routing and machine-ID updations;
            lookup.route_next_node(curr, hashvalue, id);
                
        
            //std::cout << "HERE->";
            if (lookup.is_in_correct_set(start, curr, hashvalue, bitcount)) {
                curr->add_remove_file(hashvalue, filepath, input);
                writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
                cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << filepath << endl;
                lookup.route_to_node(curr, curr->getId());
                lookup.terminate_routing(true);//stores and clears routing history buffers
                return;
            }

            if (BigInteger(hashvalue) <= id && curr->prev->getId() < BigInteger(hashvalue))
            {
                curr->add_remove_file(hashvalue, filepath, input);
                writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
                cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << filepath << endl;
                lookup.route_to_node(curr, curr->getId());
                lookup.terminate_routing(true);//stores and clears routing history buffers
                return;
            }

            //std::cout << "\nHERE\n" << endl;
            //curr = curr->next; old version...

        }
            
        //if (lookup.is_in_correct_set(start, curr, hashvalue, bitcount)) {
        //    curr->add_remove_file(hashvalue, filepath, input);
        //    writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
        //    cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << filepath << endl;
        //    lookup.route_to_node(curr, curr->getId());
        //    lookup.terminate_routing(true);//stores and clears routing history buffers
        //    return;
        //}

        //case 7 , if last id to be found or it doesn't exist...
        if (curr->getId() == id)
        {
            cout << "FILE SUCCESSFULLY ADDED TO MACHINE :" << Machineid << endl;
            curr->add_remove_file(hashvalue, filepath, input);
            writeToFile("File " + filepath + " added to machine " + curr->getId().value + " Machine", filename_log_IPFS);
            lookup.terminate_routing(true);//stores and clears routing history buffers
            return;
        }
        else
        {
            std::cout << "NOTHING RAN--";
            cout << "NO SUCH MACHINE EXISTS IN THE SYSTEM, ADD MACHINE FIRST" << endl;
            lookup.terminate_routing(false);//stores and clears routing history buffers
        }
    }
    //...........................................................

    void removemachine(std::string val)
    {
        if (start == nullptr)
        {
            cout << "NO MACHINE IN THE SYSTEM, ADD MACHINE FIRST" << endl;
            return;
        }

        BigInteger search_machine(val);
        Node* curr = start, * prev = start, * next = nullptr;
        bool deleted = false;

        // Find the machine to be deleted
        while (curr != end)
        {
            if (curr->getId() == search_machine)
            {

                if (start == curr) {

                    end->next = curr->next;
                    curr->next->prev = end;
                    start = end->next;
                }
                else {
                    prev->next = curr->next;
                    curr->next->prev = prev;

                }

                deleted = true;
                break;
            }

            prev = curr;
            curr = curr->next;
        }

        // Check if the last machine in the ring is the one to be deleted
        if (curr->getId() == search_machine && !deleted)
        {
            prev->next = start;
            start->prev = prev;
            end = start->prev;
            deleted = true;

        }

        if (!deleted)
        {
            cout << "NO SUCH MACHINE FOUND" << endl;
            return;
        }
        /*

        next  next active machine


        */
        // createfingertable();
        curr->splitdeletemachine(curr, curr->next);
        std::string newfolder = base_directory + "\\" + val;
        removeDirectory(newfolder);
        count_machines = count_machines - adding_val;
        delete curr;
    }

    void display_node_Btree(std::string machineId) {
        if (start == nullptr) {
            std::cout << "No machine in System Yet" << std::endl;
            return;
        }
        router traverser;
        Node* curr = traverser.route_to_node(start, BigInteger(machineId));
        std::cout << "\n\n CONTENTS OF Node #" << curr->getId().value << "'s B-tree :\n\n";

        curr->filesystem->print(curr->filesystem->root);

        return;
    }

    void display_node_files(std::string machineId) {
        if (start == nullptr) {
            std::cout << "No machine in System Yet" << std::endl;
            return;
        }
        router traverser;
        Node* curr = traverser.route_to_node(start, BigInteger(machineId));
        std::cout << "\n\n CONTENTS OF MACHINE #" << machineId << "'s B-tree :\n\n";

        int sizex = 0;
        FileNode** contents = curr->filesystem->search(machineId, sizex);

        std::cout << " key \t|\t\t filepaths \t\n";
        for (int i = 0; i < sizex; i++) {
            std::cout << i + 1 << " " << contents[i]->Hkey << "\t|\t" << contents[i]->value << "\n";
        }
        int index;
        cout << "\nInput File index to open it and press " << sizex + 1 << " to return:"; cin >> index;
        if (index < sizex + 1 && index > 0) {
            cout << CYAN << endl;
            passfile_path(contents[index - 1]->value);
            return;
        }


        return;
    }
    void display_node_files_to_delete(std::string machineId) {
        if (start == nullptr) {
            std::cout << "No machine in System Yet" << std::endl;
            return;
        }
        router traverser;
        Node* curr = traverser.route_to_node(start, BigInteger(machineId));
        std::cout << "\n\n CONTENTS OF MACHINE #" << machineId << "'s B-tree :\n\n";

        int sizex = 0;
        FileNode** contents = curr->filesystem->search(machineId, sizex);

        std::cout << " key \t|\t\t filepaths \t\n";
        for (int i = 0; i < sizex; i++) {
            std::cout << i + 1 << " " << contents[i]->Hkey << "\t|\t" << contents[i]->value << "\n";
        }
        int index;
        cout << "\nInput File index to open it and press " << sizex + 1 << " to return:"; cin >> index;
        if (index < sizex + 1 && index > 0) {
            cout << CYAN << endl;
            // passfile_path(contents[index - 1]->value);
            cout <<"Path to delete file: " << contents[index - 1]->value << endl;
            deleteFile(contents[index - 1]->value);
            curr->filesystem->deleteNode(contents[index - 1]->Hkey, contents[index - 1]->value);

            return;
        }


        return;
    }

};
