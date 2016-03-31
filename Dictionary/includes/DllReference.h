#ifndef _DLLREFERENCE_
#define _DLLREFERENCE_

#include "..\Dictionary\includes\CommandHandler.h"
#include "..\Dictionary\includes\I_IOManager.h"
#include "..\Dictionary\includes\QueryInterface.h"
#include "..\Dictionary\includes\I_Dictionary.h"
#include "..\Dictionary\includes\I_CommandEngine.h"

#include <map>
#include <string>

struct Provider
{
public:
	virtual I_IOManager* getIOManager() const = 0;
	virtual QueryInterface* getQueryInterface() const = 0;
	virtual I_CommandEngine* getComandEngine() const = 0;
	virtual I_Dictionary* getDictionary() const = 0;
};

class DLLInterface
{
public:
	typedef std::map<std::string,CommandHandler&> HandlersMap;

public:
	virtual HandlersMap createHandlers(const Provider& provider) = 0;
	virtual        void	releaseHandlers() = 0;

	virtual HandlersMap getHandlers() const = 0;

};

typedef DLLInterface* (*FP_GetDLLInterface)();

extern "C" __declspec(dllexport) DLLInterface* getDLLInterface();
	
#endif //_DLLREFERENCE_