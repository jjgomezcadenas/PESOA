void histos_phys(){
    TFile *fIn1 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LXe_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
    TFile *fIn2 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LXe_TPB3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
    TFile *fIn3 = new TFile("/home/jmbenlloch/next/petalo/work/histo/LYSO_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");

    TH1F *h1 = (TH1F*) fIn1->Get("DTOF.DTOF3");
    TH1F *h2 = (TH1F*) fIn2->Get("DTOF.DTOF3");
    TH1F *h3 = (TH1F*) fIn3->Get("DTOF.DTOF3");

	TF1* gauF1 = new TF1("gauF1","gaus",-100,100);
	TF1* gauF2 = new TF1("gauF2","gaus",-100,100);
	TF1* gauF3 = new TF1("gauF3","gaus",-100,100);

	h1->Scale(1/h1->Integral(), "width");
	h2->Scale(1/h2->Integral(), "width");
	h3->Scale(1/h3->Integral(), "width");

	h1->Fit("gauF1","","e",-20,20);
	h2->Fit("gauF2","","e",-20,20);
	h3->Fit("gauF3","","e",-15,15);

	plot(h1,h2,h3);
	plot_combined(h1,h2,h3);
}

void plot(TH1F* h1, TH1F* h2, TH1F* h3){
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(1110);

	TCanvas *c2 = new TCanvas("c2","multipads",900,700);

    h1->Draw();
	c2->Print("/home/jmbenlloch/next/petalo/work/histo/crt_phys_lxe.pdf");
	c2->Print("/home/jmbenlloch/next/petalo/work/histo/crt_phys_lxe.png");

    h2->Draw();
	c2->Print("/home/jmbenlloch/next/petalo/work/histo/crt_phys_lxe_tpb.pdf");
	c2->Print("/home/jmbenlloch/next/petalo/work/histo/crt_phys_lxe_tpb.png");

    h3->Draw();
	c2->Print("/home/jmbenlloch/next/petalo/work/histo/crt_phys_lyso.pdf");
	c2->Print("/home/jmbenlloch/next/petalo/work/histo/crt_phys_lyso.png");
}

void plot_combined(TH1F* h1, TH1F* h2, TH1F* h3){
	gROOT->Reset();
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);

	h1->SetStats(kFALSE);
	h2->SetStats(kFALSE);
	h3->SetStats(kFALSE);
	
	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	gauF1->SetLineColor(kBlue);
	gauF1->SetLineWidth(1);
	gauF2->SetLineColor(kRed);
	gauF2->SetLineWidth(1);
	gauF3->SetLineColor(kGreen);
	gauF3->SetLineWidth(1);

	h1->GetFunction("gauF1")->SetLineColor(kBlue);
	h1->GetFunction("gauF1")->SetLineWidth(1.5);
	h2->GetFunction("gauF2")->SetLineColor(kBlue);
	h2->GetFunction("gauF2")->SetLineWidth(1.5);
	h3->GetFunction("gauF3")->SetLineColor(kGreen);
	h3->GetFunction("gauF3")->SetLineWidth(1.5);

	h1->SetTitle("DTOF (n fixed)");
    h1->Draw();
    h2->SetLineColor(kRed);
    h2->Draw("same");
    h3->SetLineColor(kGreen);
    h3->Draw("same");

//	std::cout << "sigma: "  << h1->GetFunction("gauF1")->GetParameter(2) << std::endl;

	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->SetFillColor(0);
	//leg->SetHeader("test legend");
	leg->AddEntry(h1, "LXe", "lp");
	leg->AddEntry(h2, "LXe-TPB", "lp");
	leg->AddEntry(h3, "LYSO", "lp");
	leg->AddEntry(h1, Form("Sigma LXe %.3g", h1->GetFunction("gauF1")->GetParameter(2)), "lp");
	leg->AddEntry(h2, Form("Sigma LXe-TPB %.3g", h2->GetFunction("gauF2")->GetParameter(2)), "lp");
	leg->AddEntry(h3, Form("Sigma LYSO %.3g", h3->GetFunction("gauF3")->GetParameter(2)), "lp");
	leg->Draw("same");

	c1->Print("/home/jmbenlloch/next/petalo/work/histo/crt_phys.pdf");
	c1->Print("/home/jmbenlloch/next/petalo/work/histo/crt_phys.png");
}
