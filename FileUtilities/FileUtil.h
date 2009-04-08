#ifndef FILEUTIL_H 	/* -*- c++ -*- */
#define FILEUTIL_H


//  $Id: FileUtil.h,v 1.5 2005-06-17 21:02:59 blowek1 Exp $
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
/// \version $Revision: 1.5 $
/// \brief  
///
///

#include <string>
#include "PathName.h"
#include "fileutilConfigure.h"

namespace fileutil {

 
  /// \brief get a path list from the enviroment
  ///
  /// env is the name of the enviroment variable with the value of a
  /// colon separated sequence of path (relative or absolute.
  FILEUTIL_EXPORT PathList GetPathFromEnviroment(const std::string &env);

  /// \brief extract a path list from a color separated list
  FILEUTIL_EXPORT PathList GetPathListFromColonSeparatedList(const std::string &value);



  /// \brief changes the current working directory to path, if
  /// !IsDirectory() then an exception will be thrown
  FILEUTIL_EXPORT bool SetCurrentDirectory(const PathName &path);

#ifdef GetCurrentDirectory
#undef GetCurrentDirectory
#endif 
  /// \brief returns the current working directory
  FILEUTIL_EXPORT PathName GetCurrentDirectory(void);
  
}


//
// ===========================================================================
//
// $Log: not supported by cvs2svn $
// Revision 1.4  2004/03/24 16:09:13  blowek1
// hacked a define in MS to be undefined
//
// Revision 1.3  2003/12/23 18:48:03  blowek1
// added export support
//
// Revision 1.2  2003/12/15 16:36:17  dave
//
// fixed doxygen typos
//
// Revision 1.1  2003/12/12 20:15:33  blowek1
// initial check in
//
//
//
// ===========================================================================
//

#endif // FILEUTIL_H
