#ifndef __StBadRunChecker_h__
#define __StBadRunChecker_h__

#include <vector>
#include <map>
#include "TString.h"

#include "BadRun.h"
//______________________________________________________________________________
class StBadRunChecker {
 public:
  StBadRunChecker();
  virtual ~StBadRunChecker(); /// Default destructor
  
  // Bad run rejection
  Bool_t isInjection(const Int_t RunId) ;
  /*
  Bool_t isBadRunTPC(const Int_t RunId) ;
  Bool_t isBadRunbTOFStatus(const Int_t RunId) ;
  Bool_t isBadRunbTOFPID(const Int_t RunId) ;
  Bool_t isBadRuneTOF(const Int_t RunId) ;
  Bool_t isBadRunEPD(const Int_t RunId) ;
  Bool_t isBadRunVPD(const Int_t RunId) ;
  Bool_t isBadRunBEMCStatus(const Int_t RunId) ;
  Bool_t isBadRunBEMCPID(const Int_t RunId) ;
  Bool_t isBadRunBEMCTrigger(const Int_t RunId) ;
  Bool_t isBadRunMTD(const Int_t RunId) ;
  Bool_t isBadRunAnalysis(const Int_t RunId) ;
  */
  Bool_t isBadRun(const Int_t RunId,const TString mSys) ; 
 private:
  void readBadRunsFromHeaderFile();
  //std::vector<Int_t> mYear              ; /// Year
  //std::vector<Int_t> mStart_runId       ; /// Start run id
  //std::vector<Int_t> mStop_runId        ; /// Stop run id

  //std::multimap<std::pair<Double_t, Int_t>, Int_t> mBeginRun ; /// Begin run number for a given (energy, year)
  //std::multimap<std::pair<Double_t, Int_t>, Int_t> mEndRun   ; /// End run number for a given (energy, year)
  std::vector<Int_t> mBadRun_all; /// Bad run number list
  std::vector<std::vector<Int_t>> mBadRun_sub;
  //const TString mSubSysName[12]={"Injection","TPC","bTOFStatus","bTOFPID","eTOF","EPD","VPD","BEMCStatus","BEMCPID","BEMCTrigger","MTD","Analysis"};
  TString mSubSysName[12]={"Injection","TPC","bTOFStatus","bTOFPID","eTOF","EPD","VPD","BEMCStatus","BEMCPID","BEMCTrigger","MTD","Analysis"};
  ClassDef(StBadRunChecker, 0)
};
#endif