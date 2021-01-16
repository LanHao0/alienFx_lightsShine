// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "./AlienFX-SDK/AlienFX_SDK.h"
#include "./alienfx-cli/LFXUtil.h"

using namespace std;

namespace
{
	LFXUtil::LFXUtilC lfxUtil;
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

				//LanHao: yeah! thanks for the example, now it is time to make it auto!, i'm trying this. just for keyboard, i'm trying
				for (int i = 0; i < 4; i++) {
					//int j = 0;
					cout << "Testing light #" << i << "(enter name or ID, ENTER for skip): ";
					AlienFX_SDK::Functions::SetColor(i, 0, 255, 0);
					AlienFX_SDK::Functions::UpdateColors();
					Sleep(200);
					//std::cin.getline(name, 255);
					if (name[0] != 0) {
						//not skipped
						if (isdigit(name[0]) && res == (-1)) {
							outName = lfxUtil.GetLightInfo(0, atoi(name))->desc;
						}
						else {
							outName = name;
						}
						cout << "Final name is " << outName << ", ";
						// Store value...
						AlienFX_SDK::mapping map;
						map.devid = pids[cdev];
						map.lightid = i;
						map.name = std::string(outName);
						AlienFX_SDK::Functions::GetMappings()->push_back(map);
					}
					else {
						cout << "Skipped. ";
					}
					AlienFX_SDK::Functions::SetColor(i, 0, 0, 0);
					AlienFX_SDK::Functions::UpdateColors();
					AlienFX_SDK::Functions::Reset(false);
					Sleep(100);
				}
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



	}else {
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
