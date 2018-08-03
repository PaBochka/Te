#include <iostream>
#include <string>
#include "TText.h"
using namespace std;
std::string strs[100];
int nl, ns;
void TextTyper(TText &txt){
	nl = 0;
	txt.Print();
}
// void TextLineMark(TText &txt){
// 	bool flag = true;
// 	std::string st = txt.Getline();

// 	for (nl = 0; nl < ns; nl++)
// 		if (st == strs[nl]) flag = false;
// 	nl = 0;
// 	if (flag == true)
// 	{
// 		std::cout << " ";
// 		nl++;
// 		std::cout << st;
// 		ns++;
// 		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { nl, ns });
// 	}
// }
void TextProc(TText &txt){
	int dir, unit;
	std::string st;
	int ch;
	do{
		std::cout << "0-enter text" << std::endl;
		std::cout << "9-EXIT" << std::endl;
		std::cout << "1-Go First Link" << std::endl;
		std::cout << "2-Go Next Link" << std::endl;
		std::cout << "3-Go Down Link" << std::endl;
		std::cout << "4-Delete piece text" << std::endl;
		std::cout << "7-Delete first" << std::endl;
		std::cout << "5-Go Prev Text" << std::endl;
		std::cout << "6-Insert Text" << std::endl;
		std::cin >> ch;
		if (ch == 9) break;
		switch (ch)
		{
		case 0:{
			system("clear");
			std::cin >> st;
			txt.SetLine(st);
			system("clear");
			TextTyper(txt);
		}
				   break;
		case 1:{
			txt.GoFirstLink();
			system("clear");
			TextTyper(txt); 
		}break;
		case 3:{
			txt.GoDownLink();
			system("clear");
			TextTyper(txt);			
		}break;
		case  5:{
			txt.GoPrevLink();
			system("clear");
			TextTyper(txt);
		}break;
		case 2:{
			txt.GoNextLink();
			system("clear");
			TextTyper(txt);
		}break;
		case 6:{
			system("clear");
			std::cout << "Direction:0-down,1-next ";
			std::cin >> dir;
			std::cout << "Unit:0-line,1-section ";
			std::cin >> unit;
			std::cin >> st;
			if (dir == 0)
				if (unit == 0)
				{
					txt.InsDownLine(st);
					system("clear");
				}
				else{
					txt.InsDownSection(st);
					system("clear");
				}
			else
				if (unit == 0){
					txt.InsNextLine(st);
					system("clear");
				}
				else{
					system("clear");
					txt.InsNextSection(st);
				}
				TextTyper(txt);
				
		}break;
		case 4:{
			system("clear");
			std::cout << "Direction:0-down,1-next ";
			std::cin >> dir;
			std::cout << "Unit:0-line,1-section ";
			std::cin >> unit;
			if (dir == 0)
				if (unit == 0)
				{
					txt.DelDownLine();
					system("clear");
				}
				else
				{
					txt.DelDownSection();
					system("clear");
				}
			else
				if (unit == 0){
					txt.DelNextLine();
					system("clear");
				}
				else
				{
					txt.DelNextSection();
					system("clear");
				}
			TextTyper(txt);
			
		}break;
		case 7:
		{
			system("clear");
			int i;
			std::cout << "delete first ";
			std::cin >> i;
			if (i > 0)
			{
				txt.DelFirst();
				system("clear");
			}
			TextTyper(txt);
		} break;

		}
	} while (ch != 9);

}
TextMem TextLink::MemHeader;
int main()
{
	TextLink::InitMemSystem();
	TText txt;
	txt.Reset();
	txt.Read("ReadDoc.txt");
	TextTyper(txt);
	TextProc(txt);
	// txt.Write("FileDoc.txt");
	TextLink::MemCleaner(txt);
	TextLink::PrintFreeLink();
	//txt.Print();
	cin.get();
	return 0;
}