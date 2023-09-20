#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

//Add a way to go back one folder in fileFolderCheck, have fun heh

filesystem::path pathRedefineFile(filesystem::path& p, string fullFile, vector<filesystem::path>& pastInputFiles, int& pastInputFilesNum) {
	pastInputFilesNum++;
	p = p / fullFile;

	pastInputFiles.push_back(p);
	return p;
}

filesystem::path pathRedefineFolder(filesystem::path& p, string fileName, vector<filesystem::path>& pastInputFiles, int& pastInputFilesNum) {
	pastInputFilesNum++;
	p = p / fileName;

	pastInputFiles.push_back(p);
	return p;
}

int printFileNames(filesystem::path& p) {
	filesystem::path p1 = filesystem::current_path() / "files";
	if (!filesystem::is_directory(p1)) {
		create_directories(p1);
		cout << "'files' folder created at " << (p1).string() << endl << endl;
	}
	else if (filesystem::is_directory(p)) {
		cout << "Files:" << endl;
		for (const auto& entry : filesystem::directory_iterator(p)) {
			if (entry.is_regular_file()) {
				cout << entry.path().filename() << endl;
			}
		}
		cout << endl << "Folders:" << endl;
		for (const auto& entry : filesystem::directory_iterator(p)) {
			if (entry.is_directory()) {
				cout << entry.path().filename() << endl;
			}
		}
	}
	cout << endl;
	return 0;
}

filesystem::path fileNotFound(string fullFile, filesystem::path& p) {
	system("cls");
	cout << "ERROR:0000 " << endl << fullFile << " Not found!" << endl << endl;
	p = filesystem::current_path() / "files";
	return p;
}

int options(string fullFile) {
	char userInput1;

	cout << "What would you like to do with " << fullFile << "?" << endl;
	cout << "N : Take notes" << endl;
	cout << "E : General entries" << endl;
	cout << "R : Read from file" << endl;
	cout << "D : Delete file" << endl;
	cout << "B : Go back" << endl;

	cin >> userInput1;
	// Lowercase op
	userInput1 = (char)tolower(userInput1);

	return(userInput1);
}

int uCharCheck(string fileName) {
	const char uchar[] = { '<', '#', '>', '$', '+', '%', '!', '`', '&', '*', '\'', '"', '|', '{', '}', '?', '=', '/', '\\', ':', ' ', '@' };
	for (int a = 0; fileName[a] != '\0'; a++) {
		for (int d = 0; d < 21; d++) {
			if (fileName[a] == uchar[d]) {
				system("cls");
				cout << '\'' << fileName << '\'' << " contains an illegal character: " << uchar[d] << endl << endl;
				return 1;
			}
		}
	}
	return 0;
}

int uCharCheckFolder(string folderUserInput) {
	const char uchar[] = { '<', '#', '>', '$', '+', '%', '!', '`', '&', '*', '\'', '"', '|', '{', '}', '?', '=', '/', '\\', ':', ' ', '@' };
	for (int a = 0; folderUserInput[a] != '\0'; a++) {
		for (int d = 0; d < 21; d++) {
			if (folderUserInput[a] == uchar[d]) {
				system("cls");
				cout << '\'' << folderUserInput << '\'' << " contains an illegal character: " << uchar[d] << endl << endl;
				return 1;
			}
		}
	}
	return 0;
}

int dirPathOp(char userInput1, filesystem::path& p) {
	system("cls");
	//Note path
	if (userInput1 == 'n') {
		cout << p << " > " << "Notes" << endl << endl;
	}
	else if (userInput1 == 'e') {
		cout << p << " > " << "Entries" << endl << endl;
	}
	else if (userInput1 == 'r') {
		cout << p << " > " << "Read" << endl << endl;
	}
	else {
		cout << p << endl << endl;
	}
	return 0;
}

int dirPathCreate(filesystem::path& p) {
	system("cls");
	cout << p << " > " << "Create" << endl << endl;
	return 0;
}

