void histos_jitter_smear(){
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
		for(int inter=1; inter<2;inter++){
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

				TH1F *h1 = (TH1F*) fIn->Get("DTOFAVG.SmearDTOF2N1");
				TF1* gauF1 = new TF1("gauF1","gaus",-200,200);
	//			h1->Scale(1/h1->Integral(), "width");
				h1->Fit("gauF1","","e",-200,200);
				h1->Draw();

				std::string histo = path + material[mat] + interaction[inter] + std::string("_pde_") + pde + std::string(".png");
				std::cout << histo << std::endl;
				c1->Print(histo.c_str());

				std::cout << "PDE: " << pde << "sigma: "  << h1->GetFunction("gauF1")->GetParameter(2) << std::endl;
				sigmas[mat][inter][i/5-1] = h1->GetFunction("gauF1")->GetParameter(2);
				errors[mat][inter][i/5-1] = h1->GetFunction("gauF1")->GetParError(2);

				fIn->Close();
			}
		}
	}
	c1->Close();

	/****************
	 * cher + scint *
	 * **************/
/*	TCanvas *c2 = new TCanvas("c2","multipads",900,700);
	TGraphErrors *gLxe = new TGraphErrors(20, pdeValues, sigmas[0][0], 0, errors[0][0]);
	gLxe->SetLineColor(kRed);
	gLxe->SetLineWidth(2);

	TGraphErrors *gTpb = new TGraphErrors(20, pdeValues, sigmas[1][0], 0, errors[1][0]);
	gTpb->SetLineColor(kBlue);
	gTpb->SetLineWidth(2);

	TGraphErrors *gLyso = new TGraphErrors(20, pdeValues, sigmas[2][0], 0, errors[2][0]);
	gLyso->SetLineColor(kGreen);
	gLyso->SetLineWidth(2);

	std::cout << "LXe: ";
	for(int i=0;i<20;i++){
		std::cout << sigmas[0][0][i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "TPB: ";
	for(int i=0;i<20;i++){
		std::cout << sigmas[1][0][i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "LYSO: ";
	for(int i=0;i<20;i++){
		std::cout << sigmas[2][0][i] << ", ";
	}
	std::cout << std::endl;

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

	c2->Print("/home/jmbenlloch/next/petalo/work/histo/jitter/jitter.png");*/

	/*********
	 * scint *
	 * *******/
	TCanvas *c3 = new TCanvas("c3","multipads",900,700);
	TGraphErrors *gLxe_noCher = new TGraphErrors(20, pdeValues, sigmas[0][1], 0, errors[0][1]);
	gLxe_noCher->SetLineColor(kRed);
	gLxe_noCher->SetLineWidth(2);

	TGraphErrors *gTpb_noCher = new TGraphErrors(20, pdeValues, sigmas[1][1], 0, errors[1][1]);
	gTpb_noCher->SetLineColor(kBlue);
	gTpb_noCher->SetLineWidth(2);

	TGraphErrors *gLyso_noCher = new TGraphErrors(20, pdeValues, sigmas[2][1], 0, errors[2][1]);
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
	leg_noCher->AddEntry(gLxe_noCher, "LXe", "lp");
	leg_noCher->AddEntry(gTpb_noCher, "LXe-TPB", "lp");
	leg_noCher->AddEntry(gLyso_noCher, "LYSO", "lp");
	leg_noCher->Draw("same");

	c3->Print("/home/jmbenlloch/next/petalo/work/histo/jitter/jitter_noCher_smear.png");

	/********
	 * cher *
	 * ******/
/*	TCanvas *c3 = new TCanvas("c3","multipads",900,700);
	TGraphErrors *gLxe_noScint = new TGraphErrors(20, pdeValues, sigmas[0][2], 0, errors[0][2]);
	gLxe_noScint->SetLineColor(kRed);
	gLxe_noScint->SetLineWidth(2);

	TGraphErrors *gTpb_noScint = new TGraphErrors(20, pdeValues, sigmas[1][2], 0, errors[1][2]);
	gTpb_noScint->SetLineColor(kBlue);
	gTpb_noScint->SetLineWidth(2);

	TGraphErrors *gLyso_noScint = new TGraphErrors(7, pdeValues+13, sigmas[2][2]+13, 0, errors[2][2]+13);
	gLyso_noScint->SetLineColor(kGreen);
	gLyso_noScint->SetLineWidth(2);

	gLyso_noScint->Draw();
	gLyso_noScint->SetTitle("noScint");
	gLyso_noScint->GetXaxis().SetTitle("PDE (%)");
	gLyso_noScint->GetXaxis()->SetLimits(0.,100.);
	gLyso_noScint->GetYaxis().SetTitle("CRT (ps)");
	gLyso_noScint->SetMinimum(0.);
	gLyso_noScint->SetMaximum(150.);
	gTpb_noScint->Draw("same");
	gLxe_noScint->Draw("same");

	TLegend *leg_noScint = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg_noScint->SetFillColor(0);
	leg_noScint->AddEntry(gLxe_noScint, "LXe", "lp");
	leg_noScint->AddEntry(gTpb_noScint, "LXe-TPB", "lp");
	leg_noScint->AddEntry(gLyso_noScint, "LYSO", "lp");
	leg_noScint->Draw("same");

	c3->Print("/home/jmbenlloch/next/petalo/work/histo/jitter/jitter_noScint_smear.png");
	*/
}
