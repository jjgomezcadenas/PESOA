#include "nextPlots.C"

void round1_noCher(){
    TFile *fIn1 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LXe_VUV3mm_xy2.4cm_z5cm_n1.7_noCher_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
    TFile *fIn2 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LXe_TPB3mm_xy2.4cm_z5cm_n1.7_noCher_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
    TFile *fIn3 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LYSO_VUV3mm_xy2.4cm_z5cm_n1.8_noCher_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");

	plotFirstPE(fIn1,fIn2,fIn3);
	plotCRTCombined(fIn1,fIn2,fIn3);

	fIn1->Close();
	fIn2->Close();
	fIn3->Close();
}

void plotCRTCombined(TFile *fIn1, TFile* fIn2, TFile* fIn3){
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(1110);

    TH1F *h1 = (TH1F*) fIn1->Get("DTOF.DTOF3");
    TH1F *h2 = (TH1F*) fIn2->Get("DTOF.DTOF3");
    TH1F *h3 = (TH1F*) fIn3->Get("DTOF.DTOF3");

	//TCanvas *c1 = new TCanvas("c1","multipads",900,700);
	TCanvas *c1 = tcanvset("c");

	//Combined
	h1->SetStats(kFALSE);
	h2->SetStats(kFALSE);
	h3->SetStats(kFALSE);

	h1->Scale(1/h1->Integral(), "width");
	h2->Scale(1/h2->Integral(), "width");
	h3->Scale(1/h3->Integral(), "width");

	h1->SetTitle("");
	h1->GetXaxis()->SetRangeUser(-60,60);
	h1->GetXaxis()->SetTitle("#Deltat (ps)");
	h1->GetYaxis()->SetTitle("Fraction of events");

	th1plot(*h1);
	th1plot(*h2);
	th1plot(*h3);

    h1->Draw();
    h2->SetLineColor(kRed);
//    h2->Draw("same");
    h3->SetLineColor(kGreen+3);
	h3->SetLineStyle(2);
    h3->Draw("same");

	//TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	TLegend *leg = tlegset();
	leg->SetFillColor(0);
	leg->AddEntry(h1, "LXe", "lp");
//	leg->AddEntry(h2, "LXe-TPB", "lp");
	leg->AddEntry(h3, "LYSO", "lp");
	leg->Draw("same");
	
	c1->Print("/home/jmbenlloch/next/petalo/PESOA/PETALOS/root/paper/plots/DTOFLXeLYSO.png");

	h1->Reset();
	h2->Reset();
	h3->Reset();

	c1->Close();
}

void plotFirstPE(TFile *fIn1, TFile* fIn2, TFile* fIn3){
    TH1F *h1 = (TH1F*) fIn1->Get("NFirst.Time_1_PEBox1");
    TH1F *h2 = (TH1F*) fIn2->Get("NFirst.Time_1_PEBox1");
    TH1F *h3 = (TH1F*) fIn3->Get("NFirst.Time_1_PEBox1");

	//TCanvas *c1 = new TCanvas("c1","multipads",900,700);
	TCanvas *c1 = tcanvset("c");

	//Combined
	h1->SetStats(kFALSE);
	h2->SetStats(kFALSE);
	h3->SetStats(kFALSE);
	h1->Scale(1/h1->Integral(), "width");
	h2->Scale(1/h2->Integral(), "width");
	h3->Scale(1/h3->Integral(), "width");

	shift(h1);
	shift(h2);
	shift(h3);

	th1plot(*h1);
	th1plot(*h2);
	th1plot(*h3);

	h1->SetTitle("");
	h1->GetXaxis()->SetRangeUser(-20,80);
	h1->GetXaxis()->SetTitle("t (ps)");
	h1->GetYaxis()->SetTitle("Fraction of events");

	h1->Draw();
    h2->SetLineColor(kRed);
//	h2->Draw("same");
	h3->SetLineColor(kGreen+3);
	h3->SetLineStyle(2);
	h3->Draw("same");
	//TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	TLegend *leg = tlegset();
	leg->SetFillColor(0);
	leg->AddEntry(h1, "LXe", "lp");
	//leg->AddEntry(h2, "LXe-TPB", "lp");
	leg->AddEntry(h3, "LYSO", "lp");
	leg->Draw("same");
	c1->Print("/home/jmbenlloch/next/petalo/PESOA/PETALOS/root/paper/plots/FirstPEScintLXeLYSO.png");

	c1->Close();
}

void shift(TH1F* h){
	for(int i=0;i<h->GetNbinsX();i++){
		double counts = h->GetBinContent(100-i-1);
		h->SetBinContent(100-i, counts);
	}
}
