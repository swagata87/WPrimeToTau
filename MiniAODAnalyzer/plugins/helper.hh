// Original Author:  Marcel Materok
//         Created:  Thu, 4 Jul 2016 10:28:57 GMT


#include <vector>
#include "TTree.h"
#include "TString.h"
#include "TH2F.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

// cant set lorentzvetor branch without this
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif


class Helper{
    public:
        Helper(edm::Service<TFileService> fileService);
        virtual void Tree_Creater(std::unordered_map< std::string , float > *m, const char * name);
        virtual void Tree_Creater(std::unordered_map< std::string , std::vector<float> > *m, const char * name);
        virtual void Tree_Filler(const char * name);
        virtual void WriteAll(const char * name);
        virtual void CreateHistoUnchangedName(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle);
        virtual void WriteTree(const char * name);
        virtual void SetFakeBranches(const char * name, const char * branchName, std::vector<float> *vector);
        virtual void SetFakeBranches(const char * name, const char * branchName, std::vector<double> *vector);
        virtual void SetFakeBranches(const char * name, const char * branchName, std::vector<TLorentzVector> *vector);
        virtual void CreateHisto(Int_t n_histos, const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle);
        virtual void CreateHisto(Int_t n_histos, const char* name, const char* particle, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle );
        virtual void CreateHisto(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle);
        virtual void CreateHisto(const char* name, const char* particle, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle);
        //virtual void CreateHisto(boost::basic_format<char> name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle);
        virtual void CreateHisto(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup, TString xtitle, TString ytitle);
        virtual void CreateHisto(Int_t n_histos, const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup, TString xtitle, TString ytitle);
        virtual void CreateHisto(const char* name, Int_t nbinsx, const Double_t * xbins,  Int_t nbinsy, Double_t ylow, Double_t yup, TString xtitle, TString ytitle);
        virtual void CreateHisto(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, const Double_t * ybins, TString xtitle, TString ytitle);
        virtual void CreateHisto(const char* name, Int_t nbinsx, const Double_t * xbins, Int_t nbinsy, const Double_t * ybins, TString xtitle, TString ytitle);


        virtual void Fill(Int_t n_histo, const char * name, double value, double weight);
        virtual void Fill(Int_t n_histo, std::string name, double value, double weight);
        virtual void Fill(const char * name, double value, double weight);
        virtual void Fill(const char * name, double valuex, double valuey, double weight);
        virtual void Fill(Int_t n_histo, const char * name, double valuex, double valuey, double weight);
    private:
        edm::Service<TFileService> fs2;
        TFileDirectory treeDir;
        TFileDirectory fakeDir;
        std::unordered_map<std::string, TTree * > trees; /*!< Map of a string and a TTree histogram, for easy tree handling. */
        std::unordered_map<std::string, TH1D * > histo; /*!< Map of a string and a TH1D histogram, for easy 1D histogram handling. */
        std::unordered_map<std::string, TH2D * > histo2; /*!< Map of a string and a TH2D histogram, for easy 2D histogram handling. */
};

Helper::Helper(edm::Service<TFileService> fileService){
    fs2 = fileService;
    treeDir = fs2->mkdir( "treeDir" );
    fakeDir = fs2->mkdir( "fakeDir" );
}
void Helper::Tree_Creater(std::unordered_map< std::string , float > *m, const char * name) {
    trees[name] = treeDir.make<TTree>(name, name);
    for (std::unordered_map< std::string , float >::iterator it = m->begin(); it != m->end(); it++) {
        trees[name]->Branch(it->first.c_str(), &(it->second), Form("%s/F", it->first.c_str()));
    }
}
void Helper::Tree_Creater(std::unordered_map< std::string , std::vector<float> > *m, const char * name) {
    trees[name] = treeDir.make<TTree>(name, name);
    for (std::unordered_map< std::string , std::vector<float> >::iterator it = m->begin(); it != m->end(); it++) {
        trees[name]->Branch(it->first.c_str(), &(it->second), Form("%s/F", it->first.c_str()));
    }
}
void Helper::Tree_Filler(const char * name) {
    trees[name]->Fill();
}
void Helper::SetFakeBranches(const char * name,const char * branchName, std::vector<float> *vector) {
    trees[name]->Branch(branchName,vector);
}
void Helper::SetFakeBranches(const char * name,const char * branchName, std::vector<double> *vector) {
    trees[name]->Branch(branchName,vector);
}
void Helper::SetFakeBranches(const char * name,const char * branchName, std::vector<TLorentzVector> *vector) {
    trees[name]->Branch(branchName,vector);
}
void Helper::WriteAll(const char * name = "") {
    std::unordered_map<std::string, TH1D * >::iterator it;
    for (std::unordered_map<std::string, TH1D * >::iterator it = histo.begin(); it != histo.end(); ++it) {
        if (strcmp(name, "") != 0 && std::string::npos != it->first.find(name)) {
            it->second -> Write();
        } else if (strcmp(name, "") == 0) {
            it->second -> Write();
        }
    }
}
void Helper::WriteTree(const char * name = "") {
    trees[name]->Write();
}

