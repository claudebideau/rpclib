#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

/**   1. Include files  (own)                                       **/
#include "rpc/xmlrpc_method.h"

using namespace std;



ElementMethodCl::ElementMethodCl()
{
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "n:A";
            // method's result and two arguments are integers
        this->_help = "this method offer the functionality to list of element.\n";
    return;
}
    
void ElementMethodCl::execute(xmlrpc_c::paramList const& paramList,xmlrpc_c::value *   const  retvalP) 
{
        
        
        if (paramList.size() == 0)
        {
            /* return list of element */
            *retvalP = xmlrpc_c::value_string("empty");
        }
}