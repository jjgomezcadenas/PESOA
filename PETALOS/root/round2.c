void round2(){
    TFile *fIn1 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LXe_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
    TFile *fIn2 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LXe_TPB3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
    TFile *fIn3 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LYSO_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");

	plotNPhotons(fIn1,fIn2,fIn3);
	plotCRT(fIn1,fIn2,fIn3);
	plotFirstPE(fIn1,fIn2,fIn3);

	fIn1->Close();
	fIn2->Close();
	fIn3->Close();

    TFile *fIn1 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LXe_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
    TFile *fIn2 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LXe_TPB3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
    TFile *fIn3 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LYSO_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
	plotCRTCombined(fIn1,fIn2,fIn3);
	fIn1->Close();
	fIn2->Close();
	fIn3->Close();
}

void plotX(TFile *fIn1, TFile* fIn2, TFile* fIn3){
    TH1F *h1 = (TH1F*) fIn1->Get("AFiducial.XBox2");
    TH1F *h2 = (TH1F*) fIn2->Get("AFiducial.XBox2");
    TH1F *h3 = (TH1F*) fIn3->Get("AFiducial.XBox2");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	h1->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/x_lxe.png");
	h2->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/x_tpb.png");
	h3->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/x_lyso.png");

	c1->Close();
}

void plotY(TFile *fIn1, TFile* fIn2, TFile* fIn3){
    TH1F *h1 = (TH1F*) fIn1->Get("AFiducial.YBox2");
    TH1F *h2 = (TH1F*) fIn2->Get("AFiducial.YBox2");
    TH1F *h3 = (TH1F*) fIn3->Get("AFiducial.YBox2");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	h1->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/y_lxe.png");
	h2->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/y_tpb.png");
	h3->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/y_lyso.png");

	c1->Close();
}

void plotZ(TFile *fIn1, TFile* fIn2, TFile* fIn3){
    TH1F *h1 = (TH1F*) fIn1->Get("AFiducial.ZBox2");
    TH1F *h2 = (TH1F*) fIn2->Get("AFiducial.ZBox2");
    TH1F *h3 = (TH1F*) fIn3->Get("AFiducial.ZBox2");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	h1->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/z_lxe.png");
	h2->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/z_tpb.png");
	h3->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/z_lyso.png");

	//Combined
	h1->SetStats(kFALSE);
	h3->SetStats(kFALSE);
	h1->Scale(1/h1->Integral(), "width");
	h3->Scale(1/h3->Integral(), "width");
	h3->Draw();
	h3->SetLineColor(kRed);
	h1->Draw("same");
	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->SetFillColor(0);
	leg->AddEntry(h1, "LXe", "lp");
	leg->AddEntry(h3, "LYSO", "lp");
	leg->Draw("same");
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/z_combined.png");

	c1->Close();
}

void plotT(TFile *fIn1, TFile* fIn2, TFile* fIn3){
    TH1F *h1 = (TH1F*) fIn1->Get("AFiducial.TBox2");
    TH1F *h2 = (TH1F*) fIn2->Get("AFiducial.TBox2");
    TH1F *h3 = (TH1F*) fIn3->Get("AFiducial.TBox2");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	h1->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/t_lxe.png");
	h2->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/t_tpb.png");
	h3->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/t_lyso.png");

	c1->Close();
}

void plotNPhotons(TFile *fIn1, TFile* fIn2, TFile* fIn3){
    TH1F *h1 = (TH1F*) fIn1->Get("ATimeMap.NGBOX1");
    TH1F *h2 = (TH1F*) fIn2->Get("ATimeMap.NGBOX1");
    TH1F *h3 = (TH1F*) fIn3->Get("ATimeMap.NGBOX1");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	h1->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/nphotons_lxe.png");
	h2->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/nphotons_tpb.png");
	h3->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/nphotons_lyso.png");

	c1->Close();
}

