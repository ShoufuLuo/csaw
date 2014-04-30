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

#include <iostream>
#include "nsMemory.h"
#include "helloxpcomImpl.h"
#include "hellopino.h"

NS_IMPL_ISUPPORTS1(helloxpcomImpl, ihelloxpcom)

helloxpcomImpl::helloxpcomImpl()
{
}

helloxpcomImpl::~helloxpcomImpl()
{
}

NS_IMETHODIMP helloxpcomImpl::Multiple(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM)
{
	_pino = new hellopino((int) a, (int) b);
	*_retval = _pino->multiple();
	return NS_OK;
}

