#ifndef _DLLHANDLERS_
#define _DLLHANDLERS_

#include "DllReference.h"
#include "TranslateHandler.h"

class DLLImplementation : public DLLInterface
{
public:
    HandlersMap createHandlers(const Provider& provider);
    void		      releaseHandlers();
    HandlersMap getHandlers() const;

private:
    TranslateHandler* _translate;
};

#endif // _DLLHANDLERS_

