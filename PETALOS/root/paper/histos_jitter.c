void histos_jitter(){
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(1110);

	std::string material[3] = {"lxe","lxe_tpb","lyso"};
	std::string interaction[3] = {"","_noCher","_noScint"};

	double sigmas[3][3][20]; // [mat][inter][pde]
	double errors[3][3][20]; // [mat][inter][pde]
	double pdeValues[20];
	char pde[5];

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);


	for(int mat=0; mat<3;mat++){
		for(int inter=1; inter<3;inter++){
			for(int i=5;i<=100;i+=5){
				pdeValues[i/5-1] = i;

				//There is an error with lsyo noScint pde 0.05
				if((mat==2 && inter==2) && i <= 40)){
					continue;
				}

				sprintf(pde, "%.2lf", i/100.0);
				if(i==100){
					sprintf(pde, "0%.2lf", i/100.0);
				}

				std::string path = "/home/jmbenlloch/next/petalo/work/histo/jitter/";
				std::string fileName = path + material[mat] + interaction[inter] + std::string("_QE_") + std::string(pde) + std::string("_SPTR_80_ASIC_30_DT300_histos.root"); std::string(Form("%d", 1));
				std::cout << fileName << std::endl;

				TFile *fIn = new TFile(fileName.c_str(), "read");

				TH1F *h1 = (TH1F*) fIn->Get("DTOF.DTOF2");
				TF1* gauF1 = new TF1("gauF1","gaus",-200,200);
	//			h1->Scale(1/h1->Integral(), "width");
				h1->Fit("gauF1","","e",-200,200);
				h1->Draw();

				std::string pathHisto = "/home/jmbenlloch/next/petalo/work/histo/jitter/fits/";
				std::string histo = pathHisto + material[mat] + interaction[inter] + std::string("_pde_") + pde + std::string(".png");
				std::cout << histo << std::endl;
				c1->Print(histo.c_str());

				std::cout << "PDE: " << pde << "sigma: "  << h1->GetFunction("gauF1")->GetParameter(2) << std::endl;
				// FWHM
				sigmas[mat][inter][i/5-1] = 2.35 * h1->GetFunction("gauF1")->GetParameter(2);
				errors[mat][inter][i/5-1] = 2.35 * h1->GetFunction("gauF1")->GetParError(2);

				fIn->Close();
			}
		}
	}
	c1->Close();

	/*********
	 * scint *
	 * *******/
	//TCanvas *c3 = new TCanvas("c3","multipads",900,700);
	TCanvas *c3 = tcanvset("c");
	TGraphErrors *gLxe_noCher = new TGraphErrors(19, pdeValues+1, sigmas[0][1]+1, 0, errors[0][1]+1);
	gLxe_noCher->SetLineColor(kBlue);
	gLxe_noCher->SetLineWidth(2);
	gLxe_noCher->SetLineStyle(1);
	grerrplot(*gLxe_noCher);

	TGraphErrors *gTpb_noCher = new TGraphErrors(19, pdeValues+1, sigmas[1][1]+1, 0, errors[1][1]+1);
	gTpb_noCher->SetLineColor(kRed);
	gTpb_noCher->SetLineWidth(2);
	gTpb_noCher->SetLineStyle(2);
	grerrplot(*gTpb_noCher);

	TGraphErrors *gLyso_noCher = new TGraphErrors(19, pdeValues+1, sigmas[2][1]+1, 0, errors[2][1]+1);
	gLyso_noCher->SetLineColor(kGreen+3);
	gLyso_noCher->SetLineWidth(2);
	gLyso_noCher->SetLineStyle(3);
	grerrplot(*gLyso_noCher);

	gLyso_noCher->Draw();
	gLyso_noCher->SetTitle("");
	gLyso_noCher->GetXaxis().SetTitle("PDE (%)");
	gLyso_noCher->GetXaxis()->SetLimits(0.,100.);
	gLyso_noCher->GetYaxis().SetTitle("CRT (ps)");
	gLyso_noCher->SetMinimum(0.);
	gLyso_noCher->SetMaximum(250.);
	gTpb_noCher->Draw("same");
	gLxe_noCher->Draw("same");

	//TLegend *leg_noCher = new TLegend(0.7, 0.7, 0.9, 0.9);
	TLegend *leg_noCher = tlegset();
	leg_noCher->SetFillColor(0);
	leg_noCher->AddEntry(gLxe_noCher, "LXe", "lp");
	leg_noCher->AddEntry(gTpb_noCher, "LXe-TPB", "lp");
	leg_noCher->AddEntry(gLyso_noCher, "LYSO", "lp");
	leg_noCher->Draw("same");

	c3->Print("/home/jmbenlloch/next/petalo/PESOA/PETALOS/root/paper/plots/CTR_jitter_fixed_n.png");

}
