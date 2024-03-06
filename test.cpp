#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <commdlg.h>
#include <iostream>
#include <string>
#include <iostream>
//#include "winmm.lib"
//#include "framework.h"
#include "fileHandler.h"
#include "DHT_RING.h"

#pragma comment(lib, "winmm.lib")

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

using namespace std;


//TEST(hashing, sha1xHex_to_Binary) {
//
//    std::cout << "sha1x(''):" << sha1x("") << std::endl;
//   
//    string ans = "1010100110011001001111100011011001000111000001101000000101101010101110100011111000100101011100010111100001010000110000100110110010011100110100001101100010011101x";
//    hashing Hash(2);
//    cout << "\nBINARY CONVERSION:" << endl;
//    cout << Hash.convert_to_binary("a9993e364706816aba3e25717850c26c9cd0d89d") << endl;
//    cout << "\nActuall Binary:" << endl;
//    cout << ans << endl <<  endl;
//   
//    EXPECT_EQ(Hash.convert_to_binary("a9993e364706816aba3e25717850c26c9cd0d89d"), ans);
//
//    BigInteger dec = Hash.convert_to_decimal(Hash.convert_to_binary("a9993e364706816aba3e25717850c26c9cd0d89d"));
//
//    string dec_ans = "968236873715988614170569073515315707566766479517";
//
//    cout << "\nDECIMAl CONVERSION:" << endl;
//    cout << dec.value << endl;
//    cout << "\nACTUAL DecimalValue:" << endl;
//    cout << dec_ans << endl << endl;  
//
//    EXPECT_EQ(dec.value, dec_ans);
//
//    cout << "\nMOD w. 31 for 5 bit system" << endl;
//
//    int bitcount = 5;
//    hashing  SystemHash(bitcount); 
//    BigInteger HASH_KEY = SystemHash.generate_key(sha1x(""));
//    cout << "\nOUR HASH KEY (ADT- BigInteger): " <<  HASH_KEY.value << endl;
//
//    EXPECT_EQ( HASH_KEY.value , "27" );
//
//}



