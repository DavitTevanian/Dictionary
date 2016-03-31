#include "DllHandlers.h"
#include "..\Dictionary\includes\I_Dictionary.h"
#include "..\Dictionary\includes\QueryInterface.h"
#include <iostream>

extern "C" __declspec(dllexport) DLLInterface* getDLLInterface()
{
    static DLLImplementation DLLImpl;
    return &DLLImpl;
}

DLLInterface::HandlersMap DLLImplementation::createHandlers(const Provider& provider)
{
    releaseHandlers();

    HandlersMap handlers;

    I_Dictionary* dict = provider.getDictionary();
    if (dict != NULL)
    {
        cout << 1;
        _translate = new TranslateHandler(*dict);
        handlers["translate"] = _translate;

    }

    return handlers;
}

DLLInterface::HandlersMap DLLImplementation::getHandlers() const
{
    HandlersMap handlers;

    if (_translate)
        handlers["translate"] = _translate;

    return handlers;
}

void DLLImplementation::releaseHandlers()
{
    if (_translate)
    {
        delete _translate;
        _translate = 0;
    }

}