int dirPath(filesystem::path& p) {
	system("cls");
	cout << (p).string() << endl << endl;
	return 0;
}

int createFile(filesystem::path& p) {
	int c = 1;
	string text;
	string fileName;

	dirPathCreate(p);
	while (true) {
		printFileNames(p);
		cout << endl;

		cout << "Type desired file name:" << endl;
		cin >> fileName;

		//Unique char check
		uCharCheck(fileName);
		if (uCharCheck(fileName) == 0) {
			break;
		}
	}


	//Add .txt to the end of userInput
	string fileName1 = fileName + ".txt";

	//File !exist check
	if (!std::filesystem::exists(p / fileName1)) {
		//Create the file
		ofstream fileName2(p / fileName1);
		fileName2.close();
		system("cls");
	}
	//File exists check
	else if (std::filesystem::exists(p / fileName1)) {
		system("cls");
		cout << "ERROR:0001" << endl << fileName1 << " ALREADY EXISTS!" << endl << endl;
		return 1;
	}
	return 0;
}

filesystem::path noteLoop(filesystem::path& p, fstream& fileName) {
	while (true) {
		string notes;
		string rawNotes;
		string notes1;

		//UserInput
		std::getline(std::cin, rawNotes);

		//`end` Check
		if (rawNotes == "end") {
			fileName.close();
			system("cls");
			p = filesystem::current_path() / "files";
			return p;
		}

		//Period check
		if (rawNotes.length() > 0 && rawNotes[rawNotes.length() - 1] != '.') {
			string notes = rawNotes + "." + " ";
			fileName << notes << endl;
		}
		else if (rawNotes.length() > 0 && rawNotes[rawNotes.length() - 1] == '.') {
			string notes = rawNotes + " ";
			fileName << notes << endl;
		}
	}
}

filesystem::path generalEntries(string fullFile, fstream& fileName, filesystem::path& p) {
	while (true) {
		string fname;
		string lname;
		string gender;
		string number;
		int num = rand() % 10000;
		std::string id = std::to_string(num);

		cout << "Type 'end' to leave" << endl << endl;

		// Last name
		cout << "Last name: ";
		cin >> lname;
		//'end' check
		if (lname == "end") {
			system("cls");
			p = filesystem::current_path() / "files";
			return p;
		}
		// First name
		cout << "First name: ";
		cin >> fname;
		//'end' check
		if (fname == "end") {
			system("cls");
			p = filesystem::current_path() / "files";
			return p;
		}
		// Gender
		cout << "Gender: ";
		cin >> gender;
		//'end' check
		if (gender == "end") {
			system("cls");
			p = filesystem::current_path() / "files";
			return p;
		}
		// Gender Check
		while (gender != "Female" && gender != "F" && gender != "Male" && gender != "M") {
			cout << "Unknown. Gender: ";
			cin >> gender;
		}
		if (gender == "Male" || gender == "M") {
			gender = "M";
		}
		else if (gender == "Female" || gender == "F") {
			gender = "F";
		}
		// Phone number
		cout << "Phone number: ";
		cin >> number;
		//'end' check
		if (number == "end") {
			system("cls");
			p = filesystem::current_path() / "files";
			return p;
		}
		// Phone number check
		while (number.length() > 10) {
			cout << "Too many digits" << endl;
			cout << "Phone number: ";
			cin >> number;
		}
		while (number.length() < 10) {
			cout << "Not enough digits" << endl;
			cout << "Phone number: ";
			cin >> number;
		}
		char answer;

		// String combination
		string userTCheck = lname + " " + fname + " " + gender + " " + number + " ";
		string userText = lname + "!" + fname + "@" + gender + "#" + number + "$" + id;

		// String confirmation
		cout << userTCheck << endl;
		cout << "Is this correct? (Y/N)" << endl;
		cin >> answer;

		// Answered yes
		if (answer == 'Y') {
			fileName = fstream(p, fstream::out | fstream::app);
			fileName << userText << endl;
			fileName.close();
			cout << "Saved successfully!" << endl;
		}
		else if (answer == 'N') {
			break;
		}
	}
	return p;
}

