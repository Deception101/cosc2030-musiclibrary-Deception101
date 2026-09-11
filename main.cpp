#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct MusicTrack {
    string title;
    string artist;
    string album;
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
    vector<MusicTrack> library;
    const string filename = "musiclibrary.dat";
    int choice = -1;

    do {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n\n";
            continue;

        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addTrack(library); break;
            case 2: displayLibrary(library); break;
            case 3: saveLibraryToFile(library,filename); break;
            case 4: loadLibraryFromFile(library,filename); break;
            case 5: cout << "Exiting Music Library. Goodbye\n"; break;
            default: cout << "Invalid choice. Select a valid option\n\n";
        }

}
    while (choice !=5);

    return 0;
}

void printMenu() {
    cout << "==== Music Library Menu ====\n";
    cout << "1. Add Track\n";
    cout << "2. Display Library\n";
    cout << "3. Save Library to File\n";
    cout << "4. Load Library from File\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: " ;
}

void addTrack(vector<MusicTrack>& library) {
    MusicTrack track;

    cout << "Enter track title: ";
    getline(cin,track.title);

    cout << "Enter artist: ";
    getline(cin,track.artist); 

    cout << "Enter album: ";
    getline(cin,track.album);

    cout << "Enter duration (seconds): ";
    cin >> track.duration;
    cin.ignore(numeric_limits<streamsize>:: max(), '\n');

    cout << "Enter genre: ";
    getline(cin,track.genre);

    cout << "Enter release year: ";
    cin >> track.releaseYear;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    library.push_back(track);
    cout << "Track added successfully.\n\n";
}

void displayLibrary(const vector<MusicTrack>& library) {
    if (library.empty() ) {
        cout << "The library is empty.\n\n";
        return;
    }

    cout << "\n==== Music Library (" << library.size() << " tracks) ====\n";
    for (size_t i = 0; i < library.size(); ++i) {
        const MusicTrack& t = library[i];
        cout << i + 1 << ". " << t.title << " - " << t.artist << "\n";
        cout << "   Album: " << t.album << "\n";
        cout << "   Duration: " << t.duration << " sec\n";
        cout << "   Genre: " << t.genre << "\n";
        cout << "   Release Year: " << t.releaseYear << "\n";
    }
    cout << "\n";
}

void writesStringToFile(ofstream& out, const string& str) {
    size_t len = str.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(str.c_str(), static_cast<streamsize>(len));
}

string readStringFromFile(ifstream& in) {
    size_t len = 0;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    string str(len, '\0');
    if (len > 0) {
        in.read(&str[0], static_cast<streamsize>(len));
    }
    return str;
}

void saveLibraryToFile(const vector<MusicTrack>& library, const string& filename) {
ofstream outFile(filename, ios::binary | ios::trunc);
    if (!outFile) {
        cout << "Error: could not open file for writing.\n\n";
        return;
}


size_t count = library.size();
outFile.write (reinterpret_cast<const char*>(&count), sizeof(count));

for (const MusicTrack& t : library) {
    writesStringToFile(outFile, t.title);
    writesStringToFile(outFile, t.artist);
    writesStringToFile(outFile, t.album);
    outFile.write(reinterpret_cast<const char*> (&t.duration), sizeof(t.duration));
     writesStringToFile(outFile, t.genre);
     outFile.write(reinterpret_cast<const char*> (&t.releaseYear), sizeof(t.releaseYear));
}

outFile.close();
cout << "Library saved to " << filename << " (" << count << " tracks).\n\n";
}

void loadLibraryFromFile(vector<MusicTrack>& library, const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Error: could not open file for reading. Has it been saved yet?\n\n";
        return;
    }

    library.clear();
    
    size_t count = 0;
    inFile.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count && inFile; ++i) {
        MusicTrack t;
        t.title = readStringFromFile(inFile);
        t.artist = readStringFromFile(inFile);
        t.album = readStringFromFile(inFile);
        inFile.read(reinterpret_cast<char*>(&t.duration), sizeof(t.duration));
        t.genre = readStringFromFile(inFile);
        inFile.read(reinterpret_cast<char*>(&t.releaseYear), sizeof(t.releaseYear));
        library.push_back(t);

    }
inFile.close();
cout << ":Loaded " << library.size() << " tracks from " << filename << ".\n\n";
}
