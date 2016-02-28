void histos_avg(){
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);

	TFile *fIn1 = new TFile("/home/jmbenlloch/next/petalo/work/histo/test-LXe_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");


 	TH1F *h1 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3N1");
 	TH1F *h2 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3N2");
 	TH1F *h3 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3N3");
 	TH1F *h4 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3N4");
 	TH1F *h5 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3N5");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

/*	h1->Scale(1/h1->Integral(), "width");
	h2->Scale(1/h2->Integral(), "width");
	h3->Scale(1/h3->Integral(), "width");
	h4->Scale(1/h4->Integral(), "width");
	h5->Scale(1/h5->Integral(), "width");*/

    h1->SetLineColor(kRed);
    h2->SetLineColor(kBlue);
    h3->SetLineColor(kGreen);
    h4->SetLineColor(kOrange);
    h5->SetLineColor(kPink);


    h1->Draw();
    h2->Draw("same");
    h3->Draw("same");
    h4->Draw("same");
    h5->Draw("same");

	c1->Print("/home/jmbenlloch/next/petalo/work/histo/lxe_avg_npe.png");

 	TH1F *h1 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3_DT10");
 	TH1F *h2 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3_DT20");
 	TH1F *h3 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3_DT50");
 	TH1F *h4 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3_DT100");
 	TH1F *h5 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3_DT150");
 	TH1F *h6 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3_DT200");
 	TH1F *h7 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3_DT250");
 	TH1F *h8 = (TH1F*) fIn1->Get("DTOFAVG.DTOF3_DT300");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

/*	h1->Scale(1/h1->Integral(), "width");
	h2->Scale(1/h2->Integral(), "width");
	h3->Scale(1/h3->Integral(), "width");
	h4->Scale(1/h4->Integral(), "width");
	h5->Scale(1/h5->Integral(), "width");*/

    h1->SetLineColor(kRed);
    h2->SetLineColor(kBlue);
    h3->SetLineColor(kGreen);
    h4->SetLineColor(kOrange);
    h5->SetLineColor(kPink);
    h6->SetLineColor(kYellow);
    h7->SetLineColor(kCyan);
    h8->SetLineColor(kViolet);

    h1->Draw();
    h2->Draw("same");
    h3->Draw("same");
    h4->Draw("same");
    h5->Draw("same");
    h6->Draw("same");
    h7->Draw("same");
    h8->Draw("same");

	c1->Print("/home/jmbenlloch/next/petalo/work/histo/lxe_avg_dt.png");
}
