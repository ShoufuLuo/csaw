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

#include "nsIClassInfoImpl.h"
#include "nsIConsoleService.h"
#include "iChimeraRider.h"
#include "nsCOMPtr.h"
#include "chimera.h"

#define CHIMERA_RIDER_CONTRACTID	"@ucsb.edu/XPCOM/ChimeraRider;1"
#define CHIMERA_RIDER_COMPONENT_CLASSNAME	"Chimera Peer-to-Peer Storage System"
#define CHIMERA_RIDER_CID		{ 0x597a61b1, 0x5272, 0x4384, { 0x9f, 0xf6, 0xef, 0x6c, 0x24, 0x2d, 0x74, 0x81 } }

#define TEST_CHAT	15

class ChimeraRider : public iChimeraRider
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_ICHIMERARIDER

	ChimeraRider();

private:
	~ChimeraRider();

	Key				m_nodeKey;
	ChimeraState	*m_state;

protected:
  /* additional members */
};
