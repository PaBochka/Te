#pragma once
#ifndef TText_h
#define TText_h
#include <stack>
#include <fstream>
#include "TextLink.h"
#include <string.h>
class TText;
//typedef TText* PText;
class TText
{
public:
	size_t count_link = 0;
	size_t count_out = 0;
	PTextLink First;
	PTextLink Current;
	std::stack <PTextLink> Path; 
	std::stack <PTextLink> St; 
	PTextLink GetFirstAtom(PTextLink p1);
	void PrintText(PTextLink p1);
	PTextLink ReadText(std::ifstream &Txtfile);
	void WriteText(std::ofstream &Txtfile, PTextLink pl, bool val);
public:
	TText(PTextLink p1 = NULL);
	~TText(){ First = NULL; }
	/*PText GetCopy(void);*/
	
	void GoFirstLink(void);
	void GoDownLink(void);
	void GoNextLink(void);
	void GoPrevLink(void);
	
	std::string Getline(void);
	void SetLine(std::string s);

	void InsDownLine(std::string s);
	void InsDownSection(std::string s);
	void InsNextLine(std::string s);
	void InsNextSection(std::string s);
	void DelDownSection(void);
	void DelDownLine(void);
	void DelNextLine(void);
	void DelNextSection(void);
	void DelFirst(void);
	int Reset(void);
	int IsTextEnded(void) const;
	int GoNext(void);
	void Read(char *FileName);
	void Write(char *FileName);
	
	void Print();
};
#endif