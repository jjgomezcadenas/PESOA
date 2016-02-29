void histos_avg(){
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(1110);

	std::string material[3] = {"lxe","lxe_tpb","lyso"};
	std::string interaction[3] = {"","_noCher","_noScint"};

	std::string filepath = "/home/jmbenlloch/next/petalo/work/histo/jitter/";
	// [mat][inter]
	std::string files[3][2];
	files[0][0] = "lxe_QE_01.00_SPTR_80_ASIC_30_DT300_histos.root";
	files[0][1] = "lxe_noCher_QE_01.00_SPTR_80_ASIC_30_DT300_histos.root";
	files[1][0] = "lxe_tpb_QE_01.00_SPTR_80_ASIC_30_DT300_histos.root";
	files[1][1] = "lxe_tpb_noCher_QE_01.00_SPTR_80_ASIC_30_DT300_histos.root";
	files[2][0] = "lyso_QE_01.00_SPTR_80_ASIC_30_DT300_histos.root";
	files[2][1] = "lyso_noCher_QE_01.00_SPTR_80_ASIC_30_DT300_histos.root";

	double sigmasNPE[3][2][2][5]; // [mat][inter][smear][npe]
	double errorsNPE[3][2][2][5]; // [mat][inter][smear][npe]
	double sigmasDT[3][2][2][8]; // [mat][inter]]smear][dt]
	double errorsDT[3][2][2][8]; // [mat][inter][smear][dt]
	int npes[5] = {1,2,3,4,5};
    int dts[8] = {10,20,50,100,150,200,250,300};
	char pde[5];

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	for(int mat=0; mat<3;mat++){
		for(int inter=0; inter<2;inter++){
			for(int smear=0; smear<2;smear++){
				for(int npe=0;npe<5;npe++){

					std::string fileName = filepath + files[mat][inter];
					std::cout << fileName << std::endl;
					TFile *fIn = new TFile(fileName.c_str(), "read");

					std::string baseName = "DTOFAVG.";
					std::string smearName = "";
					if(smear==1){
						smearName = "Smear";
					}

					std::string histName = baseName + smearName + std::string("DTOF2") + std::string("N") + std::string(Form("%d", npes[npe]));
					std::cout << histName << std::endl;

					TH1F *h1 = (TH1F*) fIn->Get(histName.c_str());
					TF1* gauF1 = new TF1("gauF1","gaus",-200,200);
					h1->Fit("gauF1","","e",-200,200);
					h1->Draw();

					std::string path = "/home/jmbenlloch/next/petalo/work/histo/jitter/";
					std::string histo = path + material[mat] + interaction[inter] + std::string("_") + histName + std::string(".png");
					std::cout << histo << std::endl;

					c1->Print(histo.c_str());

					sigmasNPE[mat][inter][smear][npe] = h1->GetFunction("gauF1")->GetParameter(2);
					errorsNPE[mat][inter][smear][npe] = h1->GetFunction("gauF1")->GetParError(2);

					fIn->Close();
				}
			}
		}
	}


	for(int mat=0; mat<3;mat++){
		for(int inter=0; inter<2;inter++){
			for(int smear=0; smear<2;smear++){
				for(int dt=0;dt<8;dt++){

					std::string fileName = filepath + files[mat][inter];
					std::cout << fileName << std::endl;
					TFile *fIn = new TFile(fileName.c_str(), "read");

					std::string baseName = "DTOFAVG.";
					std::string smearName = "";
					if(smear==1){
						smearName = "Smear";
					}

					std::string histName = baseName + smearName + std::string("DTOF2") + std::string("_DT") + std::string(Form("%d", dts[dt]));
					std::cout << histName << std::endl;

					TH1F *h1 = (TH1F*) fIn->Get(histName.c_str());
					TF1* gauF1 = new TF1("gauF1","gaus",-200,200);
					h1->Fit("gauF1","","e",-200,200);
					h1->Draw();

					std::string path = "/home/jmbenlloch/next/petalo/work/histo/jitter/";
					std::string histo = path + material[mat] + interaction[inter] + std::string("_") + histName + std::string(".png");
					std::cout << histo << std::endl;

					c1->Print(histo.c_str());

					sigmasDT[mat][inter][smear][dt] = h1->GetFunction("gauF1")->GetParameter(2);
					std::cout << "sigmasDT[" << mat << "][" << inter << "][" << smear << "][" << dt << "] = " << sigmasDT[mat][inter][smear][dt] << std::endl;
					errorsDT[mat][inter][smear][dt] = h1->GetFunction("gauF1")->GetParError(2);
					std::cout << "errorsDT[" << mat << "][" << inter << "][" << smear << "][" << dt << "] = " << errorsDT[mat][inter][smear][dt] << std::endl;

					fIn->Close();
				}
			}
		}
	}
	c1->Close();

	std::cout << "sigmaLXE: ";
	for(int i=0;i<5;i++){
		std::cout << sigmasNPE[0][0][0][i] << ", " << std::endl;
	}
	std::cout << std::endl;

	// NPE
	double npesD[5] = {1,2,3,4,5};
	for(int inter=0; inter<2;inter++){
		for(int smear=0; smear<2;smear++){
			TCanvas *c2 = new TCanvas("c2","multipads",900,700);
			TGraphErrors *gLxe = new TGraphErrors(5, npesD, sigmasNPE[0][inter][smear], 0, errorsNPE[0][inter][smear]);
			gLxe->SetLineColor(kRed);
			gLxe->SetLineWidth(2);

			TGraphErrors *gTpb = new TGraphErrors(5, npesD, sigmasNPE[1][inter][smear], 0, errorsNPE[1][inter][smear]);
			gTpb->SetLineColor(kBlue);
			gTpb->SetLineWidth(2);

			TGraphErrors *gLyso = new TGraphErrors(5, npesD, sigmasNPE[2][inter][smear], 0, errorsNPE[2][inter][smear]);
			gLyso->SetLineColor(kGreen);
			gLyso->SetLineWidth(2);

			gLyso->Draw();
			gLyso->SetTitle("");
			gLyso->GetXaxis().SetTitle("avg PE(#)");
			gLyso->GetXaxis()->SetLimits(0,10);
			gLyso->GetYaxis().SetTitle("CRT (ps)");
			gLyso->SetMinimum(0.);
			gLyso->SetMaximum(100.);
			gTpb->Draw("same");
			gLxe->Draw("same");

			TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
			leg->SetFillColor(0);
			leg->AddEntry(gLxe, "LXe", "lp");
			leg->AddEntry(gTpb, "LXe-TPB", "lp");
			leg->AddEntry(gLyso, "LYSO", "lp");
			leg->Draw("same");

			std::string smearName = "";
			if(smear==1){
				smearName = "_smear";
			}
			std::string interName = "";
			if(inter==1){
				interName = "_noCher";
			}
			std::string path = "/home/jmbenlloch/next/petalo/work/histo/";
			std::string histo = path + std::string("avg_npe") + interName + smearName + std::string(".png");

			c2->Print(histo.c_str());
			c2->Close();

			std::cout << "NPE sigmaLXE " << interName << smearName << ": ";
			for(int i=0;i<5;i++){
				std::cout << sigmasNPE[0][inter][smear][i] << ", ";
			}
			std::cout << std::endl;
			std::cout << "NPE sigmaTPB " << interName << smearName << ": ";
			for(int i=0;i<5;i++){
				std::cout << sigmasNPE[0][inter][smear][i] << ", ";
			}
			std::cout << std::endl;
			std::cout << "NPE sigmaLYSO " << interName << smearName << ": ";
			for(int i=0;i<5;i++){
				std::cout << sigmasNPE[0][inter][smear][i] << ", ";
			}
			std::cout << std::endl;

		}
	}

	//DT
	double dtsD[8] = {10,20,50,100,150,200,250,300};
	for(int inter=0; inter<2;inter++){
		for(int smear=0; smear<2;smear++){
			TCanvas *c2 = new TCanvas("c2","multipads",900,700);
			TGraphErrors *gLxe = new TGraphErrors(8, dtsD, sigmasDT[0][inter][smear], 0, errorsDT[0][inter][smear]);
			gLxe->SetLineColor(kRed);
			gLxe->SetLineWidth(2);

			TGraphErrors *gTpb = new TGraphErrors(8, dtsD, sigmasDT[1][inter][smear], 0, errorsDT[1][inter][smear]);
			gTpb->SetLineColor(kBlue);
			gTpb->SetLineWidth(2);

			TGraphErrors *gLyso = new TGraphErrors(8, dtsD, sigmasDT[2][inter][smear], 0, errorsDT[2][inter][smear]);
			gLyso->SetLineColor(kGreen);
			gLyso->SetLineWidth(2);

			gLyso->Draw();
			gLyso->SetTitle("");
			gLyso->GetXaxis().SetTitle("avg PE(#)");
			gLyso->GetXaxis()->SetLimits(0,350);
			gLyso->GetYaxis().SetTitle("CRT (ps)");
			gLyso->SetMinimum(0.);
			gLyso->SetMaximum(100.);
			gTpb->Draw("same");
			gLxe->Draw("same");

			TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
			leg->SetFillColor(0);
			leg->AddEntry(gLxe, "LXe", "lp");
			leg->AddEntry(gTpb, "LXe-TPB", "lp");
			leg->AddEntry(gLyso, "LYSO", "lp");
			leg->Draw("same");

			std::string smearName = "";
			if(smear==1){
				smearName = "_smear";
			}
			std::string interName = "";
			if(inter==1){
				interName = "_noCher";
			}
			std::string path = "/home/jmbenlloch/next/petalo/work/histo/";
			std::string histo = path + std::string("avg_dt") + interName + smearName + std::string(".png");

			c2->Print(histo.c_str());
			c2->Close();

			std::cout << "DT sigmaLXE " << interName << smearName << ": ";
			for(int i=0;i<8;i++){
				std::cout << sigmasDT[0][inter][smear][i] << ", ";
			}
			std::cout << std::endl;
			std::cout << "DT sigmaTPB " << interName << smearName << ": ";
			for(int i=0;i<8;i++){
				std::cout << sigmasDT[0][inter][smear][i] << ", ";
			}
			std::cout << std::endl;
			std::cout << "DT sigmaLYSO " << interName << smearName << ": ";
			for(int i=0;i<8;i++){
				std::cout << sigmasDT[0][inter][smear][i] << ", ";
			}
			std::cout << std::endl;

		}
	}
}
