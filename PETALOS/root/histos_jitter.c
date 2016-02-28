void histos_jitter(){
	std::string material[3] = {"lxe","lxe_tpb","lyso"};
	std::string interaction[3] = {"","_noCher","_noScint"};

	double sigmas[3][3][20]; // [mat][inter][pde]
	double pdeValues[20];
	char pde[5];

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);


	for(int mat=0; mat<3;mat++){
		for(int inter=0; inter<2;inter++){
			for(int i=5;i<=100;i+=5){
				pdeValues[i/5-1] = i;

				//There is an error with lsyo noScint pde 0.05
				if((mat==2 && inter==2) && i==5)){
					continue;
				}

				sprintf(pde, "%.2lf", i/100.0);
				if(i==100){
					sprintf(pde, "0%.2lf", i/100.0);
				}

				std::string path = "/home/jmbenlloch/next/petalo/work/histo/jitter/";
				std::string fileName = path + material[mat] + interaction[inter] + std::string("_PHYS_QE_") + std::string(pde) + std::string("_SPTR_80_ASIC_30_DT300_histos.root"); std::string(Form("%d", 1));
				std::cout << fileName << std::endl;

				TFile *fIn = new TFile(fileName.c_str(), "read");

				TH1F *h1 = (TH1F*) fIn->Get("DTOF.DTOF2");
				TF1* gauF1 = new TF1("gauF1","gaus",-200,200);
				h1->Scale(1/h1->Integral(), "width");
				h1->Fit("gauF1","","e",-70,70);
				h1->Draw();

				std::string histo = path + material[mat] + interaction[inter] + std::string("_pde_") + pde + std::string(".png");
				std::cout << histo << std::endl;
				c1->Print(histo.c_str());

				std::cout << "PDE: " << pde << "sigma: "  << h1->GetFunction("gauF1")->GetParameter(2) << std::endl;
				sigmas[mat][inter][i/5-1] = h1->GetFunction("gauF1")->GetParameter(2);

				fIn->Close();
			}
		}
	}
	c1->Close();

	TCanvas *c2 = new TCanvas("c2","multipads",900,700);
	TGraph *gLxe = new TGraph(20, pdeValues, sigmas[0][0]);
	gLxe->SetLineColor(kRed);
	gLxe->SetLineWidth(2);

	TGraph *gTpb = new TGraph(20, pdeValues, sigmas[1][0]);
	gTpb->SetLineColor(kBlue);
	gTpb->SetLineWidth(2);

	TGraph *gLyso = new TGraph(20, pdeValues, sigmas[2][0]);
	gLyso->SetLineColor(kGreen);
	gLyso->SetLineWidth(2);

	gLyso->Draw();
	gLyso->SetTitle("");
	gLyso->GetXaxis().SetTitle("PDE (%)");
	gLyso->GetXaxis()->SetLimits(0.,100.);
	gLyso->GetYaxis().SetTitle("CRT (ps)");
	gLyso->SetMinimum(0.);
	gLyso->SetMaximum(150.);
	gTpb->Draw("same");
	gLxe->Draw("same");

	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->SetFillColor(0);
	leg->AddEntry(gLxe, "LXe", "lp");
	leg->AddEntry(gTpb, "LXe-TPB", "lp");
	leg->AddEntry(gLyso, "LYSO", "lp");
	leg->Draw("same");

	c2->Print("/home/jmbenlloch/next/petalo/work/histo/jitter/jitter.png");


	TCanvas *c3 = new TCanvas("c3","multipads",900,700);
	TGraph *gLxe_noCher = new TGraph(20, pdeValues, sigmas[0][1]);
	gLxe_noCher->SetLineColor(kRed);
	gLxe_noCher->SetLineWidth(2);

	TGraph *gTpb_noCher = new TGraph(20, pdeValues, sigmas[1][1]);
	gTpb_noCher->SetLineColor(kBlue);
	gTpb_noCher->SetLineWidth(2);

	TGraph *gLyso_noCher = new TGraph(20, pdeValues, sigmas[2][1]);
	gLyso_noCher->SetLineColor(kGreen);
	gLyso_noCher->SetLineWidth(2);

	gLyso_noCher->Draw();
	gLyso_noCher->SetTitle("noCher");
	gLyso_noCher->GetXaxis().SetTitle("PDE (%)");
	gLyso_noCher->GetXaxis()->SetLimits(0.,100.);
	gLyso_noCher->GetYaxis().SetTitle("CRT (ps)");
	gLyso_noCher->SetMinimum(0.);
	gLyso_noCher->SetMaximum(150.);
	gTpb_noCher->Draw("same");
	gLxe_noCher->Draw("same");

	TLegend *leg_noCher = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg_noCher->SetFillColor(0);
	leg_noCher->AddEntry(gLxe, "LXe", "lp");
	leg_noCher->AddEntry(gTpb, "LXe-TPB", "lp");
	leg_noCher->AddEntry(gLyso, "LYSO", "lp");
	leg_noCher->Draw("same");

	c3->Print("/home/jmbenlloch/next/petalo/work/histo/jitter/jitter_noCher.png");

}
