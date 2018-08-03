#include "TextLink.h"
#include "TText.h"
#include <iostream>
#include <string.h>
TextLink::~TextLink()
{
}
void TextLink::InitMemSystem(int size){
	MemHeader.First = (PTextLink)new char[sizeof(TextLink)*size];
	MemHeader.Free = MemHeader.First;
	MemHeader.Last = MemHeader.First + (size - 1);
	PTextLink Link = MemHeader.First;
	for (int i = 0; i < size - 1; i++, Link++){
		Link->Next = Link + 1;
	}
	Link->Next = NULL;
}
void TextLink::PrintFreeLink(void){
	PTextLink Link = MemHeader.Free;
	std::cout << "List of free links" << std::endl;
	while (Link != NULL)
	{
		std::cout << Link->Str << std::endl;
		Link = Link->Next;
	}
}
void *TextLink::operator new(size_t size){
	PTextLink Link = MemHeader.Free;
	if (MemHeader.Free != NULL)
		MemHeader.Free = Link->Next;
	return Link;
}
void TextLink::operator delete(void *pM){
	PTextLink Link = (PTextLink)pM;
	Link->Next = MemHeader.Free;
	MemHeader.Free = Link;
}
void TextLink::MemCleaner(TText &txt){
	std::string st;
	txt.Reset();
	while (!txt.IsTextEnded())
	{
		if (st.find("&&&") != 0)
			txt.SetLine("&&&" + txt.Getline());
		txt.GoNext();
	}
	PTextLink Link = MemHeader.Free;
	while (Link != NULL)
	{
		strcpy(Link->Str, "&&&");
		Link = Link->Next;
	}
	Link = MemHeader.First;
	while (Link <= MemHeader.Last)
	{
		if (strstr(Link->Str, "&&&") != NULL)
			strcpy(Link->Str, Link->Str + 3);
		else delete Link;
		Link++;
	}
}