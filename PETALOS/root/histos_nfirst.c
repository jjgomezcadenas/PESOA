void histos_nfirst(){
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);

	TFile *fIn1 = new TFile("/home/jmbenlloch/next/petalo/work/histo/test-LXe_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
	TFile *fIn2 = new TFile("/home/jmbenlloch/next/petalo/work/histo/test-LXe_TPB3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");
	TFile *fIn3 = new TFile("/home/jmbenlloch/next/petalo/work/histo/test-LYSO_VUV3mm_xy2.4cm_z5cm_PHYS_QE_1_SPTR_0_ASIC_0_DT300_histos.root", "read");

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	char pos[5];

	for(int i=1;i<9;i++){
		sprintf(pos, "%d", i);

		std::string histoName = "NFirst.Time_" + std::string(pos) + "_PEBox1";
		//std::cout << histoName << std::endl;

		TH1F *h1 = (TH1F*) fIn1->Get(histoName.c_str());
		TH1F *h2 = (TH1F*) fIn2->Get(histoName.c_str());
		TH1F *h3 = (TH1F*) fIn3->Get(histoName.c_str());

		h1->Scale(1/h1->Integral(), "width");
		h2->Scale(1/h2->Integral(), "width");
		h3->Scale(1/h3->Integral(), "width");

		h1->SetStats(kFALSE);
		h2->SetStats(kFALSE);
		h3->SetStats(kFALSE);

		h1->SetTitle(histoName.c_str());
		h1->Draw();

		if(i==1){
			h1->SetMinimum(0);
			h1->SetMaximum(0.035);
		}	

		h2->SetLineColor(kRed);
		h2->Draw("same");
		h3->SetLineColor(kGreen);
		h3->Draw("same");

		TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
		leg->SetFillColor(0);
		leg->AddEntry(h1, "LXe", "lp");
		leg->AddEntry(h2, "LXe-TPB", "lp");
		leg->AddEntry(h3, "LYSO", "lp");
		leg->Draw("same");

		std::string path = "/home/jmbenlloch/next/petalo/work/histo/nfirst/";
		std::string histo = path + std::string(pos) + std::string(".png");
		//std::cout << histo << std::endl;
		c1->Print(histo.c_str());
	}
}
