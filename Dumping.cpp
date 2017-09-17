
#include "Dumping.h"

#define DUMPIDTOFILE

void Dump::DumpClassIds()
{
#ifdef DUMPIDTOFILE
#endif
	ClientClass* cClass = Interfaces::Client->GetAllClasses();
	while (cClass)
	{
	
		cClass = cClass->m_pNext;
	}
}