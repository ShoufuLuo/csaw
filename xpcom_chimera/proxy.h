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
 *	Author: Shoufu Luo (sluo2@stevens.edu)
 * 	Mon Jan 2 6:36:10 EDT 2012 
 *
 */

#ifndef __PROXY_H__
#define __PROXY_H__

#ifdef __cplusplus
extern "C" {
#endif

extern void p2p_proxy_init(ChimeraState *state);
extern void p2p_forward(Key **kp, Message **mp, ChimeraHost **hp);
extern void p2p_deliver(Key *k, Message *m);
extern void p2p_update(Key *k, ChimeraHost *h, int joined);

#ifdef __cplusplus
}
#endif
#endif
