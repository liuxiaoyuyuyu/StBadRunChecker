#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "StBadRunChecker.h"
#include "TError.h"
#include "TRandom.h"
#include "TMath.h"


ClassImp(StBadRunChecker)

using namespace std ;

//______________________________________________________________________________
// Default constructor
StBadRunChecker::StBadRunChecker(){
    readBadRunsFromHeaderFile() ;
}

//______________________________________________________________________________
// Default destructor
StBadRunChecker::~StBadRunChecker() {
  /* empty */
}

//______________________________________________________________________________

void StBadRunChecker::readBadRunsFromHeaderFile() {
    for(int i=0;i<nBadRun_run19_19p6;i++){
        mBadRun_all.push_back(badrun_run19_19p6_all[i]);
        std::vector<Int_t> row;
        for(int j=0;j<12;j++){
            row.push_back(badrun_run19_19p6_sub[i][j]);       
        }
        mBadRun_sub.push_back(row);
    }
	
    cout<<"read in nBadRun_run19_19p6: "<<nBadRun_run19_19p6<<endl;

}


Bool_t StBadRunChecker::isBadRun(const Int_t RunId, const TString mS){
    // Return true if a given run id is bad run
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        int isbad=1;
        for(int iname=0;iname<12;iname++){
            mSubSysName[iname].ToLower();
            //As long as this run was marked as a bad run for one of the sub systems, it is a bad run
            if(mS.Contains(mSubSysName[iname])){
                isbad*=(1-mBadRun_sub[index][iname]);
            }
        }
        return (isbad==0);
    }
}

Bool_t StBadRunChecker::isInjection(const Int_t RunId){
    // Return true if a given run id is bad run
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][0]);
    }
}
