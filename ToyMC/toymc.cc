// A single toymc to prove weighted method always overestimate significance, in ref arXiv:1306.5800v1 [astro-ph.HE] 24 Jun 2013
// Binned / Unbinned Likelihood method is a better way 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int toymc()
{
    double bkg_exp[3] = {10000.0, 100.0, 1.0};
    double sig_exp[3] = {0.1, 0.1, 0.1};
    double sig[3] = {0.};
    double bkg[3] = {0.};
    double weight[3] = {0.05, 0.5, 5.0};
    
    double sign = 0.;
    double modi_sig = 0.;
    double modi_bkg = 0.;

    int bin = 0;
    double change;
    double modi_sign;
    
    
    TFile *newfile = TFile::Open("toymc_bkg.root", "recreate");
    TTree *tree = new TTree("t1","tree");
    tree->Branch("sign_change",&change,"change/D"); 

    for(int i = 0; i < 10000; i++)
    {
        change = 0;
        modi_sign = 0;
        modi_sig = 0;
        modi_bkg = 0; 
        for(int j = 0; j < 3; j++)
        {
            sig[j] = gRandom->Poisson(sig_exp[j]);
            bkg[j] = gRandom->Poisson(bkg_exp[j]);
            modi_sig += sig[j] * weight[j];
            modi_bkg += bkg[j] * weight[j] * weight[j];
        }
        sign = (sig[0]+sig[1]+sig[2])/ sqrt(bkg[0]+bkg[1]+bkg[2]);
        modi_sign = modi_sig / sqrt(modi_bkg);
        change = modi_sign - sign;
        // cout << change << endl;
        tree->Fill();
    }

    newfile->Write();
    newfile->Close();

    return 0;
}