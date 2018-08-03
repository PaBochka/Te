#pragma once
#ifndef TextLink_h
#define TextLink_h
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#define MemSize 20
#define TextLineLength 20
class TText;
class TextLink;
typedef TextLink *PTextLink;
typedef char TStr[TextLineLength];
class TextMem
{
public:
	PTextLink First, Last, Free;
	friend class TextLink;  
};
typedef TextMem* PTextMem;
class TextLink
{
public:
	TStr Str;
	PTextLink Down;
	PTextLink Next;
	static TextMem MemHeader;
public:
	static void InitMemSystem(int size = MemSize);
	static void PrintFreeLink(void);
	void* operator new(size_t size);
	void operator delete(void *pM);
	static void MemCleaner(TText(&txt));
	TextLink(TStr s = NULL, PTextLink pn = NULL, PTextLink pd = NULL){
		Next = pn;
		Down = pd;
		if (s != NULL)
		{
			strcpy(Str, s);
		}
		else Str[0] = '\0';
	}
	~TextLink();
	int IsAtom(){ return Down == NULL; };
	PTextLink GetNext(){ return Next; };
	PTextLink GetDown(){ return Down; };
protected:
	virtual void Print(std::ostream &os){ os << Str; os << '\n'; };
	virtual void Write(std::ofstream &TextFile){ TextFile<<Str; };
	friend class TText;
};
#endif