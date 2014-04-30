/*!
 * \file xmlrpc_method_h.h
 * \author claude.bideau@gmail.com
 * \version 0.1
 * \brief This module provides a xmlrpc method declaration.
 * \date  2014/03/21
 * 
 * \section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This module provides a common declaration.
 *
 */
#ifndef XMLRPC_METHOD_H
#define XMLRPC_METHOD_H
/**   1. Standard Library Include                                   **/
#include <iostream>
#include <string>
#include <xmlrpc-c/base.hpp>

/**   1. Include files  (own)                                       **/
/**   2a.   External Functions                                      **/
/**   2b.   External Data                                           **/
/**   3.  Type Definitions                                          **/
/**   5.  Local Functions                                           **/
/**   6.  Macros / Defines                                          **/

 /**
 * \class CalibrateMethodCl
 * \brief 
 *
 */
class CalibrateMethodCl : public xmlrpc_c::method
{
    public:
        CalibrateMethodCl();
        void execute(xmlrpc_c::paramList const& ,xmlrpc_c::value *   const  );
};


 /**
 * \class ElementMethodCl
 * \brief 
 *
 */
class ElementMethodCl : public xmlrpc_c::method
{
    public:
        ElementMethodCl();
        void execute(xmlrpc_c::paramList const& ,xmlrpc_c::value *   const  );
};

extern void RtTraceRpcAttach(xmlrpc_c::registry * );
extern void TraceRpcAttach(xmlrpc_c::registry * );


#endif // XMLRPC_METHOD_H
