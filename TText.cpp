#include "TText.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#define BufLength 80
static char StrBuf[BufLength];
static int TextLevel;
using namespace std;
TText::TText(PTextLink p1)
{
	if (p1 == NULL) 
		p1 = new TextLink();
	First = p1;
}

void TText::GoFirstLink(void){
	while (!Path.empty())Path.pop();
	Current = First;
}
void TText::GoNextLink(void){
	if (Current != NULL)
		if (Current->Next != NULL)
		{
			Path.push(Current);
			Current = Current->Next;
		}
}
void TText::GoDownLink(void){
	if (Current != NULL)
		if (Current->Down != NULL)
		{
			Path.push(Current);
			Current = Current->Down;
		}
}
void TText::GoPrevLink(void){
	if (!Path.empty()){
		Current = Path.top(); Path.pop();
	}
}
std::string TText::Getline(void){
	if (Current == NULL)
		return std::string("");
	else return std::string(Current->Str);
}
void TText::SetLine(std::string s){
	if (Current != NULL)
	{
		strncpy(Current->Str, s.c_str(), TextLineLength);
		Current->Str[TextLineLength - 1] = '\0';
	}
}
void TText::InsDownLine(std::string s){				
	if (Current != NULL){
		PTextLink pd = Current->Down;
		PTextLink p1 = new TextLink("", pd, NULL);
		strncpy(p1->Str, s.c_str(), TextLineLength);
		Current->Down = p1;
		p1->Str[TextLineLength - 1] = '\0';
		++count_link;
	}
}
void TText::InsDownSection(std::string s){			
	if (Current != NULL){
		PTextLink pd = Current->Down;
		PTextLink p1 = new TextLink("", NULL, pd);
		strncpy(p1->Str, s.c_str(), TextLineLength);
		Current->Down = p1;
		p1->Str[TextLineLength - 1] = '\0';
		++count_link;
	}
}
void TText::InsNextLine(std::string s){			
	if (Current != NULL){
		PTextLink pn = Current->Next;
		PTextLink p1 = new TextLink("", pn, NULL);
		strncpy(p1->Str, s.c_str(), TextLineLength);
		Current->Next = p1;
		p1->Str[TextLineLength - 1] = '\0';
		++count_link;
	}
}				
	void TText::InsNextSection(std::string s){
	if (Current != NULL){
		PTextLink pn = Current->Next;
		PTextLink p1 = new TextLink("", NULL, pn);
		strncpy(p1->Str, s.c_str(), TextLineLength);
		Current->Next = p1;
		p1->Str[TextLineLength - 1] = '\0';
		++count_link;
	}
}
void TText::DelDownLine(void){
	if (Current != NULL)
		if (Current->Down != NULL){
			PTextLink p11 = Current->Down;
			PTextLink p12 = p11->Next;
			if (p11->Down == NULL)
				Current->Down = p12;
		}
	--count_link;	
}
void TText::DelDownSection(void){
	if (Current != NULL)
		if (Current->Down != NULL){
			PTextLink p11 = Current->Down;
			PTextLink p12 = p11->Next;
			Current->Down = p12;
		}
	--count_link;
}
void TText::DelNextLine(void){
	if (Current != NULL)
		if (Current->Next != NULL){
			PTextLink p11 = Current->Next;
			PTextLink p12 = p11->Next;
			if (p11->Next == NULL)
				Current->Next = p12;
		}
	--count_link;
}
void TText::DelNextSection(void){
	if (Current != NULL)
		if (Current->Next != NULL){
			PTextLink p11 = Current->Next;
			PTextLink p12 = p11->Next;
			Current->Next = p12;
		}
	--count_link;
}
void TText::DelFirst(void){
	if (First != NULL)
		if (First->Next != NULL)
		{
			Current = First->Next;
			First = First->Next;
		}
		else
			First = NULL;
	--count_link;
}
int TText::Reset(void){
	while (!St.empty())
		St.pop();
	Current = First;
	if (Current != NULL){
		St.push(Current);
		if (Current->Next != NULL)
			St.push(Current->Next);
		if (Current->Down != NULL)
			St.push(Current->Down);
	}
	return IsTextEnded();
}
int TText::IsTextEnded(void) const{
	return !St.size();
}
int TText::GoNext(void){
	if (!IsTextEnded()){
		Current = St.top(); St.pop();
		if (Current != First)
		{
			if (Current->Next != NULL)
				St.push(Current->Next);
			if (Current->Down != NULL)
				St.push(Current->Down);
		}
	}
	return IsTextEnded();
}
PTextLink TText::GetFirstAtom(PTextLink p1){
	PTextLink tmp = p1;
	while (!tmp->IsAtom())
	{
		St.push(tmp);
		tmp = tmp->GetDown();
	}
	return tmp;
}
//PText TText::GetCopy(){
//	PTextLink p11, p12, p1 = First, cp1 = NULL;
//	if (First != NULL){
//		while (St.empty()){
//			St.pop();
//			while (1){
//				if (p1 != NULL){
//					p1 = GetFirstAtom(p1);
//					St.push(p1);
//					p1 = p1->GetDown();
//				}
//				else if (St.empty()) break;
//				else{
//					p11 = St.top(); St.pop();
//					if (strstr(p11->Str, "Copy") == NULL){
//						p12 = new TextLink("Copy", p11, cp1);
//					}
//					else{
//						//
//						while (strstr(p11->Str, "Copy") != NULL)
//						{
//							p11 = St.top(); St.pop();
//						}
//						p12 = new TextLink("Copy", p11, cp1);
//
//
//					}
//				}
//			}
//		}
//	}
//	return new TText(cp1);
//}
void TText::Print(){
	TextLevel = 0;
	PrintText(First);
}
void TText::PrintText(PTextLink pt1){
	if (pt1 != NULL){
		for (int i = 0; i < TextLevel; i++)
		{
			std::cout << "  ";
		}
		if (pt1==Current)
			cout << "\b>";
		(*pt1).Print(std::cout);
		if (pt1->Down!=NULL)
		cout << endl;
		TextLevel++;
		PrintText(pt1->GetDown());
		TextLevel--;
		PrintText(pt1->GetNext());
	}
}
void TText::Read(char *pFileName){
	ifstream TxtFile(pFileName);
	TextLevel = 0;
	if (&TxtFile != NULL)
		First = ReadText(TxtFile);
}
PTextLink TText::ReadText(ifstream &TxtFile){
	PTextLink Head, pt1;
	Head = pt1 = new TextLink();
	while (TxtFile.eof() == 0){
		TxtFile.getline(StrBuf, BufLength, '\n');
		if (StrBuf[0] == '}')
		{
			/*TextLevel--;*/ break;
		}
		else if (StrBuf[0] == '{'){
			/*TextLevel++;*/
			pt1->Down = ReadText(TxtFile);
		}
		if ((StrBuf[0] != '{') && (StrBuf[0] != '}')){
			pt1->Next = new TextLink(StrBuf, NULL, NULL);
			pt1 = pt1->Next;
		}
	}
	pt1 = Head;
	if (Head->Down == NULL){
		Head = Head->Next; 
		delete pt1;
	}
	else {
		Head->Next->Down = pt1->Down;
		Head = Head->Next;
		delete pt1;
	}
	return Head;
}
void TText::Write(char *FileName)
{
	ofstream TxtFile(FileName, ios_base::out);
	TextLevel = 0;
	if (&TxtFile != NULL)
		WriteText(TxtFile, First, true);
}
void TText::WriteText(ofstream &TxtFile, PTextLink pl, bool val){
	if (pl != NULL){
		for (int i = 0; i < TextLevel; i++)
		{
			TxtFile << "  ";
		}
		(*pl).Write(TxtFile);
		TxtFile << '\n';
		if (pl->Down != NULL)
		{
			TxtFile << "{" << '\n';
			--TextLevel;
			WriteText(TxtFile, pl->GetDown(), false);
			TxtFile << "}" << '\n';
		}
		if (pl->Next != NULL)
		{
			--TextLevel;
			WriteText(TxtFile, pl->GetNext(), true);
		}
}
}
