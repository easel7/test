// A single toymc to prove weighted method always overestimate significance, in ref arXiv:1306.5800v1 [astro-ph.HE] 24 Jun 2013
// Binned / Unbinned Likelihood method is a better way 

int toymc()
{
    double bkg_exp[3] = {10000.0, 100.0, 1.0};
    double sig_exp_on[3] = {500.0, 50.0, 5.0};
    double sig_exp_off[3] = {0.1, 0.1, 0.1};
    double sig_on[3] = {0.};
    double sig_off[3] = {0.};
    double bkg[3] = {0.};
    double weight[3] = {0.05, 0.5, 5.0};
    
    double sign_on;
    double sign_off;
    double modi_sign_on;
    double modi_sign_off;
    double modi_sig_on = 0.;
    double modi_sig_off = 0.; 
    double modi_bkg = 0.;

    int bin = 0;

    TFile *newfile = TFile::Open("result.root", "recreate");
    TTree *tree = new TTree("t1","tree");
    tree->Branch("sign_on",&sign_on,"sign_on/D");
    tree->Branch("sign_off",&sign_off,"sign_off/D");
    tree->Branch("modi_sign_on",&modi_sign_on,"modi_sign_on/D");
    tree->Branch("modi_sign_off",&modi_sign_off,"modi_sign_off/D");
     

    for(int i = 0; i < 10000; i++)
    {
        
        modi_sig_on = 0;
        modi_sig_off = 0;
        modi_bkg = 0; 
        
        for(int j = 0; j < 3; j++)
        {
            sig_on[j]     = gRandom->Poisson(sig_exp_on[j]);
            sig_off[j]    = gRandom->Poisson(sig_exp_off[j]); 
            bkg[j]        = gRandom->Poisson(bkg_exp[j]);
            
            modi_sig_on  += sig_on[j] * weight[j];
            modi_sig_off += sig_off[j] * weight[j];
            modi_bkg     += bkg[j] * weight[j] * weight[j];
        }
        
        sign_on  = (sig_on[0]+sig_on[1]+sig_on[2])   / sqrt(bkg[0]+bkg[1]+bkg[2]);
        sign_off = (sig_off[0]+sig_off[1]+sig_off[2])/ sqrt(bkg[0]+bkg[1]+bkg[2]); 

        modi_sign_on  = modi_sig_on  / sqrt(modi_bkg);
        modi_sign_off = modi_sig_off / sqrt(modi_bkg);
        
        // cout << change << endl;
        tree->Fill();
    }

    newfile->Write();
    newfile->Close();

    return 0;
}