#ifndef REGRESSIONTEST_H 	/* -*- c++ -*- */
#define REGRESSIONTEST_H


//  $Id: RegressionTest.h,v 1.16 2004-05-24 20:45:32 blowek1 Exp $
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
/// \version $Revision: 1.16 $
/// \brief  declaration of the RegressionTest testing framework class
///
///

#include "FileUtilities/PathName.h"
#include <string>
#include <iostream>
#include <list>
#include "TestingFramework/TestFrameworkConfigure.h"

namespace testutil {
  
  class Measurement;
  class DifferenceVisitor;

  /// \brief A base class for implementing tests
  ///
  /// This class provides the functionality of being able help
  /// generate and compare measurements. It does this by operating in
  /// two mode, CompareMode, and non-CompareMode. In non-CompareMode
  /// the measurements are simply output to a file, in the other a
  /// file of measurements is loaded, called the input
  /// measurements, and then the measurements created, the test measuments, are
  /// compared, from this the compared output is generated.
  ///
  /// The command line arguments that it know is -I infilename -O
  /// outfilename. If -I is not specified then it will regression test
  /// will run in non-CompareMode
  class TESTINGFRAMEWORK_EXPORT RegressionTest {
  public:

    RegressionTest(void);
    virtual ~RegressionTest(void);
      
    //@{
    /// \brief set/get the path to search for the input file
    ///
    /// The paths which are searched for the input file. The first one
    /// in the list to contain InFileName will be used.
    ///
    virtual void SetInFileSearchPath(const fileutil::PathList &path);
    virtual const fileutil::PathList &GetInFileSearchPath(void) const;
    //@}
      
    //@{
    /// \brief set/get the input file name
    ///
    /// if the name is "" then it is considered not to be set, and no
    /// input will be used, there by putting the system into
    /// non-CompareMode 
    virtual void SetInFileName(const std::string &fname);
    virtual const std::string &GetInFileName(void) const;
    //@}

    //@{
    /// \brief set/get the output file name
    ///
    /// if the name is "" then it is considered not to be set and
    /// std::cout will be used for the output, and the output will
    /// conform to the expected output for Dart
    virtual void SetOutFileName(const std::string &fname);
    virtual const std::string &GetOutFileName(void) const;
    //@}

    //@{
    /// \brief set/get the relative tolerance of numeric values
    /// 
    /// Relative tolerance is used for numeric values. It is a maximum
    /// percentage error.
    virtual void SetRelativeTolerance(double tol);
    virtual double GetRelativeTolerance(void) const;
    ///@}

    /// \brief true if in CompareMode
    ///
    /// This check to see if the InfileName is openable or is already
    /// open, resultign the the measurements being in compare mode
    virtual bool GetCompareMode(void) const;

    /// \brief the main like funciton of the class
    ///
    /// This should be passed the command line arguments. It will the
    /// call ParseAndRemoveArguments to extract the input and output
    /// files. Next it will try to open them, read the input file, and then envoke Test
    /// with the remaining arguments. Finally the files will be
    /// closed.
    ///
    /// If in compare mode, the the return value is the number of
    /// measurements that did not match. Otherwise it is the return
    /// value of test.
    virtual int Main(int argc, char *argv[]);
      
  protected:

    /// \brief the function to perform the test and create measurments
    virtual int Test(int argc, char *argv[]) = 0;

    virtual int MeasurementTextString(const std::string &str, const std::string &name);
    virtual int MeasurementTextPlain(const std::string &str, const std::string &name);


    virtual int MeasurementLinkURL(const std::string &name);
    virtual int MeasurementLinkImage(const std::string &name);

    virtual int MeasurementNumericInteger(int i, const std::string &name, bool tolerant = false);
    virtual int MeasurementNumericFloat(float f, const std::string &name, bool tolerant = true);
    virtual int MeasurementNumericDouble(double d, const std::string &name, bool tolerant = true);
    virtual int MeasurementNumericBoolean(bool b, const std::string &name, bool tolerant = false);
    
    virtual int MeasurementImagePNG(const std::string &name);
    virtual int MeasurementImageJPEG(const std::string &name);