void plotCRT(TFile *fIn1, TFile* fIn2, TFile* fIn3){
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(1110);

    TH1F *h1 = (TH1F*) fIn1->Get("DTOF.DTOF3");
    TH1F *h2 = (TH1F*) fIn2->Get("DTOF.DTOF3");
    TH1F *h3 = (TH1F*) fIn3->Get("DTOF.DTOF3");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	TF1* gauF1 = new TF1("gauF1","gaus",-100,100);
	TF1* gauF2 = new TF1("gauF2","gaus",-100,100);
	TF1* gauF3 = new TF1("gauF3","gaus",-100,100);

	h1->Fit("gauF1","","e",-40,40);
	h2->Fit("gauF2","","e",-40,40);
	h3->Fit("gauF3","","e",-40,40);

	h1->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/crt_lxe_PHYS.png");
	h2->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/crt_tpb_PHYS.png");
	h3->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/crt_lyso_PHYS.png");

	c1->Close();
}

void plotCRTCombined(TFile *fIn1, TFile* fIn2, TFile* fIn3){
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(1110);

    TH1F *h1 = (TH1F*) fIn1->Get("DTOF.DTOF3");
    TH1F *h2 = (TH1F*) fIn2->Get("DTOF.DTOF3");
    TH1F *h3 = (TH1F*) fIn3->Get("DTOF.DTOF3");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	//Combined
	h1->SetStats(kFALSE);
	h2->SetStats(kFALSE);
	h3->SetStats(kFALSE);

	h1->Scale(1/h1->Integral(), "width");
	h2->Scale(1/h2->Integral(), "width");
	h3->Scale(1/h3->Integral(), "width");

	h1->SetTitle("DTOF (n fixed)");
    h1->Draw();
    h2->SetLineColor(kRed);
    h2->Draw("same");
    h3->SetLineColor(kOrange);
    h3->Draw("same");

	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->SetFillColor(0);
	leg->AddEntry(h1, "LXe", "lp");
	leg->AddEntry(h2, "LXe-TPB", "lp");
	leg->AddEntry(h3, "LYSO", "lp");
	leg->Draw("same");
	
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/crt_PHYS.png");

	c1->Close();
}

void plotFirstPE(TFile *fIn1, TFile* fIn2, TFile* fIn3){
	TH1F *h1 = (TH1F*) fIn1->Get("NFirst.Time_1_PEBox1");
    TH1F *h2 = (TH1F*) fIn2->Get("NFirst.Time_1_PEBox1");
    TH1F *h3 = (TH1F*) fIn3->Get("NFirst.Time_1_PEBox1");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	h1->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/firstPE_lxe_PHYS.png");
	h2->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/firstPE_tpb_PHYS.png");
	h3->Draw();
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/firstPE_lyso_PHYS.png");

	//Combined
/*	h1->SetStats(kFALSE);
	h2->SetStats(kFALSE);
	h3->SetStats(kFALSE);
	h1->Scale(1/h1->Integral(), "width");
	h2->Scale(1/h2->Integral(), "width");
	h3->Scale(1/h3->Integral(), "width");
	h1->Draw();
    h2->SetLineColor(kRed);
	h2->Draw("same");
	h3->SetLineColor(kOrange);
	h3->Draw("same");
	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->SetFillColor(0);
	leg->AddEntry(h1, "LXe", "lp");
	leg->AddEntry(h2, "LXe-TPB", "lp");
	leg->AddEntry(h3, "LYSO", "lp");
	leg->Draw("same");
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/firstPE_PHYS.png");
*/
	c1->Close();
}

void plotXY(TFile *fIn1, TFile* fIn2, TFile* fIn3){
    TH2F *h1 = (TH2F*) fIn1->Get("AFiducial.XYBox2");
    TH2F *h2 = (TH2F*) fIn2->Get("AFiducial.XYBox2");
    TH2F *h3 = (TH2F*) fIn3->Get("AFiducial.XYBox2");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	h1->Draw("colz");
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/xy_lxe.png");
	h2->Draw("colz");
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/xy_tpb.png");
	h3->Draw("colz");
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/round2/xy_lyso.png");

	c1->Close();
}
