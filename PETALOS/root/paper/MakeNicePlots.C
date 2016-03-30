#include "nextPlots.C"

void MakeNicePlots(){

  
  TFile* f = new TFile("ProductionScint.root");
  TH1F* histo = f->Get("ScintLambda");

  tcanvset("c");

  th1plot(*histo);
  histo->Draw();
}