    ///@{
    /// \brief Records/Compares a measurement where the content is in a file
    ///
    /// The full pathname should be used for fileName, however this
    /// will not be checked. When in compare mode The full paths will
    /// be printed in the output, otherwise just the filename will be
    /// printed. When loading the files it is assumed that the "Input"
    /// file is in the same directory as the Test file name.  
    virtual int MeasurementFileTextPlain(const std::string &fileName, const std::string &name);
    virtual int MeasurementFileImagePNG(const std::string &fileName, const std::string &name);
    virtual int MeasurementFileImageJPEG(const std::string &fileName, const std::string &name);
    ///@}

         
    /// \brief gets the output stream
    ///
    /// Valid only when the files have been opened
    virtual std::ostream &GetOutStream(void) const;

    /// \brief gets the input stream
    ///
    /// Valid only when the files have been opened
    virtual std::istream &GetInStream(void) const;
    
  private:
    /// opens and reads the files. called before Test
    virtual void BeginMeasurement(void);

    /// closes files, called after Test
    virtual void EndMeasurement(void);

    
    /// compares the test measurement with the current input
    /// measurement. May print output
    ///
    /// returns 0 if they are the same, non-zero other wise
    virtual int CompareMeasurement(Measurement &test, bool tolerant = false);

    /// a test measurement did not match the current input
    /// measurement. May pring output
    virtual void UnmatchedMeasurement(Measurement &m);

    /// the test measurement matched and has the same value as the
    /// current input measurement. May print output
    virtual void MatchedMeasurement(Measurement &m);

    /// the test and the input measurement matched but they had
    /// different values. Then calles the DifferenceVisitor on the test
    virtual void DifferenceMeasurement(Measurement &test, Measurement &input);
    

    /// Creates a difference visitor for the measurement
    virtual DifferenceVisitor *CreateDifferenceVisitor(void) const;

    /// Pareses are removes the -I infilename -O outfilename from the
    /// command line arguments
    virtual void ParseAndRemoveArguments(int argc, char *argv[]);

  
    /// writes the XML header when writing to a file
    virtual void WriteXMLOutputStart(void);

    /// writes the XML tail when writing to a file
    virtual void WriteXMLOutputEnd(void);
            

    /// Reads the InStream and creats the Input Measurements
    virtual void ReadXMLInput(void);

    /// Frees any data created
    virtual void ReadXMLInputFree(void);

    /// stores the input measuremnts
    std::list<Measurement*> Input;



  private:
      
    // these functions must be static
    static void _UnexpectedHandler(void);
    static void _TerminateHandler(void);

  protected:
    
    fileutil::PathName inFileName;
    fileutil::PathName outFileName;
    fileutil::PathList searchPath;

    std::ostream *os;
    std::istream *is;

    double relativeTolerance;

    int inputUnmatched;


  private: // private data

    RegressionTest(const RegressionTest &); // Not implemented
    RegressionTest &operator=(const RegressionTest &); // Not implemented

   
  };

      
	
}


//
// ===========================================================================
//
// $Log: not supported by cvs2svn $
// Revision 1.15  2004/02/06 16:33:13  blowek1
// updated documentation
//
// Revision 1.14  2003/12/23 18:49:20  blowek1
// added export support
//
// Revision 1.13  2003/12/19 18:28:19  blowek1
// implemented tolerant measuremtns
//
// Revision 1.12  2003/12/18 20:49:25  blowek1
// begun implementing tolerant compare
//
// Revision 1.11  2003/12/15 16:36:17  dave
//
// fixed doxygen typos
//
// Revision 1.10  2003/12/12 20:20:54  blowek1
// move file utils to a separate directory
//
// Revision 1.9  2003/12/10 22:01:23  blowek1
// added documentation to the what the Measurement file will be handled
//
// Revision 1.8  2003/12/09 16:14:26  blowek1
// fixed typeo
//
// Revision 1.7  2003/12/09 16:13:31  blowek1
// added measuementfile plaintext
//
// Revision 1.6  2003/12/08 18:50:30  blowek1
// got it to compile on windows
//
// Revision 1.5  2003/12/05 20:47:29  blowek1
// added numeric classes, and a bunch of other improvements, incremential
//
// Revision 1.4  2003/12/04 20:01:09  blowek1
// mostly added documentation
//
// Revision 1.3  2003/12/03 16:17:03  blowek1
// incremental check in
//
// Revision 1.2  2003/11/26 16:15:47  blowek1
// revision so that it is working
//
// Revision 1.1  2003/11/25 19:45:57  blowek1
// initial check in
//
//
//
// ===========================================================================
//

#endif // RegressionsTest_H
    
