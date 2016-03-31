#include "DllReference.h"
#include <iostream>
DLL_EXPORT void GetDllHandlers(vector<CommandSpace> & commands){
	 CommandSpace temp;
	 temp.command="dllhandler";
	 temp.handler=new DLLHandler(* _dictionary);
	 _commands.push_back(temp);
	 commands.push_back(temp);
	
}

DLL_EXPORT void SetDictionary(Dictionary & instance){
	 _dictionary=& instance;
 }
 
DLL_EXPORT void DeleteDllHandlers(){
	 for(size_t i=0;i<_commands.size();++i)
		 delete _commands[i].handler;
 }