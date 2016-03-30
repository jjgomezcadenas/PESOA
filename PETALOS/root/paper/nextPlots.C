#include "TROOT.h"
#include "TStyle.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TPaletteAxis.h"
#include "TCanvas.h"

void grerrplot(TGraphErrors& plot) {
  
  plot.SetTitle("");
  plot.SetLineWidth(2);
  plot.SetMarkerColor(2);
  plot.SetMarkerStyle(1);

  plot.GetXaxis()->SetTitleOffset(1);
  plot.GetYaxis()->SetTitleOffset(1.45);

  plot.GetXaxis()->SetTitleFont(42);
  plot.GetYaxis()->SetTitleFont(42);
 
  plot.GetXaxis()->SetTitleSize(0.05);
  plot.GetYaxis()->SetTitleSize(0.05);

  plot.GetXaxis()->SetLabelFont(42);
  plot.GetYaxis()->SetLabelFont(42);
  
  plot.GetXaxis()->SetLabelSize(0.05);
  plot.GetYaxis()->SetLabelSize(0.05);
 
  plot.GetXaxis()->SetLabelOffset(0.01);
  plot.GetYaxis()->SetLabelOffset(0.01);
}


void grplot(TGraph& plot) {
  
  plot.SetTitle("");
  plot.SetLineWidth(2);
  plot.SetMarkerColor(2);
  plot.SetMarkerStyle(1);

  plot.GetXaxis()->SetTitleOffset(1);
  plot.GetYaxis()->SetTitleOffset(1.45);

  plot.GetXaxis()->SetTitleFont(42);
  plot.GetYaxis()->SetTitleFont(42);
 
  plot.GetXaxis()->SetTitleSize(0.05);
  plot.GetYaxis()->SetTitleSize(0.05);

  plot.GetXaxis()->SetLabelFont(42);
  plot.GetYaxis()->SetLabelFont(42);
  
  plot.GetXaxis()->SetLabelSize(0.05);
  plot.GetYaxis()->SetLabelSize(0.05);
 
  plot.GetXaxis()->SetLabelOffset(0.01);
  plot.GetYaxis()->SetLabelOffset(0.01);
}

void th2plot(TH2& plot, TString drawOpt="colz"){

  plot.SetStats(0);
  plot.SetTitle("");
  plot.SetLineWidth(2);

  plot.GetXaxis()->SetTitleOffset(1);
  plot.GetYaxis()->SetTitleOffset(1.45);
  plot.GetZaxis()->SetTitleOffset(1.0);
  plot.GetXaxis()->SetTitleFont(42);
  plot.GetYaxis()->SetTitleFont(42);
  plot.GetZaxis()->SetTitleFont(42);
  plot.GetXaxis()->SetTitleSize(0.05);
  plot.GetYaxis()->SetTitleSize(0.05);
  plot.GetZaxis()->SetTitleSize(0.04);
  plot.GetZaxis()->RotateTitle(1);
  plot.GetZaxis()->SetTickLength(0.02);
  plot.GetXaxis()->SetLabelFont(42);
  plot.GetYaxis()->SetLabelFont(42);
  plot.GetZaxis()->SetLabelFont(42);
  plot.GetXaxis()->SetLabelSize(0.05);
  plot.GetYaxis()->SetLabelSize(0.05);
  plot.GetZaxis()->SetLabelSize(0.03);
  plot.GetXaxis()->SetLabelOffset(0.01);
  plot.GetYaxis()->SetLabelOffset(0.01);

}

