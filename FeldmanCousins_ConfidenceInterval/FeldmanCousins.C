#include "TFeldmanCousins.cxx"
#include "TModiFeldmanCousins.cxx"

using namespace std;

void FeldmanCousins()
{
    // if (!gROOT->GetClass("TFeldmanCousins"))
    //     R__LOAD_LIBRARY(libPhysics);
    // if (!gROOT->GetClass("TModiFeldmanCousins"))
    //     R__LOAD_LIBRARY(libPhysics);

    TFeldmanCousins f;
    TModiFeldmanCousins m;
    fstream file;
    // calculate either the upper or lower limit for 10 observed
    // events with an estimated background of 3.  The calculation of
    // either upper or lower limit will return that limit and fill
    // data members with both the upper and lower limit for you.
    Double_t Nobserved = 20;
    Double_t Nbackground = 0.001;
    Double_t ul;
    Double_t ll;
    Double_t mul;
    Double_t mll;
    // f.SetCL(0.95) // Set Confidence Interval 95%
    
    // 1.write in txt
    file.open("data_b.txt", ios::out); // open txt file, write into RAM from file mode
    
    for(int n = 0 ; n <= Nobserved; n++)
    {
        ul = f.CalculateUpperLimit(n, Nbackground);
        ll = f.GetLowerLimit();
		mul = m.CalculateUpperLimit(n, Nbackground);
		mll = m.GetLowerLimit();
        file << n << " " << ul << " " << ll << " " << mul << " " << mll << endl;
    }

    file.close();


    // 2.fill into a tree
    // TFile *output = new TFile("CI_data.root","recreate");
    // TTree *tree = new TTree("tree","tree");
    
    // tree->Branch("ul", &ul, "ul/D");// varible name ; quote ; data_type e.g. D - double, F - Float, I - int
    // tree->Branch("ll", &ll, "ll/D");
    
    // for(int i = 0; i < Nobserved; i++)
    // {
    //     ul = f.CalculateUpperLimit(i, Nbackground);
    //     ll = f.GetLowerLimit();

    //     tree->Fill();
    // }
    // output->Write();
    // output->Close();

    //double_t x[20], y[20], n[20], mx[20], my[20];
    //TCanvas *c1 = new TCanvas();
    //for (Int_t i=0;i<Nobserved;i++) {
    //  x[i] = f.CalculateUpperLimit(i, Nbackground);
    //  y[i] = f.GetLowerLimit();
    //  mx[i] = m.CalculateUpperLimit(i, Nbackground);
    //  my[i] = m.GetLowerLimit();
    //  n[i] = i+0.5;
    //  cout << n[i] << " "<< x[i] << " "<< y[i] << endl;
    //}
    // c1 = new TCanvas();
    // c1->SetGrid();
    
    // TMultiGraph *mg = new TMultiGraph();
    //TGraph *gr1 = new TGraph(Nobserved,n,x);
    //TGraph *gr2 = new TGraph(Nobserved,n,y);
    //TGraph *gr3 = new TGraph(Nobserved,n,mx);
    //TGraph *gr4 = new TGraph(Nobserved,n,my);
    //gr1->SetFillColor(40);
    //gr1->Draw("AB");
    //gr2->SetFillColor(30);
    //gr2->Draw("SAMEB");
    //gr3->SetFillColor(20);
    //gr3->Draw("SAMEB");
    //gr2->SetFillColor(10);
    //gr4->Draw("SAMEB");
    // mg->Add(gr1);
    // mg->Add(gr2);
    // mg->Add(gr3);
    // mg->Add(gr4);

    // mg->Draw("AB");

   
    // 3.output in terminal
    // cout << "For " <<  Nobserved << " data observed with and estimated background"<<endl;
    // cout << "of " << Nbackground << " candidates, the Feldman-Cousins method of "<<endl;
    // cout << "calculating confidence limits gives:"<<endl;
    // cout << "\tUpper Limit = " <<  ul << endl;
    // cout << "\tLower Limit = " <<  ll << endl;
    // cout << "at the 90% CL"<< endl;
}