filesystem::path readFile(filesystem::path& p, string fullFile) {
	while (true) {
		string userInput;
		string text;
		int c = 1;

		cout << "Type 'end' to leave" << endl << endl;
		cout << fullFile << ":" << endl;

		//Print  contents
		fstream fileName(filesystem::current_path() / "files" / fullFile, fstream::in | fstream::out | fstream::app);
		while (getline(fileName, text)) {
			cout << text << endl;
			c++;
		}
		fileName.close();
		cout << endl;
		cin >> userInput;

		//'end' Check
		if (userInput == "end") {
			system("cls");
			p = filesystem::current_path() / "files";
			return p;
		}
		return p;
	}
}

filesystem::path opIfStates(fstream& fileName, char userInput1, string fullFile, filesystem::path& p) {
	//Note Check
	if (userInput1 == 'n') {
		dirPathOp(userInput1, p);

		cout << "You can start to take notes. When you're done, type 'end'" << endl;

		//Note loop
		p = noteLoop(p, fileName);
	}

	//General Entries
	if (userInput1 == 'e') {
		dirPathOp(userInput1, p);
		p = generalEntries(fullFile, fileName, p);

	}
	//Read from file
	else if (userInput1 == 'r') {
		dirPathOp(userInput1, p);
		p = readFile(p, fullFile);
	}
	//Delete file
	else if (userInput1 == 'd') {
		fileName.close();
		int result = filesystem::remove(p);
		system("cls");
		if (result == 1) {
			cout << fullFile << " has been deleted" << endl << endl;
			p = filesystem::current_path() / "files";
			return p;
		}
		else {
			cout << "Error: 0003" << endl << fullFile << " deletion unsuccessful";
			p = filesystem::current_path() / "files";
			return p;
		}
	}
	//Back
	else if (userInput1 == 'b') {
		p = filesystem::current_path() / "files";
		dirPath(p);
		return p;
	}
	//Unknown op
	else if (userInput1 != 'r' && userInput1 != 'e' && userInput1 != 'n') {
		system("cls");
		cout << "ERROR:0002" << endl << "Unknown operator" << endl << endl;
		p = filesystem::current_path() / "files";
		return p;
	}
	return p;
}

filesystem::path fileFound(string fullFile, filesystem::path& p) {
	while (true) {
		fstream fileName(p, fstream::out | fstream::app);
		dirPath(p);
		cout << fullFile << " has been opened!" << endl;
		cout << endl;

		//Options
		char userInput1 = options(fullFile);

		//If statements
		p = opIfStates(fileName, userInput1, fullFile, p);

		return p;
	}
}

filesystem::path openFile(string fullFile, filesystem::path& p) {
	int c = 1;

	//File found
	if (std::filesystem::exists(p)) {
		p = fileFound(fullFile, p);
	}
	//File not found
	else if (!std::filesystem::exists(p)) {
		p = fileNotFound(fullFile, p);
	}
	return p;
}

int createFolder(filesystem::path& p) {
	int c = 1;
	string folderName;
	dirPathCreate(p);
	while (true) {
		printFileNames(p);

		cout << "Type desired folder name:" << endl;
		cin >> folderName;

		uCharCheckFolder(folderName);
		if (uCharCheckFolder(folderName) == 0) {
			break;
		}
		return 0;
	}
	//Folder !exists check
	if (!std::filesystem::exists(p / folderName)) {
		//Create the folder
		filesystem::create_directories(p / folderName);
		cout << "Folder created at " << p / folderName;
		return 0;
	}
	//Folder exists check
	else if (std::filesystem::exists(p / folderName)) {
		system("cls");
		cout << "ERROR:0001" << endl << folderName << " ALREADY EXISTS!" << endl << endl;
		return 1;
	}
	return 0;
}