void Helper::CreateHistoUnchangedName(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle = "") {
        TH1D * tmphist = new TH1D(Form("%s", name), xtitle, nbinsx, xlow, xup);
        tmphist->SetXTitle(xtitle);
        tmphist->Sumw2();
        histo[Form("%s", name)] = tmphist;
    }

void Helper::CreateHisto(Int_t n_histos, const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle = "") {
    std::string _name=name;
    for (int j = 0; j < n_histos; j++) {
        TH1D * tmphist = fakeDir.make<TH1D>(Form("h1_%d_%s", j, _name.c_str()), xtitle, nbinsx, xlow, xup);
        tmphist->SetXTitle(xtitle);
        tmphist->Sumw2();
        histo[Form("h1_%d_%s", j, _name.c_str())] = tmphist;
    }
}


void Helper::CreateHisto(Int_t n_histos, const char* name, const char* particle, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle = "") {
    std::string _name=name;
    for (int i = 0; i < n_histos; i++) {
        TH1D * tmphist = fakeDir.make<TH1D>(Form("h1_%d_%s_%s", i, particle, _name.c_str()), xtitle, nbinsx, xlow, xup);
        tmphist->SetXTitle(xtitle);
        tmphist->Sumw2();
        histo[Form("h1_%d_%s_%s", i, particle, _name.c_str())] = tmphist;
    }
}
void Helper::CreateHisto(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle = "") {
    TH1D * tmphist = fakeDir.make<TH1D>(Form("h1_%s", name), xtitle, nbinsx, xlow, xup);
    tmphist->SetXTitle(xtitle);
    tmphist->Sumw2();
    histo[Form("h1_%s", name)] = tmphist;
}
void Helper::CreateHisto(const char* name, const char* particle, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle = "") {
    TH1D * tmphist = fakeDir.make<TH1D>(Form("h1_%s_%s", particle, name), xtitle, nbinsx, xlow, xup);
    tmphist->SetXTitle(xtitle);
    tmphist->Sumw2();
    histo[Form("h1_%s_%s", particle, name)] = tmphist;
}
//void Helper::CreateHisto(boost::basic_format<char> name, Int_t nbinsx, Double_t xlow, Double_t xup, TString xtitle = "") {
    //CreateHisto(str(name).c_str(), nbinsx, xlow, xup, xtitle);
//}

