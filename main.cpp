#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct MusicTrack {
    string title;
    string artist;
    int duration;
    string genre;
    int releaseYear;
};

void printMenu();
void addTrack(vector< MusicTrack> & library);
void displayLibrary(const vector<MusicTrack>&library);
void saveLibraryToFile(const vector<MusicTrack>& library, const string& filename);
void loadLibraryFromFile(vector<MusicTrack> & library, const string& filename);


int main() {
    
    return 0;
}
