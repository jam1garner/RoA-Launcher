//Coding by jam1garner
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <time.h>
#include <algorithm>
#define _WIN32_WINNT 0x0500
#include<windows.h>

using namespace std;

void copyF(string F1, string F2){
    ifstream  oldFile(F1.c_str(), std::ios::binary);
    ofstream  newFile(F2.c_str(),   std::ios::binary);
    newFile<<oldFile.rdbuf();

    oldFile.close();
    newFile.close();
}

int main(){
    //Accessing the data file so it is no hassle.
    vector <int> data;//data from the file
    //0 - Number of custom splashes|1 - Music loading type|2 - Number of music packs or music pack to load.
    if(ifstream("launcher.dat")&&!(GetAsyncKeyState(VK_LCONTROL))){//If left control is not held down and the data file is found.
        cout<<"launcher.dat found. Proceeding to switch files.";
    }else{//No data file or left control override
        int temp0=0;
        cout<<"launcher.dat not found. Creating now...\n\nNumber of splash screen alternatives: ";
        while(temp0<=0){
            cin>>temp0;
            if(temp0=0)
                cout<<"Cannot be less than 1.\nNumber of splash screen alternatives: ";
        }
        ofstream launcherData;
        launcherData.open("launcher.dat");
        launcherData<<temp0<<endl;
        cout<<"Music pack type (1)Select on Launch (2)Random (3)Select now: ";
        temp0=0;
        while(temp0<1||temp0>3){
            cin>>temp0;
            if(temp0<1||temp0>3)
                cout<<"Cannot be 0.\nType: ";
        }
        launcherData<<temp0<<endl;
        if(temp0==3)
            cout<<"Input music pack number: ";
        else
            cout<<"Number of music packs: ";
        temp0=0;
        while(temp0<=0){
            cin>>temp0;
            if(temp0<=0)
                cout<<"Number of music packs cannot be less than 1";
        }
        launcherData<<temp0<<endl;
        launcherData.close();
        cout<<"Just a reminder that you can change this by holding left control while you launch.";
        Sleep(2000);
    }
    //Loading up the values
    int temp0;//Westballz
    ifstream launcherData("launcher.dat");
    for(int i=0;i<3;i++){
        launcherData>>temp0;
        data.push_back(temp0);
    }
    launcherData.close();

    cout<<"\n\nCurrent settings for number of pictures: "<<data[0]<<"\nCurrent music pack loading type: "<<data[1]<<"\nNumber of music packs or pack to be loaded: "<<data[2];

    //Randomly picking a file
    srand(time(NULL));
    int fileNum = (rand()%data[0])+1;
    cout<<"\nFile selected: splash"<<fileNum<<".png\nPreparing to copy over.";

    //Making the filename
    string fileName;
    ostringstream strstream;
    strstream<<"launcher/splash"<<fileNum<<".png";
    fileName = strstream.str();
    //string fileName = "launcher/splash1.png";

    //actually copying the file over
    copyF(fileName,"splash.png");

    //Music packs
    strstream.str("");
    string MusicDirectory;
    if(data[1]==1){
        string temp1;
        cout<<"Choose a music pack number from 1 to "<<data[2]<<"(or type 'default'): ";
        cin>>temp1;
        strstream<<"launcher/music/"<<temp1<<"/";
        MusicDirectory = strstream.str();
    }
    else if(data[1]==2){
        strstream<<"launcher/music/"<<((rand()%data[2])+1)<<"/";
        MusicDirectory = strstream.str();
    }
    else{
        strstream<<"launcher/music/"<<data[2]<<"/";
        MusicDirectory = strstream.str();
    }
    //Copying over music
    cout<<"\n\nPreparing to copy over files from directory "<<MusicDirectory<<endl;

    copyF(MusicDirectory+"music_air_loop.ogg","music_air_loop.ogg");
    copyF(MusicDirectory+"music_air_open.ogg","music_air_open.ogg");
    copyF(MusicDirectory+"music_earth_loop.ogg","music_earth_loop.ogg");
    copyF(MusicDirectory+"music_earth_open.ogg","music_earth_open.ogg");
    copyF(MusicDirectory+"music_fire_loop.ogg","music_fire_loop.ogg");
    copyF(MusicDirectory+"music_fire_open.ogg","music_fire_open.ogg");
    copyF(MusicDirectory+"music_tree_loop.ogg","music_tree_loop.ogg");
    copyF(MusicDirectory+"music_tree_open.ogg","music_tree_open.ogg");
    copyF(MusicDirectory+"music_water_loop.ogg","music_water_loop.ogg");
    copyF(MusicDirectory+"music_water_open.ogg","music_water_open.ogg");
    Sleep(5000);

    ShowWindow( GetConsoleWindow(), SW_HIDE );
    system("RivalsOfAether.exe");


}