void tprof2Dplot(TProfile2D& plot){

  plot.SetStats(0);
  plot.SetTitle("");
  plot.SetLineWidth(2);

  plot.GetXaxis()->SetTitleOffset(1);
  plot.GetYaxis()->SetTitleOffset(1.45);
  plot.GetZaxis()->SetTitleOffset(1.0);
  plot.GetXaxis()->SetTitleFont(42);
  plot.GetYaxis()->SetTitleFont(42);
  plot.GetZaxis()->SetTitleFont(42);
  plot.GetXaxis()->SetTitleSize(0.05);
  plot.GetYaxis()->SetTitleSize(0.05);
  plot.GetZaxis()->SetTitleSize(0.04);
  plot.GetZaxis()->RotateTitle(1);
  plot.GetZaxis()->SetTickLength(0.02);
  plot.GetXaxis()->SetLabelFont(42);
  plot.GetYaxis()->SetLabelFont(42);
  plot.GetZaxis()->SetLabelFont(42);
  plot.GetXaxis()->SetLabelSize(0.05);
  plot.GetYaxis()->SetLabelSize(0.05);
  plot.GetZaxis()->SetLabelSize(0.04);
  plot.GetXaxis()->SetLabelOffset(0.01);
  plot.GetYaxis()->SetLabelOffset(0.01);

}

void paletteAdjust(TH2& plot){

  gPad->Update();
  
  TPaletteAxis *pal = (TPaletteAxis*)plot.GetListOfFunctions()->FindObject("palette");
  pal->SetX1NDC(0.902);
  pal->SetX2NDC(0.925);
  
}

void th1plot(TH1& plot){

  plot.SetStats(0);
  plot.SetTitle("");
  plot.SetLineWidth(2);

  plot.GetXaxis()->SetTitleOffset(1);
  plot.GetYaxis()->SetTitleOffset(1.45);
  plot.GetXaxis()->SetTitleFont(42);
  plot.GetYaxis()->SetTitleFont(42);
  plot.GetXaxis()->SetTitleSize(0.05);
  plot.GetYaxis()->SetTitleSize(0.05);
  plot.GetXaxis()->SetLabelFont(42);
  plot.GetYaxis()->SetLabelFont(42);
  plot.GetXaxis()->SetLabelSize(0.05);
  plot.GetYaxis()->SetLabelSize(0.05);
  plot.GetXaxis()->SetLabelOffset(0.01);
  plot.GetYaxis()->SetLabelOffset(0.01);

}

void tprofplot(TProfile& plot){

  plot.SetStats(0);
  plot.SetTitle("");
  plot.SetLineWidth(2);

  plot.GetXaxis()->SetTitleOffset(1);
  plot.GetYaxis()->SetTitleOffset(1.45);
  plot.GetXaxis()->SetTitleFont(42);
  plot.GetYaxis()->SetTitleFont(42);
  plot.GetXaxis()->SetTitleSize(0.05);
  plot.GetYaxis()->SetTitleSize(0.05);
  plot.GetXaxis()->SetLabelFont(42);
  plot.GetYaxis()->SetLabelFont(42);
  plot.GetXaxis()->SetLabelSize(0.05);
  plot.GetYaxis()->SetLabelSize(0.05);
  plot.GetXaxis()->SetLabelOffset(0.01);
  plot.GetYaxis()->SetLabelOffset(0.01);

}

TLegend* tlegset(){
  
  TLegend *leg = new TLegend(0.7,0.9,0.9,0.7);
  leg->SetFillColor(0);
  
  return leg;
}

TCanvas* tcanvset(TString name){

  TCanvas *canv = new TCanvas(name,name,90,90,900,600);

  canv->SetLeftMargin(0.15);
  canv->SetRightMargin(0.1);
  canv->SetTopMargin(0.05);
  canv->SetBottomMargin(0.12);

  gPad->SetTickx();
  gPad->SetTicky();

  return canv;
}

void nextPlots(){
  //Load all the basic settings to make plots look good.

  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetStatColor(0);
  // gStyle->SetPalette(1,0);
  gStyle->SetPalette(53);
  gStyle->SetOptFit(111);
  gStyle->SetLabelSize(0.03,"x");
  gStyle->SetLabelSize(0.03,"y");
  gStyle->SetLabelSize(0.03,"z");

}