TEST(TestCaseName, TestName) {

	if (removeDirectory(base_directory)) {
		std::cout <<GREEN <<"Directory removed: " <<CYAN <<base_directory <<RESET <<std::endl;
	}
	else {
		std::cout<<RED << "Failed to remove directory: " << CYAN <<base_directory <<RESET <<std::endl;
	}
	createDirectory(base_directory);
	int bits = 0, order = 0;
	system("pause");
	system("cls");

	//system("color 60");
	cout << CYAN << "\n\n\t _____ _____  ______ _____                                    \n";
	cout << CYAN << "\t|_***_|**__ \\|**____/*____|                                  \n";
	cout << CYAN << "\t  |*| |*|__)*|*|__ |*(___    _ __ ___   ___ _ __  _   _       \n";
	cout << CYAN << "\t  |*| |**___/|* __| \\___*\\  |*'_*`*_*\\ /*_*\\ '_ \\|*| |*| \n";
	cout << CYAN << "\t _|*|_|*|    |*|    ____)*| |*| |*| |*| *__/*| |*|*|_|*|      \n";
	cout << CYAN << "\t|_____|_|    |_|   |_____/  |_| |_| |_|\\___|_| |_|\\__,_|      \n";


	while (bits <= 0) {
		cout <<GREEN <<"\n\n\n\t* Enter size for DHT ring in bits : "<<CYAN;
		cin >> bits;
	}
	while (order <= 0) {
		cout << GREEN<<"\n\t* Enter order of B-tree : "<<CYAN;
		cin >> order;
	}

	cout << "\n\n\n\n\n";
	system("pause");

	//LPCSTR("G:/Tauha - FAST/Github/IPFS-inkypinkyponky/IPFS/beat.wav")
	std::string sfx = "beat.wav";

	PlaySound(L"beat.wav", NULL, SND_LOOP | SND_ASYNC);

    std:string display_in_log = "Inter Planetary File System, compiled and runned succesfully.\n\n   Group Members:\n   >1.Abdullah Zubair (22i-1077)  >2.Tauha Imran (22i-1293) >3.Saffi Muhammad Hashir (22i-1293)\n\n   >>>Bits value: " + to_string(bits) + "\n   >>>B-tree order: " + to_string(order) + "\n\n";
	writeToFile(display_in_log, filename_log_IPFS, false);
	writeToFile(display_in_log, filename_log_ROUTER, false);
	string path = "C:\\IPFS data";
	DHT_ring dht(bits, order);
	bool running = true;
	while (running)
	{
		system("cls");
		system("color 06");
		cout << CYAN << "\n\n\t _____ _____  ______ _____                                    \n";
		cout << CYAN << "\t|_***_|**__ \\|**____/*____|                                  \n";
		cout << CYAN << "\t  |*| |*|__)*|*|__ |*(___    _ __ ___   ___ _ __  _   _       \n";
		cout << CYAN << "\t  |*| |**___/|* __| \\___*\\  |*'_*`*_*\\ /*_*\\ '_ \\|*| |*| \n";
		cout << CYAN << "\t _|*|_|*|    |*|    ____)*| |*| |*| |*| *__/*| |*|*|_|*|      \n";
		cout << CYAN << "\t|_____|_|    |_|   |_____/  |_| |_| |_|\\___|_| |_|\\__,_|      \n";


		cout << GREEN << "\t=========================================================" << endl;

		cout << GREEN << "\t|1. |\tAdd Machine\t\t\t\t\t|\n";
		cout << GREEN << "\t|2. |\tPrint DHT Ring (Ascending)\t\t\t|\n";
		cout << GREEN << "\t|3. |\tPrint DHT Ring (Descending)\t\t\t|\n";
		cout << GREEN << "\t|4. |\tPrint Finger Tables\t\t\t\t|\n";
		cout << GREEN << "\t|5. |\tAdd File to Machine\t\t\t\t|\n";
		cout << GREEN << "\t|6. |\tAutomatic Machine Generation\t\t\t|\n";
		cout << GREEN << "\t|7. |\tDelete Machine and automatically transfer files\t|\n";
		cout << GREEN << "\t|8. |\tDelete File from Specific Machine\t\t|\n";
		cout << GREEN << "\t|9. |\tPrint B-tree of any Machine\t\t\t|\n";
		cout << GREEN << "\t|10.|\tPrint Files of any Machine\t\t\t|\n";
		cout << GREEN << "\t|11.|\tExit\t\t\t\t\t\t|\n";
		cout << GREEN << "\t=========================================================" << RESET << endl;

		int choice;
		cout << YELLOW << "\n\t\t >> Enter your choice: ";
		cin >> choice;


		switch (choice)
		{
		case 1:
		{
			cout << "\n\n\n" << RESET;
			cout << "Type \"exit \" to return to main menu" << endl;
			cout <<GREEN <<"Enter Machine ID : "<< CYAN;
			string machineId;
			cin >> machineId;
			if (machineId == "exit") {
				break;
			}
			dht.addmachine(machineId);

			cout << "\n\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;

			break;
		}
		case 2:

			cout << "\n\n\n" << RESET;
			dht.print_fwd();

			cout << "\n\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;

			break;
		case 3:

			cout << "\n\n\n" << RESET;
			dht.print_rev();

			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;

			break;
		case 4:
			cout << "\n\n\n" << RESET;
			dht.print_fingertable();

			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;

			break;
		case 5:
		{// case to add file...
			cout << "Type \"exit \" to return to main menu" << endl;
			cout <<GREEN <<"Enter Machine ID to add file from: "<< CYAN;
			string machineId;
			cin >> machineId;
			if (machineId == "exit") {
				break;
			}
			cout << "\n\n\n" << RESET;
			string filepath = searchfile(path);

			//if dialouge box closed....
			if (filepath == "File selection canceled") {
				break;
			}

			cout << "\n\n\n" << RESET;
			dht.inputfile(machineId, filepath, true);

			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;
			break;
		}
		case 6:
		{			cout << "Type \"0 \" to return to main menu" << endl;
			cout << GREEN<<"Enter the number of machines to generate automatically: "<< CYAN;
			int numMachines;
			cin >> numMachines;
			if (numMachines == 0) {
				break;
			}
			cout << "\n\n\n" << RESET;
			dht.automatic_activation(numMachines);

			cout << "\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;
			break;
		}
		case 7:
		{
			dht.print_fwd();
			cout << "Type \"exit \" to return to main menu" << endl;
			cout << GREEN<<"\nEnter the machine id to turn off : "<< CYAN;
			string machineId;
			cin >> machineId;
			if (machineId == "exit") {
				break;
			}
			cout << "\n\n\n" << RESET;
			dht.removemachine(machineId);

			cout << "\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;
			system("cls");
			break;
		}
		case 8:
		{
			cout << "Type \"exit \" to return to main menu" << endl;
			cout <<GREEN <<"Enter Key to Delete  : "<< CYAN;
			string machineId, deletion_path;
			cin >> machineId;
			if (machineId == "exit") {
				break;
			}
			//deletion_path = path + "\\" + machineId;
			//string filepath = searchfile(deletion_path);

			////if dialouge box closed....
			//if (filepath == "File selection canceled") {
			//	break;
			//}

			cout << "\n\n\n" << RESET;

			dht.display_node_files_to_delete(machineId);

			//dht.inputfile(machineId, filepath, false);


			cout << "\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;
			system("cls");
			break;
		}
		case 9: {
			dht.print_fwd();
			cout << "Type \"exit \" to return to main menu" << endl;
			cout <<GREEN<<"\nEnter the machine id to view B-tree : "<< CYAN;
			string machineId;
			cin >> machineId;
			if (machineId == "exit") {
				break;
			}

			cout << "\n\n\n" << RESET;
			dht.display_node_Btree(machineId);
			cout << "\n\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;
			break;
		}
		case 10: {
			dht.print_fwd();
			cout << "Type \"exit \" to return to main menu" << endl;
			cout <<GREEN<< "\nEnter the Key id to Display : "<<CYAN;
			string machineId;
			cin >> machineId;
			if (machineId == "exit") {
				break;
			}
			cout << "\n\n\n" << RESET;
			//dht.display_node_files(machineId);
			cout << "\n\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;
			break;
		}
		case 11:
			system("cls");

			cout << "\n\n" << GREEN;
			cout << "\n \t you have exited the IPFS system manager ... \n\n";

			if (removeDirectory(base_directory)) {
				std::cout << "Directory removed: " << base_directory << std::endl;
			}
			else {
				std::cerr << "Failed to remove directory: " << base_directory << std::endl;
			}

			cout << "\n\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;
			running = false;
			break;
		default:
			cout <<YELLOW <<"Invalid choice. Please enter a valid option.\n";
			cout << "\n\n\n" << RESET;
			cout << RED << endl;
			system("pause");
			cout << "\n\n\n" << RESET;
			break;
		}
	}

	EXPECT_TRUE(true);
}


//---------------------------------------------------

//TEST(fileHandling, readfrompath) {
//
//
//    //gets content from the file...
//    //std::string cntxt = read_file_from_path("C:/Users/Admin/Desktop/Semester Project DES.pdf"); 
//    //std::string cntxt = read_file_from_path("C:/Users/Admin/Desktop/test.txt");
//    //std::string cntxt = read_file_from_path("C:/Users/Admin/Pictures/9.png");
//    std::string cntxt = read_file_from_path("F:/i221084_i221239_-_DLD_Project.mp4");
//
//    std::string sha1val = sha1x(cntxt);
//    int bitcount = 5;
//    hashing  SystemHash(bitcount); 
//    BigInteger key = SystemHash.generate_key(sha1val);
//
//    cout << "\n =>>  FILE CONTENTS :: \n " << cntxt << "\n\n" << endl;
//
//    cout << "\n =>> SHA1 - ecnryption :: \n " << sha1val << "\n\n" << endl;
//
//    cout << "\n =>>  HASH KEY of file :: \n " << key.value << "\n\n" << endl;
//
//
//   EXPECT_EQ(1, 1);
//
//}


//---------------------------------------------------