void Helper::CreateHisto(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup, TString xtitle = "", TString ytitle = "") {
    std::string dummy = Form("h2_%s", name);
    histo2[dummy] = fakeDir.make<TH2D>(Form("h2_%s", name), Form("h2_%s", name), nbinsx, xlow, xup, nbinsy, ylow, yup);
    histo2[dummy] -> Sumw2();
    histo2[dummy] -> GetXaxis() -> SetTitle(xtitle);
    histo2[dummy] -> GetYaxis() -> SetTitle(ytitle);
}
void Helper::CreateHisto(Int_t n_histos, const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup, TString xtitle = "", TString ytitle = "") {
    std::string _name=name;
    for (int i = 0; i < n_histos; i++) {
        TH2D * tmphist = fakeDir.make<TH2D>(Form("h2_%d_%s", i, _name.c_str()), Form("h2_%d_%s", i, _name.c_str()), nbinsx, xlow, xup, nbinsy, ylow, yup);
        tmphist->SetXTitle(xtitle);
        tmphist->SetYTitle(ytitle);
        tmphist->Sumw2();
        histo2[Form("h2_%d_%s", i, _name.c_str())] = tmphist;
    }
}
void Helper::CreateHisto(const char* name, Int_t nbinsx, const Double_t * xbins,  Int_t nbinsy, Double_t ylow, Double_t yup, TString xtitle = "", TString ytitle = "") {
    std::string dummy = Form("h2_%s", name);
    histo2[dummy] = fakeDir.make<TH2D>(Form("h2_%s", name), Form("h2_%s", name), nbinsx, xbins, nbinsy, ylow, yup);
    histo2[dummy] -> Sumw2();
    histo2[dummy] -> GetXaxis() -> SetTitle(xtitle);
    histo2[dummy] -> GetYaxis() -> SetTitle(ytitle);
}
void Helper::CreateHisto(const char* name, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, const Double_t * ybins, TString xtitle = "", TString ytitle = "") {
    std::string dummy = Form("h2_%s", name);
    histo2[dummy] = fakeDir.make<TH2D>(Form("h2_%s", name), Form("h2_%s", name), nbinsx, xlow, xup, nbinsy, ybins);
    histo2[dummy] -> Sumw2();
    histo2[dummy] -> GetXaxis() -> SetTitle(xtitle);
    histo2[dummy] -> GetYaxis() -> SetTitle(ytitle);
}
void Helper::CreateHisto(const char* name, Int_t nbinsx, const Double_t * xbins, Int_t nbinsy, const Double_t * ybins, TString xtitle = "", TString ytitle = "") {
    std::string dummy = Form("h2_%s", name);
    histo2[dummy] = fakeDir.make<TH2D>(Form("h2_%s", name), Form("h2_%s", name), nbinsx, xbins, nbinsy, ybins);
    histo2[dummy] -> Sumw2();
    histo2[dummy] -> GetXaxis() -> SetTitle(xtitle);
    histo2[dummy] -> GetYaxis() -> SetTitle(ytitle);
}
void Helper::Fill(Int_t n_histo, const char * name, double value, double weight) {
    std::unordered_map<std::string, TH1D * >::iterator it = histo.find(Form("h1_%d_%s", n_histo, name));
    if (it != histo.end()) {
        it->second->Fill(value, weight);
    } else {
        std::cerr << "(Fill) No hist: " << Form("h1_%d_%s", n_histo, name) << " in map " << n_histo <<" size is : "<<  histo.size()<<"   "<<histo.max_size()
<< std::endl;
    }
}
void Helper::Fill(Int_t n_histo, std::string name, double value, double weight) {
    Fill(n_histo, name.c_str(), value, weight);
}
void Helper::Fill(const char * name, double value, double weight) {
    std::unordered_map<std::string, TH1D * >::iterator it;
    if (strcmp(name, "h_counters") == 0) {
            it = histo.find(Form("%s", name));
    } else {
            it = histo.find(Form("h1_%s", name));
    }

    if (it != histo.end()) {
        it->second->Fill(value, weight);
    } else {
        std::cerr << "(Fill) No hist: " << Form("h1_%s", name) << " in map " << std::endl;
    }
}
void Helper::Fill(const char * name, double valuex, double valuey, double weight) {
    auto it =histo2.find(Form("h2_%s", name));
    if(it != histo2.end()){
        it->second->Fill(valuex, valuey, weight);
    }else{
        std::cerr << "(Fill) No h2: " << name << " in map " << std::endl;
    }
}
void Helper::Fill(Int_t n_histo, const char * name, double valuex, double valuey, double weight) {
    std::unordered_map<std::string, TH2D * >::iterator it = histo2.find(Form("h2_%d_%s", n_histo, name));
    if (it != histo2.end()) {
        it->second->Fill(valuex, valuey, weight);
    } else {
        std::cerr << "(Fill) No hist: " << Form("h2_%d_%s", n_histo, name) << " in map " << n_histo << std::endl;
    }
}