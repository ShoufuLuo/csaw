/**
 *  Copyright (c) 2012 Stevens Institute of Technology. 
 *  
 *  All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *	Author: Shoufu Luo
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

#ifndef __HELLO_XPCOM_H__
#define __HELLO_XPCOM_H__

#include "ihelloxpcom.h"
#include "hellopino.h"

#define HELLOXPCOM_CONTRACTID	"@pinocchio.com/XPCOM/Demo;1"
#define HELLOXPCOM_CLASSNAME	"A XPCOM Exampe for Pinocchio"
#define HELLOXPCOM_CID 		{ 0x597a60b0, 0x5272, 0x4284, { 0x90, 0xf6, 0xe9, 0x6c, 0x24, 0x2d, 0x74, 0x6 } }

class helloxpcomImpl:public ihelloxpcom
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IHELLOXPCOM

  helloxpcomImpl();

private:
  hellopino	*_pino;
  ~helloxpcomImpl();

protected:
  /* additional members */
};

#endif
