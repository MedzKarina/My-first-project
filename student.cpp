#include "student.h"

bool lyginimas(studentas i1, studentas i2){
    return (i1.galutinis < i2.galutinis);
}

string ToString(int value){
    stringstream ss;
    std::string s;
    ss << value;
    ss >> s;

    return s;
}

void Timer(clock_t begin, clock_t end){
    double timer = double(end - begin) / CLOCKS_PER_SEC;
    cout << timer << endl;
}

void Isvedimas(vector<studentas> studentai, string fileName)
{
    fileName = "files/" + fileName + "-studentai.txt";
    ofstream MyFile;
    MyFile.open(fileName.c_str());


    MyFile << setw(10) << left << "VARDAS" << setw(10) << left << "PAVARDE";
    for(int i=0; i < studentai[0].paz.size(); i++)
        MyFile << setw(10) << left << "ND" + ToString(i+1);
    MyFile << setw(10) << left << "EGZ" << endl;
    for(int i=0; i < studentai.size(); i++)
    {

        MyFile << setw(10) << left << studentai[i].vardas << setw(10) << left << studentai[i].pavarde << setw(19) << left;
        for(int j=0; j < studentai[i].paz.size(); j++)
            MyFile << setw(10) << left << studentai[i].paz[j] << setw(10);
        MyFile << setw(10) << left << studentai[i].galutinis << endl;
    }
    MyFile.close();
}

bool Grupavimas(vector<studentas> studentai)
{
    vector<studentas> nusk; //nuskriaustukai
    vector<studentas> kieti; //kietiakai

    clock_t begin = clock();
    sort(studentai.begin(), studentai.end(), lyginimas);
    clock_t end = clock();

    begin = clock();
    for(int i=0; i < studentai.size(); i++)
    {
        if(studentai[i].galutinis < 5)
        {
            nusk.push_back(studentai[i]);
        }
        else
        {
            kieti.push_back(studentai[i]);
        }
    }
    end = clock();

    cout << endl << studentai.size() << " studentu grupavimas uztruko (Vector): ";
    Timer(begin, end);
    begin = clock();
    Isvedimas(nusk, ToString(studentai.size()) + "nuskriaustukai");
    end = clock();
    begin = clock();
    Isvedimas(kieti, ToString(studentai.size()) + "kietiakai");
    end = clock();
}

void Grupavimas(list<studentas> studentai){
    list<studentas> nusk;
    list<studentas> kieti;
    int listSize = studentai.size();

    clock_t begin = clock();
    studentai.sort(lyginimas);

    list<studentas>::iterator it = studentai.begin();
    while(it != studentai.end()){
        if ((*it).galutinis < 5) {
            nusk.push_back(*it);
        } else {
            kieti.push_back(*it);
        }
            ++it;
    }
    clock_t end = clock();
    cout << listSize << " studentu grupavimas uztruko (List): ";
    Timer(begin, end);
}

studentas Gen(int cnd, int studentoId){
    stringstream ss;
    studentas nstud;
    string id;
    ss << studentoId;
    ss >> id;
    nstud.vardas = "V" + id;
    nstud.pavarde = "P" + id;
    nstud.egz = (rand() % 10) + 1;
    for(int i = 0; i < cnd; i ++)
    {
        int g = (rand() % 10) + 1;
        nstud.paz.push_back(g);
    }

    nstud.galutinis = Galutinis(nstud.egz, nstud.paz);
    nstud.mediana = Mediana(nstud.paz);

    return nstud;
}

vector<studentas> ReadFromFile (string fileName){
    clock_t begin = clock();
    ifstream inputFile(fileName);
    string line;
    vector<studentas> vec;
    if(inputFile)
    {
        int k;
        k = 0;
        while(getline(inputFile, line))
        {
            k++;
            if (k < 2)
                continue;
            studentas m;
            istringstream st(line);
            st >> m.vardas;
            st >> m.pavarde;
            for (int i = 0; i< 5; i++){
                string nd;
                st >> nd;
                m.paz.push_back(stoi(nd));
            }
            st >> m.galutinis;

            if(st)
            {
                vec.push_back(m);
            }
        }
    }
    else
    {
        cout << "Klaida su failu" << endl;
    }

    clock_t end = clock();
    cout << vec.size() << " irasu nuskaitymo laikas (Vector): ";
    Timer(begin, end);

    return vec;
}

list<studentas> ReadFromFileList (string fileName){
    clock_t begin = clock();
    ifstream inputFile(fileName);
    string line;
    list<studentas> llist;
    if(inputFile)
    {
        int k;
        k = 0;
        while(getline(inputFile, line))
        {
            k++;
            if (k < 2)
                continue;
            studentas m;
            istringstream st(line);
            st >> m.vardas;
            st >> m.pavarde;
            for (int i = 0; i< 5; i++){
                string nd;
                st >> nd;
                m.paz.push_back(stoi(nd));
            }
            st >> m.galutinis;

            if(st)
            {
                llist.push_back(m);
            }
        }
    }
    else
    {
        cout << "Klaida su failu" << endl;
    }

    clock_t end = clock();
    cout << llist.size() << " irasu nuskaitymo laikas (List) : ";
    Timer(begin, end);

    return llist;
}

void Gen2(int gstud){
    int gnd = 5;

    string fileNameToFunction = "files/" + ToString(gstud) + "-studentai.txt";
    ifstream ifile;
    ifile.open(fileNameToFunction);
    if(!ifile) {
        vector<studentas> studentai;
        for(int i=0; i < gstud; i++)
        {
            studentas stud = Gen(gnd, i+1);
            studentai.push_back(stud);
        }

        stringstream ss;
        std::string stringS;
        ss << gstud;
        ss >> stringS;

        Isvedimas(studentai, stringS);
}
        else {
        cout << "Toks failas jau yra" << endl;
        ifile.close();
        }

    vector<studentas> readFromFile = ReadFromFile(fileNameToFunction);
    list<studentas> readFromFileList = ReadFromFileList(fileNameToFunction);

    Grupavimas(readFromFile);
    Grupavimas(readFromFileList);
}
