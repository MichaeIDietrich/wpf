// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.


//------------------------------------------------------------------------------
//
//  Microsoft

//
//  Class: CAssertDllInUse
//      Used to assert that the dll is attempted to unload while
//      some objects are still in use.
//
//  Usage:
//      Put "CAssertDllInUse::Enter()" into constructor of the object that
//      should be traced, and "CAssertDllInUse::Leave()" into destructor.
//      Call CAssertDllInUse::Check() from DllMain() when the reason is
//      DLL_PROCESS_DETACH, prior to everything else.
//      This will prevent misleading messages from other assertions
//      that typically go to details too deep, while real failure reason
//      is somewhat generic (say, emergency shutdown).
//      
//------------------------------------------------------------------------------

#pragma once

class CAssertDllInUse
{
public:
#if DBG
    static void Enter() { InterlockedIncrement(&m_count); }
    static void Leave() { InterlockedDecrement(&m_count); }
    static void Check();
private:
    static volatile LONG m_count;
#else
    static void Enter() {}
    static void Leave() {}
    static void Check() {}
#endif
};