int createOption(filesystem::path& p) {
	char createUserInput;
	dirPathCreate(p);
	printFileNames(p);

	cout << "Type 'b' to go back" << endl;
	cout << "What would you like to create; Folder(F) / Text Doc(T):" << endl;
	cin >> createUserInput;

	createUserInput = (char)tolower(createUserInput);
	if (createUserInput == 'f') {
		createFolder(p);
	}
	else if (createUserInput == 't') {
		createFile(p);
	}
	else if (createUserInput == 'b') {
		return 0;
	}
	return 0;
}

filesystem::path backToStart(filesystem::path& p, vector<filesystem::path>& pastInputFiles, int& pastInputFilesNum) {
	p = filesystem::current_path() / "files";
	pastInputFiles.clear();
	pastInputFiles.push_back(p);
	pastInputFilesNum = 0;

	return p;
}

int fileFolderCheck(filesystem::path& p, vector<filesystem::path> pastInputFiles, int pastInputFilesNum) {
	char fileFolderInput;
	while (true) {
		printFileNames(p);
		cout << "'b' = go back" << endl << "'s' = back to main directory 'files'" << endl;
		cout << "Are you opening a file(T), or folder(F)? (Type 'C' to create)" << endl;
		cin >> fileFolderInput;

		fileFolderInput = (char)tolower(fileFolderInput);
		if (fileFolderInput == 't') {
			return 1;
		}
		else if (fileFolderInput == 'f') {
			return 2;
		}
		else if (fileFolderInput == 'c') {
			return 3;
		}
		else if (fileFolderInput == 'b') {
			return 4;
		}
		else if (fileFolderInput == 's') {
			p = backToStart(p, pastInputFiles, pastInputFilesNum );
		}
		else if (fileFolderInput != 'c' && fileFolderInput != 'f' && fileFolderInput != 't') {
			system("cls");
			cout << "Error: 0004" << endl << "Unknown character" << endl << endl;
			printFileNames(p);
		}
	}
}

filesystem::path folderQuestion(filesystem::path& p, vector<filesystem::path>& pastInputFiles, int& pastInputFilesNum) {
	while (true) {
		string fileName;
		dirPath(p);
		printFileNames(p);
		cout << "Which folder would you like to open?" << endl;
		cin >> fileName;
		p = pathRedefineFolder(p, fileName, pastInputFiles, pastInputFilesNum);
		return p;
	}
}

filesystem::path fileQuestion(filesystem::path& p, vector<filesystem::path>& pastInputFiles, int& pastInputFilesNum) {
	while (true) {
		string fullFile;
		string fileName;

		dirPath(p);
		printFileNames(p);
		cout << "Which file would you like to open?" << endl;
		cin >> fileName;

		fullFile = fileName + ".txt";
		p = pathRedefineFile(p, fullFile, pastInputFiles, pastInputFilesNum);
		p = openFile(fullFile, p);
		return p;
	}
}

filesystem::path goBack(filesystem::path& p, vector<filesystem::path>& pastInputFiles, int& pastInputFilesNum) {
	p = pastInputFiles[pastInputFilesNum - 1];
	pastInputFilesNum--;
	return p;
}

int main() {
	filesystem::path p = filesystem::current_path() / "files";
	vector<filesystem::path> pastInputFiles {p};
	int pastInputFilesNum = 0;

	while (true) {
		int c = 1;
		string fileName;
		string text;
		const filesystem::path files{"files"};

		dirPath(p);

		//FileFolderCheck
		int fileFolderCheckInt = fileFolderCheck(p, pastInputFiles, pastInputFilesNum);
		//File
		if (fileFolderCheckInt == 1) {
			p = fileQuestion(p, pastInputFiles, pastInputFilesNum);
		}
		//Folder
		else if (fileFolderCheckInt == 2) {
			p = folderQuestion(p, pastInputFiles, pastInputFilesNum);
		}
		//Create
		else if (fileFolderCheckInt == 3) {
			createOption(p);
		}
		else if (fileFolderCheckInt == 4) {
			p = goBack(p, pastInputFiles, pastInputFilesNum);
		}
	}
}