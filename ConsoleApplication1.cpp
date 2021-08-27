// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "./AlienFX-SDK/AlienFX_SDK.h"
#include "./alienfx-cli/LFXUtil.h"
#include <fstream>
using namespace std;

namespace
{
	LFXUtil::LFXUtilC lfxUtil;
}

int random(int max, int min) {
	return rand() % (max - min + 1) + min;
}
bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}


vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if ("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型
	char* strs = new char[str.length() + 1]; //不要忘了
	strcpy(strs, str.c_str());

	char* d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char* p = strtok(strs, d);
	while (p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(NULL, d);
	}

	return res;
}

//loopkeyboard, 0(notReverse)|1(reverse), 0, 255, 0

void loopKeyboardOnce(int reverse, int r, int g, int b) {
	if (reverse == 0) {
		//not reverse
		for (int i = 0; i < 4; i++) {
			AlienFX_SDK::Functions::SetColor(i, r, g, b);
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);

			AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
			AlienFX_SDK::Functions::UpdateColors();
			AlienFX_SDK::Functions::Reset(false);
		}
	}
	else {
		for (int i = 4; i > 0; i--) {
			AlienFX_SDK::Functions::SetColor(i, r, g, b);
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);

			AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
			AlienFX_SDK::Functions::UpdateColors();
			AlienFX_SDK::Functions::Reset(false);
		}
	}
}

void loopKeyboardRandom(int reverse) {
	if (reverse == 0) {
		//not reverse
		for (int i = 0; i < 4; i++) {
			AlienFX_SDK::Functions::SetColor(i, random(255, 100), random(255, 100), random(255, 100));
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);

			AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
			AlienFX_SDK::Functions::UpdateColors();
			AlienFX_SDK::Functions::Reset(false);
		}
	}
	else {
		for (int i = 4; i > 0; i--) {
			AlienFX_SDK::Functions::SetColor(i, random(255, 100), random(255, 100), random(255, 100));
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);

			AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
			AlienFX_SDK::Functions::UpdateColors();
			AlienFX_SDK::Functions::Reset(false);
		}
	}
}

void loopLightBarOnce(int reverse,int r,int g,int b) {

	if (reverse == 0) {
		for (int i = 4; i < 16; i++) {
			AlienFX_SDK::Functions::SetColor(i, r, g, b);
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);

			AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
			AlienFX_SDK::Functions::UpdateColors();
			AlienFX_SDK::Functions::Reset(false);
		}
	}
	else {
		for (int i = 16; i > 5; i--) {
			AlienFX_SDK::Functions::SetColor(i, r, g, b);
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);

			AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
			AlienFX_SDK::Functions::UpdateColors();
			AlienFX_SDK::Functions::Reset(false);
		}
	}


}


void loopLightBarRandom(int reverse) {
	if (reverse == 0) {
		for (int i = 4; i < 16; i++) {
			AlienFX_SDK::Functions::SetColor(i, random(255,100), random(255, 100), random(255, 100));
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);

			AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
			AlienFX_SDK::Functions::UpdateColors();
			AlienFX_SDK::Functions::Reset(false);
		}
	}
	else {
		for (int i = 16; i > 5; i--) {
			AlienFX_SDK::Functions::SetColor(i, random(255, 100), random(255, 100), random(255, 100));
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);

			AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
			AlienFX_SDK::Functions::UpdateColors();
			AlienFX_SDK::Functions::Reset(false);
		}
	}


}

void reset() {
	for (int i = 0; i < 16; i++) {
		AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
		AlienFX_SDK::Functions::UpdateColors();
		AlienFX_SDK::Functions::Reset(false);
	}
}


