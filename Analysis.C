R__LOAD_LIBRARY(./StBadRunChecker_cxx.so)
#include <TSystem.h>
#include <string>
#include <iostream>
#include <fstream>

void Analysis()
{
  StBadRunChecker* checker1=new StBadRunChecker("run20","7.7");
  if(checker1->isBadRun(21081002,"tpc")){//tpc bad run 
    cout<<21081002<<" got rejected becasue of tpc"<<endl;
  } 
  else{
    cout<<21081002<<" is a good run!"<<endl;
  }

  if(checker1->isBadRunEPD(21068034)){//injection bad run 
    cout<<21068034<<" got rejected becasue of injection"<<endl;
  }
  else{
    cout<<21068034<<" is a good run!"<<endl;
  }
  if(checker1->isBadRun(10066008,"tpc")){//good run 
    cout<<10066008<<" got rejected becasue of tpc or injection"<<endl;
  } 
  else{
    cout<<10066008<<" is a good run!"<<endl;
  }
  cout<<"Finish"<<endl;

  
    
}
