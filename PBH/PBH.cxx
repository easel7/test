#include <iostream>
using namespace std;
#include <iomanip>
using std::setw; //使用了 setw() 函数来格式化输出

double dNdE(double Energy, double Temp)
{
   double u;
   if (Energy < Temp)
   {
       u = 9e35 * TMath::Power(1/Temp,3/2) * TMath::Power(1/Energy,3/2); // GeV^-1
   } 
   else
   {
       u = 9e35 * TMath::Power(1/Energy,3.0); // GeV^-1
   }

   return u;
}

double Temp(double life)
{
    double u;
    u = 7.8e3*TMath::Power(1/life,1/3); // GeV
    return u;
}


{
    TCanvas* c1 = new TCanvas("c1","Intrinsic spectrum for different duration burst",200,10,500,300);
    c1->SetLogy(1);
    c1->SetLogx(1);

    TMultiGraph* mg = new TMultiGraph();

    Int_t n = 100;
    Double_t life1 = 0.2; // second
    Double_t life2 = 1.0;
    Double_t life3 = 10.0;
    Double_t Energy[100];
    Double_t dN0[100];
    Double_t dN1[100];
    Double_t dN2[100];
    
    ofstream out("PBH.txt");

    for (Int_t i = 0; i<100; i++)
    {
        Energy[i] = TMath::Power(10,0.06*i); // GeV
        dN0[i] = dNdE(Energy[i], life1); // GeV^-1
        dN1[i] = dNdE(Energy[i], life2); // GeV^-1
        dN2[i] = dNdE(Energy[i], life3); // GeV^-1
    }

    for (Int_t i = 0; i<100; i++)
    {
        out << Energy[i] << setw( 10 ) << dN0[i] << setw( 10 ) << dN1[i] << setw( 10 ) << dN2[i] << endl;
    }
    
    TGraph* gr1 = new TGraph(n,Energy,dN0); gr1->SetLineColor(kBlue);
    TGraph* gr2 = new TGraph(n,Energy,dN1); gr2->SetLineColor(kRed);
    TGraph* gr3 = new TGraph(n,Energy,dN2); gr3->SetLineColor(kGreen);

    mg->Add(gr1);
    mg->Add(gr2);
    mg->Add(gr3);
    mg->Draw("LP");
    gPad->Update();
    
    c1->SaveAs(PBH.png);
    return 0;
}