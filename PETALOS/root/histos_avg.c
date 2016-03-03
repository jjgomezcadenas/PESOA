void histos_avg(){
	gStyle->SetOptFit(1);
	gStyle->SetOptStat(1110);

	std::string material[3] = {"lxe","lxe_tpb","lyso"};
	std::string interaction[3] = {"","_noCher","_noScint"};

	std::string filepath = "/home/jmbenlloch/next/petalo/work/histo/jitter/";

	double sigmasNPE[3][2][2][5][10]; // [mat][inter][smear][pde][npe]
	double errorsNPE[3][2][2][5][10]; // [mat][inter][smear][pde][npe]
	double sigmasDT[3][2][2][5][8]; // [mat][inter]]smear][pde][dt]
	double errorsDT[3][2][2][5][8]; // [mat][inter][smear][pde][dt]
	int npes[10] = {1,2,3,4,5,6,7,8,9,10};
    int dts[8] = {10,20,50,100,150,200,250,300};
	int pdes[5] = {10,30,50,70,100};
	char pdeChar[5];

	TCanvas *c1 = new TCanvas("c1","multipads",900,700);

	for(int mat=0; mat<3;mat++){
		for(int inter=1; inter<2;inter++){
			for(int smear=0; smear<2;smear++){
				for(int pde=0; pde<5;pde++){
					sprintf(pdeChar, "%.2lf", pdes[pde]/100.0);
					if(pdes[pde]==100){
						sprintf(pdeChar, "0%.2lf", pdes[pde]/100.0);
					}
					std::string fileName = filepath + material[mat] + interaction[inter] + std::string("_QE_") + std::string(pdeChar) + std::string("_SPTR_80_ASIC_30_DT300_histos.root"); std::string(Form("%d", 1));
					std::cout << fileName << std::endl;
					TFile *fIn = new TFile(fileName.c_str(), "read");

					std::string baseName = "DTOFAVG.";
					std::string smearName = "";
					if(smear==1){
						smearName = "Smear";
					}

					//NPE
					for(int npe=0;npe<10;npe++){
						std::string histName = baseName + smearName + std::string("DTOF2") + std::string("N") + std::string(Form("%d", npes[npe]));
						std::cout << histName << std::endl;

						TH1F *h1 = (TH1F*) fIn->Get(histName.c_str());
						TF1* gauF1 = new TF1("gauF1","gaus",-200,200);
						h1->Fit("gauF1","","e",-200,200);
						h1->Draw();

						std::string path = "/home/jmbenlloch/next/petalo/work/histo/jitter_avg/npe/";
						std::string histo = path + material[mat] + interaction[inter] + std::string("_QE_") + std::string(pdeChar) + std::string("_") + histName + std::string(".png");
						std::cout << histo << std::endl;

						c1->Print(histo.c_str());

						sigmasNPE[mat][inter][smear][pde][npe] = h1->GetFunction("gauF1")->GetParameter(2);
						errorsNPE[mat][inter][smear][pde][npe] = h1->GetFunction("gauF1")->GetParError(2);
					}

					//DT
					for(int dt=0;dt<8;dt++){
						std::string histName = baseName + smearName + std::string("DTOF2") + std::string("_DT") + std::string(Form("%d", dts[dt]));
						std::cout << histName << std::endl;

						TH1F *h1 = (TH1F*) fIn->Get(histName.c_str());
						TF1* gauF1 = new TF1("gauF1","gaus",-200,200);
						h1->Fit("gauF1","","e",-200,200);
						h1->Draw();

						std::string path = "/home/jmbenlloch/next/petalo/work/histo/jitter_avg/dt/";
						std::string histo = path + material[mat] + interaction[inter] + std::string("_QE_") + std::string(pdeChar) + std::string("_") + histName + std::string(".png");
						std::cout << histo << std::endl;

						c1->Print(histo.c_str());

						sigmasDT[mat][inter][smear][pde][dt] = h1->GetFunction("gauF1")->GetParameter(2);
						errorsDT[mat][inter][smear][pde][dt] = h1->GetFunction("gauF1")->GetParError(2);
					}
					fIn->Close();
				}
			}
		}
	}
	c1->Close();

	double npesD[10] = {1,2,3,4,5,6,7,8,9,10};
	double dtsD[8] = {10,20,50,100,150,200,250,300};
	EColor colors[5] = {kRed,kBlue,kOrange,kYellow,kCyan};

	for(int mat=0; mat<3;mat++){
		for(int inter=1; inter<2;inter++){
			for(int smear=0; smear<2;smear++){
				std::string smearName = "";
				if(smear==1){
					smearName = "_smear";
				}
				//NPE
				TCanvas *c2 = new TCanvas("c2","multipads",900,700);

				TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
				leg->SetFillColor(0);

				for(int pde=0; pde<5;pde++){
					TGraphErrors *gLxe = new TGraphErrors(10, npesD, sigmasNPE[mat][inter][smear][pde], 0, errorsNPE[mat][inter][smear][pde]);
					gLxe->SetLineColor(colors[pde]);
					gLxe->SetLineWidth(2);

					leg->AddEntry(gLxe,Form("PDE %d%%", pdes[pde]), "lp");

					if(pde==0){
						gLxe->SetTitle("");
						gLxe->GetXaxis().SetTitle("avg PE(#)");
						gLxe->GetXaxis()->SetLimits(0,10);
						gLxe->GetYaxis().SetTitle("CRT (ps)");
						gLxe->SetMinimum(0.);
						gLxe->SetMaximum(100.);
						gLxe->Draw();

					}else{
						gLxe->Draw("same");
					}
					if(pde==4){
						leg->Draw("same");
					}
				}
				std::string path = "/home/jmbenlloch/next/petalo/work/histo/jitter_avg/";
				std::string histo = path + material[mat] + interaction[inter] + std::string("_avg_npe") + smearName + std::string(".png");

				c2->Print(histo.c_str());
				c2->Close();

				//DT
				TCanvas *c2 = new TCanvas("c2","multipads",900,700);

				TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
				leg->SetFillColor(0);

				for(int pde=0; pde<5;pde++){
					TGraphErrors *gLxe = new TGraphErrors(8, dtsD, sigmasDT[mat][inter][smear][pde], 0, errorsDT[mat][inter][smear][pde]);
					gLxe->SetLineColor(colors[pde]);
					gLxe->SetLineWidth(2);

					leg->AddEntry(gLxe,Form("PDE %d%%", pdes[pde]), "lp");

					if(pde==0){
						gLxe->SetTitle("");
						gLxe->GetXaxis().SetTitle("avg PE(#)");
						gLxe->GetXaxis()->SetLimits(0,350);
						gLxe->GetYaxis().SetTitle("CRT (ps)");
						gLxe->SetMinimum(0.);
						gLxe->SetMaximum(100.);
						gLxe->Draw();

					}else{
						gLxe->Draw("same");
					}
					if(pde==4){
						leg->Draw("same");
					}
				}
				std::string path = "/home/jmbenlloch/next/petalo/work/histo/jitter_avg/";
				std::string histo = path + material[mat] + interaction[inter] + std::string("_avg_dt") + smearName + std::string(".png");

				c2->Print(histo.c_str());
				c2->Close();
			}
		}
	}
}
