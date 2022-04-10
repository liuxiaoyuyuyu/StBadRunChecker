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
StBadRunChecker::StBadRunChecker(TString Run,TString CollisionMode, TString RunEnergy,TString Species){
    Run.ToLower();
    RunEnergy.ToLower();
    CollisionMode.ToLower();
    Species.ToLower();
    
    mRun=Run;
    mEnergy=RunEnergy;
    mColMode=CollisionMode;
    mSpecies=Species;
    TString name_tmp=mRun+"_"+mColMode+"_"+mEnergy+"_"+mSpecies;
    mRunIndex=-1;
    for(int i=0;i<mRunNameCount;i++){
        if(name_tmp==mRunNameList[i]){
            mRunIndex=i;
            break;
        }
    }
    readBadRunsFromHeaderFile();
}

//______________________________________________________________________________
// Default destructor
StBadRunChecker::~StBadRunChecker() {
  /* empty */
}

//______________________________________________________________________________
void StBadRunChecker::readBadRunsFromHeaderFile() {
    switch(mRunIndex){
        case 0:
            for(int i=0;i<2;i++){
                mRunRange.push_back(run19_col_19p6_auau_range[i]);
            }
            for(int i=0;i<nBadRun_run19_col_19p6_auau;i++){
                mBadRun_all.push_back(badrun_run19_col_19p6_auau_all[i]);
                std::vector<Int_t> row;
                for(int j=0;j<12;j++){
                    row.push_back(badrun_run19_col_19p6_auau_sub[i][j]);       
                }
                mBadRun_sub.push_back(row);
            } 
            cout<<"read in bad run list for "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<" GeV. "<<nBadRun_run19_col_19p6_auau<<" bad runs in total."<<endl;
            break;
        /*
        case 1:
            for(int i=0;i<2;i++){
                mRunRange.push_back(run19_col_14p6_auau_range[i]);
            }
            for(int i=0;i<nBadRun_run19_col_14p6_auau;i++){
                mBadRun_all.push_back(badrun_run19_col_14p6_auau_all[i]);
                std::vector<Int_t> row;
                for(int j=0;j<12;j++){
                    row.push_back(badrun_run19_col_14p6_auau_sub[i][j]);       
                }
                mBadRun_sub.push_back(row);
            } 
            cout<<"read in bad run list for "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<" GeV. "<<nBadRun_run19_col_14p6_auau<<" bad runs in total."<<endl;
            break;
        */
        //Add more runs here
        default:
            cout<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<" GeV doesn't exist or the bad run list is not available yet.Exit!"<<endl;
            exit(0);
    }

}


Bool_t StBadRunChecker::isBadRun(const Int_t RunId,TString mS){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    mS.ToLower(); 
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run 
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        int isbad=1;
        for(int iname=0;iname<12;iname++){
            mSubSysName[iname].ToLower();
            //As long as this run was marked as a bad run for one of the sub systems, it is a bad run
            if(mS.Contains(mSubSysName[iname])){
                cout<<"Check if this run is bad for: "<<mSubSysName[iname]<<endl;
                isbad*=(1-mBadRun_sub[index][iname]);
            }
        }
        return (isbad==0);
    }
}

Bool_t StBadRunChecker::isInjection(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
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

Bool_t StBadRunChecker::isBadRunTPC(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][1]);
    }
}

Bool_t StBadRunChecker::isBadRunbTOFStatus(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][2]);
    }
}

Bool_t StBadRunChecker::isBadRunbTOFPID(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][3]);
    }
}

Bool_t StBadRunChecker::isBadRuneTOF(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][4]);
    }
}

Bool_t StBadRunChecker::isBadRunEPD(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][5]);
    }
}

Bool_t StBadRunChecker::isBadRunVPD(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][6]);
    }
}
Bool_t StBadRunChecker::isBadRunBEMCStatus(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][7]);
    }
}

Bool_t StBadRunChecker::isBadRunBEMCPID(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][8]);
    }
}

Bool_t StBadRunChecker::isBadRunBEMCTrigger(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][9]);
    }
}

Bool_t StBadRunChecker::isBadRunMTD(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][10]);
    }
}

Bool_t StBadRunChecker::isBadRunAnalysis(const Int_t RunId){
    // Return true if a given run id is bad run
    if (RunId<mRunRange[0]||RunId>mRunRange[1]){
        cout<<"Warning: "<<RunId<<" is not in "<<mRun<<" "<<mColMode<<" "<<mSpecies<<" "<<mEnergy<<"GeV. Exit!"<<endl;
        exit(0);
    }
    vector<Int_t>::iterator iter = std::find(mBadRun_all.begin(), mBadRun_all.end(), RunId);
    if(iter == mBadRun_all.end()){
        return 0;//RunId is not a bad run =
    }
    //return ( iter != mBadRun.end() ) ;
    else{
        int index = std::distance(mBadRun_all.begin(), iter);//index starts at zero
        return (mBadRun_sub[index][4]);
    }
}
