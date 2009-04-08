//  $Id: FileUtil.cpp,v 1.6 2005-06-17 21:02:59 blowek1 Exp $
// ===========================================================================
//
//                            PUBLIC DOMAIN NOTICE
//            Office of High Performance Computing and Communications
//
//  This software/database is a "United States Government Work" under the
//  terms of the United States Copyright Act.  It was written as part of
//  the author's official duties as a United States Government employee and
//  thus cannot be copyrighted.  This software is freely available
//  to the public for use. The National Library of Medicine and the U.S.
//  Government have not placed any restriction on its use or reproduction.
//
//  Although all reasonable efforts have been taken to ensure the accuracy
//  and reliability of the software and data, the NLM and the U.S.
//  Government do not and cannot warrant the performance or results that
//  may be obtained by using this software or data. The NLM and the U.S.
//  Government disclaim all warranties, express or implied, including
//  warranties of performance, merchantability or fitness for any particular
//  purpose.
//
//  Please cite the author in any work or product based on this material.
//
// ===========================================================================
//

/// \file
/// \author  Bradley Lowekamp
/// \version $Revision: 1.6 $
/// \brief  
///
///


#include "FileUtil.h"


#include <sys/types.h>
#include <sys/stat.h>

#if defined(WIN32)
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#endif

#include <stdexcept>
#include <stdlib.h>
#include <iostream> 

#define MAX_PATH 1024

namespace fileutil {

  
  PathList GetPathFromEnviroment(const std::string &env) {
    PathList pl;
    char *cstr =  getenv(env.c_str());
    if (!cstr)
      return pl;

    return GetPathListFromColonSeparatedList(cstr);
  }

  PathList GetPathListFromColonSeparatedList(const std::string &value) {
    PathList pl;

    if (value == "")
      return pl;
   
    std::string::size_type i = 0;
    
    while (i != std::string::npos) {
      std::string::size_type j = i;
      i = value.find(':', j);
      if (i == std::string::npos)
	pl.push_back(PathName(value.substr(j, value.length() - j)));
      else {
	pl.push_back(PathName(value.substr(j, i - j )));
	++i;
      }
    }

    return pl;
  }
  

  bool SetCurrentDirectory(const PathName &path) {
    if (!path.IsDirectory())
      throw std::runtime_error(std::string("\"") + path.GetNativePathName() + "\" is not a directory.");
    return chdir(path.GetNativePathName().c_str()) != -1;
  }

  PathName GetCurrentDirectory(void) {
    std::string result;
    struct stat s;

    if (!stat(".", &s)) {
      char currentName[MAX_PATH];
      getcwd(currentName, MAX_PATH);
      result = currentName;
    }
    return PathName(result);
  }
  
  
	
}


//
// ===========================================================================
//
// $Log: not supported by cvs2svn $
// Revision 1.5  2004/05/13 18:19:14  blowek1
// removed extra output statement
//
// Revision 1.4  2004/05/13 18:17:42  blowek1
// fixed bugs in GetPathFromEnviroment
//
// Revision 1.3  2004/03/02 20:21:52  blowek1
// fixed null string bug in get path for enviroment function
//
// Revision 1.2  2003/12/15 15:36:27  blowek1
// changed system defined
//
// Revision 1.1  2003/12/12 20:15:32  blowek1
// initial check in
//
// Revision 1.2  2003/12/08 18:50:30  blowek1
// got it to compile on windows
//
// Revision 1.1  2003/12/04 20:00:45  blowek1
// initial check in
//
// Revision 1.1  2003/12/03 16:17:07  blowek1
// incremental check in
//
//
//
//
// ===========================================================================
//