void parseDIYLine(string line) {
	std::vector<string> res = split(line, ", ");
	std::string command = res[0];
	if (is_number(command)) {
		AlienFX_SDK::Functions::SetColor(std::stoi(command), std::stoi(res[1]), std::stoi(res[2]), std::stoi(res[3]));
		AlienFX_SDK::Functions::UpdateColors();
	}
	else {
		if (command == "loopkeyboard") {
			loopKeyboardOnce(std::stoi(res[1]), std::stoi(res[2]), std::stoi(res[3]), std::stoi(res[4]));
		}
		else if (command == "loopkeyboardRandom") {
			loopKeyboardRandom(std::stoi(res[1]));
		}
		else if (command == "looplightbar") {
			loopLightBarOnce(std::stoi(res[1]), std::stoi(res[2]), std::stoi(res[3]), std::stoi(res[4]));
		}
		else if (command == "looplightbarRadom") {
			loopLightBarRandom(std::stoi(res[1]));
		}
	}
}
int main(int argc, char* argv[])
{
	//the code start from here, credit is belongs to Github: @T-Troll
	//LanHao: those code are good! thanks!
	int numlights = 16;
	vector<int> pids;
	pids = AlienFX_SDK::Functions::AlienFXEnumDevices(AlienFX_SDK::Functions::vid);
	if (pids.size() > 0) {
		cout << "Found " << pids.size() << " device(s)" << endl;
		cout << "Probing Dell SDK... ";
		int res = lfxUtil.InitLFX();
		if (res != -1) {
			switch (res) {
			case 0: cerr << "Dell library DLL not found (no library?)!" << endl; break;
			case 1: cerr << "Can't init Dell library!" << endl; break;
			case 2: cerr << "No high-level devices found!" << endl; break;
			default: cerr << "Dell library unknown error!" << endl; break;
			}
			// No SDK detected
			cout << "No LightFX SDK detected, you should provide names yourself!" << endl;
		}
		else {
			lfxUtil.FillInfo();
			cout << "Found!" << endl << endl;
			for (unsigned cdev = 0; cdev < lfxUtil.GetNumDev(); cdev++) {
				cout << "Device #" << cdev << " (" << lfxUtil.GetDevInfo(cdev)->desc << "):" << endl;
				for (UINT i = 0; i < lfxUtil.GetDevInfo(cdev)->lights; i++) {
					cout << "\tLight #" << lfxUtil.GetLightInfo(cdev, i)->id
						<< " - " << lfxUtil.GetLightInfo(cdev, i)->desc << endl;
				}
			}
		}
		for (int cdev = 0; cdev < pids.size(); cdev++) {
			cout << "Probing device PID 0x..." << std::hex << pids[cdev];
			int isInit = AlienFX_SDK::Functions::AlienFXChangeDevice(pids[cdev]);
			if (isInit != -1)
			{
				cout << " Connected." << endl;
				char name[256], * outName;
				int count;
				for (count = 0; count < 5 && !AlienFX_SDK::Functions::IsDeviceReady(); count++)
					Sleep(20);
				AlienFX_SDK::Functions::Reset(false);
				cout << "Enter device name or id: ";
				std::cin.getline(name, 255);
				if (isdigit(name[0]) && res == (-1)) {
					outName = lfxUtil.GetDevInfo(atoi(name))->desc;
				}
				else {
					outName = name;
				}
				cout << "Final name is " << outName << endl;
				AlienFX_SDK::devmap devs;
				devs.devid = pids[cdev];
				devs.name = outName;
				AlienFX_SDK::Functions::GetDevices()->push_back(devs);
				// How many lights to check?
				if (argc > 1) // we have number of lights...
					numlights = atoi(argv[1]);
				// Let's probe low-level lights....

				//select the file
				reset();
				char filename[256];
				//cout << "Enter DIY txt filename: ";
				//std::cin.getline(filename, 255);
				std::ifstream input("transport.txt");

				while (true) {
					std::ifstream input("transport.txt");
					for (std::string line; getline(input, line); )
					{
						cout << line;

						if (is_number(line)) {
							Sleep(std::stoi(line));
						}
						else {
							if (line.find("//") != std::string::npos) {
								//comment 注释行跳过
							}
							else {
								if (line == "reset")
								{
									reset();
								}
								else {
									if (line.find("#") != std::string::npos) {
										//found
										std::vector<string> res = split(line, "#");
										for (int i = 0; i < res.size(); ++i)
										{
											parseDIYLine(res[i]);
										}


									}
									else {
										parseDIYLine(line);
									}
								}
							}
						}
					}
					Sleep(100);
				}


			
				
				//for (int i = 0; i < 4; i++) {
				//	//int j = 0;
				//	cout << "Testing light #" << i << "(enter name or ID, ENTER for skip): ";
				//	AlienFX_SDK::Functions::SetColor(i, 0, 255, 0);
				//	AlienFX_SDK::Functions::UpdateColors();
				//	Sleep(200);
				//	//std::cin.getline(name, 255);
				//	if (name[0] != 0) {
				//		//not skipped
				//		if (isdigit(name[0]) && res == (-1)) {
				//			outName = lfxUtil.GetLightInfo(0, atoi(name))->desc;
				//		}
				//		else {
				//			outName = name;
				//		}
				//		cout << "Final name is " << outName << ", ";
				//		// Store value...
				//		AlienFX_SDK::mapping map;
				//		map.devid = pids[cdev];
				//		map.lightid = i;
				//		map.name = std::string(outName);
				//		AlienFX_SDK::Functions::GetMappings()->push_back(map);
				//	}
				//	else {
				//		cout << "Skipped. ";
				//	}
				//	AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
				//	AlienFX_SDK::Functions::UpdateColors();
				//	AlienFX_SDK::Functions::Reset(false);
				//	Sleep(100);
				//}
				// now store config...
				AlienFX_SDK::Functions::SaveMappings();
			}
			else {
				cerr << " Device didn't answer!" << endl;
			}
		}
		if (res == (-1))
			lfxUtil.Release();
		AlienFX_SDK::Functions::AlienFXClose();



	}
	else {
		cout << "AlienFX devices not present, please check device manage!" << endl;
	}
	return 0;



}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
